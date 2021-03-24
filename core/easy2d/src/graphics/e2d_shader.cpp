#include "e2d_shader.h"

//using name space
using namespace Easy2D;

Shader::Shader(const String& vsFile, const String& fsFile)
{
    init(vsFile, fsFile);
}

Shader::Shader(const GLchar* inlineVert, const GLchar* inlineFrag)
{
    init(inlineVert, inlineFrag);
}

Shader::~Shader()
{
    glDeleteProgram(mProgramID);
}

bool Shader::init(const String& vsFile, const String& fsFile)
{
    if (!compileShader(&mVertexShader, GL_VERTEX_SHADER, vsFile))
    {
        return false;
    }
    if (!compileShader(&mFragmentShader, GL_FRAGMENT_SHADER, fsFile))
    {
        return false;
    }
    return glInit();
}

bool Shader::init(const GLchar* inlineVert, const GLchar* inlineFrag)
{
    if (!compileShader(&mVertexShader, GL_VERTEX_SHADER, inlineVert))
    {
        return false;
    }
    if (!compileShader(&mFragmentShader, GL_FRAGMENT_SHADER, inlineFrag))
    {
        return false;
    }
    return glInit();
}

bool Shader::glInit()
{
    mProgramID = glCreateProgram();
    if (mProgramID == 0)
    {
        return false;
    }

    glAttachShader(mProgramID, mVertexShader);
    glAttachShader(mProgramID, mFragmentShader);

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
            // Stringstream buffer;
            // buffer	<< _T("Shader::GLInit: Failed to link program: ") << infoLog;
            // LOG(LogLevel::Error, buffer.str(), STARENGINE_LOG_TAG);
            delete infoLog;

        }
#ifdef ANDROID
        else
        {
            char* infoLog = new char[ANDROID_ERROR_SIZE];
            glGetProgramInfoLog(mProgramID, ANDROID_ERROR_SIZE, NULL, infoLog);
            // Stringstream buffer;
            // buffer << _T("Shader::GLInit: Failed to link program: ") << infoLog;
            // LOG(LogLevel::Error, buffer.str());
            delete infoLog;

        }
#endif
        glDeleteProgram(mProgramID);
        return false;
    }
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
    return true;
}

bool Shader::compileShader(GLuint* shader, GLenum type, const String& file)
{
    char* source;
    uint32 size;
    //char * buffer = ReadBinaryFile(file, size);
    //source = new char[size+1];
    //memcpy(source, buffer, size);
    //delete [] buffer;
    source[size] = '\0';
    bool returnValue(compileShader(shader, type, source));
    delete[] source;
    return returnValue;
}

bool Shader::compileShader(GLuint* shader, GLenum type, const GLchar* inlineFile)
{
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &inlineFile, NULL);
    glCompileShader(*shader);
    GLint status;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        GLint infolength;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
        if (infolength > 1)
        {
            char* buf = new char[infolength];
            if (buf)
            {
                String stringType;
                switch (type)
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
                glGetShaderInfoLog(*shader, infolength, NULL, buf);
                // Stringstream buffer;
                // buffer	<< _T("Shader::CompileShader: Could not compile shader of type ") << stringType << _T(": ") << buf;
                // LOG(LogLevel::Error, buffer.str(), STARENGINE_LOG_TAG);
                delete buf;
            }
        }
#ifdef ANDROID
        else
        {
            //This is necessary due to an Android bug!
            char* buf = new char[ANDROID_ERROR_SIZE];
            if (buf)
            {
                String stringType;
                switch (type)
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
                glGetShaderInfoLog(*shader, ANDROID_ERROR_SIZE, NULL, buf);
                // Stringstream buffer;
                // buffer 	<< _T("Shader::CompileShader: Could not compile shader of type ") << stringType << _T(": ") << buf;
                // LOG(LogLevel::Error, buffer.str(), STARENGINE_LOG_TAG);
                delete buf;
            }
        }
#endif
        glDeleteShader(*shader);
        shader = 0;
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

void Shader::printActiveAttribs() const
{
    GLint nAttribs;
    GLsizei maxLength;

    glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar* name = new GLchar[maxLength];

    GLenum type;
    GLint written, size, location;
    for (GLuint i = 0; i < GLuint(nAttribs); ++i)
    {
        glGetActiveAttrib(mProgramID, i, maxLength, &written, &size, &type, name);
        location = glGetAttribLocation(mProgramID, name);
    }
    delete[] name;
}

void Shader::printActiveUniforms() const
{
    GLint nUniforms;
    GLsizei maxLength;

    glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &nUniforms);
    glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar* name = new GLchar[maxLength];

    GLenum type;
    GLsizei written;
    GLint size, location;
    for (GLuint i = 0; i < GLuint(nUniforms); ++i)
    {
        glGetActiveUniform(mProgramID, i, maxLength, &written, &size, &type, name);
        location = glGetUniformLocation(mProgramID, name);
    }
    delete[] name;
}
