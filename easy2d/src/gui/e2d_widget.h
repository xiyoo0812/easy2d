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

        virtual BubbleType onMouseMove(SPtr<MouseEvent> event);
    };

    class UIRoot : public UIWidget
    {
    public:
        UIRoot();
        ~UIRoot() {}

        virtual void initialize();

        inline static String GUID = "gui_root";
    };
}

#endif
