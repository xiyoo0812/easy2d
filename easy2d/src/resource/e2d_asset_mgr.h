#ifndef ASSET_MGR_H
#define ASSET_MGR_H

#include "e2d_config.h"
#include "e2d_stream.h"

namespace Easy2D
{
    class AssetManager final : public Singleton<AssetManager>
    {
    public:
        friend Singleton<AssetManager>;
        ~AssetManager() {}

        const Path& getPath() const { return mBasePath; }
        void initialize(const Path& path) { mBasePath = path; }

        Vector<Path> enumerateDirectory(const Path& path, bool full = true);

        SPtr<Stream> loadAsset(const Path& path);
        bool loadAssetData(const Path& path, Bytes& data);

        SPtr<Stream> asyncAsset(const Path& path);

    private:
        AssetManager();
        Path mBasePath;
    };
}

#endif
