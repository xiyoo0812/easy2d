#include "e2d_render_batch.h"
#include "e2d_scale_system.h"
#include "e2d_graphics_mgr.h"
#include "object/component/e2d_text_component.h"
#include "object/component/e2d_sprite_component.h"
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
    Path vShader(_T("shader/shader.vs"));
    Path fShader(_T("shader/shader.fs"));
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
}

void RenderBatch::sort()
{
    switch (mSortingMode)
    {
    case RenderSortingMode::BackFront:
        std::sort(mRenderQueue.begin(), mRenderQueue.end(), [](SPtr<RenderObject> a, SPtr<RenderObject> b) -> bool
        {
            return a->mTransform->getWorldPosition().l < b->mTransform->getWorldPosition().l;
        });
        break;
    case RenderSortingMode::FrontBack:
        std::sort(mRenderQueue.begin(), mRenderQueue.end(), [](SPtr<RenderObject> a, SPtr<RenderObject> b) -> bool
        {
            return a->mTransform->getWorldPosition().l > b->mTransform->getWorldPosition().l;
        });
        break;
    default:
        break;
    }
}

void RenderBatch::addRenderQueue(SPtr<RenderObject> object)
{
    mRenderQueue.push_back(object);
}

void RenderBatch::setSortingMode(RenderSortingMode mode)
{
    mSortingMode = mode;
}

void RenderBatch::flush()
{
    sort();
    build();
    begin();
    draw();
    end();
}

void RenderBatch::build()
{
    //Create Vertexbuffer
    for (auto object : mRenderQueue)
    {
        switch (object->mType)
        {
        case RenderObjectType::ObjectSprite:
            {
                auto sprite = std::dynamic_pointer_cast<RenderSprite>(object);
                if (sprite)
                {
                    createSpriteQuad(sprite);
                }
            }
            break;
        case RenderObjectType::ObjectText:
            {
                auto text = std::dynamic_pointer_cast<RenderText>(object);
                if (text)
                {
                    for (int16 shadow = text->mShadowSize; shadow >= 0; shadow--)
                    {
                        createTextQuad(text, shadow);
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}

void RenderBatch::begin()
{
    mProgram->bind();
    //[TODO] Test android!
    glEnableVertexAttribArray(mVertexID);
    glEnableVertexAttribArray(mTexCoordID);
    glEnableVertexAttribArray(mHUDID);
    glEnableVertexAttribArray(mColorID);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Set uniforms
    glUniform1i(mTexSamplerID, 0);
    float scaleValue = ScaleSystem::getInstance()->getScale();
    Mat4 scaleMat = scale(scaleValue, scaleValue, 0);
    glUniformMatrix4fv(mScaleID, 1, GL_FALSE, toPointer(scaleMat));
    const Mat4& viewInverseMat = GraphicsManager::getInstance()->getViewInverseMatrix();
    glUniformMatrix4fv(mViewID, 1, GL_FALSE, toPointer(viewInverseMat));
    const Mat4& projectionMat = GraphicsManager::getInstance()->getProjectionMatrix();
    glUniformMatrix4fv(mProjID, 1, GL_FALSE, toPointer(projectionMat));
}

void RenderBatch::draw()
{
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
    glDisableVertexAttribArray(mHUDID);
    glDisableVertexAttribArray(mColorID);
    glDisableVertexAttribArray(mVertexID);
    glDisableVertexAttribArray(mTexCoordID);
    mProgram->unbind();
    mVertexBuffer.clear();
    mUvCoordBuffer.clear();
    mIsHUDBuffer.clear();
    mColorBuffer.clear();
    mTextureQueue.clear();
    mRenderQueue.clear();
}


void RenderBatch::createSpriteQuad(SPtr<RenderSprite> sprite)
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
    Mat4 transformMat = transpose(sprite->mTransform->getWorldMatrix());
    Vec4 TL = Vec4(0, sprite->mVertices.y, 0, 1);
    mul(TL, transformMat, TL);
    Vec4 TR = Vec4(sprite->mVertices.x, sprite->mVertices.y, 0, 1);
    mul(TR, transformMat, TR);
    Vec4 BL = Vec4(0, 0, 0, 1);
    mul(BL, transformMat, BL);
    Vec4 BR = Vec4(sprite->mVertices.x, 0, 0, 1);
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
    mUvCoordBuffer.push_back(sprite->mUvCoords.x);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y + sprite->mUvCoords.w);
    //1
    mUvCoordBuffer.push_back(sprite->mUvCoords.x + sprite->mUvCoords.z);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y + sprite->mUvCoords.w);
    //2
    mUvCoordBuffer.push_back(sprite->mUvCoords.x);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y);
    //1
    mUvCoordBuffer.push_back(sprite->mUvCoords.x + sprite->mUvCoords.z);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y + sprite->mUvCoords.w);
    //3
    mUvCoordBuffer.push_back(sprite->mUvCoords.x + sprite->mUvCoords.z);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y);
    //2
    mUvCoordBuffer.push_back(sprite->mUvCoords.x);
    mUvCoordBuffer.push_back(sprite->mUvCoords.y);
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

void RenderBatch::createTextQuad(SPtr<RenderText> text, uint16 shadowSize /* = 0 */)
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
    int32 line_counter = 0;
    int32 offsetY = -shadowSize;
    int32 offsetX = shadowSize + text->mAlianOffset.at(line_counter);
    int32 fontHeight(text->mFont->getMaxLetterHeight() + text->mFont->getMinLetterHeight());
    const Mat4& worldMat = text->mTransform->getWorldMatrix();
    for (auto it : text->mText)
    {
        auto fChar = text->mFont->getFontChar(it, text->mbBold, text->mbItalic);
        Mat4 offsetMatrix = translate(Vec3(offsetX + fChar->letterDimensions.x, offsetY + fChar->letterDimensions.y + text->mTextHeight - fontHeight, 0));
        offsetX += fChar->advence;

        Mat4 transformMat = transpose(worldMat * offsetMatrix);

        Vec4 TL = Vec4(0, fChar->vertexDimensions.y, 0, 1);
        mul(TL, transformMat, TL);
        Vec4 TR = Vec4(fChar->vertexDimensions.x, fChar->vertexDimensions.y, 0, 1);
        mul(TR, transformMat, TR);
        Vec4 BL = Vec4(0, 0, 0, 1);
        mul(BL, transformMat, BL);
        Vec4 BR = Vec4(fChar->vertexDimensions.x, 0, 0, 1);
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
        mUvCoordBuffer.push_back(fChar->uvCoordTL.x);
        mUvCoordBuffer.push_back(fChar->uvCoordTL.y);
        //1
        mUvCoordBuffer.push_back(fChar->uvCoordBR.x);
        mUvCoordBuffer.push_back(fChar->uvCoordTL.y);
        //2
        mUvCoordBuffer.push_back(fChar->uvCoordTL.x);
        mUvCoordBuffer.push_back(fChar->uvCoordBR.y);
        //1
        mUvCoordBuffer.push_back(fChar->uvCoordBR.x);
        mUvCoordBuffer.push_back(fChar->uvCoordTL.y);
        //3
        mUvCoordBuffer.push_back(fChar->uvCoordBR.x);
        mUvCoordBuffer.push_back(fChar->uvCoordBR.y);
        //2
        mUvCoordBuffer.push_back(fChar->uvCoordTL.x);
        mUvCoordBuffer.push_back(fChar->uvCoordBR.y);

        //tex
        mTextureQueue.push_back(fChar->textureID);

        //bool & color buffer
        for (uint32 i = 0; i < 6; ++i)
        {
            mIsHUDBuffer.push_back(float32(text->mbHud));
            //rgba
            mColorBuffer.push_back(shadowSize > 0 ? text->mShadowColor : text->mColor);
        }
        if (it == _T('\n'))
        {
            offsetY -= text->mFont->getMaxLetterHeight() + text->mSpacing;
            ++line_counter;
            offsetX = text->mAlianOffset.at(line_counter);
        }
    }
}
