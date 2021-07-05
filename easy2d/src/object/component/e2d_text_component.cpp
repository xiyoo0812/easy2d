#include "e2d_text_component.h"
#include "e2d_transform_component.h"
#include "object/e2d_entity.h"
#include "graphics/e2d_render_batch.h"
#include "graphics/e2d_graphics_mgr.h"

/* Easy2D */
using namespace Easy2D;

TextComponent::TextComponent() : Component(TextComponent::GUID)
{

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
    uint16 fontHeight = mFont->getFontHeight();
    uint16 lineHeight = fontHeight + mSpacing;
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
        auto fChar = mFont->getFontChar(it, mbBold, mbItalic);
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
        rChar.mChar = fChar;
        rChar.mIndex = index++;
        rChar.mLocal = Vec2(offsetX, offsetY);
        rChar.mTexture = std::make_shared<RenderTexture>();
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
    const Mat4& matWorld = getTransform()->getWorldMatrix();
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
            Mat4 matTrans = Easy2D::transpose(matWorld * Easy2D::translate(diffX, diffY, 0));
            rChar.mTexture->buildRect(Vec2(0), rChar.mChar->vertexSize, matTrans);
            rChar.mTexture->mTextureID = rChar.mChar->textureID;
            rChar.mTexture->setUvCooreds(rChar.mChar->uvCoords);
        }
    }
}

void TextComponent::update(const uint32& escapeMs)
{
    if (mFont)
    {
        if (mbChanged)
        {
            checkWrapping();
            mbChanged = false;
        }
        const Mat4& matWorld = getTransform()->getWorldMatrix();
        for (auto renders : mRenderChars)
        {
            for (auto rChar : renders)
            {
                /*if (mShadowSize > 0)
                {
                    for (int16 shadow = mShadowSize + mOutlineSize; shadow > mOutlineSize; shadow--)
                    {
                        auto texture = std::make_shared<RenderTexture>();
                        texture->mbHud = true;
                        texture->mColor = mShadowColor;
                        texture->mTextureID = rChar.mChar->textureID;
                        texture->setUvCooreds(rChar.mChar->uvCoords);
                        Mat4 matTrans = Easy2D::transpose(matWorld * Easy2D::translate(rChar.mLocal.x, rChar.mLocal.y, 0));
                        texture->buildRect(Vec2(0), rChar.mChar->vertexSize, matTrans);
                        RenderBatch::instance()->createSpriteQuad(texture);

                        createTextQuad(text, Vec2(shadow, shadow), text->mShadowColor);
                    }
                }
                if (text->mOutlineSize > 0)
                {
                    for (int16 outline = text->mOutlineSize; outline > 0; outline--)
                    {
                        createTextQuad(text, Vec2(-outline, -outline), text->mOutlineColor);
                        createTextQuad(text, Vec2(-outline, outline), text->mOutlineColor);
                        createTextQuad(text, Vec2(outline, -outline), text->mOutlineColor);
                        createTextQuad(text, Vec2(outline, outline), text->mOutlineColor);
                    }
                }
                createTextQuad(text, Vec2(0, 0), text->mColor);*/
                RenderBatch::instance()->createSpriteQuad(rChar.mTexture);
            }
        }
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
    mColor = color;
}

const Color& TextComponent::getColor() const
{
    return mColor;
}

void TextComponent::setShadowColor(const Color& color, uint16 shodowSize /* = 1 */)
{
    mShadowColor = color;
    mShadowSize = shodowSize;
}

const Color& TextComponent::getShadowColor() const
{
    return mShadowColor;
}

uint16 TextComponent::getShadowSize() const
{
    return mShadowSize;
}

void TextComponent::setOutlineColor(const Color& color, uint16 outlineSize /* = 1 */)
{
    mOutlineColor = color;
    mOutlineSize = outlineSize;
}

const Color& TextComponent::getOutlineColor() const
{
    return mOutlineColor;
}

uint16 TextComponent::getOutlineSize() const
{
    return mOutlineSize;
}

void TextComponent::setBold(bool bold)
{
    mbBold = bold;
    mbChanged = true;
}

bool TextComponent::isBold() const
{
    return mbBold;
}

void TextComponent::setItalic(bool italoc)
{
    mbItalic = italoc;
    mbChanged = true;
}

bool TextComponent::isItalic() const
{
    return mbItalic;
}

void TextComponent::setFont(const SPtr<Font> font)
{
    mFont = font;
    mbChanged = true;
}

const SPtr<Font> TextComponent::getFont() const
{
    return mFont;
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
    mSpacing = spacing;
    mbChanged = true;
}

uint32 TextComponent::getSpacing() const
{
    return mSpacing;
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
    mbHud = enabled;
}

bool TextComponent::isHUDEnabled() const
{
    return mbHud;
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
