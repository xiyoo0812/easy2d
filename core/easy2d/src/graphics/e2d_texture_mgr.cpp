#include "e2d_texture_mgr.h"

using namespace Easy2D;

TextureManager::~TextureManager()
{
    mTextureMap.clear();
    mPathList.clear();
}

TextureManager::TextureManager()
{

}

void TextureManager::loadTexture(const String& path, const String& name)
{
    if (mTextureMap.find(name) != mTextureMap.end())
    {
        return;
    }
    auto pathit = mPathList.find(path);
    if (pathit != mPathList.end())
    {
        String nameOld = pathit->second;
        auto nameit = mTextureMap.find(nameOld);
        if (nameit != mTextureMap.end())
        {
            mTextureMap[name] = nameit->second;
            return;
        }
        mPathList.erase(pathit);
        return;
    }
    mTextureMap[name] = NewSPtr<Texture2D>(path);
    mPathList[path] = name;
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
    if (mTextureMap.find(name) != mTextureMap.end())
    {
        return mTextureMap[name]->getTextureID();
    }
    return 0;
}

Vec2 TextureManager::getTextureDimensions(const String& name)
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

bool TextureManager::reload()
{
    mTextureMap.clear();
    for (auto it = mPathList.begin(); it != mPathList.end(); ++it)
    {
        mTextureMap[it->second] = NewSPtr<Texture2D>(it->first);
    }
    return true;
}
