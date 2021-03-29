
#ifndef OBJECT_H
#define OBJECT_H

#include "e2d_config.h"

namespace Easy2D
{
	// 子类需要调用shared_from_this()
	class Object final : public enable_shared_from_this<Object>
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
