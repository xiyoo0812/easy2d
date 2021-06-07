#ifndef ENGINE_H
#define ENGINE_H

#include "e2d_config.h"
#include "gui/e2d_widget.h"
#include "base/e2d_stopwatch.h"

namespace Easy2D
{
    class E2dEngine final : public Singleton<E2dEngine>
    {
    public:
        friend Singleton<E2dEngine>;

        void initialize(uint32 window_width, uint32 window_height);

        ~E2dEngine();

        void update();
        void stop();

        void setActive();
        void setInactive();

        uint32 getCurrentFPS() const;
        uint32 getPreviousFPS() const;

        void quit();

    private:
        E2dEngine();

        //FPS mFPS;
        SPtr<UIRoot> mUIRoot = nullptr;
        SPtr<Stopwatch> mStopWatch = nullptr;
    };
}

#endif
