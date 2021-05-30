#include "e2d_window.h"
#include "graphics/e2d_graphics_mgr.h"

#ifdef WIN32
#include <Shlobj.h>

/* Easy2D */
using namespace Easy2D;

#ifdef GLFW
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
#else
#define IDI_STARGAMEICON 201
#define WNDCLASSNAME _T("E2DWindow")
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
#endif

void Window::initialize(HINSTANCE instance, uint32 width /* = 800 */, uint32 height/* = 600 */, bool useConsole /* = false */)
{
    if (!mInitialized)
    {
        mE2dEngine = SPtr<E2dEngine>(E2dEngine::getInstance());
        LOG_INIT("./logs/", "E2D_LOG", logger::rolling_type::HOURLY, 10000);

#ifdef GLFW
         glfwInit();
         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

         window = glfwCreateWindow(width, height, _T("E2DGAME"), NULL, NULL);
         if (window == NULL)
         {
             std::cout << "Failed to create GLFW window" << std::endl;
             glfwTerminate();
             return;
         }
         glfwMakeContextCurrent(window);
         glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

         if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
         {
             std::cout << "Failed to initialize GLAD" << std::endl;
             return;
         }
#else
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

        mHandle = CreateWindow(WNDCLASSNAME, _T("E2DGAME"), WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
            GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4,
            width, height, NULL, NULL, instance, NULL);

        if (mHandle == NULL)
        {
            LOG_FATAL << _T("Couldn't create the window.");
            return;
        }
        SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)this);
        setResolution(width, height, false);
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
        if (glewInit() != GLEW_OK)
        {
            return;
        }
#endif
        printGlVersionInfo();
        mE2dEngine->initialize(width, height);
        mInitialized = true;
        mainLoop();
        mE2dEngine->stop();

#ifdef GLFW
        glfwTerminate();  //释放/删除分配的资源
#endif
    }
}

void Window::mainLoop()
{
#ifdef GLFW
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        mE2dEngine->update();
        mE2dEngine->draw();

        glfwSwapBuffers(window);  //交换颜色缓冲，并显示到窗口
        glfwPollEvents();  //检查触发事件，更新窗口状态，并调用对应回调函数
    }
#else
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
            mE2dEngine->update();
            mE2dEngine->draw();
            SwapBuffers(Window::mHDC); // Swaps display buffers
        }
    }
#endif
}

bool Window::isInitialized() const
{
    return mInitialized;
}

#ifndef GLFW
bool Window::onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return true;
    }
    break;
    case WM_SIZE:
    {
        RECT clienRect;
        GetClientRect(hWnd, &clienRect);
        GraphicsManager::getInstance()->setScreenResolution(clienRect.right - clienRect.left,clienRect.bottom - clienRect.top);
        return true;
    }
    break;
    }
    return false;
}

void Window::setResolution(uint32 width, uint32 height, bool reset /* = true */)
{
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

void Window::clientResize(uint32& width, uint32& height)
{
    uint32 difX, difY;
    getWindowDiffSize(difX, difY);
    width += difX;
    height += difY;
}

void Window::getWindowDiffSize(uint32& difX, uint32& difY)
{
    RECT rcClient, rcWindow;
    GetClientRect(mHandle, &rcClient);
    GetWindowRect(mHandle, &rcWindow);
    difX = (rcWindow.right - rcWindow.left) - rcClient.right;
    difY = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
}
#endif

Window::~Window()
{
    // InputManager::DeleteSingleton();
    // delete StarEngine::getInstance();
}

void Window::printGlVersionInfo()
{
    LOG_DEBUG << "OpenGL version: " << glGetString(GL_VERSION);
    LOG_DEBUG << "GL_VENDOR: " << glGetString(GL_VENDOR);
    LOG_DEBUG << "GL_RENDERER: " << glGetString(GL_RENDERER);
    LOG_DEBUG << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
}


#endif
