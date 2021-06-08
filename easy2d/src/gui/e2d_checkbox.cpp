#include "e2d_checkbox.h"
#include "e2d_factory.h"


/* Easy2D */
using namespace Easy2D;

UICheckBox::UICheckBox(const String& name) : UIWidget(name)
{

}

bool UICheckBox::setup()
{
    if (!Entity::setup())
    {
        LOG_WARN << _T("UICheckBox::setup: Entity setup failed!");
        return false;
    }
    mVisible = VisibleType::HitSelf;
    return true;
}

BubbleType UICheckBox::onLButtonUp(SPtr<MouseEvent> event)
{
    if (mStatus != ChoseStatus::Disable)
    {
        setStatus(mStatus == ChoseStatus::ChoseOff ? ChoseStatus::ChoseOn : ChoseStatus::ChoseOn);
        return BubbleType::Break;
    }
    return BubbleType::Continue;
}

ChoseStatus UICheckBox::getStatus()
{
    return mStatus;
}

void UICheckBox::setStatus(ChoseStatus status)
{
    updateStatus(false);
    mStatus = status;
    updateStatus(true);
}

bool UICheckBox::isSelected()
{
    return mStatus == ChoseStatus::ChoseOn;
}

void UICheckBox::select()
{
    if (mStatus == ChoseStatus::ChoseOff)
    {
        setStatus(ChoseStatus::ChoseOn);
    }
}

void UICheckBox::unselect()
{
    if (mStatus == ChoseStatus::ChoseOn)
    {
        setStatus(ChoseStatus::ChoseOff);
    }
}

SPtr<UIImage> UICheckBox::getOffImage()
{
    return mChoseOff;
}

SPtr<UIImage> UICheckBox::getOnImage()
{
    return mChoseOn;
}

SPtr<UIImage> UICheckBox::getDisableImage()
{
    return mDisable;
}


void UICheckBox::setOffImage(const String& off)
{
    if (mChoseOff)
    {
        if (off.empty())
        {
            return mChoseOff->setTexture(nullptr);
        }
        mChoseOff->loadTexture(off);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(CHOSEOFF_NAME, off, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UICheckBox::setOffImage error: image(" << off << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Visible);
    image->setDockerAlign(DockerAlign::Full);
    mChoseOff = image;
}

void UICheckBox::setOnImage(const String& on)
{
    if (mChoseOn)
    {
        if (on.empty())
        {
            return mChoseOn->setTexture(nullptr);
        }
        mChoseOn->loadTexture(on);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(CHOSEON_NAME, on, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UICheckBox::setOnImage error: image(" << on << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Hidden);
    image->setDockerAlign(DockerAlign::Full);
    mChoseOn = image;
}

void UICheckBox::setDisableImage(const String& disable)
{
    if (mDisable)
    {
        if (disable.empty())
        {
            return mDisable->setTexture(nullptr);
        }
        mDisable->loadTexture(disable);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(DISABLE_NAME, disable, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UICheckBox::setDisableImage error: image(" << disable << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Hidden);
    image->setDockerAlign(DockerAlign::Full);
    mDisable = image;
}

void UICheckBox::updateStatus(bool showOrHide)
{
    SPtr<UIImage> ctrlImage = nullptr;
    switch (mStatus)
    {
    case ChoseStatus::ChoseOff:
        ctrlImage = mChoseOff;
        break;
    case ChoseStatus::ChoseOn:
        ctrlImage = mChoseOn ? mChoseOn : mChoseOff;
        break;
    case ChoseStatus::Disable:
        ctrlImage = mDisable ? mDisable : mChoseOff;
        break;
    }
    if (ctrlImage)
    {
        ctrlImage->setVisible(showOrHide ? VisibleType::Visible : VisibleType::Hidden);
    }
}

void UICheckBox::updateSize(SPtr<UIImage> image)
{
    auto dim = getSize();
    if (dim.x <= 1 && dim.y <= 1)
    {
        setSize(image->getSize());
    }
}