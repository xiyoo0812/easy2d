#include "e2d_asset_mgr.h"

using namespace Easy2D;

AssetManager::AssetManager()
{
}

SPtr<DataStream> AssetManager::loadAsset(const Path& path)
{
#ifdef WIN32
    Path fullPath = mBasePath / path;
    auto stream = std::make_shared<FileStream>(fullPath);
    return std::dynamic_pointer_cast<DataStream>(stream);
#endif
    return nullptr;
}

SPtr<DataStream> AssetManager::asyncAsset(const Path& path)
{
    return nullptr;
}
