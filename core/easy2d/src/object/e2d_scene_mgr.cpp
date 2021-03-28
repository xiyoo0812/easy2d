#include "e2d_scene_mgr.h"

#define INPUT_MANAGER (InputManager::GetInstance())

/* Easy2D */
using namespace Easy2D;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for(auto scene : mScenes)
	{
		safeDelete(scene);
	}
	mScenes.clear();
}

SPtr<Scene> SceneManager::GetActiveScene()
{
	return mActiveScene;
}

SPtr<Scene> SceneManager::GetScene(const String& name)
{
	auto it = mScenes.find(name);
	if(it != mScenes.end())
	{
		return it.second;
	}
	return nullptr;
}

bool SceneManager::SetActiveScene(const String& name)
{
	if(mCurSceneName == name)
	{
		LOG_WARN << _T("SceneManager::SetActiveScene: Scene is already active!");
		return true;
	}
	auto it = mScenes.find(name);
	if(it != mScenes.end())
	{
		if(mActiveScene == nullptr)
		{
			mActiveScene = it.second;
		}
		mSwitchingScene = true;
		mNewActiveScene = it.second;
		mInitialized = mNewActiveScene->isInitialized();
		mCurSceneName = name;
		LOG_INGO << _T("Scene ") << name << _T(" is now Active");
		return true;
	}
	else
	{
		mSwitchingScene = false;
		return false;
	}
	return true;
}

bool SceneManager::AddScene(Scene* scene)
{
	if(!scene)
	{
		LOG_ERROR << _T("SceneManager::AddScene: Trying to add a nullptr as a scene.");
		return false;
	}
	if (mScenes.find(scene->GetName()) == mScenes.end())
	{
		scene->Initialize();
		mScenes.insert(std::make_pair(scene->GetName(), scene));
		LOG_INGO << _T("SceneManager::AddScene: Adding scene");
	}
	else
	{
		LOG_WARN << _T("SceneManager::AddScene: Scene Already Exists");
		return false;
	}
	return true;
}

bool SceneManager::AddScene(const String& name, Scene* scene)
{
	if(!scene)
	{
		LOG_ERROR << _T("SceneManager::AddScene: Trying to add a nullptr as a scene.");
		return false;
	}
	scene->SetName(name);
	return AddScene(scene);
}

bool SceneManager::RemoveScene(const String& name)
{
	auto it = mScenes.find(name);
	if(it != mScenes.end())
	{
		mScenes.erase(it);
		return true;
	}
	return false;
}

bool SceneManager::InitializeCurScene(const Context& context)
{
	if(mInitialized)
	{
		return true;
	}
	if(mNewActiveScene == nullptr)
	{
		return false;
	}
	LOG_INGO << _T("Initializing Scene :") << mCurSceneName;
	mNewActiveScene->initialize();
	mInitialized = mNewActiveScene->isInitialized();
	return mInitialized;
}

void SceneManager::Update(const Context& context)
{
	if(mDestroyRequested)
	{
		return;
	}
	if(mSwitchingScene)
	{
		if(!mInitialized)
		{
			InitializeCurScene(context);
		}
		if(mActiveScene != nullptr)
		{
			mActiveScene->onDeactivate();
		}
		mActiveScene = mNewActiveScene;
		mActiveScene->onActivate();
		mNewActiveScene = nullptr;
		mSwitchingScene = false;
		return;
	}
	else if(mActiveScene != nullptr)
	{
		return mActiveScene->Update(context);
	}
}

void SceneManager::Draw()
{
	if(mDestroyRequested)
	{
		return;
	}
	if(mActiveScene != nullptr)
	{
		mActiveScene->draw();
		SpriteBatch::GetInstance()->Flush();
		DebugDraw::GetInstance()->Flush();
	}
}

#ifdef ANDROID
void SceneManager::processActivityEvent(int32 pCommand, android_app* pApplication)
{
	if(mActiveScene == nullptr)
	{
		return;
	}
	mApplicationPtr = pApplication;
	switch(pCommand)
	{
	//First save state - then Stop - then Start - then Resume - then gained focus
	case APP_CMD_STOP:
		LOG_INGO << _T("SceneManager : APP_CMD_STOP");
		break;

	case APP_CMD_GAINED_FOCUS:
		LOG_INGO << _T("SceneManager : APP_CMD_GAINED_FOCUS");
		break;
	case APP_CMD_SAVE_STATE:
		LOG_INGO << _T("SceneManager : APP_CMD_SAVE_STATE");
		mActiveScene->OnSaveState(&mApplicationPtr->savedState,&mApplicationPtr->savedStateSize);
		break;
	}
}

int32 SceneManager::processInputEvent(AInputEvent* pEvent)
{
	//[TODO] Cast the input event to motionEvent and pass that type
	int32_t lEventType = AInputEvent_getType(pEvent);
	switch (lEventType)
	{
	case AINPUT_EVENT_TYPE_MOTION:
		switch (AInputEvent_getSource(pEvent))
		{
		case AINPUT_SOURCE_TOUCHSCREEN:
			INPUT_MANAGER->OnTouchEvent(pEvent);
			return (true);
		default:
			return (false);
		}
		break;
	case AINPUT_EVENT_TYPE_KEY:
		return INPUT_MANAGER->OnKeyboardEvent(pEvent);
	default:
		return false;
	}
	return false;
}
#endif
