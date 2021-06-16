#include "e2d_console.h"

/* Easy2D */
using namespace Easy2D;

Console::Console()
{
}

Console::~Console()
{
#ifdef WIN32
    FreeConsole();
#endif
}

//启动console窗口
void Console::initialize(const String& name, short width, short height)
{
#ifdef WIN32
    AllocConsole();
    SetConsoleTitle(name.c_str());

    m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //指明句柄为标准输出HANDLE
    m_hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    COORD co = { 400, 300 };
    SetConsoleScreenBufferSize(m_hStdOut, co);  //指明缓冲区大小

    freopen("conin$", "r+t", stdin);            // in redirect.    
    freopen("conout$", "w+t", stdout);          // out redirect    
    freopen("conout$", "w+t", stderr);          // err redirect 
#endif
}

//清除屏幕
void Console::consoleBack()
{
#ifdef WIN32
    DWORD cCharsWritten;
    /* here's where we'll home the cursor */
    COORD coordScreen = { 0,0 };
    /* to get buffer info */
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // Get the number of character cells in the current buffer. 
    if (!GetConsoleScreenBufferInfo(m_hStdOut, &csbi))
        return;
    coordScreen.X = csbi.dwCursorPosition.X;
    coordScreen.Y = csbi.dwCursorPosition.Y;
    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(m_hStdOut, (TCHAR)' ', 1, coordScreen, &cCharsWritten))
        return;
    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(m_hStdOut, &csbi))
        return;
    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(m_hStdOut, csbi.wAttributes, 1, coordScreen, &cCharsWritten))
        return;
#endif
}


//取得输入
String& Console::peekComand()
{
#ifdef WIN32
    DWORD num = 0;
    INPUT_RECORD record;
    while (PeekConsoleInput(m_hStdIn, &record, 1, &num) && num > 0)
    {
        ReadConsoleInput(m_hStdIn, &record, 1, &num);
        if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
        {
            char c = record.Event.KeyEvent.uChar.AsciiChar;
            if (c == '\r') c = '\n';
            if (c < 32 && c != '\n' && c != VK_BACK) continue;
            switch (c)
            {
            case '\n':
            {
                switch (mMode)
                {
                case ConsoleMode::None:
                    WriteConsoleA(m_hStdOut, INPUT_PREFIX.c_str(), INPUT_PREFIX.size(), NULL, NULL);
                    mMode = ConsoleMode::Debug;
                    mCommand.clear();
                    break;
                case ConsoleMode::Debug:
                    for (int i = 0; i < INPUT_PREFIX.size(); ++i) 
                    {
                        c = VK_BACK;
                        WriteConsoleA(m_hStdOut, &c, 1, NULL, NULL);
                        consoleBack();
                    }
                    mMode = ConsoleMode::None;
                    mCommand.clear();
                    break;
                }
                return mCommand;
            }
            case VK_BACK:
                if (!mCommand.empty())
                {
                    WriteConsoleA(m_hStdOut, &c, 1, NULL, NULL);
                    mCommand = mCommand.substr(0, mCommand.size() - 1);
                    consoleBack();
                }
                break;
            default:
                if (mMode == ConsoleMode::Debug)
                {
                    mCommand.append(1, c);
                    WriteConsoleA(m_hStdOut, &c, 1, NULL, NULL);
                }
            }
        }
    }
#endif
    return mCommand;
}

