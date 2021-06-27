#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "e2d_config.h"

namespace Easy2D
{
    class GraphicsManager final : public Singleton<GraphicsManager>
    {
    public:
        friend Singleton<GraphicsManager>;

#ifdef WIN32
        void initialize(int32 screenWidth, int32 screenHeight);
#endif
#ifdef ANDROID
        void initialize(SPtr<android_app> pApplication);
        void destroy();
#endif

        void update();

        int32 getWindowWidth() const;
        int32 getWindowHeight() const;

        int32 getViewportWidth() const;
        int32 getViewportHeight() const;

        int32 getScreenWidth() const;
        int32 getScreenHeight() const;

        const Vec4& getViewport() const;
        const Mat4& getScaleMatrix() const;
        const Mat4& getViewMatrix() const;
        const Mat4& getProjectionMatrix() const;
        const Mat4& getViewInverseMatrix() const;
        const Mat4& getViewInverseProjectionMatrix() const;

        const Vec2& getDesignResolution() const;
        const Vec2& getViewportResolution() const;
        const Vec2& getScreenResolution() const;

        float32 getDesignAspectRatio() const;
        float32 getViewportAspectRatio() const;

        int32 getHorizontalViewportOffset() const;
        int32 getVerticalViewportOffset() const;

        void setDesignResolution(int32 width, int32 height);
        void setScreenResolution(int32 width, int32 height);

    private:
        GraphicsManager();
        ~GraphicsManager();

        void calculateViewPort();

        Vec4 mViewport = {};
        Mat4 mViewMatrix = {};
        Mat4 mScaleMatrix = {};
        Mat4 mProjectionMatrix = {};
        Mat4 mViewInverseMatrix = {};
        Mat4 mViewProjectionMatrix = {};
        Vec2 mDesignResolution = {}, mViewportResolution = {}, mScreenResolution = {};
        int32 mHorizontalViewportOffset = 0, mVerticalViewportOffset = 0;
        bool mbInitialize = false;

#ifdef ANDROID
        EGLDisplay mDisplay = {};
        EGLSurface mSurface = {};
        EGLContext mContext = {};
#endif
    };
}

#endif
