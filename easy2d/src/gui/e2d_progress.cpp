#include "e2d_progress.h"
#include "e2d_factory.h"

/* Easy2D */
using namespace Easy2D;

UIProgress::UIProgress(const String& name) : UIImage(name)
{

}

bool UIProgress::setup()
{
    if (!UIImage::setup())
    {
        LOG_WARN << _T("UIProgress::setup: UIImage setup failed!");
        return false;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    mLabel = UIFactory::instance()->createLabel(TEXT_NAME, L"", shared_this);
    if (nullptr == mLabel)
    {
        LOG_ERROR << "UIProgress::createLabel failed!";
        return false;
    }
    mLabel->setZorder(2);
    mLabel->setFont("fzltxh-12");
    mLabel->setColor(Color::Red);
    mLabel->setVisible(VisibleType::Visible);
    mLabel->setVerticalAlign(VerticalAlign::Center);
    mLabel->setHorizontalAlign(HorizontalAlign::Center);
    mLabel->setDockerAlign(DockerAlign::Full);
    mVisible = VisibleType::HitSelf;
    return true;
}

void UIProgress::onTransformUpdate()
{
    updateProgress();
}

SPtr<UIImage> UIProgress::getBarImage()
{
    return mBar;
}

SPtr<UILabel> UIProgress::getLabel()
{
    return mLabel;
}

void UIProgress::setGroundImage(const String& ground)
{
    if (ground.empty())
    {
        return setTexture(nullptr);
    }
    if (!loadTexture(ground))
    {
        LOG_ERROR << "UIProgress::setGroundImage error: image(" << ground << ") create failed!";
    }
}

void UIProgress::setBarImage(const String& bar)
{
    if (mBar)
    {
        if (bar.empty())
        {
            return mBar->setTexture(nullptr);
        }
        mBar->loadTexture(bar);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(BAR_NAME, bar, Vec2(0, 0), shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UIProgress::setBarImage error: image(" << bar << ") create failed!";
        return;
    }
    image->setZorder(1);
    image->setAnchor(0, 0.5);
    image->setVisible(VisibleType::HitSelf);
    image->setDockerAlign(DockerAlign::Left);
    mBar = image;
}

uint32 UIProgress::getProgress() const
{
    return mProgress;
}

uint32 UIProgress::getProgressMax() const
{
    return mProgressMax;
}

void UIProgress::setProgress(uint32 progress)
{
    mProgress = std::min(progress, mProgressMax);
    updateProgress();
}

void UIProgress::setProgressMax(uint32 progressMax)
{
    mProgressMax = (progressMax < mProgress) ? mProgress : progressMax;
    updateProgress();
}

void UIProgress::updateProgress()
{
    float32 width = getWidth();
    float32 bar_width = width * mProgress / mProgressMax;
    mBar->setSizeX(bar_width);
    Wtring text = std::to_wstring(mProgress) + L"/" + std::to_wstring(mProgressMax);
    mLabel->setText(text);
}
