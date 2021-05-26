#ifndef PROGRAM_H
#define PROGRAM_H

#include "e2d_shader.h"

namespace Easy2D
{
    class Program
    {
    public:
        Program();
        ~Program();

        bool load(const Path& vFile, const Path& fFile);
        void bind();
        void unbind();

        const GLuint getProgramID() const;

        GLuint getUniformLocation(const GLchar* nameInShader) const;

        GLuint getAttribLocation(const GLchar* nameInShader) const;

    private:
        GLuint mProgramID = 0;
    };
}

#endif
