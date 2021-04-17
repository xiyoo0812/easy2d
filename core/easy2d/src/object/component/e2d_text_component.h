#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "base/e2d_color.h"
#include "object/e2d_component.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_render_object.h"

namespace Easy2D
{
    class TextComponent : public Component
    {
    public:
        TextComponent();

        virtual ~TextComponent();

        virtual void draw();

        virtual void initialize();

        virtual void update(const uint32& escapeMs);

        virtual bool checkCulling(float32 left, float32 right, float32 top, float32 bottom) const;

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

        void setWrapWidth(int32 width);
        int32 getWrapWidth() const;

        void setVerticalSpacing(uint32 spacing);

        void setHUDOptionEnabled(bool enabled);
        bool isHUDOptionEnabled() const;

        void alignTextLeft();
        void alignTextCenter();
        void alignTextRight();

    protected:
        void calculateTextHeight();
        void calculateTextDimensions();
        void calculateHorizontalTextOffset();
        void calculateWrappedTextDimensions(uint8 lines);

        void cleanUpText(const Wtring& str);
        int32 getLongestLine(const Wtring& str);

        virtual void fillTextInfo();

    private:
        Wtring checkWrapping(const Wtring& stringIn, int32 wrapWidth);
        void splitString(PointerArray<Wtring, uint32>& words, Wtring str, char delimiter);

        int32 mWrapWidth = NO_WRAPPING;
        uint32 mStringLength = 0;
        Wtring mOrigText = L"", mEditText = L"";

        SPtr<Font> mFont = nullptr;
        SPtr<RenderText> mTextInfo = nullptr;
        HorizontalAlignment mTextAlignment = HorizontalAlignment::Center;

    public:
        inline static String GUID = "text";
    };
    
}

#endif
