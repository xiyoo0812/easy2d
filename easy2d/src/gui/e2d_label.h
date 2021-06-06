#ifndef LABEL_H
#define LABEL_H

#include "e2d_widget.h"
#include "base/e2d_color.h"
#include "graphics/e2d_font.h"

namespace Easy2D
{
    class TextComponent;
    class UILabel : public UIWidget
    {
    public:
        UILabel(const String& name);

        virtual ~UILabel();

        void setVerticalAlign(VerticalAlign align);
        void setHorizontalAlign(HorizontalAlign align);

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

        void setLineWidth(uint32 lineWrap);
        uint32 getLineWidth() const;
        bool isLineWarp() const;

        void setContentFollow(bool follow);
        bool isContentFollow() const;

        void setSpacing(uint32 spacing);
        uint32 getSpacing() const;

        bool setFont(const String& fontName);
        void setFont(const SPtr<Font> font);
        const SPtr<Font> getFont() const;

    protected:
        SPtr<TextComponent> mTextComponent;
    };
}

#endif
