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

void RenderBatch::addRenderQueue(SPtr<RenderTexture> texture)
{
    createSpriteQuad(texture);
}

void RenderBatch::addRenderQueue(SPtr<RenderObject> obj)
{
    createObjQuad(obj);
}

void RenderBatch::addRenderQueue(SPtr<RenderText> text)
{
    if (text->mShadowSize > 0)
    {
        for (int16 shadow = text->mShadowSize + text->mOutlineSize; shadow > text->mOutlineSize; shadow--)
        {
            createTextQuad(text, Vec2(shadow, shadow), text->mShadowColor);
        }
    }
    if (text->mOutlineSize > 0)
    {
        for (int16 outline = text->mOutlineSize; outline > 0; outline--)
        {
            createTextQuad(text, Vec2(-outline, -outline), text->mOutlineColor);
            createTextQuad(text, Vec2(-outline, outline), text->mOutlineColor);
            createTextQuad(text, Vec2(outline, -outline), text->mOutlineColor);
            createTextQuad(text, Vec2(outline, outline), text->mOutlineColor);
        }
    }
    createTextQuad(text, Vec2(0, 0), text->mColor);
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

void RenderBatch::createTextQuad(SPtr<RenderText> text, Vec2& offset, Color& color)
{
    //Variables per textcomponent
    size_t line_count = text->mTextList.size();
    for (size_t line = 0; line < line_count; ++line)
    {
        uint32 fontHeight = text->mFont->getFontHeight();
        int32 offsetY = offset.y + text->mVerticalOffset[line];
        int32 offsetX = offset.x + text->mHorizontalOffset[line];
        for (auto it : text->mTextList[line])
        {
            auto fChar = text->mFont->getFontChar(it, text->mbBold, text->mbItalic);
            Mat4 offsetMatrix = text->matWorld * Easy2D::translate(Vec3(offsetX + fChar->letterSize.x, offsetY - fChar->letterSize.y, 0));
            offsetMatrix *= Easy2D::translate(0, fontHeight / 2.0f, 0);
            offsetMatrix *= Easy2D::scale(1, -1, 1);
            offsetMatrix *= Easy2D::translate(0, fontHeight / -2.0f, 0);
            Mat4 transformMat = Easy2D::transpose(offsetMatrix);
            offsetX += fChar->advence + text->mOutlineSize;
            Vec4 TL = Vec4(0, fChar->vertexSize.y, 0, 1);
            mul(TL, transformMat, TL);
            Vec4 TR = Vec4(fChar->vertexSize.x, fChar->vertexSize.y, 0, 1);
            mul(TR, transformMat, TR);
            Vec4 BL = Vec4(0, 0, 0, 1);
            mul(BL, transformMat, BL);
            Vec4 BR = Vec4(fChar->vertexSize.x, 0, 0, 1);
            mul(BR, transformMat, BR);

            GLuint index = mVertexBuffer.size();
            //vextics 0123
            mVertexBuffer.push_back(TL);
            mVertexBuffer.push_back(TR);
            mVertexBuffer.push_back(BL);
            mVertexBuffer.push_back(BR);
            //indices 012,132
            Vector<GLuint> indices = { index, index + 1, index + 2, index + 1, index + 3, index + 2 };
            mIndexBuffer.insert(mIndexBuffer.end(), indices.begin(), indices.end());
            //Push back all uv's
            mUvCoordBuffer.push_back(Vec2(fChar->uvCoords.x, fChar->uvCoords.y));
            mUvCoordBuffer.push_back(Vec2(fChar->uvCoords.z, fChar->uvCoords.y));
            mUvCoordBuffer.push_back(Vec2(fChar->uvCoords.x, fChar->uvCoords.w));
            mUvCoordBuffer.push_back(Vec2(fChar->uvCoords.z, fChar->uvCoords.w));
            //hud
            mIsHUDBuffer.insert(mIsHUDBuffer.end(), 4, float32(text->mbHud));
            //color
            mColorBuffer.insert(mColorBuffer.end(), 4, color);
            //tex
            mTextureQueue.push_back(fChar->textureID);
        }
    }
}
