#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "e2d_scene.h"

#ifdef ANDROID
#include <android_native_app_glue.h>
#endif

namespace Easy2D
{
    class AInputEvent;
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        friend Singleton<SceneManager>;

        SPtr<Scene> getActiveScene();
        template <typename T = Scene>
        SPtr<T> getScene(const uint64 guid);
        bool setActiveScene(const uint64 guid);
        bool addScene(SPtr<Scene> scene);
        bool addScene(const String& name, SPtr<Scene> scene);
        bool removeScene(const uint64 guid);

        bool initialized();

        void update(const uint32& escapeMs);

#ifdef ANDROID
        void processActivityEvent(int32 pCommand, android_app* pApplication);
        int32 processInputEvent(AInputEvent* pEvent);

    private:
        android_app* mApplicationPtr = nullptr;
#endif
    private:
        SceneManager();
        ~SceneManager();

        uint64 mCurSceneID = 0;
        bool mInitialized = false;
        UnorderedMap<uint64, SPtr<Scene>> mScenes;
        bool mSwitchingScene = false, mDestroyRequested = false;
        SPtr<Scene>	mActiveScene = nullptr, mNewActiveScene = nullptr;
    };
}

#include "e2d_scene_mgr.hpp"

#endif
