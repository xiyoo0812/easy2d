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

        virtual void initialize();

        virtual void update(const uint32& escapeMs); 
        virtual void onHandleEvent(SPtr<Event> event);

        void setText(const Wtring& text);
        const Wtring& getText() const;

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

        void setLineWidth(uint32 lineWidth);
        uint32 getLineWidth() const;
        bool isLineWarp() const;

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

    private:
        void checkWrapping();
        void calculateTextSize(uint32 textWidth, uint32 textHeight);
        void calculateTextOffset(Vector<uint16>& lineWidths);

        bool mbContentFollow = false;

        uint32 mLineWidth = 0;
        uint32 mFrameOffset = 1;
        Wtring mOrigText = EMPTY_STRING;
        SPtr<RenderText> mRenderText = nullptr;
        VerticalAlign mVerticalAlign = VerticalAlign::Center;
        HorizontalAlign mHorizontalAlign = HorizontalAlign::Left;

    public:
        inline static String GUID = "render_text";
    };
}

#endif
