#include "e2d_render_batch.h"
#include "e2d_graphics_mgr.h"
#include "object/component/e2d_text_component.h"
#include "object/component/e2d_texture_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

RenderBatch::RenderBatch() : Singleton<RenderBatch>()
{
}

RenderBatch::~RenderBatch()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(4, mVBO);
}

void RenderBatch::initialize()
{
    //Set Shader and shader variables
    Path vShader(_T("shader/texture.vs"));
    Path fShader(_T("shader/texture.fs"));
    mProgram = std::make_shared<Program>();
    if (!mProgram->load(vShader, fShader))
    {
        LOG_ERROR << _T("SpriteBatch initialize load Program failed");
    }
    mHUDID = mProgram->getAttribLocation("isHUD");
    mColorID = mProgram->getAttribLocation("color");
    mVertexID = mProgram->getAttribLocation("position");
    mTexCoordID = mProgram->getAttribLocation("texCoord");
    mScaleID = mProgram->getUniformLocation("matScale");
    mProjID = mProgram->getUniformLocation("matProj");
    mViewID = mProgram->getUniformLocation("matView");
    mTexSamplerID = mProgram->getUniformLocation("texSampler");
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(4, mVBO);
}

void RenderBatch::initializeGLStates()
{
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void RenderBatch::setSortingMode(RenderSortingMode mode)
{
    mSortingMode = mode;
}

const RenderSortingMode RenderBatch::getSortingMode()
{
    return mSortingMode;
}

void RenderBatch::flush()
{
    begin();
    draw();
    end();
}

void RenderBatch::begin()
{
    mProgram->bind();

    glBindVertexArray(mVAO);

    glUniform1i(mTexSamplerID, 0);
    const Mat4& scaleMat = GraphicsManager::instance()->getScaleMatrix();
    glUniformMatrix4fv(mScaleID, 1, GL_FALSE, toPointer(scaleMat));
    const Mat4& viewInverseMat = GraphicsManager::instance()->getViewInverseMatrix();
    glUniformMatrix4fv(mViewID, 1, GL_FALSE, toPointer(viewInverseMat));
    const Mat4& projectionMat = GraphicsManager::instance()->getProjectionMatrix();
    glUniformMatrix4fv(mProjID, 1, GL_FALSE, toPointer(projectionMat));

    size_t vSize = mVertexBuffer.size();
    size_t iSize = mIndexBuffer.size();
    if (vSize > 0 && iSize > 0)
    {
        // position attribute
        glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4) * vSize, reinterpret_cast<GLvoid*>(&mVertexBuffer.at(0)), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(mVertexID, 4, GL_FLOAT, GL_FALSE, sizeof(Vec4), (void*)0);
        glEnableVertexAttribArray(mVertexID);
        // coord attribute
        size_t uvSize = mUvCoordBuffer.size();
        glBindBuffer(GL_ARRAY_BUFFER, mVBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * uvSize, reinterpret_cast<GLvoid*>(&mUvCoordBuffer.at(0)), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(mTexCoordID, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), (void*)0);
        glEnableVertexAttribArray(mTexCoordID);
        // color attribute
        size_t cSize = mColorBuffer.size();
        glBindBuffer(GL_ARRAY_BUFFER, mVBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * cSize, reinterpret_cast<GLvoid*>(&mColorBuffer.at(0)), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(mColorID, 4, GL_FLOAT, GL_FALSE, sizeof(Color), (void*)0);
        glEnableVertexAttribArray(mColorID);
        // hud attribute
        size_t uSize = mIsHUDBuffer.size();
        glBindBuffer(GL_ARRAY_BUFFER, mVBO[3]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float32) * uSize, reinterpret_cast<GLvoid*>(&mIsHUDBuffer.at(0)), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(mHUDID, 1, GL_FLOAT, GL_FALSE, sizeof(float32), (void*)0);
        glEnableVertexAttribArray(mHUDID);
    }
}

void RenderBatch::end()
{
    //Unbind attributes and buffers
    glDisableVertexAttribArray(mColorID);
    glDisableVertexAttribArray(mVertexID);
    glDisableVertexAttribArray(mHUDID);
    glDisableVertexAttribArray(mTexCoordID);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    mProgram->unbind();
    mIndexBuffer.clear();
    mVertexBuffer.clear();
    mUvCoordBuffer.clear();
    mIsHUDBuffer.clear();
    mColorBuffer.clear();
    mTextureQueue.clear();
}

void RenderBatch::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLuint curTexture = 0;
    uint32 batchStart = 0, batchSize = 0;
    for (auto texture : mTextureQueue)
    {
        //If != -> flush
        if (texture != curTexture)
        {
            drawTexture(batchStart, batchSize, curTexture);
            batchStart += batchSize;
            curTexture = texture;
            batchSize = 0;
        }
        ++batchSize;
    }
    drawTexture(batchStart, batchSize, curTexture);
    glFlush();
}

void RenderBatch::drawTexture(uint32 start, uint32 size, uint32 texture)
{
    if (size > 0)
    {
        size_t index = start * 6;
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, size * 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(&mIndexBuffer.at(index)));
    }
}

void RenderBatch::createObjQuad(SPtr<RenderObject> obj)
{
    //Push back all vertices
    GLuint index = mVertexBuffer.size();
    //vextics0123
    mVertexBuffer.insert(mVertexBuffer.end(), obj->mRect.mVectics.begin(), obj->mRect.mVectics.end());
    //indices 012,132
    Vector<GLuint> indices = { index, index + 1, index + 2, index + 1, index + 3, index + 2 };
    mIndexBuffer.insert(mIndexBuffer.end(), indices.begin(), indices.end());
    //uv
    mUvCoordBuffer.insert(mUvCoordBuffer.end(), 4, Vec2(0, 0));
    //hud
    mIsHUDBuffer.insert(mIsHUDBuffer.end(), 4, float32(true));
    //color
    mColorBuffer.insert(mColorBuffer.end(), 4, obj->mColor);
    //tex
    mTextureQueue.push_back(0);
}

void RenderBatch::createSpriteQuad(SPtr<RenderTexture> sprite)
{
    //Push back all vertices
    GLuint index = mVertexBuffer.size();
    //Push vextics 0123
    mVertexBuffer.insert(mVertexBuffer.end(), sprite->mRect.mVectics.begin(), sprite->mRect.mVectics.end());
    //Push indices 012,132
    Vector<GLuint> indices = { index, index + 1, index + 2, index + 1, index + 3, index + 2 };
    mIndexBuffer.insert(mIndexBuffer.end(), indices.begin(), indices.end());
    //Push back all uv's
    mUvCoordBuffer.insert(mUvCoordBuffer.end(), sprite->mUvCoords.begin(), sprite->mUvCoords.end());
    //hud
    mIsHUDBuffer.insert(mIsHUDBuffer.end(), 4, float32(sprite->mbHud));
    //color
    mColorBuffer.insert(mColorBuffer.end(), 4, sprite->mColor);
    //tex
    mTextureQueue.push_back(sprite->mTextureID);
}
