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
    uiRoot->initialize();
    return uiRoot;
}

SPtr<UIButton> UIFactory::createButton(const String& name, const String& texPath, SPtr<UIWidget> parent /* = nullptr */)
{
    auto button = std::make_shared<UIButton>(name);
    button->setNormalImage(texPath);
    if (nullptr != parent)
    {
        parent->addChild(button);
    }
    return button;
}

SPtr<UIButton> UIFactory::createButton(const String& name, const String& texPath, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent /* = nullptr */)
{
    auto button = createButton(name, texPath, parent);
    if (nullptr != parent)
    {
        parent->addChild(button);
    }
    if (button)
    {
        button->setPosition(pos);
        button->setSize(size);
    }
    return button;
}

SPtr<UIRadio> UIFactory::createRadio(const String& name, SPtr<UIWidget> parent /* = nullptr */)
{
    auto radio = std::make_shared<UIRadio>(name);
    if (nullptr != parent)
    {
        parent->addChild(radio);
    }
    return radio;
}

SPtr<UICheckBox> UIFactory::createCheckBox(const String& name, SPtr<UIWidget> parent /* = nullptr */)
{
    auto checkbox = std::make_shared<UICheckBox>(name);
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
    if (label)
    {
        label->setPosition(pos);
        label->setSize(size);
    }
    return label;
}

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texPath, SPtr<UIWidget> parent /* = nullptr */)
{
    auto image = std::make_shared<UIImage>(name);
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

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texPath, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent /* = nullptr */)
{
    auto image = createImage(name, texPath, parent);
    if (image)
    {
        image->setPosition(pos);
        image->setSize(size);
    }
    return image;
}
