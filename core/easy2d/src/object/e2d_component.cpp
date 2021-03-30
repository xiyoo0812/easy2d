#include "e2d_component.h"
#include "e2d_entity.h"

/* Easy2D */
using namespace Easy2D;

Component::Component() : Object()
{
}

Component::Component(const String& name): Object(name)
{

}

Component::~Component()
{
}

void Component::destroy()
{
	if(mMaster && mMaster.expired())
	{
		mMaster->removeComponent(mName);
	}
}

WPtr<Scene> Component::getScene() const
{ 
	if(mMaster && mMaster.expired())
	{
		return mMaster->getScene();
	}
	return nullptr;
}

SPtr<TransformComponent> Component::getTransform() const
{
	if(mMaster && mMaster.expired())
	{
		mMaster->getTransform();
	}
	return nullptr;
}

bool Component::checkCulling(float left,float right,float top,float bottom) const
{
	return false;
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

const ivec2 & Component::getDimensions() const
{
	return mDimensions;
}

int32 Component::getWidth() const
{
	return mDimensions.x;
}

int32 Component::getHeight() const
{
	return mDimensions.y; 
}

WPtr<Entity> Component::getMaster() const
{
	return mMaster;
}

void Component::setMaster(SPtr<Entity>* pEntity)
{
	mMaster = pEntity;
}