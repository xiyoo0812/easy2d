#include "e2d_root.h"

/* Easy2D */
using namespace Easy2D;

UIRoot::UIRoot() : Entity(GUID)
{

}

void UIRoot::initialize()
{
    Entity::initialize();
}

BubbleType UIRoot::onHandlerEvent(SPtr<Event> event)
{
    return BubbleType::Next;
}

void UIRoot::update(const uint32& escapeMs)
{
    Entity::update(escapeMs);
}
