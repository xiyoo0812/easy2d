#ifndef FACTORY_H
#define FACTORY_H

#include "base/e2d_singleton.h"
#include "e2d_image.h"
#include "e2d_label.h"
#include "e2d_button.h"

namespace Easy2D
{
    class UIFactory : public Singleton<UIFactory>
    {
    public:
        friend class Singleton<UIFactory>;

        SPtr<UIRoot> createRoot();

        SPtr<UIButton> createButton(const String& name, SPtr<UIWidget> parent = nullptr);

        SPtr<UILabel> createLabel(const String& name, const Wtring& text, const String& fontName, SPtr<UIWidget> parent = nullptr);
        SPtr<UILabel> createLabel(const String& name, const Wtring& text, const String& fontName, Vec2& pos, Vec2& size, SPtr<UIWidget> parent = nullptr);

        SPtr<UIImage> createImage(const String& name, const String& texPath, SPtr<UIWidget> parent = nullptr);
        SPtr<UIImage> createImage(const String& name, const String& texPath, Vec2& pos, Vec2& size, SPtr<UIWidget> parent = nullptr);

    private:
        UIFactory(){}
        ~UIFactory(){}
    };
}

#endif
