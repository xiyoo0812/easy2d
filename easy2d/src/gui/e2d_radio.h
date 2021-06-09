#ifndef RADIO_H
#define RADIO_H

#include "e2d_image.h"
#include "e2d_checkbox.h"

namespace Easy2D
{
    class UIRadio;
    class UIRadioGroup : public UIImage
    {
    public:
        friend class UIRadio;
        UIRadioGroup(const String& name);
        ~UIRadioGroup();

        virtual bool setup();

        void clean();
        void select(size_t index);
        void unselect(size_t index);

    protected:
        void select(SPtr<UIRadio> radio);
        void unselect(SPtr<UIRadio> radio);

    protected:
        SPtr<UIRadio> mSelect;
    };

    class UIRadio : public UICheckBox
    {
    public:
        UIRadio(const String& name);
        ~UIRadio(){}

        virtual void select();

        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);
    };
}

#endif
