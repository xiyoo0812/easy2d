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
		mParent->removeChild(mName);
	}
	if(mScene && mScene->expired())
	{
		mScene->removeEntity(mName);
	}
}

void Entity::initialize()
{

}

void Entity::update(const uint32& escapeMs)
{
	if(!m_IsFrozen)
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
	for ( auto component : mComponents)
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

void Entity::addChild(SPtr<Entity> pChild)
{
	if(IsChildNameExist(pChild->getName()))
	{
		LOG_DEBUG << _T("Entity::addChild: a child with the name '") << pChild->getName() << 
			_T("' already exists. Child gets added but beware, duplicate names can become the cause of problems.")
	}
	auto it = mChildren.find(pChild->getName())
	if (it != mChildren.end())
	{
		pChild->initialize();
		pChild->setScene(mScene);
		pChild->setParent(dynamic_pointer_cast<Entity>(shared_from_this(this)));
		mChildren.insert(pChild->getName(), pChild);
	}
}

void Entity::removeChild(const SPtr<Entity> pEntity)
{
	removeChild(pEntity->getName());
}

void Entity::removeChild(const String& name)
{
	auto it = mChildren.find(name)
	if (it != mChildren.end())
	{
		it.second->setParent(nullptr);
		mChildren.erase(it);
	}
}

const UnorderedMap<String, SPtr<Entity>>& Entity::getChildren() const
{
	return mChildren;
}

void Entity::setChildDisabled(const String& name, bool disabled)
{
	auto it = mChildren.find(name)
	if (it != mChildren.end())
	{
		it->second->setDisabled(disabled);
	}
}

void Entity::setChildVisible(const String& name, bool visible)
{
	auto it = mChildren.find(name)
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

void Entity::addAction(SPtr<Action> pAction)
{
	if(IsActionNameExist(pAction->getName()))
	{
		LOG_DEBUG << _T("Entity::addAction: a child with the name '") << pAction->getName() << 
			_T("' already exists. Action gets added but beware, duplicate names can become the cause of problems.")
	}
	auto it = mActions.find(pAction->getName())
	if (it != mActions.end())
	{
		pAction->initialize();
		pAction->setMaster(dynamic_pointer_cast<Entity>(shared_from_this(this)));
		mActions.insert(pAction->getName(), pAction);
	}
}

void Entity::removeAction(const SPtr<Action> pAction)
{
	removeAction(pAction->getName());
}

void Entity::removeAction(const String& name)
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		it.second->setMaster(nullptr);
		mActions.erase(it);
	}
}

void Entity::restartAction(const String& name)
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		it.second->restart();
	}
}

void Entity::pauseAction(const String& name)
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		it.second->pause();
	}
}

void Entity::resumeAction(const String& name)
{
	auto it = pAction.find(name)
	if (it != pAction.end())
	{
		it.second->resume();
	}
}

void Entity::addComponent(SPtr<Component> pComponent)
{
	auto it = mComponents.find(pComponent->getName())
	if (it != mComponents.end())
	{
		pComponent->initialize();
		pComponent->setMaster(dynamic_pointer_cast<Entity>(shared_from_this(this)));
		mComponents.insert(pComponent->getName(), pComponent);
	}
}

void Entity::removeComponent(const SPtr<Component> pComponent)
{
	removeComponent(pAction->getName());
}

void Entity::removeComponent(const String& name)
{
	auto it = mComponents.find(name)
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

void Entity::setDisabled(bool disabled)
{
	mVisible = !disabled;
}

bool Entity::isDisabled() const
{
	return !mVisible && m_IsFrozen;
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

SPtr<TransformComponent> Entity::getTransform() const
{
	return getComponent<TransformComponent>(TransformComponent::GUID);
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

void Entity::reset()
{
	for(auto child : mChildren)
	{
		child->reset();
	}
}

template <typename T>
SPtr<T> Entity::getChild(const String& name) const
{
	auto it = mChildren.find(name)
	if (it != mChildren.end())
	{
		if(typeid(*it->second.get()) == typeid(T))
		{
			return dynamic_pointer_cast<T>(it->second));
		}
	}
	return nullptr;
}

template <typename T>
SPtr<T> Entity::getAction(const String& name) const
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		Action* action = it->second.get(); 
		if(typeid(*it->second.get()) == typeid(T))
		{
			return dynamic_pointer_cast<T>(it->second));
		}
	}
	return nullptr;
}

template <typename T>
SPtr<T> Entity::getComponent(const String& name) const
{
	auto it = mComponents.find(name)
	if (it != mComponents.end())
	{
		if(typeid(*it->second.get()) == typeid(T))
		{
			return dynamic_pointer_cast<T>(it->second));
		}
	}
	return nullptr;
}
