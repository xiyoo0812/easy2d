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
        bool isInitialized() const;

#ifndef GLFW
        void setResolution(uint32 width, uint32 height, bool reset = true);
        bool onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif
    private:
        Window() {}
        void mainLoop();
        void printGlVersionInfo();

        struct WindowState
        {
            RECT winRect;
            BOOL maximized;
            long style, exStyle;
        };

        WindowState mWindowState;

        bool mInitialized = false;
        SPtr<E2dEngine> mE2dEngine = nullptr;

#ifdef GLFW
        GLFWwindow* window = nullptr;
#else
        void clientResize(uint32& width, uint32& height);
        void getWindowDiffSize(uint32& difX, uint32& difY);
        HDC mHDC = nullptr;
        HWND mHandle = nullptr;
        HGLRC mOGLContext = nullptr;
#endif
    };
}

#endif

#endif
