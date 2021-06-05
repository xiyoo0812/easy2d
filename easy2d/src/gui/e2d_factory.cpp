#include "e2d_factory.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_texture_mgr.h"

/* Easy2D */
using namespace Easy2D;

SPtr<UIRoot> UIFactory::createRoot()
{
    auto uiRoot = std::make_shared<UIRoot>();
    uiRoot->initialize();
    return uiRoot;
}

SPtr<UIButton> UIFactory::createButton(const String& name, SPtr<UIWidget> parent /* = nullptr */)
{
    auto button = std::make_shared<UIButton>(name);
    if (nullptr != parent)
    {
        parent->addChild(button);
    }
    return button;
}

SPtr<UILabel> UIFactory::createLabel(const String& name, const Wtring& text, const String& fontName, SPtr<UIWidget> parent /* = nullptr */)
{
    auto font = FontManager::getInstance()->getFont(fontName);
    if (nullptr == font)
    {
        LOG_ERROR << "UIFactory::createLabel error: font(" << fontName << ") not load!";
        return nullptr;
    }
    auto label = std::make_shared<UILabel>(name);
    if (nullptr != parent)
    {
        parent->addChild(label);
    }
    label->setText(text);
    label->setFont(font);
    return label;
}

SPtr<UILabel> UIFactory::createLabel(const String& name, const Wtring& text, const String& fontName, Vec2& pos, Vec2& size, SPtr<UIWidget> parent /* = nullptr */)
{
    auto label = createLabel(name, text, fontName, parent);
    if (label)
    {
        label->setPosition(pos);
        label->setSize(size);
    }
    return label;
}

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texPath, SPtr<UIWidget> parent /* = nullptr */)
{
    auto texture = TextureManager::getInstance()->loadTexture(texPath);
    if (nullptr == texture)
    {
        LOG_ERROR << "UIFactory::createImage error: texture(" << texPath << ") load failed!";
        return nullptr;
    }
    auto image = std::make_shared<UIImage>(name);
    if (nullptr != parent)
    {
        parent->addChild(image);
    }
    image->setTexture(texture);
    return image;
}

SPtr<UIImage> UIFactory::createImage(const String& name, const String& texPath, Vec2& pos, Vec2& size, SPtr<UIWidget> parent /* = nullptr */)
{
    auto image = createImage(name, texPath, parent);
    if (image)
    {
        image->setPosition(pos);
        image->setSize(size);
    }
    return image;
}
