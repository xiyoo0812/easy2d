#ifndef WINDOW_H
#define WINDOW_H

#ifdef WIN32
#include "e2d_config.h"
#include "base/e2d_game.h"
#include "base/e2d_singleton.h"

namespace Easy2D
{
	class TimeManager;
	class TextureManager;

	class Window final : public Singleton<Window>
	{
	public:
		~Window();

		void initialize(HINSTANCE instance, E2DGame* pE2DGame, bool useConsole = false);

		const HDC& GetHDC() const;
		const HWND& GetHandle() const;

		bool isFullScreen() const;
		bool isInitialized() const;
		bool isFixResolution() const;

		void setFullScreen(HWND hWnd, bool fullscreen);

		void setResolution(int32 width, int32 height, bool reset = true);
		
		bool onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		Window() {}
		void mainLoop();

		void clientResize(int32 & width, int32 & height);
		void getWindowDiffSize(int32 & difX, int32 & difY);

		struct WindowState
        {
            RECT winRect;
			BOOL maximized;
            long style, exStyle;
		};

		WindowState mWindowState;

		bool mFullScreen = false;
		bool mInitialized = false;
		bool mFixResolution = false;

		HDC mHDC = nullptr;
		HWND mHandle = nullptr;
		HGLRC mOGLContext = nullptr;
		E2DGame* mE2dGame = nullptr;

	};
}

#endif

#endif
