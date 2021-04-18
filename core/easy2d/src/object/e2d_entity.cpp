#include "e2d_entity.h"
#include "e2d_scene.h"
#include "graphics/e2d_render_batch.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

Entity::Entity(void) : Object()
{
    addComponent(std::make_shared<TransformComponent>());
}

Entity::Entity(const String& name) : Object(name)
{
    addComponent(std::make_shared<TransformComponent>());
}

Entity::Entity(const String& name, const String& group)
    : Object(name), mGroup(group)
{
    addComponent(std::make_shared<TransformComponent>());
}

Entity::~Entity()
{
    mActions.clear();
    mChildrens.clear();
    mComponents.clear();
}

void Entity::destroy()
{
    if (!mParent.expired())
    {
        mParent.lock()->removeChild(mGUID);
    }
    if (!mScene.expired())
    {
        mScene.lock()->removeEntity(mGUID);
    }
}

void Entity::initialize()
{
    for (auto component : mComponents)
    {
        component->setMaster(std::dynamic_pointer_cast<Entity>(shared_from_this()));
    }
}

void Entity::sortChild()
{
    switch (RenderBatch::getInstance()->getSortingMode())
    {
    case RenderSortingMode::BackFront:
        std::sort(mChildrens.begin(), mChildrens.end(), [](SPtr<Entity> a, SPtr<Entity> b) -> bool
        {
            return a->getZorder() < b->getZorder();
        });
        break;
    case RenderSortingMode::FrontBack:
        std::sort(mChildrens.begin(), mChildrens.end(), [](SPtr<Entity> a, SPtr<Entity> b) -> bool
        {
            return a->getZorder() < b->getZorder();
        });
        break;
    default:
        break;
    }
}

void Entity::setPosition(const Vec2& pos)
{
    getTransform()->translate(pos);
}

void Entity::setPosition(float32 x, float32 y)
{
    getTransform()->translate(x, y);
}

void Entity::setPositionX(float32 x)
{
    getTransform()->translateX(x);
}

void Entity::setPositionY(float32 y)
{
    getTransform()->translateY(y);
}

const Vec2& Entity::getWorldPosition() const
{
    return getTransform()->getWorldPosition();
}

const Vec2& Entity::getLocalPosition() const
{
    return getTransform()->getLocalPosition();
}

const Vec2& Entity::getDimensions() const
{
    return getTransform()->getDimensions();
}

void Entity::update(const uint32& escapeMs)
{
    if (!mDisable)
    {
        for (auto action : mActions)
        {
            action->update(escapeMs);
        }
        for (auto component : mComponents)
        {
            component->update(escapeMs);
        }
        for (auto child : mChildrens)
        {
            child->update(escapeMs);
        }
    }
}


bool Entity::checkCulling(float32 left, float32 right, float32 top, float32 bottom)
{
    for (auto component : mComponents)
    {
        if (component->checkCulling(left, right, top, bottom))
        {
            return true;
        }
    }
    return false;
}

void Entity::draw()
{
    if (mVisible)
    {
        for (auto component : mComponents)
        {
            component->draw();
        }
        for (auto child : mChildrens)
        {
            child->draw();
        }
    }
}

void Entity::drawWithCulling(float32 left, float32 right, float32 top, float32 bottom)
{
    if (mVisible)
    {
        if (checkCulling(left, right, top, bottom))
        {
            for (auto component : mComponents)
            {
                component->draw();
            }
        }
        for (auto child : mChildrens)
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
    if (isChildNameExist(pChild->getName()))
    {
        LOG_WARN << _T("Entity::addChild: a child with the name '") << pChild->getName() <<
            _T("' already exists. Child gets added but beware, duplicate names can become the cause of problems.");
        return false;
    }
    pChild->setScene(mScene.lock());
    pChild->setParent(std::dynamic_pointer_cast<Entity>(shared_from_this()));
    mChildrens.push_back(pChild);
    pChild->initialize();
    sortChild();
    return true;
}

void Entity::removeChild(const SPtr<Entity> pEntity)
{
    removeChild(pEntity->getGUID());
}

void Entity::removeChild(const uint64 guid)
{
    auto it = std::find_if(mChildrens.begin(), mChildrens.end(), [&](SPtr<Entity> pEntity) -> bool
    {
        return pEntity->compareGUID(guid);
    });
    if (it != mChildrens.end())
    {
        mChildrens.erase(it);
        sortChild();
    }
}

void Entity::removeChild(const String& name)
{
    auto it = std::find_if(mChildrens.begin(), mChildrens.end(), [&](SPtr<Entity> pEntity) -> bool
    {
        return pEntity->compareName(name);
    });
    if (it != mChildrens.end())
    {
        mChildrens.erase(it);
        sortChild();
    }
}

const Vector<SPtr<Entity>>& Entity::getChildren() const
{
    return mChildrens;
}

void Entity::setChildDisabled(const uint64 guid, bool disabled)
{
    for (auto pEntity : mChildrens)
    {
        if (pEntity->compareGUID(guid))
        {
            pEntity->setDisabled(disabled);
            break;
        }
    }
}

void Entity::setChildVisible(const uint64 guid, bool visible)
{
    for (auto pEntity : mChildrens)
    {
        if (pEntity->compareGUID(guid))
        {
            pEntity->setVisible(visible);
            break;
        }
    }
}

void Entity::setChildrenDisabled(bool disable)
{
    for (auto child : mChildrens)
    {
        child->setDisabled(disable);
    }
}

void Entity::setChildrenVisible(bool visible)
{
    for (auto child : mChildrens)
    {
        child->setVisible(visible);
    }
}

bool Entity::addAction(SPtr<Action> pAction)
{
    if (isActionNameExist(pAction->getName()))
    {
        LOG_WARN << _T("Entity::addAction: a child with the name '") << pAction->getName() <<
            _T("' already exists. Action gets added but beware, duplicate names can become the cause of problems.");
        return false;
    }
    pAction->setMaster(std::dynamic_pointer_cast<Entity>(shared_from_this()));
    mActions.push_back(pAction);
    pAction->initialize();
    return true;
}

void Entity::removeAction(const SPtr<Action> pAction)
{
    removeAction(pAction->getGUID());
}

void Entity::removeAction(const uint64 guid)
{
    auto it = std::find_if(mActions.begin(), mActions.end(), [&](SPtr<Action> pAction) -> bool
    {
        return pAction->compareGUID(guid);
    });
    if (it != mActions.end())
    {
        (*it)->setMaster(nullptr);
        mActions.erase(it);
    }
}

void Entity::removeAction(const String& name)
{
    auto it = std::find_if(mActions.begin(), mActions.end(), [&](SPtr<Action> pAction) -> bool
    {
        return pAction->compareName(name);
    });
    if (it != mActions.end())
    {
        (*it)->setMaster(nullptr);
        mActions.erase(it);
    }
}

void Entity::restartAction(const uint64 guid)
{
    for (auto pAction : mActions)
    {
        if (pAction->compareGUID(guid))
        {
            pAction->restart();
            break;
        }
    }
}

void Entity::pauseAction(const uint64 guid)
{
    for (auto pAction : mActions)
    {
        if (pAction->compareGUID(guid))
        {
            pAction->pause();
            break;
        }
    }
}

void Entity::resumeAction(const uint64 guid)
{
    for (auto pAction : mActions)
    {
        if (pAction->compareGUID(guid))
        {
            pAction->resume();
            break;
        }
    }
}

bool Entity::addComponent(SPtr<Component> pComponent)
{
    if (isActionNameExist(pComponent->getName()))
    {
        LOG_WARN << _T("Entity::addComponent: a child with the name '") << pComponent->getName() <<
            _T("' already exists. Component gets added but beware, duplicate names can become the cause of problems.");
        return false;
    }
    mComponents.push_back(pComponent);
    pComponent->initialize();
    return true;
}

void Entity::removeComponent(const SPtr<Component> pComponent)
{
    removeComponent(pComponent->getGUID());
}

void Entity::removeComponent(const uint64 guid)
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(), [&](SPtr<Component> pComponent) -> bool
    {
        return pComponent->compareGUID(guid);
    });
    if (it != mComponents.end())
    {
        mComponents.erase(it);
    }
}

void Entity::removeComponent(const String& name)
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(), [&](SPtr<Component> pComponent) -> bool
    {
        return pComponent->compareName(name);
    });
    if (it != mComponents.end())
    {
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
    for (auto pChild : mChildrens)
    {
        if (pChild->compareName(name))
        {
            return true;
        }
    }
    return false;
}

bool Entity::isActionNameExist(const String& name) const
{
    for (auto pAction : mActions)
    {
        if (pAction->compareName(name))
        {
            return true;
        }
    }
    return false;
}

bool Entity::isComponentNameExist(const String& name) const
{
    for (auto pComponent : mComponents)
    {
        if (pComponent->compareName(name))
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
    if (!mParent.expired())
    {
        mParent.lock()->sortChild();
        return;
    }
    if (!mScene.expired())
    {
        mScene.lock()->sortEntity();
    }
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
        for (auto child : mChildrens)
        {
            child->setScene(pScene);
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
    for (auto child : mChildrens)
    {
        child->reset();
    }
}

void Entity::recalculateDimensions()
{
    Vec2 dim(0, 0);
    auto transform = getTransform();
    for (auto comp : mComponents)
    {
        if (comp != transform)
        {
            Vec2 temp = comp->getDimensions();
            if (temp.x > dim.x)
            {
                dim.x = temp.x;
            }
            if (temp.y > dim.y)
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

