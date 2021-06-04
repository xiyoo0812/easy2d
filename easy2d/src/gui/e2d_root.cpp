#include "e2d_root.h"
#include "base/e2d_input.h"

/* Easy2D */
using namespace Easy2D;

UIRoot::UIRoot() : Entity(GUID)
{

}

void UIRoot::initialize()
{
    InputSystem::getInstance()->addInputSink(std::dynamic_pointer_cast<InputSink>(shared_from_this()));
    Entity::initialize();
}
