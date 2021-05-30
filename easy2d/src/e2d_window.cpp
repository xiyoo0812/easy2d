#include "e2d_window.h"
#include "graphics/e2d_graphics_mgr.h"

/* Easy2D */
using namespace Easy2D;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::initialize(HINSTANCE instance, uint32 width /* = 800 */, uint32 height/* = 600 */, bool useConsole /* = false */)
{
    if (!mInitialized)
    {
        mE2dEngine = SPtr<E2dEngine>(E2dEngine::getInstance());
        LOG_INIT("./logs/", "E2D_LOG", logger::rolling_type::HOURLY, 10000);

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, _T("E2DGAME"), NULL, NULL);
        if (window == NULL)
        {
            LOG_ERROR << "Failed to create GLFW window";
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_ERROR << "Failed to initialize GLAD";
            glfwTerminate();
            return;
        }

        printGlVersionInfo();

        mE2dEngine->initialize(width, height);
        mInitialized = true;
        mainLoop();
        mE2dEngine->stop();

        glfwTerminate();
    }
}

void Window::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        mE2dEngine->update();
        mE2dEngine->draw();

        glfwSwapBuffers(window);  //交换颜色缓冲，并显示到窗口
        glfwPollEvents();  //检查触发事件，更新窗口状态，并调用对应回调函数
    }
}

bool Window::isInitialized() const
{
    return mInitialized;
}

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

