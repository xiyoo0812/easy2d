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

		virtual void initialize() = 0;

		virtual void restart();
		virtual void pause();
		virtual void resume();
		virtual void update(const uint32& escapeMs) = 0;

		WPtr<Entity> getMaster() const;
		void setMaster(SPtr<Entity> pMaster);

	protected:
		bool mPaused;
		WPtr<Entity> mMaster = nullptr;
	};
}

#endif
