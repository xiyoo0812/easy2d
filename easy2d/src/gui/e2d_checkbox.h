#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "e2d_image.h"
#include "e2d_label.h"

namespace Easy2D
{
    enum class ChoseStatus
    {
        ChoseOff,
        ChoseOn,
        Disable,
    };

    class UICheckBox : public UIWidget
    {
    public:
        UICheckBox(const String& name);
        ~UICheckBox() {}

        virtual bool setup();

        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);

        virtual void select();
        void unselect();
        bool isSelected();

        ChoseStatus getStatus();
        void setStatus(ChoseStatus status);

        SPtr<UIImage> getOffImage();
        SPtr<UIImage> getOnImage();

        void setOnImage(const String& on);
        void setOffImage(const String& off);

    protected:
        void updateStatus(bool showOrHide);
        void updateSize(SPtr<UIImage> image);

    protected:
        SPtr<UIImage> mChoseOff = nullptr;
        SPtr<UIImage> mChoseOn = nullptr;
        ChoseStatus mStatus = ChoseStatus::ChoseOff;

        inline static String CHOSEOFF_NAME  = _T("__choseoff_image");
        inline static String CHOSEON_NAME   = _T("__choseon_image");
    };

    class UISwitch : public UICheckBox
    {
    public:
        UISwitch(const String& name);
        ~UISwitch() {}
    };
}

#endif
