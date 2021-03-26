#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "e2d_texture2d.h"
#include "math/e2d_math.h"

namespace Easy2D
{
    class TextureManager final : public Singleton<TextureManager>
    {
    public:
        void loadTexture(const String& path, const String& name);
        bool removeTexture(const String& name);

        GLuint getTextureID(const String& name);
        Vec2 getTextureDimensions(const String& name);

        void clear();
        bool reload();

    private:
        UnorderedMap<String, String> mPathList;
        UnorderedMap<String, SPtr<Texture2D>> mTextureMap;

        TextureManager();
        ~TextureManager();
    };
}

#endif
