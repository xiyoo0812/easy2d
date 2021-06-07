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

void Component::setChanged(bool changed)
{
    mbChanged = changed;
}

bool Component::isChanged() const
{
    return mbChanged;
}

SPtr<Entity> Component::getMaster() const
{
    return mMaster.lock();
}

void Component::setMaster(SPtr<Entity> pEntity)
{
    mMaster = pEntity;
}
