#ifndef SCROLL_VIEW_H
#define SCROLL_VIEW_H

#include "e2d_widget.h"

namespace Easy2D
{
    class UIScrollView : public UIWidget
    {
    public:
        UIScrollView(const String& name);
        ~UIScrollView(){}

        void setContentSize(const Vec2& dim);
        const Vec2& getContentSize() const;

        void setScrollPercent(const Vec2& pos);
        const Vec2& getScrollPercent() const;

        void showVerticalBar(bool bShow);
        void showHorizontalBar(bool bShow);

        virtual void onSizeChanged(const Vec2& pos);

    protected:
        void updateScrollPercent(const Vec2& size);

    protected:
        bool mbShowVerticalBar = false;
        bool mbShowHorizontalBar = false;
        Vec2 mScrollPos = VEC2_ZERO;
        Vec2 mContentSize = VEC2_ZERO;
        Vec2 mScrollPercent = VEC2_ZERO;
    };
}

#endif
