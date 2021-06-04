#include "e2d_scene.h"
#include "e2d_camera.h"
#include "e2d_scene_mgr.h"
#include "math/e2d_pos.h"
#include "base/e2d_input.h"
#include "graphics/e2d_graphics_mgr.h"
#include "graphics/e2d_render_batch.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

Scene::Scene(const String& name) : Entity(name)
{
}

Scene::~Scene()
{
}

void Scene::destroy()
{
    SceneManager::getInstance()->removeScene(mGUID);
}

void Scene::initialize()
{
    if (!mInitialized)
    {
        Entity::initialize();
        if (mDefaultCamera == nullptr)
        {
            mDefaultCamera = std::make_shared<Camera>();
            addChild(mDefaultCamera);
        }
        InputSystem::getInstance()->addInputSink(std::dynamic_pointer_cast<InputSink>(shared_from_this()));
        setActiveCamera(mDefaultCamera);
        mInitialized = true;
    }
}

void Scene::onActivate()
{

}

void Scene::onDeactivate()
{
    for (auto entity : mChildrens)
    {
        entity->reset();
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
