//��win32�����н���console���ڣ����ڵ���
//
#ifndef CONSOLE_H
#define CONSOLE_H

#include "e2d_config.h"
#include "e2d_singleton.h"

namespace Easy2D
{
    enum class ConsoleMode
    {
        None,
        Debug,
    };

    class Console : public Singleton<Console>
    {
    public:
        friend class Singleton<Console>;

        Console();
        ~Console();

        void initialize(const String& name, short width = 800, short height = 600);

        String& peekComand();

    protected:
        void consoleBack();
 
    private:
        handle m_hStdOut = nullptr;
        handle m_hStdIn = nullptr;

        String mCommand = "";
        ConsoleMode mMode = ConsoleMode::None;
        const String mDebugFlag = _T("Input>");
    };
}

#endif