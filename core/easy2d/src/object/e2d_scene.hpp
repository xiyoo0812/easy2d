#include "e2d_scene.h"

namespace Easy2D
{
    template <typename T>
    SPtr<T> Scene::getEntity(const uint64 guid) const
    {
        auto it = mEntitys.find(guid)
            if (it != mEntitys.end())
            {
                return dynamic_pointer_cast<T>(it->second);
            }
        return nullptr;
    }

    template <typename T>
    SPtr<T> Scene::getEntity(const String& name) const
    {
        for (auto entity : mEntitys)
        {
            if (entity.second->compareName(name))
            {
                return std::dynamic_pointer_cast<T>(entity.second);
            }
        }
        for (auto entity : mEntitys)
        {
            auto pEntity = entity->getChild<T>(name);
            if (pEntity)
            {
                return pEntity
            }
        }
        return nullptr;
    }
}


