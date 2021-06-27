#include "e2d_graphics_mgr.h"
#include "e2d_render_batch.h"
#include "object/e2d_camera.h"
#include "object/e2d_scene_mgr.h"
#include "object/component/e2d_camera_component.h"

using namespace Easy2D;

GraphicsManager::GraphicsManager() : Singleton<GraphicsManager>()
{
}

GraphicsManager::~GraphicsManager()
{
}

void GraphicsManager::calculateViewPort()
{
    if (mbInitialize)
    {
        float32 width = mDesignResolution.x / mScreenResolution.x;
        float32 height = mDesignResolution.y / mScreenResolution.y;

        float32 aspectRatio(0);
        if (width > height)
        {
            height = mScreenResolution.y;
            aspectRatio = (mDesignResolution.x / mDesignResolution.y);
            width = height * aspectRatio;
            mHorizontalViewportOffset = static_cast<int32>((mScreenResolution.x - width) / 2);
        }
        else
        {
            width = mScreenResolution.x;
            aspectRatio = (mDesignResolution.y / mDesignResolution.x);
            height = width * aspectRatio;
            mVerticalViewportOffset = static_cast<int32>((mScreenResolution.y - height) / 2);
        }
        mViewportResolution.x = width;
        mViewportResolution.y = height;
        float32 scale = mViewportResolution.x / mDesignResolution.x;
        mViewport = Vec4(mHorizontalViewportOffset, mVerticalViewportOffset, width, height);
        glViewport(mHorizontalViewportOffset, mVerticalViewportOffset, static_cast<int32>(width), static_cast<int32>(height));
        mScaleMatrix = Easy2D::scale(scale, scale, 0);
    }
}


#ifdef WIN32
void GraphicsManager::initialize(int32 screenWidth, int32 screenHeight)
{
    setScreenResolution(screenWidth, screenHeight);
    setDesignResolution(screenWidth, screenHeight);

    mbInitialize = true;
    calculateViewPort();
}
#endif
#ifdef ANDROID
void GraphicsManager::initialize(SPtr<android_app> pApplication)
{
    LOG_INFO << _T("Graphics Manager : Initializing OpenGL");
    EGLint lFormat, lNumConfigs, lErrorResult;
    EGLConfig lConfig;
    // Defines display requirements. 16bits mode here.
    const EGLint lAttributes[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };
    mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mDisplay == EGL_NO_DISPLAY)
    {
        LOG_ERROR << _T("Graphics Manager : No display found");
        return;
    }
    if (!eglInitialize(mDisplay, NULL, NULL))
    {
        LOG_ERROR << _T("Graphics Manager : Could not initialize display");
        return;
    }
    if (!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1, &lNumConfigs) || (lNumConfigs <= 0))
    {
        LOG_ERROR << _T("Graphics Manager : No display config");
        return;
    }
    if (!eglGetConfigAttrib(mDisplay, lConfig, EGL_NATIVE_VISUAL_ID, &lFormat))
    {
        LOG_ERROR << _T("Graphics Manager : No config attributes");
        return;
    }
    ANativeWindow_setBuffersGeometry(pApplication->window, 0, 0, lFormat);
    mSurface = eglCreateWindowSurface(mDisplay, lConfig, pApplication->window, NULL);
    if (mSurface == EGL_NO_SURFACE)
    {
        LOG_ERROR << _T("Graphics Manager : Could not create surface");
        return;
    }
    EGLint contextAttrs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, contextAttrs);
    if (mContext == EGL_NO_CONTEXT)
    {
        LOG_ERROR << _T("Graphics Manager : Could not create context");
        return;
    }
    EGLint sX(0), sY(0);
    if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
        || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &sX)
        || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &sY)
        || (sX <= 0) || (sY <= 0))
    {
        LOG_ERROR << _T("Graphics Manager : Could not activate display");
        return;
    }
    //[COMMENT] This might be redundant!
    mViewportResolution.x = sX;
    mViewportResolution.y = sY;
    mDesignResolution = mViewportResolution;
    glViewport(0, 0, mViewportResolution.x, mViewportResolution.y);
    initializeOpenGLStates();
    LOG_INFO << _T("Graphics Manager : Initialized");
}

void GraphicsManager::destroy()
{
    // Destroys OpenGL context.
    if (mDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (mContext != EGL_NO_CONTEXT)
        {
            eglDestroyContext(mDisplay, mContext);
            mContext = EGL_NO_CONTEXT;
        }
        if (mSurface != EGL_NO_SURFACE)
        {
            eglDestroySurface(mDisplay, mSurface);
            mSurface = EGL_NO_SURFACE;
        }
        eglTerminate(mDisplay);
        mDisplay = EGL_NO_DISPLAY;
        LOG_INFO << _T("Graphics Manager : Destroyed");
    }
}
#endif

void GraphicsManager::update()
{
    auto activeScene = SceneManager::instance()->getActiveScene();
    if (activeScene)
    {
        auto camera = activeScene->getActiveCamera();
        if (camera)
        {
            auto component = camera->getComponent<CameraComponent>(CameraComponent::GUID);
            if (component)
            {
                const Mat4& view = component->getView();
                const Mat4& projection = component->getProjection();
                const Mat4& viewInverse = component->getViewInverse();
                mViewMatrix = view;
                mProjectionMatrix = projection;
                mViewInverseMatrix = viewInverse;
                mViewProjectionMatrix = projection * viewInverse;
            }
        }
    }
}

int32 GraphicsManager::getWindowWidth() const
{
    return int32(mDesignResolution.x);
}

int32 GraphicsManager::getWindowHeight() const
{
    return int32(mDesignResolution.y);
}

int32 GraphicsManager::getViewportWidth() const
{
    return int32(mViewportResolution.x);
}

int32 GraphicsManager::getViewportHeight() const
{
    return int32(mViewportResolution.y);
}

int32 GraphicsManager::getScreenWidth() const
{
    return mScreenResolution.x;
}

int32 GraphicsManager::getScreenHeight() const
{
    return mScreenResolution.y;
}

const Vec4& GraphicsManager::getViewport() const
{
    return mViewport;
}

const Mat4& GraphicsManager::getScaleMatrix() const
{
    return mScaleMatrix;
}

const Mat4& GraphicsManager::getViewInverseProjectionMatrix() const
{
    return mViewProjectionMatrix;
}

const Mat4& GraphicsManager::getProjectionMatrix() const
{
    return mProjectionMatrix;
}

const Mat4& GraphicsManager::getViewMatrix() const
{
    return mViewMatrix;
}

const Mat4& GraphicsManager::getViewInverseMatrix() const
{
    return mViewInverseMatrix;
}

float32 GraphicsManager::getDesignAspectRatio() const
{
    return mDesignResolution.x / mDesignResolution.y;
}

const Vec2& GraphicsManager::getDesignResolution() const
{
    return mDesignResolution;
}

const Vec2& GraphicsManager::getViewportResolution() const
{
    return mViewportResolution;
}

const Vec2& GraphicsManager::getScreenResolution() const
{
    return mScreenResolution;
}

float32 GraphicsManager::getViewportAspectRatio() const
{
    return mViewportResolution.x / mViewportResolution.y;
}

int32 GraphicsManager::getHorizontalViewportOffset() const
{
    return mHorizontalViewportOffset;
}

int32 GraphicsManager::getVerticalViewportOffset() const
{
    return mVerticalViewportOffset;
}

void GraphicsManager::setScreenResolution(int32 width, int32 height)
{
    mScreenResolution.x = float32(width);
    mScreenResolution.y = float32(height);
    calculateViewPort();
}

void GraphicsManager::setDesignResolution(int32 width, int32 height)
{
    mDesignResolution.x = float32(width);
    mDesignResolution.y = float32(height);
    calculateViewPort();
}

