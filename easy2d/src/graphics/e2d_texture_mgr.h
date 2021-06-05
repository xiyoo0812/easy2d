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
        SPtr<Texture2D> loadTexture(const String& path);
        bool removeTexture(GLuint texID);

        SPtr<Texture2D> getTexture(GLuint texID);
        Vec2 getTextureSize(GLuint texID);

        void clear();

    private:
        UnorderedMap<String, GLuint> mPathList;
        UnorderedMap<GLuint, SPtr<Texture2D>> mTextureMap;

        TextureManager();
        ~TextureManager();
    };
}

#endif
