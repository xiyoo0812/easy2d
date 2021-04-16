#include "e2d_text_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_render_batch.h"

/* Easy2D */
using namespace Easy2D;

TextComponent::TextComponent() : Component(TextComponent::GUID)
{
    mTextInfo = std::make_shared<RenderText>();
}

TextComponent::~TextComponent()
{
}

void TextComponent::initialize()
{
    /*if (mWrapWidth == NO_WRAPPING)
    {
        cleanUpText(mOrigText);
        calculateTextDimensions();
    }
    else
    {
        cleanUpText(checkWrapping(mOrigText, mWrapWidth));
    }
    fillTextInfo();*/
}

void TextComponent::fillTextInfo()
{
    mTextInfo->mFont = mFont;
    mTextInfo->mTransform = getTransform();
    mTextInfo->mType = RenderObjectType::ObjectText;
}

void TextComponent::calculateTextDimensions()
{
    getLongestLine(mEditText);
    calculateTextHeight();
}

void TextComponent::calculateWrappedTextDimensions(uint8 lines)
{
    mDimensions.y = (mFont->getMaxLetterHeight() * lines) + (mTextInfo->mSpacing * (lines - 1));
    getTransform()->setDimensionsYSafe(mDimensions.y);
}

void TextComponent::calculateTextHeight()
{
    auto count = std::count(mEditText.begin(), mEditText.end(), _T('\n'));
    ++count;
    mDimensions.y = (mFont->getMaxLetterHeight() * count) + (mTextInfo->mSpacing * (count - 1));
    mTextInfo->mTextHeight = mDimensions.y;
    getTransform()->setDimensionsYSafe(mDimensions.y);
}

void TextComponent::cleanUpText(const Wtring& str)
{
    size_t length = str.length();
    mEditText = EMPTY_STRING;
    for (size_t i = 0; i < length; ++i)
    {
        if (str[i] == L'\t')
        {
            mEditText += TAB;
        }
        else
        {
            mEditText += str[i];
        }
    }
    calculateHorizontalTextOffset();
}

void TextComponent::calculateHorizontalTextOffset()
{
    mTextInfo->mAlianOffset.clear();
    if (mTextAlignment == HorizontalAlignment::Center)
    {
        uint32 counter(0);
        uint32 length = getLongestLine(mEditText);
        if (length == 0)
        {
            mTextInfo->mText = mEditText;
        }
        else
        {
            mTextInfo->mText = EMPTY_STRING;
            Wtring substr(EMPTY_STRING);
            for (size_t i = 0; i < mEditText.length(); ++i)
            {
                if (mEditText[i] == L'\n')
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
                    substr += mEditText[i];
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
    else if (mTextAlignment == HorizontalAlignment::Right)
    {
        uint32 counter(0);
        uint32 length = getLongestLine(mEditText);
        if (length == 0)
        {
            mTextInfo->mText = mEditText;
        }
        else
        {
            mTextInfo->mText = EMPTY_STRING;
            Wtring substr(EMPTY_STRING);
            for (size_t i = 0; i < mEditText.length(); ++i)
            {
                if (mEditText[i] == L'\n')
                {
                    mTextInfo->mText += substr + L'\n';

                    uint32 diff = length - mFont->getStringLength(substr);
                    mTextInfo->mAlianOffset.push_back(diff);

                    substr = EMPTY_STRING;
                    counter = 0;
                }
                else
                {
                    substr += mEditText[i];
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
        getLongestLine(mEditText);
        mTextInfo->mText = mEditText;
        mTextInfo->mAlianOffset.push_back(0);
        auto n = std::count(mEditText.begin(), mEditText.end(), _T('\n'));
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
                getTransform()->setDimensionsXSafe(mDimensions.x);
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
        getTransform()->setDimensionsXSafe(mDimensions.x);
    }
    return length;
}


void TextComponent::draw()
{
    if (mTextInfo->mText.size() == 0)
    {
        return;
    }
    RenderBatch::getInstance()->addRenderQueue(mTextInfo);
}

void TextComponent::update(const uint32& escapeMs)
{
    fillTextInfo();
}

bool TextComponent::checkCulling(float32 left, float32 right, float32 top, float32 bottom) const
{
    float32 textWidth, textHeight, textW, textH;
    Pos objectPos = getTransform()->getWorldPosition();

    if (mTextInfo->mbHud)
    {
        objectPos.x += left;
        objectPos.y += bottom;
    }

    textW = float32(mFont->getStringLength(mOrigText));
    textH = float32(mFont->getMaxLetterHeight());

    textWidth = textW * getTransform()->getWorldScale().x;
    textHeight = textH * getTransform()->getWorldScale().y;

    float32 teRight = objectPos.x + textWidth;
    float32 texTop = objectPos.y + textHeight;

    return (objectPos.x <= right && teRight >= left) && (objectPos.y <= top && texTop >= bottom);
}


void TextComponent::setText(const Wtring& text)
{
    mOrigText = text;
    if (mWrapWidth != NO_WRAPPING)
    {
        cleanUpText(checkWrapping(mOrigText, int32(mWrapWidth)));
    }
    else
    {
        cleanUpText(mOrigText);
        calculateTextDimensions();
    }
    mStringLength = mFont->getStringLength(mOrigText);
}

const Wtring& TextComponent::getText() const
{
    return mOrigText;
}

void TextComponent::setColor(const Color& color)
{
    mTextInfo->mColor = color;
}

const Color& TextComponent::getColor() const
{
    return mTextInfo->mColor;
}

void TextComponent::setShadowColor(const Color& color, uint16 shodowSize /* = 1 */)
{
    mTextInfo->mShadowColor = color;
    mTextInfo->mShadowSize = shodowSize;
}

const Color& TextComponent::getShadowColor() const
{
    return mTextInfo->mShadowColor;
}

void TextComponent::setBold(bool bold)
{
    mTextInfo->mbBold = bold;
}

bool TextComponent::isBold() const
{
    return mTextInfo->mbBold;
}

void TextComponent::setItalic(bool italoc)
{
    mTextInfo->mbItalic = italoc;
}

bool TextComponent::isItalic() const
{
    return mTextInfo->mbItalic;
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
    if (width == NO_WRAPPING)
    {
        calculateTextDimensions();
    }
    else
    {
        mDimensions.x = 0;
        getTransform()->setDimensionsXSafe(mDimensions.x);
        cleanUpText(checkWrapping(mOrigText, mWrapWidth));
    }
}

int32 TextComponent::getWrapWidth() const
{
    return mWrapWidth;
}

Wtring TextComponent::checkWrapping(const Wtring& stringIn, int32 wrapWidth)
{
    Wtring line(EMPTY_STRING), returnString(EMPTY_STRING);

    PointerArray<Wtring, uint32> words;
    splitString(words, stringIn, _T(' '));

    mDimensions.y = mFont->getMaxLetterHeight();
    getTransform()->setDimensionsYSafe(mDimensions.y);

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
                getTransform()->setDimensionsXSafe(mDimensions.x);
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

void TextComponent::setVerticalSpacing(uint32 spacing)
{
    mTextInfo->mSpacing = spacing;
    if (mWrapWidth != NO_WRAPPING)
    {
        cleanUpText(checkWrapping(mOrigText, mWrapWidth));
    }
}

void TextComponent::setHUDOptionEnabled(bool enabled)
{
    mTextInfo->mbHud = enabled;
}

bool TextComponent::isHUDOptionEnabled() const
{
    return mTextInfo->mbHud;
}

void TextComponent::alignTextLeft()
{
    mTextAlignment = HorizontalAlignment::Left;
    calculateHorizontalTextOffset();
}

void TextComponent::alignTextCenter()
{
    mTextAlignment = HorizontalAlignment::Center;
    calculateHorizontalTextOffset();
}

void TextComponent::alignTextRight()
{
    mTextAlignment = HorizontalAlignment::Right;
    calculateHorizontalTextOffset();
}
