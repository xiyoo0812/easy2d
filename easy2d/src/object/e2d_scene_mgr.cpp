#include "e2d_scene_mgr.h"
#include "graphics/e2d_render_batch.h"

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
        mCurSceneID = guid;
        LOG_INFO << _T("Scene ") << guid << _T(" is now Active");
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
    mScenes.insert(std::make_pair(scene->getGUID(), scene));
    LOG_INFO << _T("SceneManager::addScene: Adding scene");
    if (mCurSceneID == 0)
    {
        setActiveScene(scene->getGUID());
    }
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

void SceneManager::update(const uint32& escapeMs, bool escapeSec)
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
    }
    if (mActiveScene)
    {
        mActiveScene->update(escapeMs, escapeSec);
    }
}
