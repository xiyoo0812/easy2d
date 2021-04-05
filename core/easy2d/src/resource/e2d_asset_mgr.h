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
		
		String& getPath() const { return mBasePath; }
		const setPath(const String& path) { mBasePath = path; }

		SPtr<DataStream> loadAsset(const Path& path);
		
		SPtr<DataStream> asyncAsset(const Path& path);

	private:
		AssetManager();
		Path& mBasePath;
	};
}

#endif
