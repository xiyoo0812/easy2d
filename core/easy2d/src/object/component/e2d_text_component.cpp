#include "e2d_render_text.h"
#include "graphics/e2d_render_batch.h"
#include "component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

TextComponent::TextComponent(const String& name) : Entity(name)
{
}

TextComponent::~TextComponent()
{
}

void TextComponent::initialize()
{

}

void TextComponent::calculateTextDimensions()
{
    getLongestLine(mShowText);
    calculateTextHeight();
}

void TextComponent::calculateWrappedTextDimensions(uint8 lines)
{
    mDimensions.y = (mFont->getMaxLetterHeight() * lines) + (mSpacing * (lines - 1));
    getTransform()->setDimensionsY(mDimensions.y);
}

void TextComponent::calculateTextHeight()
{
    auto count = std::count(mShowText.begin(), mShowText.end(), ENTER);
    ++count;
    mDimensions.y = (mFont->getMaxLetterHeight() * count) + (mSpacing * (count - 1));
    mTextInfo->mTextHeight = mDimensions.y;
    getTransform()->setDimensionsY(mDimensions.y);
}

void TextComponent::cleanUpText(const Wtring& str)
{
    size_t length = str.length();
    mShowText = EMPTY_STRING;
    for (size_t i = 0; i < length; ++i)
    {
        if (str[i] == L'\t')
        {
            mShowText += TAB;
        }
        else
        {
            mShowText += str[i];
        }
    }
    calculateHorizontalTextOffset();
}

void TextComponent::calculateHorizontalTextOffset()
{
    mAlianOffset.clear();
    if (mTextAlignment == HorizontalAlign::Center)
    {
        uint32 counter(0);
        uint32 length = getLongestLine(mShowText);
        if (length == 0)
        {
            mTextInfo->mText = mShowText;
        }
        else
        {
            mTextInfo->mText = EMPTY_STRING;
            Wtring substr(EMPTY_STRING);
            for (size_t i = 0; i < mShowText.length(); ++i)
            {
                if (mShowText[i] == L'\n')
                {
                    mTextInfo->mText += substr + L'\n';

                    uint32 diff = length - mFont->getStringLength(substr);
                    if (diff > 0)
                    {
                        diff /= 2;
                    }
                    mTextInfo->mAlianOffset.push_back(diff);

                    substr = EMPTY_STRING;
                    counter = 0;
                }
                else
                {
                    substr += mShowText[i];
                    ++counter;
                }
            }
            mTextInfo->mText += substr;

            uint32 diff = length - mFont->getStringLength(substr);
            if (diff > 0)
            {
                diff /= 2;
            }
            mTextInfo->mAlianOffset.push_back(diff);
        }
    }
    else if (mTextAlignment == HorizontalAlign::Right)
    {
        uint32 counter(0);
        uint32 length = getLongestLine(mShowText);
        if (length == 0)
        {
            mTextInfo->mText = mShowText;
        }
        else
        {
            mTextInfo->mText = EMPTY_STRING;
            Wtring substr(EMPTY_STRING);
            for (size_t i = 0; i < mShowText.length(); ++i)
            {
                if (mShowText[i] == L'\n')
                {
                    mTextInfo->mText += substr + L'\n';

                    uint32 diff = length - mFont->getStringLength(substr);
                    mTextInfo->mAlianOffset.push_back(diff);

                    substr = EMPTY_STRING;
                    counter = 0;
                }
                else
                {
                    substr += mShowText[i];
                    ++counter;
                }
            }

            mTextInfo->mText += substr;

            uint32 diff = length - mFont->getStringLength(substr);
            mTextInfo->mAlianOffset.push_back(diff);
        }
    }
    else
    {
        getLongestLine(mShowText);
        mTextInfo->mText = mShowText;
        mTextInfo->mAlianOffset.push_back(0);
        auto n = std::count(mShowText.begin(), mShowText.end(), _T('\n'));
        for (; n > 0; --n)
        {
            mTextInfo->mAlianOffset.push_back(0);
        }
    }
}

int32 TextComponent::getLongestLine(const Wtring& str)
{
    int32 length(0);
    Wtring substr(EMPTY_STRING);
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == _T('\n'))
        {
            int32 strLength = mFont->getStringLength(substr);
            if (strLength > length)
            {
                length = strLength;
                mDimensions.x = strLength;
                getTransform()->setDimensionsX(mDimensions.x);
            }
            substr = EMPTY_STRING;
        }
        else
        {
            substr += str[i];
        }
    }

    int32 strLength = mFont->getStringLength(substr);
    if (strLength > length)
    {
        length = strLength;
        mDimensions.x = strLength;
        getTransform()->setDimensionsX(mDimensions.x);
    }
    return length;
}


Wtring TextComponent::checkWrapping(const Wtring& stringIn, int32 wrapWidth)
{
    Wtring line(EMPTY_STRING), returnString(EMPTY_STRING);

    PointerArray<Wtring, uint32> words;
    splitString(words, stringIn, _T(' '));

    mDimensions.y = mFont->getMaxLetterHeight();
    getTransform()->setDimensionsY(mDimensions.y);

    uint8 lines(1);

    for (uint32 i = 0; i < words.amount; ++i)
    {
        size_t n_count = words.elements[i].find(L'\n');
        if (n_count != String::npos)
        {
            if (words.elements[i][0] == L'\n')
            {
                returnString += line + L'\n';
                line = words.elements[i].substr(0, words.elements[i].size() - 1);
            }
            else
            {
                returnString += line + words.elements[i];
                line = EMPTY_STRING;
            }
            ++lines;
        }
        else
        {
            int32 w = mFont->getStringLength(line + words.elements[i]);
            if (w > mDimensions.x)
            {
                mDimensions.x = w;
                getTransform()->setDimensionsX(mDimensions.x);
            }
            if (w > wrapWidth)
            {
                returnString += line + L"\n";
                ++lines;
                line = EMPTY_STRING;
            }
            line += words.elements[i] + L" ";
        }
    }

    delete[] words.elements;
    calculateWrappedTextDimensions(lines);
    return returnString + line;
}

void TextComponent::splitString(PointerArray<Wtring, uint32>& words, Wtring str, char delimiter)
{
    words.amount = std::count(str.begin(), str.end(), delimiter) + 1;
    words.elements = new Wtring[words.amount];
    size_t n = 0, pos = 0;
    for (; n < words.amount - 1; ++n)
    {
        pos = str.find(delimiter);
        words.elements[n] = str.substr(0, pos);
        str.erase(0, pos + 1);
    }
    words.elements[n] = str;
}

void TextComponent::update(const uint32& escapeMs)
{
    if (mFont && !mOrigText.empty())
    {
        RenderBatch::getInstance()->addRenderQueue(std::dynamic_pointer_cast<TextComponent>(shared_from_this()));
    }
}

void TextComponent::setText(const Wtring& text)
{
    mOrigText = text;
}

const Wtring& TextComponent::getText() const
{
    return mOrigText;
}

const Wtring& TextComponent::getShowText() const
{
    return mShowText;
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
}

bool TextComponent::isBold() const
{
    return mbBold;
}

void TextComponent::setItalic(bool italoc)
{
    mbItalic = italoc;
}

bool TextComponent::isItalic() const
{
    return mbItalic;
}

void TextComponent::setFont(const SPtr<Font> font)
{
    mFont = font;
}

const SPtr<Font> TextComponent::getFont() const
{
    return mFont;
}

void TextComponent::setWrapWidth(int32 width)
{
    mWrapWidth = width;
}

int32 TextComponent::getWrapWidth() const
{
    return mWrapWidth;
}

void TextComponent::setSpacing(uint32 spacing)
{
    mSpacing = spacing;
}

uint32 TextComponent::getSpacing() const
{
    return mSpacing;
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
}

bool TextComponent::isContentFollow() const
{
    return mbContentFollow;
}

void TextComponent::setVerticalAlign(VerticalAlign align)
{
    mVerticalAlign = align;
}

void TextComponent::setHorizontalAlign(HorizontalAlign align)
{
    mHorizontalAlign = align;
}

VerticalAlign TextComponent::getVerticalAlign() const
{
    return mVerticalAlign;
}

HorizontalAlign TextComponent::getHorizontalAlign() const
{
    return mHorizontalAlign;
}