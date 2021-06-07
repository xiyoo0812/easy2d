#include "e2d_entity.h"

namespace Easy2D
{
    template <typename T>
    SPtr<T> Entity::createAction()
    {
        auto pAction = std::make_shared<T>();
        if (isActionNameExist(pAction->getName()))
        {
            LOG_WARN << _T("Entity::createAction: a child with the name '") << pAction->getName() <<
                _T("' already exists. Action gets added but beware, duplicate names can become the cause of problems.");
            return nullptr;
        }
        if (!pAction->setup(std::dynamic_pointer_cast<Entity>(shared_from_this())))
        {
            LOG_WARN << _T("Entity::createAction: setup '") << pAction->getName() << _T("' failed!");
            return nullptr;
        }
        mActions.push_back(pAction);
        return pAction;
    }

    template <typename T>
    SPtr<T> Entity::createComponent()
    {
        auto pComponent = std::make_shared<T>();
        if (isActionNameExist(pComponent->getName()))
        {
            LOG_WARN << _T("Entity::createComponent: a child with the name '") << pComponent->getName() <<
                _T("' already exists. Component gets added but beware, duplicate names can become the cause of problems.");
            return nullptr;
        }
        if (!pComponent->setup(std::dynamic_pointer_cast<Entity>(shared_from_this())))
        {
            LOG_WARN << _T("Entity::createComponent: setup '") << pComponent->getName() << _T("' failed!");
            return nullptr;
        }
        mComponents.push_back(pComponent);
        return pComponent;
    }

    template <typename T>
    SPtr<T> Entity::getChild(const uint64 guid) const
    {
        for (auto child : mChildrens)
        {
            if (child->compareGUID(guid))
            {
                return std::dynamic_pointer_cast<T>(child);
            }
        }
        for (auto child : mChildrens)
        {
            auto pChild = child->getChild<T>(guid);
            if (pChild)
            {
                return pChild
            }
        }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Entity::getChild(const String& name) const
    {
        for (auto child : mChildrens)
        {
            if (child->compareName(name))
            {
                return std::dynamic_pointer_cast<T>(child);
            }
        }
        for (auto child : mChildrens)
        {
            auto pChild = child->getChild<T>(name);
            if (pChild)
            {
                return pChild
            }
        }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Entity::getAction(const uint64 guid) const
    {
        for (auto pAction : mActions)
        {
            if (pAction->compareGUID(guid))
            {
                return std::dynamic_pointer_cast<T>(pAction);
            }
        }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Entity::getComponent(const String& name) const
    {
        for (auto pComponent : mComponents)
        {
            if (pComponent->compareName(name))
            {
                return std::dynamic_pointer_cast<T>(pComponent);
            }
        }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Entity::getComponent(const uint64 guid) const
    {
        for (auto pComponent : mComponents)
        {
            if (pComponent->compareGUID(guid))
            {
                return std::dynamic_pointer_cast<T>(pComponent);
            }
        }
        return nullptr;
    }
}

