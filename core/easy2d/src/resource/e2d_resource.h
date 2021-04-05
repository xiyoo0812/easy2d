#ifndef RESOURCE_H
#define RESOURCE_H

#include "e2d_config.h"

namespace Easy2D
{
	class Resource
	{
	public:
		Resource(String path);
		virtual ~Resource() {}

		virtual bool load() = 0;
		String& getPath() const { return mPath; }

	private:
		String mPath;
	};
}

#endif
