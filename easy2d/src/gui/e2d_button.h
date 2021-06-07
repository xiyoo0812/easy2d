#ifndef BUTTON_H
#define BUTTON_H

#include "e2d_image.h"
#include "e2d_label.h"

namespace Easy2D
{
    enum class ButtonStatus
    {
        Normal,
        Pushed,
        Hover,
        Disable,
    };

    class UIButton : public UIWidget
    {
    public:
        UIButton(const String& name);
        ~UIButton() {}

        virtual bool setup();

        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);
        virtual BubbleType onLButtonDown(SPtr<MouseEvent> event);
        virtual void onMouseEnter(SPtr<MouseEvent> event);
        virtual void onMouseLeave(SPtr<MouseEvent> event);

        ButtonStatus getStatus();
        void setStatus(ButtonStatus status);

        SPtr<UIImage> getNormalImage();
        SPtr<UIImage> getPushedImage();
        SPtr<UIImage> getHoverImage();
        SPtr<UIImage> getDisableImage();
        SPtr<UILabel> getLabel();

        void setNormalImage(const String& normal);
        void setPushedImage(const String& pushed);
        void setHoverImage(const String& hover);
        void setDisableImage(const String& disable);

        void setText(const Wtring& text);
        const Wtring& getText();

        void setHoverFactor(float32 hf);
        void setPushedFactor(float32 pf);

    protected:
        void updateStatus(bool showOrHide);
        void updateSize(SPtr<UIImage> image);

    protected:
        float32 mHoverFactor = 1.1f;
        float32 mPushedFactor = 0.9f;
        SPtr<UILabel> mLabel = nullptr;
        SPtr<UIImage> mNormal = nullptr;
        SPtr<UIImage> mPushed = nullptr;
        SPtr<UIImage> mDisable = nullptr;
        SPtr<UIImage> mHover = nullptr;
        ButtonStatus  mStatus = ButtonStatus::Normal;

        inline static String NORMAL_NAME    = _T("__normal_image");
        inline static String PUSHED_NAME    = _T("__pushed_image");
        inline static String HOVER_NAME     = _T("__hover_image");
        inline static String DISABLE_NAME   = _T("__disable_image");
        inline static String LABEL_NAME     = _T("__lable_text");

    };
}

#endif
