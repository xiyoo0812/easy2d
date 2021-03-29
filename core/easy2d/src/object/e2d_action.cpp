#include "e2d_action.h"
#include "e2d_entity.h"

/* Easy2D */
using namespace Easy2D;


Action::Action() : Object()
{

}

Action::Action(const tstring & name): Object(name)
{

}

Action::~Action()
{

}

void Action::restart()
{
	mPaused = false;
}

void Action::pause()
{
	mPaused = true;
}

void Action::resume()
{
	mPaused = false;
}

WPtr<Entity> Action::getMaster() const
{
	return mMaster;
}

void Action::setMaster(SPtr<Entity> pEntity)
{
	mMaster = pEntity;
}
