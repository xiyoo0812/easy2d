#ifndef FONT_H
#define FONT_H

#include "ft2build.h"
#include "freetype/freetype.h"

#include "e2d_config.h"
#include "resource/e2d_resource.h"
#include "resource/e2d_stream.h"

namespace Easy2D
{
    class FontChar
    {
    public:
        GLuint texId = 0;
        Vec2 vertexDimensions = Vec2(0, 0);
        Vec2 letterDimensions = Vec2(0, 0);
        Vec2 uvCoordTL = Vec2(0, 0), uvCoordBR = Vec2(1, 1);
    };

    class Font final : public Resource
    {
    public:
        Font(const Path& path, uint32 size, FT_Library library);
        ~Font();

        bool load();

        uint32 getFontSize() const;

        const SPtr<FontChar> getFontChar(wchar_t ch);

        uint32 getMaxLetterHeight() const;
        uint32 getMinLetterHeight() const;
        uint32 getStringLength(const Wtring& string);

    private:
        void unload();
        uint32 nextPowerOfTwo(uint32 number) const;
        SPtr<FontChar> loadFontChar(wchar_t ch);

        GLuint* mTextures = 0;
        GLuint mTextureIndex = 0;
        FT_Face mFace = nullptr;
        FT_Library mFTLibrary = nullptr;
        SPtr<Stream> mFontData = nullptr;
        uint32 mFontDpi = 72, mFontSize = 0;
        float32 mTextureX = 0, mTextureY = 0, mTextureLineY = 0;
        uint32 mMaxLetterHeight = 0, mMinLetterHeight = 0;
        UnorderedMap<wchar_t, SPtr<FontChar>> mFontCharMap;

        inline static uint32 FONT_TEXTURE_NUM = 8;
        inline static uint32 FONT_TEXTURE_SIZE = 1024;
    };
}

#endif
