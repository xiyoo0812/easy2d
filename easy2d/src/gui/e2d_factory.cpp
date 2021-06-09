#include "e2d_factory.h"

/* Easy2D */
using namespace Easy2D;

void Easy2D::UIFactory::setFont(const String& fontName)
{
    mFontName = fontName;
}

SPtr<UIRoot> UIFactory::createRoot()
{
    auto uiRoot = std::make_shared<UIRoot>();
    if (!uiRoot->setup())
    {
        LOG_WARN << _T("UIFactory::createRoot: UIRoot setup failed!");
        return nullptr;
    }
    return uiRoot;
}

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texture, SPtr<UIWidget> parent)
{
    auto image = std::make_shared<UIImage>(name);
    if (!image->setup())
    {
        LOG_WARN << _T("UIFactory::createImage: UIImage setup failed!");
        return nullptr;
    }
    if (!image->loadTexture(texture))
    {
        LOG_ERROR << "UIFactory::createImage error: texture(" << texture << ") load failed!";
        return nullptr;
    }
    if (nullptr != parent)
    {
        parent->addChild(image);
    }
    return image;
}

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texture, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto image = createImage(name, texture, parent);
    if (nullptr == image)
    {
        LOG_WARN << _T("UIFactory::createImage: create image failed!");
        return nullptr;
    }
    image->setPosition(pos);
    return image;
}

SPtr<UILabel> UIFactory::createLabel(const String& name, const Wtring& text, SPtr<UIWidget> parent)
{
    if (mFontName.empty())
    {
        LOG_ERROR << "UIFactory::createLabel error: default not setupo!";
        return nullptr;
    }
    auto label = std::make_shared<UILabel>(name);
    if (!label->setup())
    {
        LOG_WARN << _T("UIFactory::createLabel: UILabel setup failed!");
        return nullptr;
    }
    if (!label->setFont(mFontName))
    {
        LOG_ERROR << "UIFactory::createLabel error: font(" << mFontName << ") not load!";
        return nullptr;
    }
    if (nullptr != parent)
    {
        parent->addChild(label);
    }
    label->setText(text);
    return label;
}

SPtr<UILabel> UIFactory::createLabel(const String& name, const Wtring& text, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent)
{
    auto label = createLabel(name, text, parent);
    if (nullptr == label)
    {
        LOG_WARN << _T("UIFactory::createLabel: create label failed!");
        return nullptr;
    }
    label->setPosition(pos);
    label->setSize(size);
    return label;
}

SPtr<UIButton> UIFactory::createButton(const String& name, const String& normal, SPtr<UIWidget> parent)
{
    auto button = std::make_shared<UIButton>(name);
    if (!button->setup())
    {
        LOG_WARN << _T("UIFactory::createButton: UIButton setup failed!");
        return nullptr;
    }
    button->setNormalImage(normal);
    if (nullptr != parent)
    {
        parent->addChild(button);
    }
    return button;
}

SPtr<UIButton> UIFactory::createButton(const String& name, const String& normal, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto button = createButton(name, normal, parent);
    if (nullptr == button)
    {
        LOG_WARN << _T("UIFactory::createButton: create button failed!");
        return nullptr;
    }
    button->setPosition(pos);
    return button;
}

SPtr<UIButton> Easy2D::UIFactory::createButton(const String& name, const String& normal, const String& pushed, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto button = createButton(name, normal, pos, parent);
    if (nullptr == button)
    {
        LOG_WARN << _T("UIFactory::createButton: create button failed!");
        return nullptr;
    }
    button->setPushedImage(pushed);
    return button;
}

SPtr<UIRadio> UIFactory::createRadio(const String& name, const String& off, const String& on, SPtr<UIRadioGroup> parent)
{
    auto radio = std::make_shared<UIRadio>(name);
    if (!radio->setup())
    {
        LOG_WARN << _T("UIFactory::createRadio: UIRadio setup failed!");
        return nullptr;
    }
    radio->setOffImage(off);
    radio->setOnImage(on); 
    if (nullptr != parent)
    {
        parent->addChild(radio);
        if (parent->getChildrenCount() == 1)
        {
            radio->select();
        }
    }
    return radio;
}

SPtr<UIRadio> UIFactory::createRadio(const String& name, const String& off, const String& on, const Vec2& pos, SPtr<UIRadioGroup> parent)
{
    auto radio = createRadio(name, off, on, parent);
    if (nullptr == radio)
    {
        LOG_WARN << _T("UIFactory::createRadio: create radio  failed!");
        return nullptr;
    }
    radio->setPosition(pos);
    return radio;
}

SPtr<UIRadioGroup> UIFactory::createRadioGroup(const String& name, const String& texture, SPtr<UIWidget> parent)
{
    auto radioGroup = std::make_shared<UIRadioGroup>(name);
    if (!radioGroup->setup())
    {
        LOG_WARN << _T("UIFactory::createRadioGroup: UIImage setup failed!");
        return nullptr;
    }
    if (!radioGroup->loadTexture(texture))
    {
        LOG_ERROR << "UIFactory::createRadioGroup error: texture(" << texture << ") load failed!";
        return nullptr;
    }
    if (nullptr != parent)
    {
        parent->addChild(radioGroup);
    }
    return radioGroup;
}

SPtr<UIRadioGroup> UIFactory::createRadioGroup(const String& name, const String& texture, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto radioGroup = createRadioGroup(name, texture, parent);
    if (nullptr == radioGroup)
    {
        LOG_WARN << _T("UIFactory::createRadioGroup: create image failed!");
        return nullptr;
    }
    radioGroup->setPosition(pos);
    return radioGroup;
}

SPtr<UISwitch> UIFactory::createSwitch(const String& name, const String& off, const String& on, SPtr<UIWidget> parent)
{
    auto uiSwitch = std::make_shared<UISwitch>(name);
    if (!uiSwitch->setup())
    {
        LOG_WARN << _T("UIFactory::createSwitch: UISwitch setup failed!");
        return nullptr;
    }
    uiSwitch->setOffImage(off);
    uiSwitch->setOnImage(on);
    if (nullptr != parent)
    {
        parent->addChild(uiSwitch);
    }
    return uiSwitch;
}

SPtr<UISwitch> UIFactory::createSwitch(const String& name, const String& off, const String& on, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto uiSwitch = createSwitch(name, off, on, parent);
    if (nullptr == uiSwitch)
    {
        LOG_WARN << _T("UIFactory::createSwitch: create switch  failed!");
        return nullptr;
    }
    uiSwitch->setPosition(pos);
    return uiSwitch;
}

SPtr<UICheckBox> UIFactory::createCheckBox(const String& name, const String& off, const String& on, SPtr<UIWidget> parent)
{
    auto checkbox = std::make_shared<UICheckBox>(name);
    if (!checkbox->setup())
    {
        LOG_WARN << _T("UIFactory::createCheckBox: UICheckBox setup failed!");
        return nullptr;
    }
    checkbox->setOffImage(off);
    checkbox->setOnImage(on);
    if (nullptr != parent)
    {
        parent->addChild(checkbox);
    }
    return checkbox;
}

SPtr<UICheckBox> UIFactory::createCheckBox(const String& name, const String& off, const String& on, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto checkbox = createCheckBox(name, off, on, parent);
    if (nullptr == checkbox)
    {
        LOG_WARN << _T("UIFactory::createCheckBox: create checkbox failed!");
        return nullptr;
    }
    checkbox->setPosition(pos);
    return checkbox;
}

SPtr<UIProgress> UIFactory::createProgress(const String& name, const String& ground, const String& bar, SPtr<UIWidget> parent)
{
    auto progress = std::make_shared<UIProgress>(name);
    if (!progress->setup())
    {
        LOG_WARN << _T("UIFactory::createProgress: UIProgress setup failed!");
        return nullptr;
    }
    progress->setGroundImage(ground);
    progress->setBarImage(bar);
    if (nullptr != parent)
    {
        parent->addChild(progress);
    }
    return progress;
}

SPtr<UIProgress> UIFactory::createProgress(const String& name, const String& ground, const String& bar, const Vec2& pos, SPtr<UIWidget> parent)
{
    auto progress = createProgress(name, ground, bar, parent);
    if (nullptr == progress)
    {
        LOG_WARN << _T("UIFactory::createProgress: create progress failed!");
        return nullptr;
    }
    progress->setPosition(pos);
    return progress;
}
