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
    mLabel->setHorizontalAlign(HorizontalAlign::Left);
    mLabel->setDockerAlign(DockerAlign::Full);
    return true;
}

void UIEditbox::update(const uint32& escapeMs, bool escapeSec)
{
    Entity::update(escapeMs, escapeSec);
    if (escapeSec && mbFocus)
    {
        mbShowInput = !mbShowInput;
        showText();
    }
}

void UIEditbox::showText()
{
    if (mbFocus)
    {
        Wtring text = mEditText;
        if (mbShowInput)
        {
            text.insert(mFocusIdx, 1, INPUT);
            mLabel->setText(text);
        }
        else
        {
            text.insert(mFocusIdx, 1, ' ');
            mLabel->setText(text);
        }
    }
    else
    {
        mLabel->setText(mEditText);
    }
}

BubbleType UIEditbox::onChar(SPtr<KeyEvent> event)
{
    mEditText.insert(mFocusIdx++, 1, event->mKey);
    showText();
    return BubbleType::Break;
}

BubbleType UIEditbox::onKeyDown(SPtr<KeyEvent> event)
{
    if (mbFocus)
    {
        switch (event->mKey)
        {
        case GLFW_KEY_BACKSPACE:
            if (mFocusIdx > 0 && !mEditText.empty())
            {
                mEditText.erase(--mFocusIdx, 1);
                showText();
            }
            return BubbleType::Break;
        case GLFW_KEY_LEFT:
            if (mFocusIdx > 0 && !mEditText.empty())
            {
                mFocusIdx--;
                showText();
            }
            return BubbleType::Break;
        case GLFW_KEY_RIGHT:
            if (mFocusIdx < mEditText.size())
            {
                mFocusIdx++;
                showText();
            }
            return BubbleType::Break;
        }
    }
    return BubbleType::Continue;
}

BubbleType UIEditbox::onLButtonUp(SPtr<MouseEvent> event)
{
    setFocus(isInRect(event->mPos));
    showText();
    return BubbleType::Continue;
}

BubbleType UIEditbox::onLButtonDown(SPtr<MouseEvent> event)
{
    setFocus(true);
    UIRoot::instance()->setInputFocus(std::dynamic_pointer_cast<UIWidget>(shared_from_this()));
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

void UIEditbox::setFont(const String& fontName)
{
    if (mLabel)
    {
        mLabel->setFont(fontName);
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
