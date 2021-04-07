#ifndef FONT_H
#define FONT_H

#include "ft2build.h"
#include "freetype/freetype.h"

#include "e2d_config.h"
#include "resource/e2d_resource.h"

namespace Easy2D
{
#define FONT_DPI 96
#define FONT_TEXTURES 128

    struct CharacterInfo
    {
        CharacterInfo() : vertexDimensions(), uvDimensions(), letterDimensions() { }
        Vec2 vertexDimensions, uvDimensions, letterDimensions;
    };

    class Font final : public Resource
    {
    public:
        Font(const Path& path, uint32 size, FT_Library library);
        ~Font();

        bool load();
        
        GLuint* getTextures() const;
        uint32 getFontSize() const;

        const CharacterInfo& getCharacterInfo(uchar character) const;
        const UnorderedMap<uchar, CharacterInfo>& getCharacterInfoMap() const;

        uint32 getMaxLetterHeight() const;
        uint32 getMinLetterHeight() const;
        uint32 getStringLength(const String& string) const;

    private:
        void unload();
        void make_D_List(FT_Face face, uchar ch, GLuint* tex_base);
        uint32 nextPowerOfTwo(uint32 number) const;

        uint32  mSize = 0;
        FT_Face mFace = nullptr;
        GLuint* mTextures = nullptr;
        FT_Library mFTLibrary = nullptr;
        uint32 mMaxLetterHeight = 0, mMinLetterHeight = 0;
        UnorderedMap<uchar, CharacterInfo> mCharacterInfoMap;
    };
}

#endif
