#ifndef WINDOW_H
#define WINDOW_H

#ifdef WIN32
#include "e2d_engine.h"
#include "base/e2d_singleton.h"

namespace Easy2D
{
    class TimeManager;
    class TextureManager;

    class Window final : public Singleton<Window>
    {
    public:
        friend Singleton<Window>;

        ~Window();

        void initialize(HINSTANCE instance, uint32 width = 800, uint32 height = 600, bool useConsole = false);

        const HDC& getHDC() const;
        const HWND& getHandle() const;

        bool isFullScreen() const;
        bool isInitialized() const;
        bool isFixResolution() const;

        void setFullScreen(HWND hWnd, bool fullscreen);

        void setResolution(uint32 width, uint32 height, bool reset = true);

        bool onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        Window() {}
        void mainLoop();

        void PrintGlVersionInfo();

        void clientResize(uint32 & width, uint32 & height);
        void getWindowDiffSize(uint32 & difX, uint32 & difY);

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
        GLFWwindow* window = nullptr;
        SPtr<E2dEngine> mE2dEngine = nullptr;

    };
}

#endif

#endif
