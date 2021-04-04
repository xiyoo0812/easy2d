#ifndef ENGINE_H
#define ENGINE_H

#include "e2d_config.h"

namespace Easy2D
{
    class E2dEngine final : public Singleton<E2dEngine>
    {
    public:
        friend Singleton<E2dEngine>;
#ifdef WIN32
        friend class Window;
        void initialize(uint32 window_width, uint32 window_height);
#endif
#ifdef ANDROID
        void initialize(SPtr<android_app> app);
        SPtr<android_app> getAndroidApp() const;
    private:
        SPtr<android_app> mAndroidApp;
#endif

        ~E2dEngine();

        void update(const uint32& escapeMs);
        void draw();
        void stop();

        void setActive();
        void setInactive();

        uint32 getCurrentFPS() const;
        uint32 getPreviousFPS() const;

        void setTitle(const String& title);
        void setSubTitle(const String & title);
        const String& getTitle();
        const String& getSubTitle();

        bool hasTitleUpdated() const;
        void resetTitleUpdateMark();

        void quit();

    private:
        E2dEngine();

        //FPS mFPS;
        String mTitle = "";
        String mSubTitle = "";
        bool mTitleHasUpdated = false;
    };
}

#endif
