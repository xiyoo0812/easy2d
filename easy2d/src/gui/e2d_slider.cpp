#include "e2d_slider.h"
#include "e2d_factory.h"

/* Easy2D */
using namespace Easy2D;

UISlider::UISlider(const String& name) : UIImage(name)
{

}

bool UISlider::setup()
{
    if (!UIImage::setup())
    {
        LOG_WARN << _T("UISlider::setup: UIImage setup failed!");
        return false;
    }
    return true;
}

void UISlider::onSizeChanged(const Vec2& size)
{
    updateProgress();
}

BubbleType UISlider::onLButtonUp(SPtr<MouseEvent> event)
{
    Vec2 ratio = screen2Ratio(event->mPos);
    setProgress(ratio.x);
    return BubbleType::Break;
}

BubbleType UISlider::onMouseMove(SPtr<MouseEvent> event)
{
    if (mButton->getStatus() == ButtonStatus::Pushed)
    {
        Vec2 ratio = screen2Ratio(event->mPos);
        setProgress(ratio.x);
    }
    return BubbleType::Continue;
}

SPtr<UIButton> UISlider::getSlider()
{
    return mButton;
}

void UISlider::setGroundImage(const String& ground)
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

void UISlider::setNormalSlider(const String& normal)
{
    if (mButton)
    {
        mButton->setNormalImage(normal);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto button = UIFactory::instance()->createButton(SLIDER_BUTTON, normal, Vec2(0, 0), shared_this);
    if (nullptr == button)
    {
        LOG_ERROR << "UISlider::setNormalSlider error: button(" << normal << ") create failed!";
        return;
    }
    button->setZorder(1);
    button->setAnchor(0.5, 0.5);
    button->setDockerAlign(DockerAlign::Left);
    mButton = button;
    updateProgress();
}

void UISlider::setPushedSlider(const String& pushed)
{
    if (mButton)
    {
        mButton->setPushedImage(pushed);
    }
}

void UISlider::setHoverSlider(const String& hover)
{
    if (mButton)
    {
        mButton->setHoverImage(hover);
    }
}

float32 UISlider::getProgress() const
{
    return mProgress;
}

void UISlider::setProgress(float32 progress)
{
    progress = std::min(progress, 1.0f);
    mProgress = std::max(progress, 0.0f);
    updateProgress();
}

void UISlider::updateProgress()
{
    if (mButton)
    {
        float32 width = getWidth();
        float32 btnWidth = mButton->getHeight();
        float32 btnPosX = btnWidth / 2 + (width - btnWidth) * mProgress;
        mButton->setPositionX(btnPosX);
    }
}
