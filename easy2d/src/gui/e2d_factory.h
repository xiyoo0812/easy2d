#ifndef FACTORY_H
#define FACTORY_H

#include "e2d_image.h"
#include "e2d_label.h"
#include "e2d_radio.h"
#include "e2d_button.h"
#include "e2d_checkbox.h"
#include "base/e2d_singleton.h"

namespace Easy2D
{
    class UIFactory : public Singleton<UIFactory>
    {
    public:
        friend class Singleton<UIFactory>;

        void setFont(const String& fontName);

        SPtr<UIRoot> createRoot();

        SPtr<UIButton> createButton(const String& name, const String& texPath, SPtr<UIWidget> parent = nullptr);
        SPtr<UIButton> createButton(const String& name, const String& texPath, const Vec2& pos, SPtr<UIWidget> parent = nullptr);

        SPtr<UIRadio> createRadio(const String& name, SPtr<UIWidget> parent = nullptr);
        SPtr<UICheckBox> createCheckBox(const String& name, SPtr<UIWidget> parent = nullptr);

        SPtr<UILabel> createLabel(const String& name, const Wtring& text, SPtr<UIWidget> parent = nullptr);
        SPtr<UILabel> createLabel(const String& name, const Wtring& text, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent = nullptr);

        SPtr<UIImage> createImage(const String& name, const String& texPath, SPtr<UIWidget> parent = nullptr);
        SPtr<UIImage> createImage(const String& name, const String& texPath, const Vec2& pos, SPtr<UIWidget> parent = nullptr);

    private:
        UIFactory(){}
        ~UIFactory() {}

    private:
        String mFontName = "";
    };
}

#endif
