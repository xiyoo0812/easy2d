#include "e2d_entity.h"

namespace Easy2D
{
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

