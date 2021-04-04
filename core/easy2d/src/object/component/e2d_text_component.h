#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "base/e2d_color.h"
#include "object/e2d_component.h"
#include "graphics/e2d_font_mgr.h"

namespace Easy2D
{
    class TextInfo
    {
    public:
        SPtr<Font> font = nullptr;
        SPtr<TransformComponent> transform = nullptr;
        Color colorMultiplier = Color::White;
        Vector<int32> horizontalTextOffset = {};
        int32 verticalSpacing = 0;
        int32 textHeight = 10;
        bool bIsHud = false;
        String text = "";
    };

    class TextComponent : public Component
    {
    public:
        TextComponent(const String& fontName);

        virtual ~TextComponent();

        void draw();

        virtual void update(const uint32& escapeMs);

        virtual bool checkCulling(float32 left, float32 right, float32 top, float32 bottom) const;

        void setText(const String& text);

        const String& getText() const;

        void setColor(const Color& color);

        const Color& getColor() const;

        void setWrapWidth(int32 width);

        int32 getWrapWidth() const;

        void setVerticalSpacing(uint32 spacing);

        void setHUDOptionEnabled(bool enabled);

        bool isHUDOptionEnabled() const;

        void alignTextLeft();

        void alignTextCenter();

        void alignTextRight();

    protected:
        enum class HorizontalAlignment : byte
        {
            left = 0,
            center,
            right
        };

        virtual void initialize();

        void calculateTextDimensions();

        void calculateWrappedTextDimensions(uint8 lines);

        void calculateTextHeight();

        void cleanUpText(const String & str);

        void calculateHorizontalTextOffset();

        int32 getLongestLine(const String & str);

        virtual void fillTextInfo();

    private:
        String checkWrapping(const String& stringIn, int32 wrapWidth);

        void splitString(PointerArray<String, uint32>& words, String str, char delimiter);

        int32 mWrapWidth = 10;
        uint32	mFontSize = 10, mStringLength = 0;
        String mFontName = "", mOrigText = "", mEditText = "";

        SPtr<Font> mFont = nullptr;
        SPtr<TextInfo> mTextInfo = nullptr;
        Color mTextColor = Color::White;
        HorizontalAlignment mTextAlignment = HorizontalAlignment::center;
    };
}

#endif
