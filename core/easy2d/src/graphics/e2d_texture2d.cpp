#include "e2d_texture2d.h"
#include "e2d_image.h"

using namespace Easy2D;

Texture2D::Texture2D(const String& pPath)
    : mPath(pPath)
#ifdef ANDROID
	, mResource(pPath)
#endif
{
	load();
}

#ifdef ANDROID
void Texture2D::CallbackRead(png_structp png, png_bytep data, png_size_t size)
{
	Resource& lReader = *((Resource*)png_get_io_ptr(png));
	if(!lReader.Read(data,size))
	{
		lReader.Close();
		png_error(png, "Error while reading PNG file");
	}
}
#endif

Texture2D::~Texture2D()
{
	if(mTextureId != 0)
	{
		glDeleteTextures(1, &mTextureId);
		mTextureId = 0;
	}
	mWidth = 0;
	mHeight = 0;
	mFormat = 0;
}

void Texture2D::load()
{
    Image image;
    if (image.loadImage(mPath))
    {
        mWidth = image.getWidth();
        mHeight = image.getHeight();
        mFormat = image.getFormat();
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, image.getBuffer());
    }
}

const String & Texture2D::getPath() const
{
	return mPath;
}

int32 Texture2D::getHeight() const
{
	return mHeight;
}

int32 Texture2D::getWidth() const
{
	return mWidth;
}

GLuint Texture2D::getTextureID() const
{
	return mTextureId;
}
