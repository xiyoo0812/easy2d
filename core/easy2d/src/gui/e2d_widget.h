#ifndef WIDGET_H
#define WIDGET_H

#include "object/e2d_entity.h"

namespace Easy2D
{
    class UIWidget : public Entity
    {
    public:
        UIWidget(const String& name);
        virtual ~UIWidget();

        virtual void initialize();
        virtual void update(const uint32& escapeMs);

        virtual void setPosition(const Vec2& translation);
        virtual void setPosition(float32 x, float32 y);
        virtual void setPositionX(float32 x);
        virtual void setPositionY(float32 y);

        virtual void setHorizontalAlignment(HorizontalAlign alignment, bool redefineCenter = true);
        virtual void setVerticalAlignment(VerticalAlign alignment, bool redefineCenter = true);
        void setAlignmentCentered(bool redefineCenter = true);

        void reposition();
        void setRootWidget();

    protected:
        Vec2 getDockDimensions() const;
        float32 translateUIX(float32 x);
        float32 translateUIY(float32 y);

        void repositionChildren();

        bool mbRootWidget = false;
        VerticalAlign mVerticalAlignment;
        HorizontalAlign mHorizontalAlignment;
    };
}

#endif
