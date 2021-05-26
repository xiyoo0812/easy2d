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
    };
}

#endif
