
#ifndef OBJECT_H
#define OBJECT_H

#include "e2d_config.h"

namespace Easy2D
{
	class Object
	{
	public:
		Object();
		Object(const String& name);
		virtual ~Object();

		String& getName() const;
		void setName(String& name);
		bool compareName(const String& name);

		bool isInitialized() const;
		virtual void destroy() = 0;

	protected:
		String mName = "";
		bool mInitialized = false;
	};
}

#endif
