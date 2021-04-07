#include "e2d_shader.h"
#include "resource/e2d_asset_mgr.h"

//using name space
using namespace Easy2D;

Shader::Shader(const Path& sFile, GLenum type)
    :Resource(sFile), mType(type)
{
}

Shader::~Shader()
{
    glDeleteProgram(mProgramID);
}

bool Shader::load()
{
    if (!mbLoad)
    {
        if (!compileShader())
        {
            return false;
        }
        mbLoad = glInit();
    }
    return mbLoad;
}

bool Shader::glInit()
{
    mProgramID = glCreateProgram();
    if (mProgramID == 0)
    {
        return false;
    }

    glAttachShader(mProgramID, mShader);

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
            LOG_ERROR << _T("Shader::GLInit: Failed to link program: ") << infoLog;
            delete infoLog;
        }
        glDeleteProgram(mProgramID);
        return false;
    }
    glDeleteShader(mShader);
    return true;
}

bool Shader::compileShader()
{
    auto stream = AssetManager::getInstance()->loadAsset(mPath);
    if (stream = nullptr)
    {
        LOG_ERROR << _T("Shader::compileShader loadAsset failed!");
        return false;
    }
    Bytes result;
    if (stream->read(result) <= 0)
    {
        LOG_ERROR << _T("Shader::compileShader read data failed!");
        return false;
    }
    return compileShader((GLchar*)result.data());
}

bool Shader::compileShader(const GLchar* sData)
{
    mShader = glCreateShader(mType);
    glShaderSource(mShader, 1, &sData, NULL);
    glCompileShader(mShader);
    GLint status;
    glGetShaderiv(mShader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        GLint infolength;
        glGetShaderiv(mShader, GL_INFO_LOG_LENGTH, &infolength);
        if (infolength > 1)
        {
            char* buf = new char[infolength];
            String stringType;
            switch (mType)
            {
            case GL_VERTEX_SHADER:
                stringType = _T("GL_VERTEX_SHADER");
                break;
            case GL_FRAGMENT_SHADER:
                stringType = _T("GL_FRAGMENT_SHADER");
                break;
            default:
                stringType = _T("UNKNOWN_SHADER_TYPE");
                break;
            }
            glGetShaderInfoLog(mShader, infolength, NULL, buf);
            LOG_ERROR << _T("Shader::CompileShader: Could not compile shader of type ") << stringType << buf;
            delete buf;
        }
        glDeleteShader(mShader);
        mShader = 0;
        return false;
    }
    return true;
}

void Shader::bind()
{
    glUseProgram(mProgramID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

const GLuint Shader::getProgramID() const
{
    return mProgramID;
}

GLuint Shader::getUniformLocation(const GLchar* nameInShader) const
{
    return glGetUniformLocation(mProgramID, nameInShader);
}

GLuint Shader::getAttribLocation(const GLchar* nameInShader) const
{
    return glGetAttribLocation(mProgramID, nameInShader);
}
