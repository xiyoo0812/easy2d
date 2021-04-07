#include "e2d_entity.h"
#include "e2d_scene.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

Entity::Entity(void) : Object()
{
}

Entity::Entity(const String& name) : Object(name)
{
}

Entity::Entity(const String& name, const String& group)
	: Object(name), mGroup(group)
{
}

Entity::~Entity()
{
	mActions.clear();
	mChildren.clear();
	mComponents.clear();
}

void Entity::destroy()
{
	if(!mParent.expired())
	{
		mParent.lock()->removeChild(mGUID);
	}
	if(!mScene.expired())
	{
		mScene.lock()->removeEntity(mGUID);
	}
}

void Entity::initialize()
{
	addComponent(std::make_shared<TransformComponent>());
}

void Entity::translate(const Vec2& translation)
{
	getTransform()->translate(translation);
}

void Entity::translate(float32 x, float32 y)
{
	getTransform()->translate(x, y);
}

void Entity::translate(const Vec2& translation, lay l)
{
	getTransform()->translate(translation, l);
}

void Entity::translate(float32 x, float32 y, lay l)
{
	getTransform()->translate(x, y, l);
}

void Entity::translate(const Pos& pos2D)
{
	getTransform()->translate(pos2D);
}

void Entity::translateX(float32 x)
{
	getTransform()->translateX(x);
}

void Entity::translateY(float32 y)
{
	getTransform()->translateY(y);
}

void Entity::translateL(lay l)
{
	getTransform()->translateL(l);
}

const Pos& Entity::getWorldPosition() const
{
	return getTransform()->getWorldPosition();
}

const Pos& Entity::getLocalPosition() const
{
	return getTransform()->getLocalPosition();
}

const Vec2& Entity::getDimensions() const
{
	return getTransform()->getDimensions();
}

void Entity::update(const uint32& escapeMs)
{
	if(!mDisable)
	{
		for(auto action : mActions)
		{
			action.second->update(escapeMs);
		}
		for(auto component : mComponents)
		{
			component.second->update(escapeMs);
		}
		for(auto child : mChildren)
		{
			child.second->update(escapeMs);
		}
	}
}


bool Entity::checkCulling(float32 left, float32 right, float32 top, float32 bottom)
{
	for (auto component : mComponents)
	{
		if(component.second->checkCulling(left, right, top, bottom))
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
			component.second->draw();
		}
		for(auto child : mChildren)
		{
			child.second->draw();
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
				component.second->draw();
			}
		}
		for(auto child : mChildren)
		{
			child.second->drawWithCulling(left, right, top, bottom);
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
	if(isChildNameExist(pChild->getName()))
	{
        LOG_WARN << _T("Entity::addChild: a child with the name '") << pChild->getName() <<
            _T("' already exists. Child gets added but beware, duplicate names can become the cause of problems.");
		return false;
	}
	pChild->setScene(mScene.lock());
	pChild->setParent(std::dynamic_pointer_cast<Entity>(shared_from_this()));
	mChildren.insert(std::make_pair(pChild->getGUID(), pChild));
	pChild->initialize();
	return true;
}

void Entity::removeChild(const SPtr<Entity> pEntity)
{
	removeChild(pEntity->getGUID());
}

void Entity::removeChild(const uint64 guid)
{
    auto it = mChildren.find(guid);
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
    auto it = mChildren.find(guid);
	if (it != mChildren.end())
	{
		it->second->setDisabled(disabled);
	}
}

void Entity::setChildVisible(const uint64 guid, bool visible)
{
    auto it = mChildren.find(guid);
	if (it != mChildren.end())
	{
		it->second->setVisible(visible);
	}
}

void Entity::setChildrenDisabled(bool disable)
{
	for(auto child : mChildren)
	{
		child.second->setDisabled(disable);
	}
}

void Entity::setChildrenVisible(bool visible)
{
	for(auto child : mChildren)
	{
		child.second->setVisible(visible);
	}
}

bool Entity::addAction(SPtr<Action> pAction)
{
	if(isActionNameExist(pAction->getName()))
	{
        LOG_WARN << _T("Entity::addAction: a child with the name '") << pAction->getName() <<
            _T("' already exists. Action gets added but beware, duplicate names can become the cause of problems.");
		return false;
	}
	pAction->setMaster(std::dynamic_pointer_cast<Entity>(shared_from_this()));
	mActions.insert(std::make_pair(pAction->getGUID(), pAction));
	pAction->initialize();
	return true;
}

void Entity::removeAction(const SPtr<Action> pAction)
{
	removeAction(pAction->getGUID());
}

void Entity::removeAction(const uint64 guid)
{
    auto it = mActions.find(guid);
	if (it != mActions.end())
	{
		it->second->setMaster(nullptr);
		mActions.erase(it);
	}
}

void Entity::restartAction(const uint64 guid)
{
    auto it = mActions.find(guid);
	if (it != mActions.end())
	{
		it->second->restart();
	}
}

void Entity::pauseAction(const uint64 guid)
{
    auto it = mActions.find(guid);
	if (it != mActions.end())
	{
		it->second->pause();
	}
}

void Entity::resumeAction(const uint64 guid)
{
	auto it = mActions.find(guid);
	if (it != mActions.end())
	{
		it->second->resume();
	}
}

bool Entity::addComponent(SPtr<Component> pComponent)
{
	if(isActionNameExist(pComponent->getName()))
	{
        LOG_WARN << _T("Entity::addComponent: a child with the name '") << pComponent->getName() <<
            _T("' already exists. Component gets added but beware, duplicate names can become the cause of problems.");
		return false;
	}
	pComponent->setMaster(std::dynamic_pointer_cast<Entity>(shared_from_this()));
	mComponents.insert(std::make_pair(pComponent->getGUID(), pComponent));
	pComponent->initialize();
	return true;
}

void Entity::removeComponent(const SPtr<Component> pComponent)
{
	removeComponent(pComponent->getGUID());
}

void Entity::removeComponent(const uint64 guid)
{
    auto it = mComponents.find(guid);
	if (it != mComponents.end())
	{
		it->second->setMaster(nullptr);
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
		if(pChild.second->compareName(name))
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
		if(pAction.second->compareName(name))
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
		if(pComponent.second->compareName(name))
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

int32 Entity::getZorder() const
{
	return mZorder;
}

void Entity::setZorder(int32 order)
{
	mZorder = order;
}

SPtr<Scene> Entity::getScene() const
{
	return mScene.lock();
}

void Entity::setScene(SPtr<Scene> pScene)
{
	if (mScene.lock() != pScene)
	{
		mScene = pScene;
		for(auto child : mChildren)
		{
			child.second->setScene(pScene);
		}
	}
}

SPtr<Entity> Entity::getParent() const
{
	return mParent.lock();
}

void Entity::setParent(SPtr<Entity> pEntity)
{
	mParent = pEntity;
}

void Entity::reset()
{
	for(auto child : mChildren)
	{
		child.second->reset();
	}
}

void Entity::recalculateDimensions()
{
	Vec2 dim(0, 0);
	auto transform = getTransform();
	for(auto comp : mComponents)
	{
		if(comp.second != transform)
		{
			Vec2 temp = comp.second->getDimensions();
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

