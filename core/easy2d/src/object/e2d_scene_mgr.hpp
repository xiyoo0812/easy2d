#include "e2d_scene_mgr.h"

namespace Easy2D
{
    template <typename T>
    SPtr<T> SceneManager::getScene(const uint64 guid)
    {
        auto it = mScenes.find(guid);
        if (it != mScenes.end())
        {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }
}
