#include "e2d_font.h"
#include "e2d_font_mgr.h"
#include "resource/e2d_stream.h"

using namespace Easy2D;

Font::Font(const Path& path, uint32 size)
    : Resource(path)
    , mFontSize(size)
{

}

Font::~Font()
{
    unload();
    mFontCharMap.clear();
}

bool Font::load()
{
    if (!mbLoad)
    {
        FT_Library fLibrary = FontManager::getInstance()->getLibrary();
        auto fontData = FontManager::getInstance()->getStream(mPath);
        if (fontData == nullptr)
        {
            LOG_ERROR << _T("Font::load loadAsset failed!");
            return false;
        }
        FT_Error error = FT_New_Memory_Face(fLibrary, fontData->data(), fontData->size(), 0, &mFace);
        if (error == FT_Err_Unknown_File_Format)
        {
            LOG_ERROR << _T("Font::load FT_New_Memory_Face file format error!");
            return false;
        }
        else if (error)
        {
            LOG_ERROR << _T("Font::load FT_New_Memory_Face file error! code: ") << error;
            return false;
        }

        FT_Set_Char_Size(mFace, mFontSize << 6, mFontSize << 6, mFontDpi, mFontDpi);
        mTextures = new GLuint[FONT_TEXTURE_NUM];
        glGenTextures(FONT_TEXTURE_NUM, mTextures);
        for (int i = 0; i < FONT_TEXTURE_NUM; ++i)
        {
            glBindTexture(GL_TEXTURE_2D, mTextures[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 0);
        }
        mTextureIndex = 0;
        mbLoad = true;
    }    
    return true;
}

void Font::unload()
{
    if (mFace)
    {
        FT_Done_Face(mFace);
        mFace = nullptr;
    }
    if (mTextures)
    {
        glDeleteTextures(FONT_TEXTURE_NUM, mTextures);
        safeDeleteArray(mTextures);
    }
}

SPtr<FontChar> Font::loadFontChar(wchar_t ch)
{
    auto error = FT_Load_Char(mFace, ch, FT_LOAD_DEFAULT);
    if (error)
    {
        LOG_ERROR << _T("Font::loadFontChar FT_Load_Char error! ch: ") << ch;
        return nullptr;
    }
    error = FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL);
    if (error)
    {
        LOG_ERROR << _T("Font::loadFontChar FT_Render_Glyph error! ch: ") << ch;
        return nullptr;
    }
    FT_Bitmap& bitmap = mFace->glyph->bitmap;

    uint32 width = bitmap.width  + bitmap.width % 2;
    uint32 height = bitmap.rows;

    GLubyte* expanded_data = new GLubyte[2 * width * height];
    for (uint32 j = 0; j < height; ++j)
    {
        for (uint32 i = 0; i < width; ++i)
        {
            expanded_data[2 * (i + j * width)] = 255;
            expanded_data[2 * (i + j * width) + 1] = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
        }
    }
    //letter height
    int32 dimX = (mFace->glyph->metrics.horiBearingX / 64);
    int32 dimY = ((mFace->glyph->metrics.horiBearingY) - (mFace->glyph->metrics.height)) / 64;
    if (mMaxLetterHeight < mFace->glyph->bitmap_top)
    {
        mMaxLetterHeight = mFace->glyph->bitmap_top;
    }
    if (mMinLetterHeight > dimY)
    {
        mMinLetterHeight = dimY;
    }
    mTextureLineY = (mTextureLineY < height) ? height : mTextureLineY;
    if (mTextureX + width >= FONT_TEXTURE_SIZE)
    {
        mTextureX = 0;
        mTextureY += mTextureLineY;
    }
    if (mTextureY + height >= FONT_TEXTURE_SIZE)
    {
        mTextureIndex++;
        mTextureX = mTextureY = 0;
    }
    auto fChar = std::make_shared<FontChar>();
    fChar->textureID = mTextures[mTextureIndex];
    fChar->letterDimensions = Vec2(dimX, dimY);
    fChar->vertexDimensions = Vec2(width, height);
    fChar->advence = (mFace->glyph->metrics.horiAdvance / 64);
    fChar->uvCoordTL = Vec2(mTextureX / FONT_TEXTURE_SIZE, mTextureY / FONT_TEXTURE_SIZE);
    fChar->uvCoordBR = Vec2((mTextureX + width) / FONT_TEXTURE_SIZE, (mTextureY + height) / FONT_TEXTURE_SIZE);
    glBindTexture(GL_TEXTURE_2D, mTextures[mTextureIndex]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, mTextureX, mTextureY, width, height, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
    mTextureX += width;
    mFontCharMap.insert(std::make_pair(ch, fChar));
    safeDeleteArray(expanded_data);
    return fChar;
}


uint32 Font::getFontSize() const
{
    return mFontSize;
}


const SPtr<FontChar> Font::getFontChar(wchar_t ch)
{
    auto it = mFontCharMap.find(ch);
    if (it != mFontCharMap.end())
    {
        return it->second;
    }
    return loadFontChar(ch);
}

uint32 Font::getMaxLetterHeight() const
{
    return mMaxLetterHeight;
}

uint32 Font::getMinLetterHeight() const
{
    return mMinLetterHeight;
}


uint32 Font::getStringLength(const Wtring& string)
{
    uint32 length = 0;
    for (auto it : string)
    {
        auto fChar = getFontChar(it);
        if (fChar != nullptr)
        {
            length += fChar->advence;
        }
    }
    return length;
}
