#include "e2d_object.h"

/* Easy2D */
using namespace Easy2D;

Object::Object()
{
	mGUID = NEW_GUID();
}

Object::Object(const String& name)
	: mName(name)
{
	mGUID = NEW_GUID();
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
