// Demo.h : ����Ӧ�ó������ڵ㡣
#include "windows/e2d_window.h"

using namespace Easy2D;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    LPCTSTR WinTile = "Blaze Demo";

    CoInitialize(NULL);
    Window* pWindow = Window::getInstance();
    pWindow->initialize(hInstance);
    return 0;
}