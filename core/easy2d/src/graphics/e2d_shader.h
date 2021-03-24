#ifndef SHADER_H
#define SHADER_H

#include "e2d_config.h"

namespace Easy2D
{
    class Shader final
    {
    public:
        Shader(const String& vsFile, const String& fsFile);
        Shader(const GLchar* inlineVert, const GLchar* inlineFrag);
        ~Shader();

        void bind();
        void unbind();

        const GLuint getProgramID() const;

        GLuint getUniformLocation(const GLchar* nameInShader) const;

        GLuint getAttribLocation(const GLchar* nameInShader) const;

        void printActiveAttribs() const;

        void printActiveUniforms() const;

    private:
        bool init(const String& vsFile, const String& fsFile);
        bool init(const GLchar* inlineVert, const GLchar* inlineFrag);

        bool compileShader(GLuint* shader, GLenum type, const String& file);

        bool compileShader(GLuint* shader, GLenum type, const GLchar* inlineFile);

        bool glInit();

        GLuint mProgramID = 0;
        GLuint mVertexShader = 0;
        GLuint mFragmentShader = 0;

#ifdef ANDROID
        static const int32 ANDROID_ERROR_SIZE = 4096;
#endif
    };
}

#endif
