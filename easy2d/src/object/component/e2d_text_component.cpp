#include "e2d_text_component.h"
#include "e2d_transform_component.h"
#include "object/e2d_entity.h"
#include "graphics/e2d_render_batch.h"
#include "graphics/e2d_graphics_mgr.h"

/* Easy2D */
using namespace Easy2D;

TextComponent::TextComponent() : Component(TextComponent::GUID)
{
    mRenderText = std::make_shared<RenderText>();
}

TextComponent::~TextComponent()
{
}

bool TextComponent::setup(SPtr<Entity> master)
{
    setMaster(master);
    master->addTrigger(TransformEvent::GUID, std::dynamic_pointer_cast<EventListerner>(shared_from_this()));
    return true;
}

void TextComponent::checkWrapping()
{
    mRenderChars.clear();
    Vector<uint16> lineWidths;
    Vector<RenderChar> lineChars;
    float32 textWidth = 0, offsetX = mFrameOffset, offsetY = mFrameOffset;
    uint16 fontHeight = mRenderText->mFont->getFontHeight();
    uint16 lineHeight = fontHeight + mRenderText->mSpacing;
    uint16 index = 0;
    for (auto it : mOrigText)
    {
        if (it == ENTER)
        {
            index++;
            offsetX = mFrameOffset;
            offsetY += lineHeight;
            lineWidths.push_back(textWidth);
            mRenderChars.push_back(lineChars);
            lineChars.clear();
            continue;
        }
        auto fChar = mRenderText->mFont->getFontChar(it, mRenderText->mbBold, mRenderText->mbItalic);
        if (!fChar)
        {
            continue;
        }
        uint32 charWidth = fChar->advence;
        if (isLineWarp())
        {
            uint32 curWidth = offsetX + charWidth + mFrameOffset;
            if (curWidth > mLineWidth)
            {
                if (curWidth > textWidth)
                {
                    textWidth = curWidth;
                }
                offsetX = mFrameOffset;
                offsetY += lineHeight;
                lineWidths.push_back(textWidth);
                mRenderChars.push_back(lineChars);
                lineChars.clear();
            }
        }
        else
        {
            textWidth += charWidth;
        }
        RenderChar rChar;
        rChar.mIndex = index++;
        rChar.mTextureID = fChar->textureID;
        rChar.mLocal = Vec2(offsetX, offsetY);
        rChar.setUvCooreds(fChar->uvCoords);
        lineChars.push_back(rChar);
        offsetX += charWidth;
    }
    float32 textHeight = offsetY + mFrameOffset;
    if (!lineChars.empty())
    {
        lineWidths.push_back(textWidth);
        mRenderChars.push_back(lineChars);
        textHeight += lineHeight;
    }
    const Vec2& contentSize = getTransform()->getContentSize();
    if (textWidth > contentSize.x || textHeight > contentSize.y)
    {
        float32 cx = std::max(textWidth, contentSize.x);
        float32 cy = std::max(textHeight, contentSize.y);
        getTransform()->setContentSize(cx, cy);
        if (mbContentFollow)
        {
            getTransform()->setSize(cx, cy);
        }
    }
    calculateTextOffset(lineWidths, textHeight);
}

void TextComponent::calculateTextOffset(Vector<uint16>& lineWidths, uint32 textHeight)
{
    uint32 diffY = 0;
    size_t lineCount = lineWidths.size();
    const Vec2& contentSize = getTransform()->getContentSize();
    if (mVerticalAlign == VerticalAlign::Center)
    {
        diffY = (contentSize.y - textHeight) / 2;
    }
    else if (mVerticalAlign == VerticalAlign::Bottom)
    {
        diffY = contentSize.y - textHeight;
    }
    uint32 lineWidth = contentSize.x - mFrameOffset * 2;
    for (size_t line = 0; line < lineCount; ++line)
    {
        uint32 diffX = 0;
        uint32 length = lineWidths[line];
        Vector<RenderChar>& rChars = mRenderChars[line];
        if (mHorizontalAlign == HorizontalAlign::Center)
        {
            diffX = (lineWidth - length / 2);
        }
        else if (mHorizontalAlign == HorizontalAlign::Right)
        {
            diffX = lineWidth - length;
        }
        for (auto rChar : rChars)
        {
            rChar.mLocal.x += diffX;
            rChar.mLocal.y += diffY;
        }
    }
}

void TextComponent::update(const uint32& escapeMs)
{
    if (mRenderText->mFont)
    {
        if (mbChanged)
        {
            checkWrapping();
            mRenderText->matWorld = getTransform()->getWorldMatrix();
            mbChanged = false;
        }
        RenderBatch::instance()->addRenderQueue(mRenderText);
    }
}

void TextComponent::onHandleEvent(SPtr<Event> event)
{
    if (event->getGuid() == TransformEvent::GUID)
    {
        mbChanged = true;
    }
}

void TextComponent::setText(const Wtring& text)
{
    mOrigText = text;
    mbChanged = true;
}

const Wtring& TextComponent::getText() const
{
    return mOrigText;
}

void TextComponent::setColor(const Color& color)
{
    mRenderText->mColor = color;
}

const Color& TextComponent::getColor() const
{
    return mRenderText->mColor;
}

void TextComponent::setShadowColor(const Color& color, uint16 shodowSize /* = 1 */)
{
    mRenderText->mShadowColor = color;
    mRenderText->mShadowSize = shodowSize;
}

const Color& TextComponent::getShadowColor() const
{
    return mRenderText->mShadowColor;
}

uint16 TextComponent::getShadowSize() const
{
    return mRenderText->mShadowSize;
}

void TextComponent::setOutlineColor(const Color& color, uint16 outlineSize /* = 1 */)
{
    mRenderText->mOutlineColor = color;
    mRenderText->mOutlineSize = outlineSize;
}

const Color& TextComponent::getOutlineColor() const
{
    return mRenderText->mOutlineColor;
}

uint16 TextComponent::getOutlineSize() const
{
    return mRenderText->mOutlineSize;
}

void TextComponent::setBold(bool bold)
{
    mRenderText->mbBold = bold;
    mbChanged = true;
}

bool TextComponent::isBold() const
{
    return mRenderText->mbBold;
}

void TextComponent::setItalic(bool italoc)
{
    mRenderText->mbItalic = italoc;
    mbChanged = true;
}

bool TextComponent::isItalic() const
{
    return mRenderText->mbItalic;
}

void TextComponent::setFont(const SPtr<Font> font)
{
    mRenderText->mFont = font;
    mbChanged = true;
}

const SPtr<Font> TextComponent::getFont() const
{
    return mRenderText->mFont;
}

void TextComponent::setLineWidth(uint32 lineWidth)
{
    mLineWidth = lineWidth;
    mbChanged = true;
}

bool TextComponent::isLineWarp() const
{
    return mLineWidth > 0;
}

uint32 TextComponent::getLineWidth() const
{
    return mLineWidth;
}

void TextComponent::setSpacing(uint32 spacing)
{
    mRenderText->mSpacing = spacing;
    mbChanged = true;
}

uint32 TextComponent::getSpacing() const
{
    return mRenderText->mSpacing;
}

void TextComponent::setFrameOffset(uint32 offset)
{
    mFrameOffset = offset;
    mbChanged = true;
}

uint32 TextComponent::getFrameOffset() const
{
    return mFrameOffset;
}

void TextComponent::setHUDEnabled(bool enabled)
{
    mRenderText->mbHud = enabled;
}

bool TextComponent::isHUDEnabled() const
{
    return mRenderText->mbHud;
}

void TextComponent::setContentFollow(bool follow)
{
    mbContentFollow = follow;
    mbChanged = true;
}

bool TextComponent::isContentFollow() const
{
    return mbContentFollow;
}

void TextComponent::setVerticalAlign(VerticalAlign align)
{
    mVerticalAlign = align;
    mbChanged = true;
}

void TextComponent::setHorizontalAlign(HorizontalAlign align)
{
    mHorizontalAlign = align;
    mbChanged = true;
}

VerticalAlign TextComponent::getVerticalAlign() const
{
    return mVerticalAlign;
}

HorizontalAlign TextComponent::getHorizontalAlign() const
{
    return mHorizontalAlign;
}