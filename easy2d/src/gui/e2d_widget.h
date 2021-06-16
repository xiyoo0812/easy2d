#ifndef WIDGET_H
#define WIDGET_H

#include "object/e2d_entity.h"
#include "base/e2d_singleton.h"

namespace Easy2D
{
    class UIWidget : public Entity
    {
    public:
        UIWidget(const String& name);
        virtual ~UIWidget();

        virtual BubbleType onMouseMove(SPtr<MouseEvent> event);
    };

    class UIRoot : public UIWidget, public Singleton<UIRoot>
    {
    public:
        friend class Singleton<UIRoot>;

        ~UIRoot() {}

        virtual bool setup();

        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);

        void setCtrlWidget(SPtr<UIWidget> widget);
        void setFocusWidget(SPtr<UIWidget> widget);

    private:
        UIRoot();
        SPtr<UIWidget> mCtrlWidget;
        SPtr<UIWidget> mFocusWidget;

        inline static String GUID = "gui_root";
    };
}

#endif
