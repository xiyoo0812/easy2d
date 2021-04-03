#include "e2d_entity.h"

namespace Easy2D
{
    template <typename T>
    SPtr<T> Entity::getChild(const uint64 guid) const
    {
        auto it = mChildren.find(guid);
        if (it != mChildren.end())
        {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Entity::getChild(const String& name) const
    {
        for (auto child : mChildren)
        {
            if (child->compareName(name))
            {
                return std::dynamic_pointer_cast<T>(it->second);
            }
        }
        for (auto child : mChildren)
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
        auto it = mActions.find(guid)
            if (it != mActions.end())
            {
                return std::dynamic_pointer_cast<T>(it->second);
            }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Entity::getComponent(const String& name) const
    {
        for (auto pComponent : mComponents)
        {
            if (pComponent.second->compareName(name))
            {
                return std::dynamic_pointer_cast<T>(pComponent.second);
            }
        }
        return nullptr;
    }
}

