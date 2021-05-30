#ifndef WINDOW_H
#define WINDOW_H

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
        GLFWwindow* window = nullptr;
    };
}

#endif
