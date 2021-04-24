#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "e2d_widget.h"
#include "base/e2d_color.h"
#include "graphics/e2d_font.h"

namespace Easy2D
{
    class TextComponent;
    class UITextField : public UIWidget
    {
    public:
        UITextField(const String& name);

        virtual ~UITextField();

        virtual void initialize();

        virtual void setHorizontalAlignment(HorizontalAlign alignment, bool redefineCenter = true);
        virtual void setVerticalAlignment(VerticalAlign alignment, bool redefineCenter = true);

        void setText(const Wtring& text);
        const Wtring& getText() const;

        void setColor(const Color& color);
        const Color& getColor() const;

        void setShadowColor(const Color& color, uint16 shodowSize = 1);
        const Color& getShadowColor() const;

        void setOutlineColor(const Color& color, uint16 outlineSize = 1);
        const Color& getOutlineColor() const;

        void setBold(bool bold);
        bool isBold() const;

        void setItalic(bool italoc);
        bool isItalic() const;

        void setFont(const SPtr<Font> font);
        const SPtr<Font> getFont() const;

    protected:
        SPtr<TextComponent> mTextComponent;
    };
}

#endif
