#include "e2d_object.h"

/* Easy2D */
using namespace Easy2D;

Object::Object()
{
	mGUID = MAKE_GUID(RandIntDist(0, MAX_WORLD), RandIntDist(0, MAX_TYPE));
}

Object::Object(const String& name)
	: mName(name)
{
	mGUID = MAKE_GUID(RandIntDist(0, MAX_WORLD), RandIntDist(0, MAX_TYPE));
}

Object::~Object()
{

}

bool Object::isInitialized() const
{
	return mInitialized;
}

bool Object::compareName(const String& name)
{
	return mName == name;
}

String& Object::getName() const
{
	return mName;
}

void Object::setName(const String& name)
{
	mName = name;
}

bool Object::compareGUID(const uint64 guid)
{
	return mGUID == guid;
}

uint64 Object::getGUID() const
{
	return mGUID;
}
