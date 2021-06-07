#include "e2d_button.h"
#include "e2d_factory.h"

/* Easy2D */
using namespace Easy2D;

UIButton::UIButton(const String& name) : UIWidget(name)
{

}

bool UIButton::setup()
{
    if (!Entity::setup())
    {
        LOG_WARN << _T("UIButton::setup: Entity setup failed!");
        return false;
    }
    mHoverFactor = 1.1f;
    mPushedFactor = 0.9f;
    mVisible = VisibleType::HitSelf;
    return true;
}

BubbleType UIButton::onLButtonUp(SPtr<MouseEvent> event)
{
    if (mStatus == ButtonStatus::Pushed)
    {
        if (mbMouseHover)
        {
            setStatus(ButtonStatus::Hover);
            setScale(mHoverFactor);
        }
        else
        {
            setStatus(ButtonStatus::Normal);
        }
        return BubbleType::Break;
    }
    return BubbleType::Continue;
}

BubbleType UIButton::onLButtonDown(SPtr<MouseEvent> event)
{
    if (mStatus == ButtonStatus::Hover || mStatus == ButtonStatus::Normal)
    {
        setStatus(ButtonStatus::Pushed);
        setScale(mPushedFactor);
        return BubbleType::Break;
    }
    return BubbleType::Continue;
}

void UIButton::onMouseEnter(SPtr<MouseEvent> event)
{
    if (mStatus == ButtonStatus::Normal)
    {
        setStatus(ButtonStatus::Hover);
        setScale(mHoverFactor);
    }
}

void UIButton::onMouseLeave(SPtr<MouseEvent> event)
{
    if (mStatus == ButtonStatus::Hover || mStatus == ButtonStatus::Pushed)
    {
        setStatus(ButtonStatus::Normal);
    }
}

ButtonStatus UIButton::getStatus()
{
    return mStatus;
}

void UIButton::setStatus(ButtonStatus status)
{
    setScale(1.0f);
    updateStatus(false);
    mStatus = status;
    updateStatus(true);
}

SPtr<UIImage> UIButton::getNormalImage()
{
    return mNormal;
}

SPtr<UIImage> UIButton::getPushedImage()
{
    return mPushed;
}

SPtr<UIImage> UIButton::getHoverImage()
{
    return mHover;
}

SPtr<UIImage> UIButton::getDisableImage()
{
    return mDisable;
}

SPtr<UILabel> UIButton::getLabel()
{
    return mLabel;
}

void UIButton::setNormalImage(const String& normal)
{
    if (mNormal)
    {
        if (normal.empty())
        {
            return mNormal->setTexture(nullptr);
        }
        mNormal->loadTexture(normal);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(NORMAL_NAME, normal, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UIButton::setNormalImage error: image(" << normal << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Visible);
    image->setDockerAlign(DockerAlign::Full);
    mNormal = image;
}

void UIButton::setPushedImage(const String& pushed)
{
    if (mPushed)
    {
        if (pushed.empty())
        {
            return mPushed->setTexture(nullptr);
        }
        mPushed->loadTexture(pushed);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(PUSHED_NAME, pushed, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UIButton::setPushedImage error: image(" << pushed << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Hidden);
    image->setDockerAlign(DockerAlign::Full);
    mPushed = image;
}

void UIButton::setHoverImage(const String& hover)
{
    if (mHover)
    {
        if (hover.empty())
        {
            return mHover->setTexture(nullptr);
        }
        mHover->loadTexture(hover);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(HOVER_NAME, hover, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UIButton::setHoverImage error: image(" << hover << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Hidden);
    image->setDockerAlign(DockerAlign::Full);
    mHover = image;
}

void UIButton::setDisableImage(const String& disable)
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
        LOG_ERROR << "UIButton::setDisableImage error: image(" << disable << ") create failed!";
        return;
    }
    updateSize(image);
    image->setAnchor(0.5, 0.5);
    image->setVisible(VisibleType::Hidden);
    image->setDockerAlign(DockerAlign::Full);
    mDisable = image;
}

void UIButton::setText(const Wtring& text)
{
    if (mLabel)
    {
        mLabel->setText(text);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto label = UIFactory::instance()->createLabel(DISABLE_NAME, text, Vec2(0, 0), getSize(), shared_this);
    if (nullptr == label)
    {
        LOG_ERROR << "UIButton::setText error: label(" << text.c_str() << ") create failed!";
        return;
    }
    label->setAnchor(0.5, 0.5);
    label->setVisible(VisibleType::Hidden);
    label->setVerticalAlign(VerticalAlign::Center);
    label->setHorizontalAlign(HorizontalAlign::Center);
    label->setDockerAlign(DockerAlign::Full);
    mLabel = label;
}

const Wtring& UIButton::getText()
{
    if (mLabel)
    {
        return mLabel->getText();
    }
    return EMPTY_STRING;
}

void UIButton::setHoverFactor(float32 hf)
{
    mHoverFactor = hf;
}

void UIButton::setPushedFactor(float32 pf)
{
    mPushedFactor = pf;
}

void UIButton::updateStatus(bool showOrHide)
{
    SPtr<UIImage> ctrlImage = nullptr;
    switch (mStatus)
    {
    case ButtonStatus::Normal:
        ctrlImage = mNormal;
        break;
    case ButtonStatus::Pushed:
        ctrlImage = mPushed ? mPushed : mNormal;
        break;
    case ButtonStatus::Hover:
        ctrlImage = mHover ? mHover : mNormal;
        break;
    case ButtonStatus::Disable:
        ctrlImage = mDisable ? mDisable : mNormal;
        break;
    }
    if (ctrlImage)
    {
        ctrlImage->setVisible(showOrHide ? VisibleType::Visible : VisibleType::Hidden);
    }
}

void UIButton::updateSize(SPtr<UIImage> image)
{
    auto dim = getSize();
    if (dim.x <= 1 && dim.y <= 1)
    {
        setSize(image->getSize());
    }
}
