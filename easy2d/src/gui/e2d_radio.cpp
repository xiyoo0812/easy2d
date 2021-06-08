#include "e2d_radio.h"

/* Easy2D */
using namespace Easy2D;

//-------------------------------------------------------------------------
UIRadioGroup::~UIRadioGroup()
{
    mSelect = nullptr;
    mRadios.clear();
}

UIRadioGroup::UIRadioGroup(const String& name) : Object(name)
{
}

void UIRadioGroup::select(size_t index)
{
    if (index >= mRadios.size())
    {
        LOG_ERROR << "UIRadioGroup::select out of rangge, index: " << index;
        return;
    }
    auto radio = mRadios[index];
    select(radio);
}

void UIRadioGroup::select(SPtr<UIRadio> radio)
{
    if (compareGUID(radio->getRadioGroup()))
    {
        if (mSelect)
        {
            mSelect->unselect();
        }
        radio->select();
        mSelect = radio;
    }
}

size_t UIRadioGroup::addRadio(SPtr<UIRadio> radio)
{
    size_t index = mRadios.size();
    mRadios.push_back(radio);
    if (mSelect == nullptr)
    {
        mSelect = radio;
    }
    radio->setRadioGroup(mGUID);
    return index;
}

//-------------------------------------------------------------------------
UIRadio::UIRadio(const String& name) : UICheckBox(name)
{

}

uint64 UIRadio::getRadioGroup()
{
    return mGroupGuid;
}

void UIRadio::setRadioGroup(uint64 guid)
{
    mGroupGuid = guid;
}
