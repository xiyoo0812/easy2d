#include "e2d_scrollview.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UIScrollView::UIScrollView(const String& name) : UIWidget(name)
{

}

void UIScrollView::setScrollPercent(const Vec2& percent)
{
    if (mScrollPercent != percent)
    {
        mScrollPercent.x = std::max(0.0f, percent.x);
        mScrollPercent.x = std::min(100.0f, percent.x);
        mScrollPercent.y = std::max(0.0f, percent.y);
        mScrollPercent.y = std::min(100.0f, percent.y);
        updateScrollPercent(mTransform->getSize());
    }
}

const Vec2& UIScrollView::getScrollPercent() const
{
    return mScrollPercent;
}

void UIScrollView::showVerticalBar(bool bShow)
{
    mbShowVerticalBar = bShow;
}

void UIScrollView::showHorizontalBar(bool bShow)
{
    mbShowHorizontalBar = bShow;
}

void UIScrollView::onSizeChanged(const Vec2& size)
{
    updateScrollPercent(size, getContentSize());
}

void UIScrollView::onContentChanged(const Vec2& contentSize)
{
    updateScrollPercent(getSize(), contentSize);
}

void UIScrollView::updateScrollPercent(const Vec2& size, const Vec2& contentSize)
{
    auto dx = contentSize.x - size.x;
    auto dy = contentSize.y - size.y;
    mScrollPos = Vec2(dx * mScrollPercent.x, dy * mScrollPercent.y);
    //todo ¸üĞÂscrollbarÎ»ÖÃ
    mTransform->setChanged(true);
}
