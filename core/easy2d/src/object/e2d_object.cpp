#include "e2d_object.h"

/* Easy2D */
using namespace Easy2D;

Object::Object()
{

}

Object::Object(const String& name)
	: mName(name)
{

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

const String& Object::getName() const
{
	return mName;
}

void Object::setName(const String& name)
{
	mName = name;
}
