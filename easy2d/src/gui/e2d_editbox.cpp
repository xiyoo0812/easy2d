#include "e2d_editbox.h"
#include "e2d_factory.h"

/* Easy2D */
using namespace Easy2D;

UIEditbox::UIEditbox(const String& name) : UIImage(name)
{

}

bool UIEditbox::setup()
{
    if (!UIImage::setup())
    {
        LOG_WARN << _T("UIEditbox::setup: UIImage setup failed!");
        return false;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    mLabel = UIFactory::instance()->createLabel(LABEL_NAME, L"", shared_this);
    if (nullptr == mLabel)
    {
        LOG_ERROR << "UIEditbox::setText error: label create failed!";
        return false;
    }
    mLabel->setVisible(VisibleType::HitNobody);
    mLabel->setVerticalAlign(VerticalAlign::Center);
    mLabel->setHorizontalAlign(HorizontalAlign::Center);
    mLabel->setDockerAlign(DockerAlign::Full);
    return true;
}

BubbleType UIEditbox::onChar(SPtr<KeyEvent> event)
{
    return BubbleType::Continue;
}

BubbleType UIEditbox::onKeyUp(SPtr<KeyEvent> event)
{
    return BubbleType::Continue;
}

BubbleType UIEditbox::onLButtonUp(SPtr<MouseEvent> event)
{
    Vec2 innerPos = getInnerPos(event->mPos);
    return BubbleType::Break;
}

void UIEditbox::setGroundImage(const String& ground)
{
    if (ground.empty())
    {
        return setTexture(nullptr);
    }
    if (!loadTexture(ground))
    {
        LOG_ERROR << "UISlider::setGroundImage error: image(" << ground << ") create failed!";
    }
}

void UIEditbox::setText(const Wtring& text)
{
    if (mLabel)
    {
        mLabel->setText(text);
    }
}

const Wtring& UIEditbox::getText()
{
    if (mLabel)
    {
        return mLabel->getText();
    }
    return EMPTY_STRING;
}
