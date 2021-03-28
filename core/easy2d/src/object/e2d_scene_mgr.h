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

		SPtr<Scene> GetActiveScene();
		SPtr<Scene> GetScene(const String& name);
		template <typename T>
		T* GetScene(const String& name);
		bool SetActiveScene(const String& name);
		bool AddScene(Scene* scene);
		bool AddScene(const String& name, Scene* scene);
		bool RemoveScene(const String& name);

		void Update(const Context& context);
		void Draw();

#ifdef ANDROID
		void processActivityEvent(int32 pCommand, android_app* pApplication);
		int32 processInputEvent(AInputEvent* pEvent);

	private:
		android_app* mApplicationPtr = nullptr;
#endif
	private:
		SceneManager();
		~SceneManager();

		String mCurSceneName = "";
		UnorderedMap<String, SPtr<Scene>> mScenes;
		bool mSwitchingScene = false, mDestroyRequested = false;
		SPtr<Scene>	mActiveScene = nullptr, mNewActiveScene = nullptr;
	};
}

#endif
