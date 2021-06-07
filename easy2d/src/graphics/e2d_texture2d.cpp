#include "e2d_texture2d.h"
#include "e2d_picture.h"
#include "resource\e2d_asset_mgr.h"

using namespace Easy2D;

Texture2D::Texture2D(const String& pPath)
    : Resource(pPath)
{
}

Texture2D::~Texture2D()
{
    if (mTextureId != 0)
    {
        glDeleteTextures(1, &mTextureId);
        mTextureId = 0;
    }
    mWidth = 0;
    mHeight = 0;
    mFormat = 0;
}

bool Texture2D::load()
{
    if (!mbLoad)
    {
        Bytes fileData;
        if (!AssetManager::instance()->loadAssetData(mPath, fileData))
        {
            LOG_ERROR << _T("Texture2D::load loadAssetData failed!");
            return false;
        }
        Picture picture;
        if (picture.loadFromData(fileData.data(), fileData.size()))
        {
            mWidth = picture.getWidth();
            mHeight = picture.getHeight();
            mFormat = picture.getFormat();
            glGenTextures(1, &mTextureId);
            glBindTexture(GL_TEXTURE_2D, mTextureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, picture.getBuffer());
        }
        mbLoad = true;
    }    
    return true;
}

uint32 Texture2D::getHeight() const
{
    return mHeight;
}

uint32 Texture2D::getWidth() const
{
    return mWidth;
}

GLuint Texture2D::getTextureID() const
{
    return mTextureId;
}
