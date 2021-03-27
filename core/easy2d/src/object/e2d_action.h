#ifndef ACTION_H
#define ACTION_H

#include "e2d_object.h"

namespace Easy2D
{
	class Entity;
	class Action : public Object
	{
	public:
		Action();
		Action(const String& name);
		virtual ~Action();

		void destroy();

		virtual void restart();
		virtual void pause();
		virtual void resume();
		virtual void update(const uint32& escapeMs) = 0;

		SPtr<Entity> getMaster() const;
		void setMaster(Entity* pMaster);

	protected:
		virtual void initialize() = 0;

		bool mPaused;
		SPtr<Entity> mMaster = nullptr;
	};
}

#endif
