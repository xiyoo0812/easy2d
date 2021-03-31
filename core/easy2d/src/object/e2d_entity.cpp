#include "e2d_entity.h"

/* Easy2D */
using namespace Easy2D;

Entity::Entity(void) : Object()
{
	addComponent(new TransformComponent());
}

Entity::Entity(const String& name) : Object(name)
{
	addComponent(new TransformComponent());
}

Entity::Entity(const String& name, const String& group)
	: Object(name), mGroup(group)
{
	addComponent(new TransformComponent());
}

Entity::~Entity()
{
	mActions.clear();
	mChildren.clear();
	mComponents.clear();
}

void Entity::destroy()
{
	if(mParent && mParent->expired())
	{
		mParent->removeChild(mGUID);
	}
	if(mScene && mScene->expired())
	{
		mScene->removeEntity(mGUID);
	}
}

void Entity::initialize()
{

}

void Entity::update(const uint32& escapeMs)
{
	if(!mDisable)
	{
		for(auto action : mActions)
		{
			action->update(escapeMs);
		}
		for(auto component : mComponents)
		{
			component->update(escapeMs);
		}
		for(auto child : mChildren)
		{
			child->update(escapeMs);
		}
	}
}


bool Entity::checkCulling(float32 left, float32 right, float32 top, float32 bottom)
{
	for (auto component : mComponents)
	{
		if(component->checkCulling(left, right, top, bottom))
		{
			return true;
		}
	}
	return false;
}

void Entity::draw()
{
	if(mVisible)
	{
		for(auto component : mComponents)
		{
			component->draw();
		}
		for(auto child : mChildren)
		{
			child->draw();
		}
	}
}

void Entity::drawWithCulling(float32 left,float32 right,float32 top,float32 bottom)
{
	if(mVisible)
	{
		if(checkCulling(left, right, top, bottom))
		{
			for(auto component : mComponents)
			{
				component->draw();
			}
		}
		for(auto child : mChildren)
		{
			child->drawWithCulling(left, right, top, bottom);
		}
	}
}

const String& Entity::getPhysics() const
{
	return mPhysics;
}

void Entity::setPhysics(const String& physics)
{
	mPhysics = physics;
}

bool Entity::comparePhysics(const String& physics)
{
	return mPhysics == physics;
}

bool Entity::compareGroup(const String& group)
{
	return mGroup == group;
}

const String& Entity::getGroup() const
{
	return mGroup;
}

void Entity::setGroup(const String& group)
{
	mGroup = group;
}

bool Entity::addChild(SPtr<Entity> pChild)
{
	if(IsChildNameExist(pChild->getName()))
	{
		LOG_WARN << _T("Entity::addChild: a child with the name '") << pChild->getName() << 
			_T("' already exists. Child gets added but beware, duplicate names can become the cause of problems.")
		return false;
	}
	pChild->initialize();
	pChild->setScene(mScene);
	pChild->setParent(dynamic_pointer_cast<Entity>(shared_from_this(this)));
	mChildren.insert(pChild->getGUID(), pChild);
	return true;
}

void Entity::removeChild(const SPtr<Entity> pEntity)
{
	removeChild(pEntity->getGUID());
}

void Entity::removeChild(const uint64 guid)
{
	auto it = mChildren.find(guid)
	if (it != mChildren.end())
	{
		mChildren.erase(it);
	}
}

const UnorderedMap<uint64, SPtr<Entity>>& Entity::getChildren() const
{
	return mChildren;
}

void Entity::setChildDisabled(const uint64 guid, bool disabled)
{
	auto it = mChildren.find(guid)
	if (it != mChildren.end())
	{
		it->second->setDisabled(disabled);
	}
}

void Entity::setChildVisible(const uint64 guid,, bool visible)
{
	auto it = mChildren.find(guid)
	if (it != mChildren.end())
	{
		it->second->setVisible(disabled);
	}
}

void Entity::setChildrenDisabled(bool disable)
{
	for(auto child : mChildren)
	{
		child->setDisabled(disable);
	}
}

void Entity::setChildrenVisible(bool visible)
{
	for(auto child : mChildren)
	{
		child->setVisible(visible);
	}
}

bool Entity::addAction(SPtr<Action> pAction)
{
	if(IsActionNameExist(pAction->getName()))
	{
		LOG_WARN << _T("Entity::addAction: a child with the name '") << pAction->getName() << 
			_T("' already exists. Action gets added but beware, duplicate names can become the cause of problems.")
		return false;
	}
	pAction->initialize();
	pAction->setMaster(dynamic_pointer_cast<Entity>(shared_from_this(this)));
	mActions.insert(pAction->getGUID(), pAction);
	return true;
}

void Entity::removeAction(const SPtr<Action> pAction)
{
	removeAction(pAction->getGUID());
}

void Entity::removeAction(const uint64 guid)
{
	auto it = mActions.find(guid)
	if (it != mActions.end())
	{
		it.second->setMaster(nullptr);
		mActions.erase(it);
	}
}

void Entity::restartAction(const uint64 guid)
{
	auto it = mActions.find(guid)
	if (it != mActions.end())
	{
		it.second->restart();
	}
}

void Entity::pauseAction(const uint64 guid)
{
	auto it = mActions.find(guid)
	if (it != mActions.end())
	{
		it.second->pause();
	}
}

void Entity::resumeAction(const uint64 guid)
{
	auto it = mActions.find(guid);
	if (it != mActions.end())
	{
		it.second->resume();
	}
}

bool Entity::addComponent(SPtr<Component> pComponent)
{
	if(IsActionNameExist(pComponent->getName()))
	{
		LOG_WARN << _T("Entity::addComponent: a child with the name '") << pComponent->getName() << 
			_T("' already exists. Component gets added but beware, duplicate names can become the cause of problems.")
		return false;
	}
	pComponent->initialize();
	pComponent->setMaster(dynamic_pointer_cast<Entity>(shared_from_this(this)));
	mComponents.insert(pComponent->getGUID(), pComponent);
	return true;
}

void Entity::removeComponent(const SPtr<Component> pComponent)
{
	removeComponent(pAction->getGUID());
}

void Entity::removeComponent(const uint64 guid)
{
	auto it = mComponents.find(guid)
	if (it != mComponents.end())
	{
		it.second->setMaster(nullptr);
		mComponents.erase(it);
	}
}

void Entity::setVisible(bool visible)
{
	mVisible = visible;
}

bool Entity::isVisible() const
{
	return mVisible;
}

bool Entity::isChildNameExist(const String& name) const
{
	for(auto pChild : mChildren)
	{
		if(pChild->compareName(name))
		{
			return true;
		}
	}
	return false;
}

bool Entity::isActionNameExist(const String& name) const
{
	for(auto pAction : mActions)
	{
		if(pAction->compareName(name))
		{
			return true;
		}
	}
	return false;
}

bool Entity::isComponentNameExist(const String& name) const
{
	for(auto pComponent : mComponents)
	{
		if(pComponent->compareName(name))
		{
			return true;
		}
	}
	return false;
}

void Entity::setDisabled(bool disabled)
{
	mDisable = disabled;
}

bool Entity::isDisabled() const
{
	return mDisable;
}


int32* Entity::getZorder() const
{
	return mZorder;
}

void Entity::setZorder(int32* order)
{
	mZorder = order;
}

WPtr<Scene> Entity::getScene() const
{
	return mScene;
}

void Entity::setScene(SPtr<Scene> pScene)
{
	if (mScene != pScene)
	{
		mScene = pScene;
		for(auto child : mChildren)
		{
			child->setScene(pScene);
		}
	}
}

WPtr<Entity> Entity::getParent() const
{
	return mParent;
}

void Entity::setParent(SPtr<Entity> pEntity)
{
	mParent = pEntity;
}

void Entity::reset()
{
	for(auto child : mChildren)
	{
		child->reset();
	}
}

void Entity::recalculateDimensions()
{
	Vec2 dim(0, 0);
	auto transform = getTransform();
	for(auto comp : m_pComponents)
	{
		if(comp != transform)
		{
			Vec2 temp = comp->getDimensions();
			if(temp.x > dim.x)
			{
				dim.x = temp.x;
			}
			if(temp.y > dim.y)
			{
				dim.y = temp.y;
			}
		}
	}
	transform->setDimensions(dim);
}

SPtr<TransformComponent> Entity::getTransform() const
{
	return getComponent<TransformComponent>(TransformComponent::GUID);
}

template <typename T>
SPtr<T> Entity::getChild(const uint64 guid) const
{
	auto it = mChildren.find(guid)
	if (it != mChildren.end())
	{
		return dynamic_pointer_cast<T>(it->second));
	}
	return nullptr;
}

template <typename T>
SPtr<T> Entity::getChild(const String& name) const
{
	for(auto child : mChildren)
	{
		if(child->compareName(name))
		{
			return dynamic_pointer_cast<T>(it->second));
		}
	}
	for(auto child : mChildren)
	{
		auto pChild = child->getChild<T>(name);
		if(pChild)
		{
			return pChild
		}
	}
	return nullptr;
}

template <typename T>
SPtr<T> Entity::getAction(const uint64 guid) const
{
	auto it = mActions.find(guid)
	if (it != mActions.end())
	{
		return dynamic_pointer_cast<T>(it->second));
	}
	return nullptr;
}

template <typename T>
SPtr<T> Entity::getComponent(const String& name) const
{
	for(auto pComponent : mComponents)
	{
		if(pComponent->compareName(name))
		{
			return dynamic_pointer_cast<T>(pComponent));
		}
	}
	return nullptr;
}
