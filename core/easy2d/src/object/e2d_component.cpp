#include "e2d_component.h"
#include "e2d_entity.h"

/* Easy2D */
using namespace Easy2D;

Component::Component() : Object()
{
}

Component::Component(const String& name) : Object(name)
{

}

Component::~Component()
{
}

void Component::destroy()
{
    if (!mMaster.expired())
    {
        mMaster.lock()->removeComponent(mGUID);
    }
}

SPtr<Scene> Component::getScene() const
{
    if (!mMaster.expired())
    {
        return mMaster.lock()->getScene();
    }
    return nullptr;
}

SPtr<TransformComponent> Component::getTransform() const
{
    if (!mMaster.expired())
    {
        return mMaster.lock()->getTransform();
    }
    return nullptr;
}

bool Component::checkCulling(float32 left, float32 right, float32 top, float32 bottom) const
{
    return true;
}

void Component::setEnabled(bool bEnabled)
{
    mEnabled = bEnabled;
}

bool Component::isEnabled() const
{
    return mEnabled;
}

void Component::setVisible(bool bVisible)
{
    mVisible = bVisible;
}

bool Component::isVisible() const
{
    return mVisible;
}

SPtr<Entity> Component::getMaster() const
{
    return mMaster.lock();
}

void Component::setMaster(SPtr<Entity> pEntity)
{
    mMaster = pEntity;
}
