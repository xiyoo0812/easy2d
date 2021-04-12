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
    mShader = glCreateShader(mType);
    GLint length = shaderData.size();
    const GLchar* data = (GLchar*)shaderData.data();
    glShaderSource(mShader, 1, &data, &length);
    glCompileShader(mShader);
    GLint status;
    glGetShaderiv(mShader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(mShader, 1024, NULL, InfoLog);
        LOG_ERROR << _T("Shader::CompileShader: Could not compile shader:") << mPath << _T(", err:") << InfoLog;
        glDeleteShader(mShader);
        mShader = 0;
        return false;
    }
    return true;
}

const GLuint Shader::getShader() const
{
    return mShader;
}
