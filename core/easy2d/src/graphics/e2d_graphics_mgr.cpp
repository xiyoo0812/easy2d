#include "e2d_graphics_mgr.h"
#include "e2d_sprite_batch.h"
#include "e2d_scale_system.h"
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
    Vec2 screenRes = getWindowResolution();
    Vec2 workingRes = ScaleSystem::getInstance()->getWorkingResolution();
    float32 width = screenRes.x / workingRes.x;
    float32 height = screenRes.y / workingRes.y;

    float32 aspectRatio(0);
    if (width > height)
    {
        height = screenRes.y;
        aspectRatio = (workingRes.x / workingRes.y);
        width = height * aspectRatio;
        mHorizontalViewportOffset = static_cast<int32>((screenRes.x - width) / 2);
    }
    else
    {
        width = screenRes.x;
        aspectRatio = (workingRes.y / workingRes.x);
        height = width * aspectRatio;
        mVerticalViewportOffset = static_cast<int32>((screenRes.y - height) / 2);
    }
    glViewport(mHorizontalViewportOffset, mVerticalViewportOffset, static_cast<int32>(width), static_cast<int32>(height));
    mViewportResolution.x = width;
    mViewportResolution.y = height;
    ScaleSystem::getInstance()->calculateScale();
}

void GraphicsManager::setVSync(bool vSync)
{
#ifdef WIN32
    //Enables or disables VSync.
    //0 = No Sync , 1+ = VSync
    //Default value is 1.
    if (!vSync)
    {
        mWglSwapIntervalEXT(0);
    }
    else
    {
        mWglSwapIntervalEXT(1);
    }
#endif
}

bool GraphicsManager::getVSync() const
{
#ifdef WIN32
    return !(mWglGetSwapIntervalEXT() == 0);
#else
    return true;
#endif
}

#ifdef WIN32
void GraphicsManager::initialize(int32 screenWidth, int32 screenHeight)
{
    mScreenResolution.x = float32(screenWidth);
    mScreenResolution.y = float32(screenHeight);
    glewInit();

    LOG_INFO << _T("Graphics Manager : Initializing OpenGL Functors");
    if (!initializeOpenGLFunctors())
    {
        LOG_ERROR << _T("Graphics Manager : Graphics card doesn't support VSync option!!");
    }
    //Initializes base GL state.
    //DEPTH_TEST is default disabled
    initializeOpenGLStates();
}
#else
void GraphicsManager::initialize(const android_app* pApplication)
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
    mScreenResolution = mViewportResolution;
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

void GraphicsManager::initializeOpenGLStates()
{
    //glDisable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void GraphicsManager::startDraw()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void GraphicsManager::stopDraw()
{
#ifdef ANDROID
    if (eglSwapBuffers(mDisplay, mSurface) != EGL_TRUE)
    {
        return;
    }
#endif
}

void GraphicsManager::update()
{
    auto activeScene = SceneManager::getInstance()->getActiveScene();
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
    return int32(mScreenResolution.x);
}

int32 GraphicsManager::getWindowHeight() const
{
    return int32(mScreenResolution.y);
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
    return int32(ScaleSystem::getInstance()->getWorkingResolution().x);
}

int32 GraphicsManager::getScreenHeight() const
{
    return int32(ScaleSystem::getInstance()->getWorkingResolution().y);
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

float32 GraphicsManager::getWindowAspectRatio() const
{
    return mScreenResolution.x / mScreenResolution.y;
}

const Vec2& GraphicsManager::getWindowResolution() const
{
    return mScreenResolution;
}

const Vec2& GraphicsManager::getViewportResolution() const
{
    return mViewportResolution;
}

const Vec2& GraphicsManager::getScreenResolution() const
{
    return ScaleSystem::getInstance()->getWorkingResolution();
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

void GraphicsManager::setWindowDimensions(int32 width, int32 height)
{
    mScreenResolution.x = float32(width);
    mScreenResolution.y = float32(height);
    calculateViewPort();
}

void GraphicsManager::setWindowChanged(bool changed)
{
    mbWindowChanged = changed;
    if (changed)
    {
        calculateViewPort();
    }
}

bool GraphicsManager::getWindowChanged() const
{
    return mbWindowChanged;
}

#ifdef WIN32
bool GraphicsManager::wglExtensionSupported(const char* extension_name)
{
    // this is the pointer to the function which returns the pointer to string with the list of all wgl extensions
    PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;
    // determine pointer to wglGetExtensionsStringEXT function
    _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");
    if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL)
    {
        // string was not found
        return false;
    }
    // extension is supported
    return true;
}

bool GraphicsManager::initializeOpenGLFunctors()
{
    if (wglExtensionSupported("WGL_EXT_swap_control"))
    {
        // Extension is supported, init pointers.
        mWglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        // this is another function from WGL_EXT_swap_control extension
        mWglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
        // VSync
        setVSync(true);
        return true;
    }
    return false;
}
#endif
