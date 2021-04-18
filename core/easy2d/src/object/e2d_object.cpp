#include "e2d_object.h"
#include "base\e2d_guid.h"

/* Easy2D */
using namespace Easy2D;

Object::Object()
{
    mGUID = BUILD_GUID();
}

Object::Object(const String& name)
    : mName(name)
{
    mGUID = BUILD_GUID();
}

Object::~Object()
{

}

bool Object::isInitialized() const
{
    return mInitialized;
}

bool Object::compareName(const String& name) const
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

bool Object::compareGUID(const uint64 guid) const
{
    return mGUID == guid;
}

uint64 Object::getGUID() const
{
    return mGUID;
}
