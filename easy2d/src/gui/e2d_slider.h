#ifndef SLIDER_H
#define SLIDER_H

#include "e2d_image.h"
#include "e2d_button.h"

namespace Easy2D
{
    class UISlider : public UIImage
    {
    public:
        UISlider(const String& name);
        ~UISlider() {}

        virtual bool setup();
        virtual void onTransformUpdate();

        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);
        virtual BubbleType onMouseMove(SPtr<MouseEvent> event);

        SPtr<UIButton> getSlider();
        void setGroundImage(const String& ground);
        void setNormalSlider(const String& normal);
        void setPushedSlider(const String& pushed);
        void setHoverSlider(const String& hover);

        float32 getProgress() const;
        void setProgress(float32 progress);

    protected:
        void updateProgress();

    protected:
        float32 mProgress = 0.5f;
        SPtr<UIButton> mButton = nullptr;
        inline static String SLIDER_BUTTON = _T("__slider_button");
    };
}

#endif
