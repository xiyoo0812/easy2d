// Demo.h : 定义应用程序的入口点。
#include "e2d_window.h"

using namespace Easy2D;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(NULL);
    Window* pWindow = Window::instance();
    pWindow->initialize(hInstance);
    return 0;
}
