#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "e2d_texture2d.h"
#include "math/e2d_math.h"

namespace Easy2D
{
    class TextureManager final : public Singleton<TextureManager>
    {
    public:
        friend Singleton<TextureManager>;
        SPtr<Texture2D> loadTexture(const String& path, const String& name);
        bool removeTexture(const String& name);

        GLuint getTextureID(const String& name);
        Vec2 getTextureSize(const String& name);

        void clear();

    private:
        UnorderedMap<String, String> mPathList;
        UnorderedMap<String, SPtr<Texture2D>> mTextureMap;

        TextureManager();
        ~TextureManager();
    };
}

#endif
