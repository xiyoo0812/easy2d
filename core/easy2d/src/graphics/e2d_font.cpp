#include "e2d_font.h"
#include "resource\e2d_asset_mgr.h"

using namespace Easy2D;

Font::Font(const Path& path, uint32 size, FT_Library library)
    : Resource(path)
    , mFTLibrary(library)
    , mSize(size)
{

}

Font::~Font()
{
    unload();
    mCharacterInfoMap.clear();
}

bool Font::load()
{
    if (!mbLoad)
    {
        Bytes fontData;
        if (!AssetManager::getInstance()->loadAssetData(mPath, fontData))
        {
            LOG_ERROR << _T("Font::load loadAssetData failed!");
            return false;
        }
        FT_Error error = FT_New_Memory_Face(mFTLibrary, fontData.data(), fontData.size(), 0, &mFace);
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
        FT_Set_Char_Size(mFace, mSize << 6, mSize << 6, FONT_DPI, FONT_DPI);
        mTextures = new GLuint[FONT_TEXTURES];
        glGenTextures(FONT_TEXTURES, mTextures);
        for (uchar i = 0; i < FONT_TEXTURES; ++i)
        {
            mCharacterInfoMap.insert(std::make_pair(i, CharacterInfo()));
            make_D_List(mFace, i, mTextures);
        }
        FT_Done_Face(mFace);
        mbLoad = true;
    }    
    return true;
}

void Font::unload()
{
    mFace = nullptr;
    mFTLibrary = nullptr;
    if (mTextures)
    {
        glDeleteTextures(FONT_TEXTURES, mTextures);
        safeDeleteArray(mTextures);
    }
}

void Font::make_D_List(FT_Face face, uchar ch, GLuint* tex_base)
{
    auto error = FT_Load_Char(face, ch, FT_LOAD_DEFAULT);
    if (error)
    {
        LOG_ERROR << _T("Font::make_D_List FT_Load_Char error! ch: ") << ch;
        return;
    }
    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error)
    {
        LOG_ERROR << _T("Font::make_D_List FT_Render_Glyph error! ch: ") << ch;
        return;
    }

    FT_Bitmap& bitmap = face->glyph->bitmap;

    uint32 width = nextPowerOfTwo(bitmap.width);
    uint32 height = nextPowerOfTwo(bitmap.rows);

    GLubyte* expanded_data = new GLubyte[2 * width * height];

    for (uint32 j = 0; j < height; ++j)
    {
        for (uint32 i = 0; i < width; ++i)
        {
            expanded_data[2 * (i + j * width)] = 255;
            expanded_data[2 * (i + j * width) + 1] = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
        }
    }

    glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#ifdef WIN32
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
#else
    //For android "internal format" must be the same as "format" in glTexImage2D
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
#endif
    delete[] expanded_data;

    //uvs
    float32 x = static_cast<float32>(bitmap.width) / static_cast<float32>(width);
    float32 y = static_cast<float32>(bitmap.rows) / static_cast<float32>(height);
    //letter height
    int32 dimX = (face->glyph->metrics.horiAdvance / 64);
    int32 dimY = ((face->glyph->metrics.horiBearingY) - (face->glyph->metrics.height)) / 64;
    if (mMaxLetterHeight < face->glyph->bitmap_top)
    {
        mMaxLetterHeight = face->glyph->bitmap_top;
    }
    if (mMinLetterHeight > dimY)
    {
        mMinLetterHeight = dimY;
    }
    mCharacterInfoMap.at(ch).letterDimensions = Vec2(dimX, dimY);
    mCharacterInfoMap.at(ch).vertexDimensions = Vec2(bitmap.width, bitmap.rows);
    mCharacterInfoMap.at(ch).uvDimensions = Vec2(x, y);
}


GLuint* Font::getTextures() const
{
    return mTextures;
}

uint32 Font::getFontSize() const
{
    return mSize;
}

uint32 Font::nextPowerOfTwo(uint32 number) const
{
    uint32 rval = 1;
    while (rval < number)
    {
        rval <<= 1;
    }
    return rval;
}

const UnorderedMap<uchar, CharacterInfo>& Font::getCharacterInfoMap() const
{
    return mCharacterInfoMap;
}

const CharacterInfo& Font::getCharacterInfo(uchar character) const
{
    //[COMMENT] Performing a good check here 
    //with std::find will only slow things down
    //If the map.at has an unknown value, it will throw an exception anyway
    return mCharacterInfoMap.at(character);
}

uint32 Font::getMaxLetterHeight() const
{
    return mMaxLetterHeight;
}

uint32 Font::getMinLetterHeight() const
{
    return mMinLetterHeight;
}

uint32 Font::getStringLength(const String& string) const
{
    int32 length = 0;
    const char* line = string.c_str();
    for (uint32 i = 0; line[i] != 0; ++i)
    {
        length += mCharacterInfoMap.at(line[i]).letterDimensions.x;
    }
    return length;
}
