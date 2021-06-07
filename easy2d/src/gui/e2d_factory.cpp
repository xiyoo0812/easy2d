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

SPtr<UIButton> UIFactory::createButton(const String& name, const String& texPath, SPtr<UIWidget> parent /* = nullptr */)
{
    auto button = std::make_shared<UIButton>(name);
    if (!button->setup())
    {
        LOG_WARN << _T("UIFactory::createButton: UIButton setup failed!");
        return nullptr;
    }
    button->setNormalImage(texPath);
    if (nullptr != parent)
    {
        parent->addChild(button);
    }
    return button;
}

SPtr<UIButton> UIFactory::createButton(const String& name, const String& texPath, const Vec2& pos, SPtr<UIWidget> parent /* = nullptr */)
{
    auto button = createButton(name, texPath, parent);
    if (nullptr == button)
    {
        LOG_WARN << _T("UIFactory::createButton: create button failed!");
        return nullptr;
    }
    button->setPosition(pos);
    return button;
}

SPtr<UIRadio> UIFactory::createRadio(const String& name, SPtr<UIWidget> parent /* = nullptr */)
{
    auto radio = std::make_shared<UIRadio>(name);
    if (!radio->setup())
    {
        LOG_WARN << _T("UIFactory::createRadio: UIRadio setup failed!");
        return nullptr;
    }
    if (nullptr != parent)
    {
        parent->addChild(radio);
    }
    return radio;
}

SPtr<UICheckBox> UIFactory::createCheckBox(const String& name, SPtr<UIWidget> parent /* = nullptr */)
{
    auto checkbox = std::make_shared<UICheckBox>(name);
    if (!checkbox->setup())
    {
        LOG_WARN << _T("UIFactory::createCheckBox: UICheckBox setup failed!");
        return nullptr;
    }
    if (nullptr != parent)
    {
        parent->addChild(checkbox);
    }
    return checkbox;
}

SPtr<UILabel> UIFactory::createLabel(const String& name, const Wtring& text, SPtr<UIWidget> parent /* = nullptr */)
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

SPtr<UILabel> UIFactory::createLabel(const String& name, const Wtring& text, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent /* = nullptr */)
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

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texPath, SPtr<UIWidget> parent /* = nullptr */)
{
    auto image = std::make_shared<UIImage>(name);
    if (!image->setup())
    {
        LOG_WARN << _T("UIFactory::createImage: UIImage setup failed!");
        return nullptr;
    }
    if (!image->loadTexture(texPath))
    {
        LOG_ERROR << "UIFactory::createImage error: texture(" << texPath << ") load failed!";
        return nullptr;
    }
    if (nullptr != parent)
    {
        parent->addChild(image);
    }
    return image;
}

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texPath, const Vec2& pos, SPtr<UIWidget> parent /* = nullptr */)
{
    auto image = createImage(name, texPath, parent);
    if (nullptr == image)
    {
        LOG_WARN << _T("UIFactory::createImage: create image failed!");
        return nullptr;
    }
    image->setPosition(pos);
    return image;
}
