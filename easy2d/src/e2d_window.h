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

        ~Window(){}

        void initialize(HINSTANCE instance, uint32 width = 800, uint32 height = 600, bool useConsole = false);

    private:
        Window() {}
        void mainLoop();
        void printGlVersionInfo();

        GLFWwindow* window = nullptr;
        SPtr<E2dEngine> mE2dEngine = nullptr;
    };
}

#endif
