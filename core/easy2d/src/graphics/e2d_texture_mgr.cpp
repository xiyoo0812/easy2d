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

SPtr<Texture2D> TextureManager::loadTexture(const String& path, const String& name)
{
    auto it = mTextureMap.find(name);
    if (it != mTextureMap.end())
    {
        return it->second;
    }
    auto pathit = mPathList.find(path);
    if (pathit != mPathList.end())
    {
        String nameOld = pathit->second;
        auto nameit = mTextureMap.find(nameOld);
        if (nameit != mTextureMap.end())
        {
            mTextureMap.insert(std::make_pair(name, nameit->second));
            return nameit->second;
        }
        mPathList.erase(pathit);
    }
    auto texture = std::make_shared<Texture2D>(path);
    if (!texture->load())
    {
        LOG_ERROR << _T("TextureManager::loadTexture texture load failed! path: ") << path;
        return nullptr;
    }
    mTextureMap.insert(std::make_pair(name, texture));
    mPathList.insert(std::make_pair(path, name));
    return texture;
}

bool TextureManager::removeTexture(const String& name)
{
    auto it = mTextureMap.find(name);
    if (it != mTextureMap.end())
    {
        mTextureMap.erase(it);
        return true;
    }
    return false;
}

GLuint TextureManager::getTextureID(const String& name)
{
    auto it = mTextureMap.find(name);
    if (it != mTextureMap.end())
    {
        return it->second->getTextureID();
    }
    return 0;
}

Vec2 TextureManager::getTextureSize(const String& name)
{
    auto it = mTextureMap.find(name);
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

