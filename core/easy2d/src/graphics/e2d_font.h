#ifndef FONT_H
#define FONT_H

#include "ft2build.h"
#include "freetype/freetype.h"

#include "e2d_config.h"

namespace Easy2D
{
#define FONT_DPI 96
#define FONT_TEXTURES 128

    struct CharacterInfo
    {
        CharacterInfo() : vertexDimensions(), uvDimensions(), letterDimensions() { }
        Vec2 vertexDimensions, uvDimensions, letterDimensions;
    };

    class Font
    {
    public:
        Font() {}
        ~Font();

        bool load(const String& path, uint32 size, FT_Library& library);
        void unload();

        const String& getFontPath() const;

        GLuint* getTextures() const;
        uint32 getFontSize() const;

        const CharacterInfo& getCharacterInfo(uchar character) const;
        const UnorderedMap<uchar, CharacterInfo>& getCharacterInfoMap() const;

        uint32 getMaxLetterHeight() const;
        uint32 getMinLetterHeight() const;
        uint32 getStringLength(const String& string) const;

    private:
        void make_D_List(FT_Face face, uchar ch, GLuint* tex_base);
        uint32 nextPowerOfTwo(uint32 number) const;

        uint32  mSize = 0;
        String  mFontPath = "";
        FT_Face mFace = nullptr;
        GLuint* mTextures = nullptr;
        uint32 mMaxLetterHeight = 0, mMinLetterHeight = 0;
        UnorderedMap<uchar, CharacterInfo> mCharacterInfoMap;

#ifdef ANDROID
        BYTE* mFontBuffer;
#endif
    };
}

#endif
