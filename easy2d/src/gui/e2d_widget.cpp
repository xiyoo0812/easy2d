#include "e2d_widget.h"
#include "base/e2d_input.h"

/* Easy2D */
using namespace Easy2D;

//------------------------------------------------------------------------------
UIWidget::UIWidget(const String& name) : Entity(name)
{

}

UIWidget::~UIWidget()
{
}

void UIWidget::initialize()
{
    Entity::initialize();
}

void UIWidget::update(const uint32& escapeMs)
{
    Entity::update(escapeMs);
}

//------------------------------------------------------------------------------
UIRoot::UIRoot() : UIWidget(GUID)
{

}

void UIRoot::initialize()
{
    InputSystem::getInstance()->addInputSink(std::dynamic_pointer_cast<InputSink>(shared_from_this()));
}
