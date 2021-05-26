#ifndef SHADER_H
#define SHADER_H

#include "e2d_config.h"
#include "resource/e2d_resource.h"

namespace Easy2D
{
    class Shader final : public Resource
    {
    public:
        Shader(const Path& sFile, GLenum type);
        ~Shader();

        bool load();

        const GLuint getShader() const;

    private:
        bool compileShader();

        GLenum mType = 0;
        GLuint mShader = 0;
    };
}

#endif
