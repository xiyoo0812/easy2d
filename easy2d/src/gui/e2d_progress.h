#ifndef PROGRESS_H
#define PROGRESS_H

#include "e2d_image.h"
#include "e2d_label.h"

namespace Easy2D
{
    class UIProgress : public UIImage
    {
    public:
        UIProgress(const String& name);
        ~UIProgress(){}

        virtual bool setup();
        virtual void onTransformUpdate();

        SPtr<UIImage> getBarImage();
        SPtr<UILabel> getLabel();

        void setGroundImage(const String& ground);
        void setBarImage(const String& bar);

        uint32 getProgress() const;
        uint32 getProgressMax() const;
        void setProgress(uint32 progress);
        void setProgressMax(uint32 progressMax);

    protected:
        void updateProgress();

    protected:
        uint32 mProgress = 50;
        uint32 mProgressMax = 100;
        SPtr<UIImage> mBar = nullptr;
        SPtr<UILabel> mLabel = nullptr;
        inline static String BAR_NAME = _T("__bar_image");
        inline static String TEXT_NAME = _T("__text_image");

    };
}

#endif
