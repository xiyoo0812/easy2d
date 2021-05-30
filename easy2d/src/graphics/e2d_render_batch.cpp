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
}

void RenderBatch::initialize()
{
    //Set Shader and shader variables
#ifdef GLFW
    Path vShader(_T("shader/rect.vs"));
    Path fShader(_T("shader/rect.fs"));
    mProgram = std::make_shared<Program>();
    if (!mProgram->load(vShader, fShader))
    {
        LOG_ERROR << _T("SpriteBatch initialize load Program failed");
    }
    mVertexID = mProgram->getAttribLocation("position");
    mColorID = mProgram->getAttribLocation("color");
#else
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
#endif
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
    //createSpriteQuad(texture);
}

void RenderBatch::addRenderQueue(SPtr<RenderRect> rect)
{
    createRectQuad(rect);
}

void RenderBatch::addRenderQueue(SPtr<RenderText> text)
{
    /*if (text->mShadowSize > 0)
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
    createTextQuad(text, Vec2(0, 0), text->mColor);*/
}

unsigned int VBO, VAO, VCO;
void RenderBatch::flush()
{

    SPtr<RenderRect> rect = std::make_shared<RenderRect>();
    rect->mColor = Color::White;
    //rect->mVertices = Vec2(300, 200);
    addRenderQueue(rect);
    begin();
    draw();
    end();
}

void RenderBatch::begin()
{
     mProgram->bind();
     //[TODO] Test android!
     glEnableVertexAttribArray(mVertexID);
     glEnableVertexAttribArray(mColorID);
#ifndef GLFW
    glEnableVertexAttribArray(mTexCoordID);
    glEnableVertexAttribArray(mHUDID);
#endif
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Set uniforms
#ifndef GLFW
    glUniform1i(mTexSamplerID, 0);
    float scaleValue = GraphicsManager::getInstance()->getScale();
    Mat4 scaleMat = scale(scaleValue, scaleValue, 0);
    glUniformMatrix4fv(mScaleID, 1, GL_FALSE, toPointer(scaleMat));
    const Mat4& viewInverseMat = GraphicsManager::getInstance()->getViewInverseMatrix();
    glUniformMatrix4fv(mViewID, 1, GL_FALSE, toPointer(viewInverseMat));
    const Mat4& projectionMat = GraphicsManager::getInstance()->getProjectionMatrix();
    glUniformMatrix4fv(mProjID, 1, GL_FALSE, toPointer(projectionMat));
#endif
}

void RenderBatch::draw()
{
    GLuint curTexture = 0;
    uint32 batchStart = 0, batchSize = 0;
    if (mTextureQueue.empty())
    {
        drawRect(0, mVertexBuffer.size());
        return;
    }
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
}

void RenderBatch::drawRect(uint32 start, uint32 size)
{
    if (size > 0)
    {
        glGenVertexArrays(2, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &VCO);
        glBindVertexArray(VAO);
 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4) * size, reinterpret_cast<GLvoid*>(&mVertexBuffer.at(0)), GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(mVertexID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(mVertexID);
 
        glBindBuffer(GL_ARRAY_BUFFER, VCO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4) * size, reinterpret_cast<GLvoid*>(&mColorBuffer.at(0)), GL_STATIC_DRAW);
        // color attribute
        glVertexAttribPointer(mColorID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(mColorID);

        glDrawArrays(GL_TRIANGLES, start, size);
    }
}

void RenderBatch::drawTexture(uint32 start, uint32 size, uint32 texture)
{
    if (size > 0)
    {
        //[TODO] Check if this can be optimized
        glBindTexture(GL_TEXTURE_2D, texture);
        //Set attributes and buffers
        glVertexAttribPointer(mHUDID, 1, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mIsHUDBuffer.at(0)));
        glVertexAttribPointer(mColorID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mColorBuffer.at(0)));
        glVertexAttribPointer(mVertexID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mVertexBuffer.at(0)));
        glVertexAttribPointer(mTexCoordID, 2, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mUvCoordBuffer.at(0)));
        glDrawArrays(GL_TRIANGLES, start * 6, size * 6);
    }
}

void RenderBatch::end()
{
    //Unbind attributes and buffers
    glDisableVertexAttribArray(mColorID);
    glDisableVertexAttribArray(mVertexID);
#ifndef GLFW
    glDisableVertexAttribArray(mHUDID);
    glDisableVertexAttribArray(mTexCoordID);
#endif
    mProgram->unbind();
    mVertexBuffer.clear();
    mUvCoordBuffer.clear();
    mIsHUDBuffer.clear();
    mColorBuffer.clear();
    mTextureQueue.clear();
}

void RenderBatch::createRectQuad(SPtr<RenderRect> rect)
{
    //for every sprite that has to be drawn, push back all vertices 
    //(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
    //(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
    /*
    *  TL    TR
    *   0----1
    *   |   /|
    *   |  / |
    *   | /  |
    *   |/   |
    *   2----3
    *  BL    BR
    */
    //Push back all vertices
    Vec4 TL = Vec4(0, rect->mVertices.y, 0, 1);
    mul(TL, rect->matWorld, TL);
    Vec4 TR = Vec4(rect->mVertices.x, rect->mVertices.y, 0, 1);
    mul(TR, rect->matWorld, TR);
    Vec4 BL = Vec4(0, 0, 0, 1);
    mul(BL, rect->matWorld, BL);
    Vec4 BR = Vec4(rect->mVertices.x, 0, 0, 1);
    mul(BR, rect->matWorld, BR);
    //0
     mVertexBuffer.push_back(TL);
     //1
     mVertexBuffer.push_back(TR);
     //2
     mVertexBuffer.push_back(BL);
    //1
    mVertexBuffer.push_back(TR);
    //3
    mVertexBuffer.push_back(BR);
    //2
    mVertexBuffer.push_back(BL);
    //bool & color buffer
    for (uint32 i = 0; i < 6; ++i)
    {
        //rgba
        mColorBuffer.push_back(Color::Red);
    }
}

void RenderBatch::createSpriteQuad(SPtr<RenderTexture> sprite)
{
    //for every sprite that has to be drawn, push back all vertices 
    //(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
    //(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
    /*
    *  TL    TR
    *   0----1
    *   |   /|
    *   |  / |
    *   | /  |
    *   |/   |
    *   2----3
    *  BL    BR
    */
    //Push back all vertices
    Vec4 TL = Vec4(0, sprite->mVertices.y, 0, 1);
    mul(TL, sprite->matWorld, TL);
    Vec4 TR = Vec4(sprite->mVertices.x, sprite->mVertices.y, 0, 1);
    mul(TR, sprite->matWorld, TR);
    Vec4 BL = Vec4(0, 0, 0, 1);
    mul(BL, sprite->matWorld, BL);
    Vec4 BR = Vec4(sprite->mVertices.x, 0, 0, 1);
    mul(BR, sprite->matWorld, BR);
    //0
    mVertexBuffer.push_back(TL);
    //1
    mVertexBuffer.push_back(TR);
    //2
    mVertexBuffer.push_back(BL);
    //1
    mVertexBuffer.push_back(TR);
    //3
    mVertexBuffer.push_back(BR);
    //2
    mVertexBuffer.push_back(BL);
    //Push back all uv's
    //0
    mUvCoordBuffer.push_back(sprite->mUvCoords.x);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y);
    //1
    mUvCoordBuffer.push_back(sprite->mUvCoords.z);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y);
    //2
    mUvCoordBuffer.push_back(sprite->mUvCoords.x);
    mUvCoordBuffer.push_back(sprite->mUvCoords.w);
    //1
    mUvCoordBuffer.push_back(sprite->mUvCoords.z);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y);
    //3
    mUvCoordBuffer.push_back(sprite->mUvCoords.z);
    mUvCoordBuffer.push_back(sprite->mUvCoords.w);
    //2
    mUvCoordBuffer.push_back(sprite->mUvCoords.x);
    mUvCoordBuffer.push_back(sprite->mUvCoords.w);
    //tex
    mTextureQueue.push_back(sprite->mTextureID);
    //bool & color buffer
    for (uint32 i = 0; i < 6; ++i)
    {
        mIsHUDBuffer.push_back(float32(sprite->mbHud));
        //rgba
        mColorBuffer.push_back(sprite->mColor);
    }
}

void RenderBatch::createTextQuad(SPtr<RenderText> text, Vec2& offset, Color& color)
{
    //for every sprite that has to be drawn, push back all vertices 
    //(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
    //(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
    /*
    *  TL    TR
    *   0----1
    *   |   /|
    *   |  / |
    *   | /  |
    *   |/   |
    *   2----3
    *  BL    BR
    */
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
            //0
            mVertexBuffer.push_back(TL);
            //1
            mVertexBuffer.push_back(TR);
            //2
            mVertexBuffer.push_back(BL);
            //1
            mVertexBuffer.push_back(TR);
            //3
            mVertexBuffer.push_back(BR);
            //2
            mVertexBuffer.push_back(BL);
            //Push back all uv's
            //0
            mUvCoordBuffer.push_back(fChar->uvCoords.x);
            mUvCoordBuffer.push_back(fChar->uvCoords.y);
            //1
            mUvCoordBuffer.push_back(fChar->uvCoords.z);
            mUvCoordBuffer.push_back(fChar->uvCoords.y);
            //2
            mUvCoordBuffer.push_back(fChar->uvCoords.x);
            mUvCoordBuffer.push_back(fChar->uvCoords.w);
            //1
            mUvCoordBuffer.push_back(fChar->uvCoords.z);
            mUvCoordBuffer.push_back(fChar->uvCoords.y);
            //3
            mUvCoordBuffer.push_back(fChar->uvCoords.z);
            mUvCoordBuffer.push_back(fChar->uvCoords.w);
            //2
            mUvCoordBuffer.push_back(fChar->uvCoords.x);
            mUvCoordBuffer.push_back(fChar->uvCoords.w);
            //tex
            mTextureQueue.push_back(fChar->textureID);
            //bool & color buffer
            for (uint32 i = 0; i < 6; ++i)
            {
                mIsHUDBuffer.push_back(float32(text->mbHud));
                mColorBuffer.push_back(color);
            }
        }
    }
}
