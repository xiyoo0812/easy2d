#include "e2d_scene.h"
#include "e2d_camera.h"
#include "e2d_scene_mgr.h"
#include "math/e2d_pos.h"
#include "graphics/e2d_graphics_mgr.h"
#include "graphics/e2d_render_batch.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

bool Scene::CULLING_IS_ENABLED = false;

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
        entity->reset();
    }
}

void Scene::update(const uint32& escapeMs)
{
    for (auto entity : mEntitys)
    {
        entity->update(escapeMs);
    }
    // m_pCollisionManager->Update(context);
}

void Scene::draw()
{
    if (!CULLING_IS_ENABLED)
    {
        for (auto entity : mEntitys)
        {
            entity->draw();
        }
    }
    else
    {
        Vec2 camPos = mDefaultCamera->getTransform()->getWorldPosition();
        int32 screenWidth = GraphicsManager::getInstance()->getWindowResolution().x;
        int32 screenHeight = GraphicsManager::getInstance()->getWindowResolution().y;
        float32 left = camPos.x - mCullingOffsetX;
        float32 right = camPos.x + screenWidth + mCullingOffsetX;
        float32 top = camPos.y + screenHeight + mCullingOffsetY;
        float32 bottom = camPos.y - mCullingOffsetY;
        for (auto entity : mEntitys)
        {
            entity->drawWithCulling(left, right, top, bottom);
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


void Scene::sortEntity()
{
    switch (RenderBatch::getInstance()->getSortingMode())
    {
    case RenderSortingMode::BackFront:
        std::sort(mEntitys.begin(), mEntitys.end(), [](SPtr<Entity> a, SPtr<Entity> b) -> bool
        {
            return a->getZorder() < b->getZorder();
        });
        break;
    case RenderSortingMode::FrontBack:
        std::sort(mEntitys.begin(), mEntitys.end(), [](SPtr<Entity> a, SPtr<Entity> b) -> bool
        {
            return a->getZorder() < b->getZorder();
        });
        break;
    default:
        break;
    }
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
        pEntity->setScene(std::dynamic_pointer_cast<Scene>(shared_from_this()));
        mEntitys.push_back(pEntity);
        pEntity->initialize();
        sortEntity();
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
    auto it = std::find_if(mEntitys.begin(), mEntitys.end(), [&](SPtr<Entity> pEntity) -> bool
    {
        return pEntity->compareGUID(guid);
    });
    if (it != mEntitys.end())
    {
        mEntitys.erase(it);
        sortEntity();
    }
}

void Scene::removeEntity(const String& name)
{
    auto it = std::find_if(mEntitys.begin(), mEntitys.end(), [&](SPtr<Entity> pEntity) -> bool
    {
        return pEntity->compareName(name);
    });
    if (it != mEntitys.end())
    {
        mEntitys.erase(it);
        sortEntity();
    }
}

void Scene::setEntityDisabled(const uint64 guid, bool disabled)
{
    for (auto entity : mEntitys)
    {
        if (entity->compareGUID(guid))
        {
            entity->setDisabled(disabled);
            break;
        }
    }
}

void Scene::setEntityVisible(const uint64 guid, bool visible)
{
    for (auto entity : mEntitys)
    {
        if (entity->compareGUID(guid))
        {
            entity->setVisible(visible);
            break;
        }
    }
}

void Scene::setGroupDisabled(const String& tag, bool visible)
{
    for (auto entity : mEntitys)
    {
        if (entity->compareGroup(tag))
        {
            entity->setDisabled(visible);
        }
    }
}

void Scene::setGroupVisible(const String& tag, bool visible)
{
    for (auto entity : mEntitys)
    {
        if (entity->compareGroup(tag))
        {
            entity->setVisible(visible);
        }
    }
}

void Scene::getGroup(const String& tag, Vector<SPtr<Entity>>& group)
{
    for (auto entity : mEntitys)
    {
        if (entity->compareGroup(tag))
        {
            group.push_back(entity);
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
        if (entity->compareName(name))
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

