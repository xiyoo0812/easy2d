#include "e2d_scene.h"

namespace Easy2D
{
    template <typename T>
    SPtr<T> Scene::getEntity(const String& name) const
    {
        for (auto entity : mEntitys)
        {
            if (entity->compareName(name))
            {
                return std::dynamic_pointer_cast<T>(entity);
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

    template <typename T>
    SPtr<T> Scene::getEntity(const uint64 guid) const
    {
        for (auto entity : mEntitys)
        {
            if (entity->compareGUID(guid))
            {
                return std::dynamic_pointer_cast<T>(entity);
            }
        }
        for (auto entity : mEntitys)
        {
            auto pEntity = entity->getChild<T>(guid);
            if (pEntity)
            {
                return pEntity
            }
        }
        return nullptr;
    }
}


