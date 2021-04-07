#include "e2d_widget.h"
#include "graphics/e2d_graphics_mgr.h"

/* Easy2D */
using namespace Easy2D;

uint64 UIObject::UNIQUE_ID_COUNTER = 0;

UIObject::UIObject(const tstring & name)
	: Object(name, _T("UI"))
	, mPosition()
	, mHorizontalAlignment(HorizontalAlignment::Left)
	, mVerticalAlignment(VerticalAlignment::Bottom)
	, m_UniqueUIObjectID(
		_T("UIObject") +
		string_cast<tstring>(UNIQUE_ID_COUNTER++)
		)
	, m_pParent(nullptr)
	, m_DebugDrawColor()
	, mDebugDrawFilled(false)
	, mDebugDraw(false)
{

}

UIObject::~UIObject()
{
}

void UIObject::initialize()
{
	reposition();
	repositionChildren();
}


void UIObject::setHorizontalAlignment(HorizontalAlignment alignment,bool redefineCenter)
{
	mHorizontalAlignment = alignment;
	translateXUI(mPosition.x, getDockDimensions());
}

void UIObject::setVerticalAlignment(VerticalAlignment alignment,bool redefineCenter)
{
	mVerticalAlignment = alignment;
	translateYUI(mPosition.y, getDockDimensions());
}

void UIObject::setAlignmentCentered(bool redefineCenter)
{
	setHorizontalAlignment(HorizontalAlignment::Center, redefineCenter);
	setVerticalAlignment(VerticalAlignment::Center, redefineCenter);
}

void UIObject::reposition()
{
	translate();
}

void UIObject::update(const uint32& escapeMs)
{
	Object::update(escapeMs);
}

void UIObject::draw()
{
	UIObject::draw();
}

UIObject * UIObject::getRootParent() const
{
	UIObject *pParent(nullptr);
	UIObject *pChild = const_cast<UIObject*>(this);

	do
	{
		pChild = pChild->getUIParent();
		if(pChild != nullptr)
		{
			pParent = pChild;
		}
	} while(pChild != nullptr);

	return pParent;
}

void UIObject:setRootWidget();
{
	mbRootWidget = true;
}

Vec2 UIObject::getDockDimensions() const
{
	if (mbRootWidget)
	{
		return GraphicsManager::getInstance()->getScreenResolution();
	}
	if(mRoot.expired())
	{
		dimensions = mParent.lock()->getDimensions();
	}
	return mDimensions;
}

void UIObject::translateUI(Pos& pos)
{
	
}

void UIObject::translate(const Vec2& translation)
{
	getTransform()->translate(translation);
}

void UIObject::translate(float32 x, float32 y)
{
	getTransform()->translate(x, y);
}

void UIObject::translate(const Vec2& translation, lay l)
{
	getTransform()->translate(translation, l);
}

void UIObject::translate(float32 x, float32 y, lay l)
{
	getTransform()->translate(x, y, l);
}

void UIObject::translate(const Pos& pos2D)
{
	getTransform()->translate(pos2D);
}

void UIObject::translateX(float32 x)
{
	getTransform()->translateX(x);
}

void UIObject::translateY(float32 y)
{
	getTransform()->translateY(y);
}

void UIObject::translateXUI(float32 x, const Vec2 & dimensions)
{
	switch(mHorizontalAlignment)
	{
		case HorizontalAlignment::Center:
			x += dimensions.x / 2;
			break;
		case HorizontalAlignment::Right:
			x += dimensions.x;
			break;
	}
	Entity::translateX(x);
}

void UIObject::translateYUI(float32 y, const Vec2 & dimensions)
{
	switch(mVerticalAlignment)
	{
		case VerticalAlignment::Center:
			y += dimensions.y / 2;
			break;
		case VerticalAlignment::Top:
			y += dimensions.y;
			break;
	}
	Entity::translateY(y);
}

void UIObject::repositionChildren()
{
	for(auto child : mChildren)
	{
		auto element = dynamic_cast<UIObject*>(child);
		if(element != nullptr)
		{
			element->reposition();
		}
	}
}

