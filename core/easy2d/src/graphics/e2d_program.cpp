#include "e2d_program.h"

//using name space
using namespace Easy2D;

Program::Program()
{
}

Program::~Program()
{
    glDeleteProgram(mProgramID);
}

bool Program::load(const Path& vFile, const Path& fFile)
{
    mProgramID = glCreateProgram();
    if (mProgramID == 0)
    {
        return false;
    }
    Shader vShader(vFile, GL_VERTEX_SHADER);
    if (!vShader.load())
    {
        LOG_ERROR << _T("Program load shader failed: ") << vFile;
        return false;
    }
    glAttachShader(mProgramID, vShader.getShader());
    Shader fShader(fFile, GL_FRAGMENT_SHADER);
    if (!fShader.load())
    {
        LOG_ERROR << _T("Program load shader failed: ") << fFile;
        return false;
    }
    glAttachShader(mProgramID, fShader.getShader());

    glLinkProgram(mProgramID);
    GLint status;
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &status);
    if (!status)
    {
        GLint infoLen(0);
        glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog(mProgramID, infoLen, NULL, infoLog);
            LOG_ERROR << _T("Program::load: Failed to link program: ") << infoLog;
            delete infoLog;
        }
        return false;
    }
    return true;
}

void Program::bind()
{
    glUseProgram(mProgramID);
}

void Program::unbind()
{
    glUseProgram(0);
}

const GLuint Program::getProgramID() const
{
    return mProgramID;
}

GLuint Program::getUniformLocation(const GLchar* nameInShader) const
{
    return glGetUniformLocation(mProgramID, nameInShader);
}

GLuint Program::getAttribLocation(const GLchar* nameInShader) const
{
    return glGetAttribLocation(mProgramID, nameInShader);
}
