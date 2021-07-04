#ifndef SCROLL_VIEW_H
#define SCROLL_VIEW_H

#include "e2d_widget.h"

namespace Easy2D
{
    class UIScrollView : public UIWidget
    {
    public:
        UIScrollView(const String& name);
        ~UIScrollView() {}

        void setScrollPercent(const Vec2& pos);
        const Vec2& getScrollPercent() const;

        void showVerticalBar(bool bShow);
        void showHorizontalBar(bool bShow);

        virtual void onSizeChanged(const Vec2& pos);
        virtual void onContentChanged(const Vec2& contentSize);

    protected:
        void updateScrollPercent(const Vec2& size, const Vec2& contentSize);

    protected:
        bool mbShowVerticalBar = false;
        bool mbShowHorizontalBar = false;
        Vec2 mScrollPos = VEC2_ZERO;
        Vec2 mScrollPercent = VEC2_ZERO;
    };
}

#endif
