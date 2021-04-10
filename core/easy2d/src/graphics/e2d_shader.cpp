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
    if (mShader != 0)
    {
        glDeleteShader(mShader);
    }
}

bool Shader::load()
{
    if (!mbLoad)
    {
        if (!compileShader())
        {
            return false;
        }
        mbLoad = true;
    }
    return mbLoad;
}

bool Shader::compileShader()
{
    Bytes shaderData;
    if (!AssetManager::getInstance()->loadAssetData(mPath, shaderData))
    {
        LOG_ERROR << _T("Shader::compileShader loadAssetData failed!");
        return false;
    }
    return compileShader((GLchar*)shaderData.data());
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
        mShader = 0;
        return false;
    }
    return true;
}

const GLuint Shader::getShader() const
{
    return mShader;
}
