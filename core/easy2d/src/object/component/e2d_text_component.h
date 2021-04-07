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
        String text = "";
        bool bIsHud = false;
        int32 textHeight = 10;
        int32 verticalSpacing = 0;
        Color colorMultiplier = Color::White;
        Vector<int32> horizontalTextOffset = {};
        SPtr<TransformComponent> transform = nullptr;
        SPtr<Font> font = nullptr;
    };

    class TextComponent : public Component
    {
    public:
        TextComponent();

        virtual ~TextComponent();

        void draw();

        virtual void update(const uint32& escapeMs);

        virtual bool checkCulling(float32 left, float32 right, float32 top, float32 bottom) const;

        void setText(const String& text);

        const String& getText() const;

        void setColor(const Color& color);

        const Color& getColor() const;

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
        uint32 mStringLength = 0;
        String mOrigText = "", mEditText = "";

        SPtr<Font> mFont = nullptr;
        SPtr<TextInfo> mTextInfo = nullptr;
        HorizontalAlignment mTextAlignment = HorizontalAlignment::Center;

    public:
        inline static String GUID = "text";
    };
    
}

#endif
