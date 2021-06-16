#ifndef FACTORY_H
#define FACTORY_H

#include "e2d_image.h"
#include "e2d_label.h"
#include "e2d_radio.h"
#include "e2d_button.h"
#include "e2d_switch.h"
#include "e2d_slider.h"
#include "e2d_editbox.h"
#include "e2d_checkbox.h"
#include "e2d_progress.h"
#include "base/e2d_singleton.h"

namespace Easy2D
{
    class UIFactory : public Singleton<UIFactory>
    {
    public:
        friend class Singleton<UIFactory>;

        SPtr<UIRoot> initialize(const String& fontName);

        SPtr<UIImage> createImage(const String& name, const String& texture, SPtr<UIWidget> parent);
        SPtr<UIImage> createImage(const String& name, const String& texture, const Vec2& pos, SPtr<UIWidget> parent);

        SPtr<UILabel> createLabel(const String& name, const Wtring& text, SPtr<UIWidget> parent);
        SPtr<UILabel> createLabel(const String& name, const Wtring& text, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent);

        SPtr<UIButton> createButton(const String& name, const String& normal, SPtr<UIWidget> parent);
        SPtr<UIButton> createButton(const String& name, const String& normal, const Vec2& pos, SPtr<UIWidget> parent);
        SPtr<UIButton> createButton(const String& name, const String& normal, const String& pushed, const Vec2& pos, SPtr<UIWidget> parent);

        SPtr<UIRadio> createRadio(const String& name, const String& off, const String& on, SPtr<UIRadioGroup> parent);
        SPtr<UIRadio> createRadio(const String& name, const String& off, const String& on, const Vec2& pos, SPtr<UIRadioGroup> parent);

        SPtr<UIRadioGroup> createRadioGroup(const String& name, const String& texture, SPtr<UIWidget> parent);
        SPtr<UIRadioGroup> createRadioGroup(const String& name, const String& texture, const Vec2& pos, SPtr<UIWidget> parent);

        SPtr<UISwitch> createSwitch(const String& name, const String& off, const String& on, SPtr<UIWidget> parent);
        SPtr<UISwitch> createSwitch(const String& name, const String& off, const String& on, const Vec2& pos, SPtr<UIWidget> parent);

        SPtr<UICheckBox> createCheckBox(const String& name, const String& off, const String& on, SPtr<UIWidget> parent);
        SPtr<UICheckBox> createCheckBox(const String& name, const String& off, const String& on, const Vec2& pos, SPtr<UIWidget> parent);

        SPtr<UIProgress> createProgress(const String& name, const String& ground, const String& bar, SPtr<UIWidget> parent);
        SPtr<UIProgress> createProgress(const String& name, const String& ground, const String& bar, const Vec2& pos, SPtr<UIWidget> parent);

        SPtr<UIEditbox> createEditbox(const String& name, const Wtring& text, SPtr<UIWidget> parent);
        SPtr<UIEditbox> createEditbox(const String& name, const Wtring& text, const Vec2& pos, const Vec2& size, SPtr<UIWidget> parent);

        SPtr<UISlider> createSlider(const String& name, const String& ground, const String& normal, SPtr<UIWidget> parent);
        SPtr<UISlider> createSlider(const String& name, const String& ground, const String& normal, const Vec2& pos, SPtr<UIWidget> parent);

    private:
        UIFactory(){}
        ~UIFactory() {}

    private:
        String mFontName = "";
    };
}

#endif
