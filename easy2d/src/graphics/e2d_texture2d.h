#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "e2d_config.h"
#include "resource/e2d_resource.h"

namespace Easy2D
{
    class Texture2D final : public Resource
    {
    public:
        Texture2D(const String& pPath);
        ~Texture2D();

        bool load();

        uint32 getHeight() const;
        uint32 getWidth() const;
        GLuint getTextureID() const;

    private:
        GLint   mFormat = 0;
        GLuint  mTextureId = 0;
        uint32   mWidth = 0, mHeight = 0;
#ifdef ANDROID
        Resource mResource;
        static void CallbackRead(png_structp png, png_bytep data, png_size_t size);
#endif
    };
}

#endif
