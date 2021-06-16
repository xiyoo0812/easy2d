#ifndef EDITBOX_H
#define EDITBOX_H

#include "e2d_label.h"
#include "e2d_image.h"
#include "base/e2d_stopwatch.h"

namespace Easy2D
{
    class UIEditbox : public UIImage
    {
    public:
        UIEditbox(const String& name);
        ~UIEditbox(){}

        virtual bool setup();
        virtual void update(const uint32& escapeMs, bool escapeSec);

        virtual BubbleType onChar(SPtr<KeyEvent> event);
        virtual BubbleType onKeyDown(SPtr<KeyEvent> event);
        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);
        virtual BubbleType onLButtonDown(SPtr<MouseEvent> event);

        void setGroundImage(const String& ground);
        void setFont(const String& fontName);

        void setText(const Wtring& text);
        const Wtring& getText();

    protected:
        void showText();

    protected:
        bool mbShowInput = false;
        uint32 mFocusIdx = 0;
        Wtring mEditText = L"";
        SPtr<UILabel> mLabel = nullptr;

        inline static String LABEL_NAME = _T("__lable_text");
    };
}

#endif
