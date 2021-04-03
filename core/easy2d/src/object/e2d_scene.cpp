#include "e2d_scene.h"
#include "e2d_camera.h"
#include "e2d_scene_mgr.h"
#include "math/e2d_pos.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

bool Scene::CULLING_IS_ENABLED = true;

Scene::Scene(const String& name) : Object(name)
{
    // m_pCollisionManager = std::make_shared<CollisionManager>();
}

Scene::~Scene()
{
    mEntitys.clear();
    // m_pCollisionManager = nullptr;
}

void Scene::destroy()
{
    SceneManager::getInstance()->removeScene(mGUID);
}

void Scene::initialize()
{
    if (!mInitialized)
    {
        if (mDefaultCamera == nullptr)
        {
            mDefaultCamera = std::make_shared<Camera>();
            addEntity(mDefaultCamera);
        }
        setActiveCamera(mDefaultCamera);
        mInitialized = true;
    }
}

void Scene::onActivate()
{

}

void Scene::onDeactivate()
{
    for (auto entity : mEntitys)
    {
        entity.second->reset();
    }
}

void Scene::update(const uint32& escapeMs)
{
    for (auto entity : mEntitys)
    {
        entity.second->update(escapeMs);
    }
    // m_pCollisionManager->Update(context);
}

void Scene::draw()
{
    if (!CULLING_IS_ENABLED)
    {
        for (auto entity : mEntitys)
        {
            entity.second->draw();
        }
    }
    else
    {
        Pos camPos = mDefaultCamera->getTransform()->getWorldPosition();
        int32 screenWidth = 800;
        int32 screenHeight = 600;
        float32 left = camPos.pos2D().x - mCullingOffsetX;
        float32 right = camPos.pos2D().x + screenWidth + mCullingOffsetX;
        float32 top = camPos.pos2D().y + screenHeight + mCullingOffsetY;
        float32 bottom = camPos.pos2D().y - mCullingOffsetY;
        for (auto entity : mEntitys)
        {
            entity.second->drawWithCulling(left, right, top, bottom);
        }
    }
}

void Scene::onSaveState(void** pData, size_t* pSize)
{

}

void Scene::onConfigurationChanged()
{

}

void Scene::onLowMemory()
{

}

void Scene::addEntity(SPtr<Entity> pEntity)
{
    if (pEntity)
    {
        if (isEntityNameExist(pEntity->getName()))
        {
            LOG_ERROR << _T("Scene::addEntity: an object with the name '")
                << pEntity->getName() << _T("' already exists. Object gets added but beware, duplicate names can become the cause of problems.");
            return;
        }
        pEntity->initialize();
        pEntity->setScene(std::dynamic_pointer_cast<Scene>(shared_from_this()));
        mEntitys.insert(std::make_pair(pEntity->getGUID(), pEntity));
    }
}

void Scene::addEntity(SPtr<Entity> pEntity, const String& name)
{
    if (pEntity)
    {
        pEntity->setName(name);
        addEntity(pEntity);
    }
}

void Scene::removeEntity(SPtr<Entity> pEntity)
{
    removeEntity(pEntity->getGUID());
}

void Scene::removeEntity(const uint64 guid)
{
    auto it = mEntitys.find(guid);
    if (it != mEntitys.end())
    {
        mEntitys.erase(it);
    }
}

void Scene::setEntityDisabled(const uint64 guid, bool disabled)
{
    auto it = mEntitys.find(guid);
    if (it != mEntitys.end())
    {
        it->second->setDisabled(disabled);
    }
}

void Scene::setEntityVisible(const uint64 guid, bool visible)
{
    auto it = mEntitys.find(guid);
    if (it != mEntitys.end())
    {
        it->second->setVisible(visible);
    }
}

void Scene::setGroupDisabled(const String& tag, bool visible)
{
    for (auto entity : mEntitys)
    {
        if (entity.second->compareGroup(tag))
        {
            entity.second->setDisabled(visible);
        }
    }
}

void Scene::setGroupVisible(const String& tag, bool visible)
{
    for (auto entity : mEntitys)
    {
        if (entity.second->compareGroup(tag))
        {
            entity.second->setVisible(visible);
        }
    }
}

void Scene::getGroup(const String& tag, Vector<SPtr<Entity>>& group)
{
    for (auto entity : mEntitys)
    {
        if (entity.second->compareGroup(tag))
        {
            group.push_back(entity.second);
        }
    }
}

void Scene::setActiveCamera(SPtr<Camera> pCamera)
{
    if (!pCamera || mActiveCamera == pCamera)
    {
        return;
    }
    if (mActiveCamera != nullptr)
    {
        mActiveCamera->deactivate();
    }
    mActiveCamera = pCamera;
    mActiveCamera->activate();
}

SPtr<Camera> Scene::getActiveCamera() const
{
    return mActiveCamera;
}

void Scene::setCullingIsEnabled(bool enabled)
{
    CULLING_IS_ENABLED = enabled;
}

bool Scene::isCullingEnabled()
{
    return CULLING_IS_ENABLED;
}

bool Scene::isEntityNameExist(const String& name) const
{
    for (auto entity : mEntitys)
    {
        if (entity.second->compareName(name))
        {
            return true;
        }
    }
    return false;
}

void Scene::setCullingOffset(int32 offset)
{
    mCullingOffsetX = offset;
    mCullingOffsetY = offset;
}

void Scene::setCullingOffset(int32 offsetX, int32 offsetY)
{
    mCullingOffsetX = offsetX;
    mCullingOffsetY = offsetY;
}

