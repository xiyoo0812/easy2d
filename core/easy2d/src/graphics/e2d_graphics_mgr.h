#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "e2d_config.h"

namespace Easy2D
{
	class GraphicsManager final : public Singleton<GraphicsManager>
	{
	public:
		friend Singleton<GraphicsManager>;

#ifdef _WIN32
		void initialize(const android_app* pApplication);
		void destroy();
#else
		void initialize(int32 screenWidth, int32 screenHeight);
#endif

		void startDraw();
		void stopDraw();
		void update();

		int32 getWindowWidth() const;
		int32 getWindowHeight() const;

		int32 getViewportWidth() const;
		int32 getViewportHeight() const;

		int32 getScreenWidth() const;
		int32 getScreenHeight() const;

		const Mat4& getViewInverseProjectionMatrix() const;
		const Mat4& getViewMatrix() const;
		const Mat4& getViewInverseMatrix() const;
		const Mat4& getProjectionMatrix() const;

		float32 getWindowAspectRatio() const;

		const Vec2& getWindowResolution() const;
		const Vec2& getViewportResolution() const;
		const Vec2& getScreenResolution() const;

		float32 getViewportAspectRatio() const;

		int32 getHorizontalViewportOffset() const;
		int32 getVerticalViewportOffset() const;

		void setWindowDimensions(int32 width, int32 height);
		void setWindowChanged(bool changed);
		bool getWindowChanged() const;
		void calculateViewPort();

		void setVSync(bool VSync);
		bool getVSync() const;

	private:
		GraphicsManager();
		~GraphicsManager();

		void initializeOpenGLStates();
#ifdef WIN32
		bool wglExtensionSupported(const schar* extension_name);
		bool initializeOpenGLFunctors();

		PFNWGLSWAPINTERVALEXTPROC mWglSwapIntervalEXT = nullptr;
		PFNWGLGETSWAPINTERVALEXTPROC mWglGetSwapIntervalEXT = nullptr;
#endif

		Mat4 mViewMatrix = {};
		Mat4 mProjectionMatrix = {};
		Mat4 mViewInverseMatrix = {};
		Mat4 mViewProjectionMatrix = {};
		Vec2i mScreenResolution = {}, mViewportResolution = {};
		int32 mHorizontalViewportOffset = 0, mVerticalViewportOffset = 0;
		bool mbWindowChanged = false;

#ifdef ANDROID
		EGLDisplay mDisplay = {};
		EGLSurface mSurface = {};
		EGLContext mContext = {};
#endif
	};
}

#endif
