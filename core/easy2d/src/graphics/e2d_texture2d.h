#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "e2d_config.h"

namespace Easy2D
{
	class Texture2D final
	{
    public:
        Texture2D(const String& pPath);
        Texture2D(Texture2D&& yRef);
        Texture2D(const Texture2D& yRef);
        Texture2D& operator=(Texture2D&& yRef);
        Texture2D& operator=(const Texture2D& yRef);
        ~Texture2D();

		int32 getHeight() const;
		int32 getWidth() const;
        GLuint getTextureID() const;
        const String & getPath() const;

    private:
        void load();

        String  mPath = "";
        GLint   mFormat = 0;
		GLuint  mTextureId = 0;	
		int32   mWidth = 0, mHeight = 0;
#ifdef ANDROID
		Resource mResource;
		static void CallbackRead(png_structp png, png_bytep data, png_size_t size);
#endif
	};
}

#endif
