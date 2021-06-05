#include "e2d_texture_mgr.h"

using namespace Easy2D;

TextureManager::~TextureManager()
{
    mTextureMap.clear();
    mPathList.clear();
}

TextureManager::TextureManager() : Singleton<TextureManager>()
{

}

SPtr<Texture2D> TextureManager::loadTexture(const String& path)
{
    auto pathit = mPathList.find(path);
    if (pathit != mPathList.end())
    {
        GLuint texID = pathit->second;
        auto texIt = mTextureMap.find(texID);
        if (texIt != mTextureMap.end())
        {
            return texIt->second;
        }
    }
    auto texture = std::make_shared<Texture2D>(path);
    if (!texture->load())
    {
        LOG_ERROR << _T("TextureManager::loadTexture texture load failed! path: ") << path;
        return nullptr;
    }
    GLuint texId = texture->getTextureID();
    mTextureMap.insert(std::make_pair(texId, texture));
    mPathList.insert(std::make_pair(path, texId));
    return texture;
}

bool TextureManager::removeTexture(GLuint texID)
{
    auto it = mTextureMap.find(texID);
    if (it != mTextureMap.end())
    {
        mTextureMap.erase(it);
        return true;
    }
    return false;
}

SPtr<Texture2D> TextureManager::getTexture(GLuint texID)
{
    auto it = mTextureMap.find(texID);
    if (it != mTextureMap.end())
    {
        return it->second;
    }
    return 0;
}

Vec2 TextureManager::getTextureSize(GLuint texID)
{
    auto it = mTextureMap.find(texID);
    if (it != mTextureMap.end())
    {
        return (Vec2(it->second->getWidth(), it->second->getHeight()));
    }
    return Vec2(0, 0);
}

void TextureManager::clear()
{
    mTextureMap.clear();
    mPathList.clear();
}

