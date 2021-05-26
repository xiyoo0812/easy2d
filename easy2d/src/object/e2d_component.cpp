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

void Component::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

bool Component::isEnabled() const
{
    return mEnabled;
}

void Component::setVisible(bool visible)
{
    mVisible = visible;
}

bool Component::isVisible() const
{
    return mVisible;
}

void Component::setChanged(bool changed)
{
    mChanged = changed;
}

bool Component::isChanged() const
{
    return mChanged;
}

SPtr<Entity> Component::getMaster() const
{
    return mMaster.lock();
}

void Component::setMaster(SPtr<Entity> pEntity)
{
    mMaster = pEntity;
}
