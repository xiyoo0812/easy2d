#include "e2d_radio.h"

/* Easy2D */
using namespace Easy2D;

//-------------------------------------------------------------------------
UIRadioGroup::UIRadioGroup(const String& name) : UIImage(name)
{
}

UIRadioGroup::~UIRadioGroup()
{
}

bool UIRadioGroup::setup()
{
    if (!UIImage::setup())
    {
        LOG_WARN << _T("UIRadioGroup::setup: UIImage setup failed!");
        return false;
    }
    mVisible = VisibleType::HitChild;
    return true;
}

void Easy2D::UIRadioGroup::clean()
{
    if (mSelect)
    {
        mSelect->unselect();
        mSelect = nullptr;
    }
}

void UIRadioGroup::select(size_t index)
{
    if (index >= mChildrens.size())
    {
        LOG_ERROR << "UIRadioGroup::select out of rangge, index: " << index;
        return;
    }
    auto radio = std::dynamic_pointer_cast<UIRadio>(mChildrens[index]);
    if (radio)
    {
        radio->select();
    }
}

void UIRadioGroup::unselect(size_t index)
{
    if (index >= mChildrens.size())
    {
        LOG_ERROR << "UIRadioGroup::select out of rangge, index: " << index;
        return;
    }
    auto radio = std::dynamic_pointer_cast<UIRadio>(mChildrens[index]);
    if (radio)
    {
        radio->unselect();
    }
}

void UIRadioGroup::select(SPtr<UIRadio> radio)
{
    auto parent = radio->getParent();
    if (nullptr == parent)
    {
        LOG_ERROR << "UIRadioGroup::select radio has not parent! index: " << radio->getName();
        return;
    }
    if (compareGUID(parent->getGUID()))
    {
        clean();
        mSelect = radio;
    }
}

void UIRadioGroup::unselect(SPtr<UIRadio> radio)
{
    if (mSelect == radio)
    {
        clean();
    }
}

//-------------------------------------------------------------------------
UIRadio::UIRadio(const String& name) : UICheckBox(name)
{

}

void Easy2D::UIRadio::select()
{
    UICheckBox::select();
    if (!mParent.expired())
    {
        auto radioGroup = std::dynamic_pointer_cast<UIRadioGroup>(mParent.lock());
        if (radioGroup)
        {
            radioGroup->select(std::dynamic_pointer_cast<UIRadio>(shared_from_this()));
        }
    }
}

BubbleType UIRadio::onLButtonUp(SPtr<MouseEvent> event)
{
    if (mStatus != ChoseStatus::Disable)
    {
        if (mStatus == ChoseStatus::ChoseOff)
        {
            select();
        }
        return BubbleType::Break;
    }
    return BubbleType::Continue;
}
