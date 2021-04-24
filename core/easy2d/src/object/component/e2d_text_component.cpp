#include "e2d_text_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_render_batch.h"

/* Easy2D */
using namespace Easy2D;

TextComponent::TextComponent() : Component(TextComponent::GUID)
{
    mRenderText = std::make_shared<RenderText>();
}

TextComponent::~TextComponent()
{
}

void TextComponent::initialize()
{

}

void TextComponent::checkWrapping()
{
    Vector<Wtring> renderWords;
    Vector<uint16> lineWidths = {};
    Wtring wrapText = EMPTY_STRING;
    uint16 lineWidth = 0, textWidth = 0;
    Vec2 transDim = getTransform()->getDimensions();
    for (auto it : mOrigText)
    {
        if (it == *(ENTER.c_str()))
        {
            if (mbLineWrap)
            {
                lineWidths.push_back(lineWidth);
                renderWords.push_back(wrapText);
                wrapText = EMPTY_STRING;
                lineWidth = 0;
            }
            continue;
        }
        uint32 charWidth = mRenderText->mFont->getCharWidth(it, mRenderText->mbBold, mRenderText->mbItalic);
        if (mbLineWrap)
        {
            if (lineWidth + charWidth > transDim.x - mFrameOffset * 2)
            {
                if (lineWidth > textWidth)
                {
                    textWidth = lineWidth;
                }
                lineWidths.push_back(lineWidth);
                renderWords.push_back(wrapText);
                wrapText = EMPTY_STRING;
                lineWidth = 0;
            }
        }
        lineWidth += charWidth;
        wrapText.append(&it);
    }
    if (!wrapText.empty())
    {
        lineWidths.push_back(lineWidth);
        renderWords.push_back(wrapText);
    }
    mRenderText->mTextList = renderWords;
    uint32 lineCount = renderWords.size();
    uint32 fontHeight = mRenderText->mFont->getMaxLetterHeight() + mRenderText->mFont->getMinLetterHeight();
    uint32 textHeight = fontHeight * lineCount + mRenderText->mSpacing * (lineCount - 1);
    calculateTextDimensions(textWidth, textHeight);
    calculateTextOffset(lineWidths);
}

void TextComponent::calculateTextDimensions(uint32 textWidth, uint32 textHeight)
{
    if (mbContentFollow)
    {
        getTransform()->setDimensions(textWidth + mFrameOffset * 2, textHeight + mFrameOffset * 2);
        return;
    }
    if (textHeight > getTransform()->getHeight())
    {
        getTransform()->setDimensionsY(textHeight + mFrameOffset * 2);
    }
}

void TextComponent::calculateTextOffset(Vector<uint16>& lineWidths)
{
    mRenderText->mVerticalOffset.clear();
    mRenderText->mHorizontalOffset.clear();
    uint32 lineCount = lineWidths.size();
    Vec2 transDim = getTransform()->getDimensions();
    uint32 fontHeight = mRenderText->mFont->getMaxLetterHeight() + mRenderText->mFont->getMinLetterHeight();
    uint32 textHeight = fontHeight * lineCount + mRenderText->mSpacing * (lineCount - 1);
    for (size_t line = 0; line < lineCount; ++line)
    {
        uint32 length = lineWidths[line];
        if (mHorizontalAlign == HorizontalAlign::Center)
        {
            uint32 diff = transDim.x - mFrameOffset * 2 - length;
            mRenderText->mHorizontalOffset.push_back(mFrameOffset + diff / 2);
        }
        else if (mHorizontalAlign == HorizontalAlign::Right)
        {
            uint32 diff = transDim.x - mFrameOffset * 2 - length;
            mRenderText->mHorizontalOffset.push_back(mFrameOffset + diff);
        }
        else
        {
            mRenderText->mHorizontalOffset.push_back(mFrameOffset);
        }
        uint32 lineHeight = mFrameOffset + line * fontHeight + (line - 1) * mRenderText->mSpacing;
        if (mVerticalAlign == VerticalAlign::Center)
        {
            uint32 diff = transDim.y - mFrameOffset * 2 - textHeight;
            mRenderText->mVerticalOffset.push_back(lineHeight + diff / 2);
        }
        else if (mVerticalAlign == VerticalAlign::Bottom)
        {
            uint32 diff = transDim.y - mFrameOffset * 2 - textHeight;
            mRenderText->mVerticalOffset.push_back(lineHeight + diff);
        }
        else
        {
            mRenderText->mVerticalOffset.push_back(lineHeight);
        }
    }
}

void TextComponent::update(const uint32& escapeMs)
{
    if (mRenderText->mFont)
    {
        if (mChanged)
        {
            checkWrapping();
            mChanged = false;
        }
        RenderBatch::getInstance()->addRenderQueue(mRenderText);
    }
}

void TextComponent::setText(const Wtring& text)
{
    mOrigText = text;
    mChanged = true;
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
    mChanged = true;
}

bool TextComponent::isBold() const
{
    return mRenderText->mbBold;
}

void TextComponent::setItalic(bool italoc)
{
    mRenderText->mbItalic = italoc;
    mChanged = true;
}

bool TextComponent::isItalic() const
{
    return mRenderText->mbItalic;
}

void TextComponent::setFont(const SPtr<Font> font)
{
    mRenderText->mFont = font;
    mChanged = true;
}

const SPtr<Font> TextComponent::getFont() const
{
    return mRenderText->mFont;
}

void TextComponent::setLineWrap(bool lineWrap)
{
    mbLineWrap = lineWrap;
    mChanged = true;
}

bool TextComponent::isLineWrap() const
{
    return mbLineWrap;
}

void TextComponent::setSpacing(uint32 spacing)
{
    mRenderText->mSpacing = spacing;
    mChanged = true;
}

uint32 TextComponent::getSpacing() const
{
    return mRenderText->mSpacing;
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
    mChanged = true;
}

bool TextComponent::isContentFollow() const
{
    return mbContentFollow;
}

void TextComponent::setVerticalAlign(VerticalAlign align)
{
    mVerticalAlign = align;
    mChanged = true;
}

void TextComponent::setHorizontalAlign(HorizontalAlign align)
{
    mHorizontalAlign = align;
    mChanged = true;
}

VerticalAlign TextComponent::getVerticalAlign() const
{
    return mVerticalAlign;
}

HorizontalAlign TextComponent::getHorizontalAlign() const
{
    return mHorizontalAlign;
}