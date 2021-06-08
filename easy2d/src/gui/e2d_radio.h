#ifndef RADIO_H
#define RADIO_H

#include "e2d_checkbox.h"

namespace Easy2D
{
    class UIRadio;
    class UIRadioGroup : public Object
    {
    public:
        UIRadioGroup(const String& name);
        ~UIRadioGroup();

        void select(size_t index);
        void select(SPtr<UIRadio> radio);
        size_t addRadio(SPtr<UIRadio> radio);

    protected:
        SPtr<UIRadio> mSelect = nullptr;
        Vector<SPtr<UIRadio>> mRadios {};
    };

    class UIRadio : public UICheckBox
    {
    public:
        UIRadio(const String& name);
        ~UIRadio(){}

        uint64 getRadioGroup();
        void setRadioGroup(uint64 guid);

    protected:
        size_t mIndex = 0;
        uint64 mGroupGuid = 0;
    };
}

#endif
