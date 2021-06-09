#include "e2d_progress.h"
#include "e2d_factory.h"

/* Easy2D */
using namespace Easy2D;

UIProgress::UIProgress(const String& name) : UIWidget(name)
{

}

bool UIProgress::setup()
{
    if (!Entity::setup())
    {
        LOG_WARN << _T("UIProgress::setup: Entity setup failed!");
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
    mVisible = VisibleType::HitNobody;
    return true;
}

void UIProgress::onTransformUpdate()
{
    updateProgress();
}

SPtr<UIImage> UIProgress::getGroundImage()
{
    return mGround;
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
    if (mGround)
    {
        if (ground.empty())
        {
            return mGround->setTexture(nullptr);
        }
        mGround->loadTexture(ground);
        return;
    }
    auto shared_this = std::dynamic_pointer_cast<UIWidget>(shared_from_this());
    auto image = UIFactory::instance()->createImage(GROUND_NAME, ground, shared_this);
    if (nullptr == image)
    {
        LOG_ERROR << "UIProgress::setGroundImage error: image(" << ground << ") create failed!";
        return;
    }
    updateSize(image);
    image->setVisible(VisibleType::Visible);
    image->setDockerAlign(DockerAlign::Full);
    mGround = image;
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
        LOG_ERROR << "UIProgress::setGroundImage error: image(" << bar << ") create failed!";
        return;
    }
    image->setZorder(1);
    image->setAnchor(0, 0.5);
    image->setVisible(VisibleType::Visible);
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
    mProgress = (progress > mProgressMax) ? mProgressMax : progress;
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

void UIProgress::updateSize(SPtr<UIImage> image)
{
    auto dim = getSize();
    if (dim.x <= 1 && dim.y <= 1)
    {
        setSize(image->getSize());
    }
}