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
        bool setActiveScene(const uint64 guid);
        bool addScene(SPtr<Scene> scene);
        bool addScene(const String& name, SPtr<Scene> scene);
        bool removeScene(const uint64 guid);

        void update(const uint32& escapeMs, bool escapeSec);

        template <typename T = Scene>
        SPtr<T> createScene(const String& name);
        template <typename T = Scene>
        SPtr<T> getScene(const uint64 guid);

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
