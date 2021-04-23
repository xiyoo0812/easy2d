#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "base/e2d_color.h"
#include "object/e2d_entity.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_render_object.h"

namespace Easy2D
{
    class TextComponent : public Entity
    {
    public:
        TextComponent(const String& name);

        virtual ~TextComponent();

        virtual void initialize();

        virtual void update(const uint32& escapeMs);

        void setText(const Wtring& text);
        const Wtring& getText() const;
        const Wtring& getShowText() const;

        void setColor(const Color& color);
        const Color& getColor() const;

        void setShadowColor(const Color& color, uint16 shodowSize = 1);
        const Color& getShadowColor() const;
        uint16 getShadowSize() const;

        void setOutlineColor(const Color& color, uint16 outlineSize = 1);
        const Color& getOutlineColor() const;
        uint16 getOutlineSize() const;

        void setBold(bool bold);
        bool isBold() const;

        void setItalic(bool italoc);
        bool isItalic() const;

        void setFont(const SPtr<Font> font);
        const SPtr<Font> getFont() const;

        void setWrapWidth(int32 width);
        int32 getWrapWidth() const;

        void setSpacing(uint32 spacing);
        uint32 getSpacing() const;

        void setHUDEnabled(bool enabled);
        bool isHUDEnabled() const;

        void setContentFollow(bool follow);
        bool isContentFollow() const;

        void setVerticalAlign(VerticalAlign align);
        void setHorizontalAlign(HorizontalAlign align);
        VerticalAlign getVerticalAlign() const;
        HorizontalAlign getHorizontalAlign() const;

    protected:
        void calculateTextHeight();
        void calculateTextDimensions();
        void calculateHorizontalTextOffset();
        void calculateWrappedTextDimensions(uint8 lines);

        void cleanUpText(const Wtring& str);
        int32 getLongestLine(const Wtring& str);

    private:
        Wtring checkWrapping(const Wtring& stringIn, int32 wrapWidth);
        void splitString(PointerArray<Wtring, uint32>& words, Wtring str, char delimiter);

        bool mbHud = false;
        bool mbBold = false;
        bool mbDirty = false;
        bool mbItalic = false;
        bool mbContentFollow = false;

        uint16 mSpacing = 0;
        uint16 mShadowSize = 0;
        uint16 mOutlineSize = 0;

        SPtr<Font> mFont = nullptr;
        Color mColor = Color::White;
        Color mShadowColor = Color::Black;
        Color mOutlineColor = Color::Black;

        uint32 mStringLength = 0;
        int32 mWrapWidth = NO_WRAPPING;
        Wtring mOrigText = L"", mShowText = L"";

        Vector<uint16> mVerticalOffset = {};
        Vector<uint16> mHorizontalOffset = {};
        VerticalAlign mVerticalAlign = VerticalAlign::Center;
        HorizontalAlign mHorizontalAlign = HorizontalAlign::Center;

    public:
        inline static const uint32 NO_WRAPPING = 0;
        inline static const Wtring TAB = L"    ";
        inline static const Wtring ENTER = L"\n";
        inline static const Wtring EMPTY_STRING = L"";
    };
}

#endif
