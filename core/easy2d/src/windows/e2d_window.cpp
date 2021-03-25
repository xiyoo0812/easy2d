#include "e2d_window.h"

#ifdef WIN32
#include <Shlobj.h>

/* Easy2D */
using namespace Easy2D;

#define IDI_STARGAMEICON 201
#define WNDCLASSNAME "E2DWindow"
#define KEYDOWN(vkCode) ((GetAsyncKeyState(vkCode) & 0x8000) ? 1 : 0)

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Window* pWindow = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (pWindow && pWindow->onMessage(hWnd, message, wParam, lParam))
    {
        return 1;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::initialize(HINSTANCE instance, E2DGame* pE2DGame, bool useConsole /* = false */)
{
    if (!mInitialized)
    {
        mE2dGame = pE2DGame;
        log_service::default_instance()->start("./logs", "E2D_LOG");

        WNDCLASSEX wndClass;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hIconSm = NULL;
        wndClass.lpszMenuName = NULL;
        wndClass.hInstance = instance;
        wndClass.lpfnWndProc = wndProc;
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.lpszClassName = WNDCLASSNAME;
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wndClass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STARGAMEICON));
        if (!RegisterClassEx(&wndClass))
        {
            LOG_FATAL << _T("Couldn't register the Windows Class!");
            return;
        }

        int position_width = 800, position_height = 600;
        mHandle = CreateWindow(WNDCLASSNAME, "E2DGAME", WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
            GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4,
            position_width, position_height, NULL, NULL, instance, NULL);

        if (mHandle == NULL)
        {
            LOG_FATAL << _T("Couldn't create the window.");
            return;
        }
        SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)this);
        setResolution(position_width, position_height, false);
        ShowWindow(mHandle, SW_SHOWNORMAL);
        UpdateWindow(mHandle);

        PIXELFORMATDESCRIPTOR pixelFormatDesc = {
            sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,32,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 24, 0, 0,PFD_MAIN_PLANE,0,0, 0, 0
        };

        mHDC = GetDC(mHandle); // Gets the display context
        if (mHDC == NULL)
        {
            LOG_FATAL << _T("Couldn't create the Display Context!");
            return;
        }
        // Chooses the pixel format
        int32 pixelFormat = ChoosePixelFormat(mHDC, &pixelFormatDesc);
        if (pixelFormat == 0)
        {
            LOG_FATAL << _T("Invalid pixel format!");
            return;
        }
        // Sets the pixel format
        if (SetPixelFormat(mHDC, pixelFormat, &pixelFormatDesc) == 0)
        {
            LOG_FATAL << _T("Couldn't set the pixel format!");
            return;
        }
        // Creates the rendering context
        HGLRC hglrc = wglCreateContext(mHDC);
        if (hglrc == NULL)
        {
            LOG_FATAL << _T("Couldn't create the rendering context!");
            return;
        }
        // Attaches the rendering context
        if (wglMakeCurrent(mHDC, hglrc) == 0)
        {
            LOG_FATAL << _T("Action couldn't be completed!");
            return;
        }
        //ShowCursor(!hide_cursor);
        mE2dGame->load(position_width, position_height);

        POINT pt;
        pt.x = position_width / 2;
        pt.y = position_height / 2;
        ClientToScreen(mHandle, &pt);
        SetCursorPos(pt.x, pt.y);
        mInitialized = true;
        mainLoop();
        mE2dGame->stop();
        delete this;
    }
}

void Window::mainLoop()
{
    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            mE2dGame->update();
            mE2dGame->draw();
            SwapBuffers(Window::mHDC); // Swaps display buffers
        }
    }
}

bool Window::isInitialized() const
{
    return mInitialized;
}

bool Window::isFullScreen() const
{
    return mFullScreen;
}

bool Window::isFixResolution() const
{
    return mFixResolution;
}

void Window::setFullScreen(HWND hWnd, bool fullscreen)
{
    if (!mFullScreen)
    {
        mWindowState.maximized = IsZoomed(hWnd);
        if (mWindowState.maximized)
        {
            // window can't be maximized in fullscreen modus
            SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
        }
        mWindowState.style = GetWindowLong(hWnd, GWL_STYLE);
        mWindowState.exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
        GetWindowRect(hWnd, &mWindowState.winRect);
    }
    auto hdc = GetDC(hWnd);
    auto& winRect = mWindowState.winRect;
    mFullScreen = fullscreen;
    if (mFullScreen)
    {
        DEVMODE fullscreenSettings = DEVMODE();
        int32 screenWidth = GetDeviceCaps(hdc, HORZRES);
        int32 screenHeight = GetDeviceCaps(hdc, VERTRES);
        if (mFixResolution)
        {
            screenWidth = winRect.right - winRect.left;
            screenHeight = winRect.bottom - winRect.top;
        }
        EnumDisplaySettings(NULL, 0, &fullscreenSettings);
        fullscreenSettings.dmPelsWidth = screenWidth;
        fullscreenSettings.dmPelsHeight = screenHeight;
        fullscreenSettings.dmBitsPerPel = GetDeviceCaps(hdc, BITSPIXEL);
        fullscreenSettings.dmDisplayFrequency = GetDeviceCaps(hdc, VREFRESH);
        fullscreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
        SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
        SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);
        ChangeDisplaySettings(&fullscreenSettings, CDS_FULLSCREEN);
        ShowWindow(hWnd, SW_MAXIMIZE);
    }
    else
    {
        SetWindowLongPtr(hWnd, GWL_EXSTYLE, mWindowState.exStyle);
        SetWindowLongPtr(hWnd, GWL_STYLE, mWindowState.style);
        ChangeDisplaySettings(NULL, CDS_RESET);
        SetWindowPos(hWnd, HWND_NOTOPMOST, winRect.left, winRect.top, winRect.right - winRect.left, winRect.bottom - winRect.top, SWP_SHOWWINDOW);
        ShowWindow(hWnd, SW_RESTORE);
        if (mWindowState.maximized)
        {
            SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
        }
    }
}

void Window::setResolution(int32 width, int32 height, bool reset)
{
    //	GraphicsManager::GetInstance()->SetWindowDimensions(width, height);
    clientResize(width, height);
    mWindowState.maximized = IsZoomed(mHandle);
    mWindowState.style = GetWindowLong(mHandle, GWL_STYLE);
    mWindowState.exStyle = GetWindowLong(mHandle, GWL_EXSTYLE);
    GetWindowRect(mHandle, &mWindowState.winRect);
    if (reset)
    {
        SetWindowLongPtr(mHandle, GWL_EXSTYLE, mWindowState.exStyle);
        SetWindowLongPtr(mHandle, GWL_STYLE, mWindowState.style);
        ChangeDisplaySettings(NULL, CDS_RESET);
    }
    SetWindowPos(mHandle, HWND_NOTOPMOST, mWindowState.winRect.left, mWindowState.winRect.top, width, height, SWP_SHOWWINDOW);
    ShowWindow(mHandle, SW_RESTORE);
    UpdateWindow(mHandle);
}

void Window::clientResize(int32& width, int32& height)
{
    int32 difX, difY;
    getWindowDiffSize(difX, difY);
    width += difX;
    height += difY;
}

void Window::getWindowDiffSize(int32 & difX, int32 & difY)
{
    RECT rcClient, rcWindow;
    GetClientRect(mHandle, &rcClient);
    GetWindowRect(mHandle, &rcWindow);
    difX = (rcWindow.right - rcWindow.left) - rcClient.right;
    difY = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
}

bool Window::onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
    {
        RECT clienRect;
        GetClientRect(hWnd, &clienRect);
        // GraphicsManager::GetInstance()->SetHasWindowChanged(true);
        // GraphicsManager::GetInstance()->SetWindowDimensions(clienRect.right - clienRect.left,clienRect.bottom - clienRect.top);
    }
    break;
    }
    return true;
}

Window::~Window()
{
    // InputManager::DeleteSingleton();
    delete (mE2dGame);
    mE2dGame = nullptr;
    // delete StarEngine::GetInstance();
}

const HDC& Window::GetHDC() const
{
    return mHDC;
}

const HWND& Window::GetHandle() const
{
    return mHandle;
}

#endif
