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
    Vector<Wtring> renderWords;
    Vector<uint16> lineWidths = {};
    Wtring wrapText = EMPTY_STR;
    uint16 lineWidth = 0, textWidth = 0;
    Vec2 transDim = getTransform()->getSize();
    if (isLineWarp() && mLineWidth > transDim.x - mFrameOffset * 2)
    {
        mLineWidth = transDim.x - mFrameOffset * 2;
    }
    for (auto it : mOrigText)
    {
        if (it == ENTER)
        {
            if (isLineWarp() && lineWidth > 0)
            {
                lineWidths.push_back(lineWidth);
                renderWords.push_back(wrapText);
                wrapText = EMPTY_STR;
                lineWidth = 0;
            }
            continue;
        }
        uint32 charWidth = mRenderText->mFont->getCharWidth(it, mRenderText->mbBold, mRenderText->mbItalic);
        if (isLineWarp())
        {
            if (lineWidth + charWidth > mLineWidth)
            {
                if (lineWidth > textWidth)
                {
                    textWidth = lineWidth;
                }
                if (lineWidth > 0)
                {
                    lineWidths.push_back(lineWidth);
                    renderWords.push_back(wrapText);
                    wrapText = EMPTY_STR;
                    lineWidth = 0;
                }
            }
        }
        else
        {
            textWidth += charWidth;
        }
        lineWidth += charWidth;
        wrapText.append(&it, 1);
    }
    if (lineWidth > 0)
    {
        lineWidths.push_back(lineWidth);
        renderWords.push_back(wrapText);
    }
    mRenderText->mTextList = renderWords;
    size_t lineCount = renderWords.size();
    uint32 fontHeight = mRenderText->mFont->getFontHeight();
    uint32 textHeight = fontHeight * lineCount + mRenderText->mSpacing * (lineCount - 1);
    calculateTextSize(textWidth, textHeight);
    calculateTextOffset(lineWidths);
}

void TextComponent::calculateTextSize(uint32 textWidth, uint32 textHeight)
{
    if (mbContentFollow)
    {
        getTransform()->setSize(textWidth + mFrameOffset * 2, textHeight + mFrameOffset * 2);
        return;
    }
    uint32 fontHeight = mRenderText->mFont->getFontHeight();
    if (fontHeight > getTransform()->getHeight() - mFrameOffset * 2)
    {
        getTransform()->setSizeY(fontHeight + mFrameOffset * 2);
    }
}

void TextComponent::calculateTextOffset(Vector<uint16>& lineWidths)
{
    mRenderText->mVerticalOffset.clear();
    mRenderText->mHorizontalOffset.clear();
    size_t lineCount = lineWidths.size();
    Vec2 transDim = getTransform()->getSize();
    uint32 lineWidth = isLineWarp() ? mLineWidth : (transDim.x - mFrameOffset * 2);
    uint32 fontHeight = mRenderText->mFont->getFontHeight();
    uint32 textHeight = fontHeight * lineCount + mRenderText->mSpacing * (lineCount - 1);
    for (size_t line = 0; line < lineCount; ++line)
    {
        uint32 length = lineWidths[line];
        if (mHorizontalAlign == HorizontalAlign::Center)
        {
            int32 diff = lineWidth - length;
            mRenderText->mHorizontalOffset.push_back(mFrameOffset + diff / 2);
        }
        else if (mHorizontalAlign == HorizontalAlign::Right)
        {
            int32 diff = lineWidth - length;
            mRenderText->mHorizontalOffset.push_back(mFrameOffset + diff);
        }
        else
        {
            mRenderText->mHorizontalOffset.push_back(mFrameOffset);
        }
        uint32 lineHeight = mFrameOffset + line * fontHeight + line * mRenderText->mSpacing;
        if (mVerticalAlign == VerticalAlign::Center)
        {
            int32 diff = transDim.y - textHeight;
            mRenderText->mVerticalOffset.push_back(lineHeight + diff / 2);
        }
        else if (mVerticalAlign == VerticalAlign::Bottom)
        {
            int32 diff = transDim.y - textHeight;
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