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
        void bind();
        void unbind();

        const GLuint getProgramID() const;

        GLuint getUniformLocation(const GLchar* nameInShader) const;

        GLuint getAttribLocation(const GLchar* nameInShader) const;

    private:
        bool compileShader();
        bool compileShader(GLchar* nameInShader);

        bool glInit();

        GLenum mType = 0;
        GLuint mProgramID = 0;
        GLuint mShader = 0;
    };
}

#endif
