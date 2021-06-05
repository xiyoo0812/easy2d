#include "e2d_entity.h"
#include "e2d_scene.h"
#include "graphics/e2d_render_batch.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

Entity::Entity(void) : Object()
{
    mTransform = std::make_shared<TransformComponent>();
    addComponent(mTransform);
}

Entity::Entity(const String& name) : Object(name)
{
    mTransform = std::make_shared<TransformComponent>();
    addComponent(mTransform);
}

Entity::Entity(const String& name, const String& group)
    : Object(name), mGroup(group)
{
    mTransform = std::make_shared<TransformComponent>();
    addComponent(mTransform);
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
        mScene.lock()->removeChild(mGUID);
    }
}

void Entity::initialize()
{
    if (!mInitialized)
    {
        for (auto component : mComponents)
        {
            component->setMaster(std::dynamic_pointer_cast<Entity>(shared_from_this()));
            component->initialize();
        }
        mInitialized = true;
    }
}

BubbleType Entity::handleInputBefor(SPtr<KeyEvent> event, VisibleType& visable)
{
    visable = mVisible;
    if (mDisable || !mFocus || mVisible == VisibleType::Hidden || mVisible == VisibleType::NotHitAll)
    {
        return BubbleType::Return;
    }
    return BubbleType::Continue;
}

BubbleType Entity::handleInputBefor(SPtr<MouseEvent> event, VisibleType& visable)
{
    visable = mVisible;
    if (mDisable || mVisible == VisibleType::Hidden || mVisible == VisibleType::NotHitAll || !isInRect(event->mPos))
    {
        return BubbleType::Return;
    }
    return BubbleType::Continue;
}

BubbleType Entity::handleChildInput(SPtr<KeyEvent> event)
{
    for (auto it = mChildrens.rbegin(), itEnd = mChildrens.rend(); it != itEnd; ++it)
    {
        SPtr<Entity> child = *it;
        BubbleType bubble = child->handleInput(event);
        if (bubble == BubbleType::Break)
        {
            return bubble;
        }
    }
    return BubbleType::Continue;
}

BubbleType Entity::handleChildInput(SPtr<MouseEvent> event)
{
    for (auto it = mChildrens.rbegin(), itEnd = mChildrens.rend(); it != itEnd; ++it)
    {
        SPtr<Entity> child = *it;
        BubbleType bubble = child->handleInput(event);
        if (bubble == BubbleType::Break)
        {
            return bubble;
        }
    }
    return BubbleType::Continue;
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

void Entity::setMirror(bool x, bool y)
{
    mTransform->mirror(x, y);
}

void Entity::setMirrorX(bool x)
{
    mTransform->mirrorX(x);
}
void Entity::setMirrorY(bool y)
{
    mTransform->mirrorY(y);
}

void Entity::setScale(const Vec2& scale)
{
    mTransform->scale(scale);
}

void Entity::setScale(float32 x, float32 y)
{
    mTransform->scale(x, y);
}

void Entity::setScale(float32 u)
{
    mTransform->scale(u, u);
}

void Entity::setScaleX(float32 x)
{
    mTransform->scaleX(x);
}

void Entity::setScaleY(float32 y)
{
    mTransform->scaleY(y);
}

void Entity::setPosition(const Vec2& pos)
{
    mTransform->translate(pos);
}

void Entity::setPosition(float32 x, float32 y)
{
    mTransform->translate(x, y);
}

void Entity::setPositionX(float32 x)
{
    mTransform->translateX(x);
}

void Entity::setPositionY(float32 y)
{
    mTransform->translateY(y);
}

void Entity::setAnchor(const Vec2& pos)
{
    mTransform->setAnchor(pos);
}

void Entity::setAnchor(float32 x, float32 y)
{
    mTransform->setAnchor(x, y);
}

void Entity::setAnchorX(float32 x)
{
    mTransform->setAnchorX(x);
}

void Entity::setAnchorY(float32 y)
{
    mTransform->setAnchorY(y);
}

const Vec2& Entity::getAbsolute() const
{
    return mTransform->getAbsolute();
}

const Vec2& Entity::getPosition() const
{
    return mTransform->getPosition();
}

void Entity::setSizeX(float32 x)
{
    mTransform->setSizeX(x);
}

void Entity::setSizeY(float32 y)
{
    mTransform->setSizeX(y);
}

void Entity::setSize(const Vec2& dim)
{
    mTransform->setSize(dim);
}

const Rect Entity::getRect() const
{
    return mTransform->getRect();
}

const Vec2& Entity::getSize() const
{
    return mTransform->getSize();
}

float32 Entity::getWidth() const
{
    return mTransform->getWidth();
}

float32 Entity::getHeight() const
{
    return mTransform->getHeight();
}

void Entity::update(const uint32& escapeMs)
{
    if (isEnabled() && isVisible())
    {
        for (auto action : mActions)
        {
            action->update(escapeMs);
        }
        for (auto component : mComponents)
        {
            component->update(escapeMs);
        }
        Vec2 dim = getSize();
        for (auto child : mChildrens)
        {
            child->update(escapeMs);
        }
    }
}

void Entity::setDockerAlign(DockerAlign align)
{
    mTransform->setDockerAlign(align);
}

DockerAlign Entity::getDockerAlign() const
{
    return mTransform->getDockerAlign();
}

bool Entity::checkCulling(float32 left, float32 top, float32 right, float32 bottom)
{
    Vec2 dim = getSize();
    Vec2 pos = getPosition();
    if ((pos.x <= right && pos.x >= left) && (pos.y <= bottom && pos.y >= top))
    {
        return true;
    }
    if ((pos.x + dim.x <= right && pos.x + dim.x >= left) && (pos.y + dim.y <= bottom && pos.y + +dim.y >= top))
    {
        return true;
    }
    return false;
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

void Entity::setChildVisible(const uint64 guid, VisibleType visible)
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

void Entity::setChildrenVisible(VisibleType visible)
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
    if (mInitialized)
    {
        pComponent->initialize();
    }
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
bool Entity::isInRect(const Vec2& pos) const
{
    return mTransform->isInRect(pos);
}

void Entity::setFocus(bool focus)
{
    mFocus = focus;
}

bool Entity::isFocus() const
{
    return mFocus;
}

void Entity::setDisabled(bool disabled)
{
    mDisable = disabled;
}

bool Entity::isEnabled() const
{
    return !mDisable;
}

bool Entity::isDisabled() const
{
    return mDisable;
}

bool Entity::isVisible() const
{
    return (mVisible != VisibleType::Hidden);
}

void Entity::setVisible(VisibleType visible)
{
    mVisible = visible;
}

VisibleType Entity::getVisible() const
{
    return mVisible;
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
        mScene.lock()->sortChild();
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
    if (pEntity != nullptr)
    {
        mTransform->setChanged(true);
    }
}

void Entity::reset()
{
    for (auto child : mChildrens)
    {
        child->reset();
    }
}

SPtr<TransformComponent> Entity::getTransform() const
{
    return mTransform;
}

