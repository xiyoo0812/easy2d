#ifndef EDITBOX_H
#define EDITBOX_H

#include "e2d_label.h"
#include "e2d_image.h"

namespace Easy2D
{
    class UIEditbox : public UIImage
    {
    public:
        UIEditbox(const String& name);
        ~UIEditbox(){}

        virtual bool setup();

        virtual BubbleType onChar(SPtr<KeyEvent> event);
        virtual BubbleType onKeyUp(SPtr<KeyEvent> event);
        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);

        void setGroundImage(const String& ground);

        void setText(const Wtring& text);
        const Wtring& getText();

    protected:
        SPtr<UILabel> mLabel = nullptr;

        inline static String LABEL_NAME = _T("__lable_text");
    };
}

#endif
