#include "e2d_widget.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

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
