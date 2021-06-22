#include "e2d_scrollview.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UIScrollView::UIScrollView(const String& name) : UIWidget(name)
{

}

void UIScrollView::setContentSize(const Vec2& dim)
{
    if (mContentSize != dim)
    {
        auto size = mTransform->getSize();
        mContentSize = Vec2(std::max(size.x, dim.x), std::max(size.y, dim.y));
        updateScrollPercent(size);
    }
}

const Vec2& UIScrollView::getContentSize() const
{
    if (mContentSize == VEC2_ZERO)
    {
        return mTransform->getSize();
    }
    return mContentSize;
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
    if (size.x > mContentSize.x || size.y > mContentSize.y)
    {
        mContentSize = Vec2(std::max(size.x, mContentSize.x), std::max(size.y, mContentSize.y));
        updateScrollPercent(size);
    }
}

void UIScrollView::updateScrollPercent(const Vec2& size)
{
    auto dx = mContentSize.x - size.x;
    auto dy = mContentSize.y - size.y;
    mScrollPos = Vec2(dx * mScrollPercent.x, dy * mScrollPercent.y);
    //todo ¸üĞÂscrollbarÎ»ÖÃ
    mTransform->setChanged(true);
}
