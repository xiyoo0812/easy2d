#include "e2d_scene_mgr.h"

/* Easy2D */
using namespace Easy2D;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    mScenes.clear();
}

SPtr<Scene> SceneManager::getActiveScene()
{
    return mActiveScene;
}

bool SceneManager::setActiveScene(const uint64 guid)
{
    if (mCurSceneID == guid)
    {
        LOG_WARN << _T("SceneManager::setActiveScene: Scene is already active!");
        return true;
    }
    auto it = mScenes.find(guid);
    if (it != mScenes.end())
    {
        if (mActiveScene == nullptr)
        {
            mActiveScene = it->second;
        }
        mSwitchingScene = true;
        mNewActiveScene = it->second;
        mInitialized = mNewActiveScene->isInitialized();
        mCurSceneID = guid;
        LOG_INGO << _T("Scene ") << guid << _T(" is now Active");
        return true;
    }
    else
    {
        mSwitchingScene = false;
        return false;
    }
    return true;
}

bool SceneManager::addScene(SPtr<Scene> scene)
{
    if (scene == nullptr)
    {
        LOG_ERROR << _T("SceneManager::addScene: Trying to add a nullptr as a scene.");
        return false;
    }
    auto it = mScenes.find(scene->getGUID());
    if (it != mScenes.end())
    {
        LOG_WARN << _T("SceneManager::addScene: Scene Already Exists");
        return false;
    }
    scene->initialize();
    mScenes.insert(std::make_pair(scene->getGUID(), scene));
    LOG_INGO << _T("SceneManager::addScene: Adding scene");
    return true;
}

bool SceneManager::addScene(const String& name, SPtr<Scene> scene)
{
    if (scene == nullptr)
    {
        LOG_ERROR << _T("SceneManager::addScene: Trying to add a nullptr as a scene.");
        return false;
    }
    scene->setName(name);
    return addScene(scene);
}

bool SceneManager::removeScene(const uint64 guid)
{
    auto it = mScenes.find(guid);
    if (it != mScenes.end())
    {
        mScenes.erase(it);
        return true;
    }
    return false;
}

bool SceneManager::initialized()
{
    if (mInitialized)
    {
        return true;
    }
    if (mNewActiveScene == nullptr)
    {
        return false;
    }
    LOG_INGO << _T("Initializing Scene :") << mCurSceneID;
    mInitialized = mNewActiveScene->isInitialized();
    return mInitialized;
}

void SceneManager::update(const uint32& escapeMs)
{
    if (mSwitchingScene)
    {
        if (mActiveScene)
        {
            mActiveScene->onDeactivate();
        }
        mActiveScene = mNewActiveScene;
        mActiveScene->onActivate();
        mNewActiveScene = nullptr;
        mSwitchingScene = false;
        return;
    }
    if (mActiveScene)
    {
        mActiveScene->update(escapeMs);
    }
}

void SceneManager::draw()
{
    if (mActiveScene)
    {
        mActiveScene->draw();
        // 		SpriteBatch::getInstance()->flush();
        // 		DebugDraw::getInstance()->flush();
    }
}

template <typename T>
SPtr<T> SceneManager::getScene(const uint64 guid)
{
    auto it = mScenes.find(guid);
    if (it != mScenes.end())
    {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

#ifdef ANDROID
#define INPUT_MANAGER (InputManager::getInstance())
void SceneManager::processActivityEvent(int32 pCommand, android_app* pApplication)
{
    if (mActiveScene == nullptr)
    {
        return;
    }
    mApplicationPtr = pApplication;
    switch (pCommand)
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
        mActiveScene->onSaveState(&mApplicationPtr->savedState, &mApplicationPtr->savedStateSize);
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
            INPUT_MANAGER->onTouchEvent(pEvent);
            return (true);
        default:
            return (false);
        }
        break;
    case AINPUT_EVENT_TYPE_KEY:
        return INPUT_MANAGER->onKeyboardEvent(pEvent);
    default:
        return false;
    }
    return false;
}
#endif
