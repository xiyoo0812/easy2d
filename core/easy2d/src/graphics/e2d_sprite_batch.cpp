#include "e2d_sprite_batch.h"
#include "e2d_scale_system.h"
#include "e2d_graphics_mgr.h"
#include "object/component/e2d_text_component.h"
#include "object/component/e2d_sprite_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

SpriteBatch::SpriteBatch() : Singleton<SpriteBatch>()
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::initialize()
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

void SpriteBatch::flush()
{
    begin();
    drawSprites();
    //Clear vertex, uv, color and isHud buffer
    mVertexBuffer.clear();
    mUvCoordBuffer.clear();
    mIsHUDBuffer.clear();
    mColorBuffer.clear();
    drawTextSprites();
    end();
}

void SpriteBatch::begin()
{
    mProgram->bind();
    //[TODO] Test android!
    glEnableVertexAttribArray(mVertexID);
    glEnableVertexAttribArray(mTexCoordID);
    glEnableVertexAttribArray(mHUDID);
    glEnableVertexAttribArray(mColorID);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Create Vertexbuffer
    sortSprites(mSpriteSortingMode);
    createSpriteQuads();
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

void SpriteBatch::drawSprites()
{
    uint32 batchStart(0);
    uint32 batchSize(0);
    GLuint texture(0);
    for (auto currentSprite : mSpriteQueue)
    {
        //If != -> flush
        if (texture != currentSprite->textureID)
        {
            flushSprites(batchStart, batchSize, texture);
            batchStart += batchSize;
            batchSize = 0;
            texture = currentSprite->textureID;
        }
        ++batchSize;
    }
    flushSprites(batchStart, batchSize, texture);
}

void SpriteBatch::flushSprites(uint32 start, uint32 size, uint32 texture)
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

void SpriteBatch::end()
{
    //Unbind attributes and buffers
    glDisableVertexAttribArray(mHUDID);
    glDisableVertexAttribArray(mColorID);
    glDisableVertexAttribArray(mVertexID);
    glDisableVertexAttribArray(mTexCoordID);
    mProgram->unbind();
    mSpriteQueue.clear();
    mTextQueue.clear();
    mVertexBuffer.clear();
    mUvCoordBuffer.clear();
    mIsHUDBuffer.clear();
    mColorBuffer.clear();
}

void SpriteBatch::drawTextSprites()
{
    createTextQuads();
    //flushText once per TextComponent (same font)
    //Check per text how many characters -> Forloop drawing
    int startIndex(0);
    for (auto text : mTextQueue)
    {
        GLuint* textures = text->font->getTextures();
        const char* start_line = text->text.c_str();
        for (int32 i = 0; start_line[i] != 0; ++i)
        {
            if (start_line[i] > FIRST_REAL_ASCII_CHAR)
            {
                glBindTexture(GL_TEXTURE_2D, textures[start_line[i]]);
                //Set attributes and buffers
                glVertexAttribPointer(mHUDID, 1, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mIsHUDBuffer.at(0)));
                glVertexAttribPointer(mColorID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mColorBuffer.at(0)));
                glVertexAttribPointer(mVertexID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mVertexBuffer.at(0)));
                glVertexAttribPointer(mTexCoordID, 2, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mUvCoordBuffer.at(0)));
                glDrawArrays(GL_TRIANGLES, startIndex * 6, 6);
            }
            ++startIndex;
        }
    }
}

void SpriteBatch::createSpriteQuads()
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

    for (auto sprite : mSpriteQueue)
    {
        //Push back all vertices
        Mat4 transformMat = transpose(sprite->transform->getWorldMatrix());
        Vec4 TL = Vec4(0, sprite->vertices.y, 0, 1);
        mul(TL, transformMat, TL);
        Vec4 TR = Vec4(sprite->vertices.x, sprite->vertices.y, 0, 1);
        mul(TR, transformMat, TR);
        Vec4 BL = Vec4(0, 0, 0, 1);
        mul(BL, transformMat, BL);
        Vec4 BR = Vec4(sprite->vertices.x, 0, 0, 1);
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
        mUvCoordBuffer.push_back(sprite->uvCoords.x);
        mUvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);
        //1
        mUvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
        mUvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);
        //2
        mUvCoordBuffer.push_back(sprite->uvCoords.x);
        mUvCoordBuffer.push_back(sprite->uvCoords.y);
        //1
        mUvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
        mUvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);
        //3
        mUvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
        mUvCoordBuffer.push_back(sprite->uvCoords.y);
        //2
        mUvCoordBuffer.push_back(sprite->uvCoords.x);
        mUvCoordBuffer.push_back(sprite->uvCoords.y);
        //bool & color buffer
        for (uint32 i = 0; i < 6; ++i)
        {
            mIsHUDBuffer.push_back(float32(sprite->bIsHud));
            //rgba
            mColorBuffer.push_back(sprite->colorMultiplier);
        }
    }
}

void SpriteBatch::createTextQuads()
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
    for (auto text : mTextQueue)
    {
        //Variables per textcomponent
        Mat4 transformMat, offsetMatrix;
        const Mat4& worldMat = text->transform->getWorldMatrix();
        int32 line_counter(0);
        int32 offsetX(text->horizontalTextOffset.at(line_counter));
        int32 offsetY(0);
        int32 fontHeight(text->font->getMaxLetterHeight() + text->font->getMinLetterHeight());
        for (auto it : text->text)
        {
            const CharacterInfo& charInfo = text->font->getCharacterInfo(static_cast<uchar>(it));
            offsetMatrix = translate(Vec3(offsetX, offsetY + charInfo.letterDimensions.y + text->textHeight - fontHeight, 0));
            offsetX += charInfo.letterDimensions.x;

            transformMat = transpose(worldMat * offsetMatrix);

            Vec4 TL = Vec4(0, charInfo.vertexDimensions.y, 0, 1);
            mul(TL, transformMat, TL);
            Vec4 TR = Vec4(charInfo.vertexDimensions.x, charInfo.vertexDimensions.y, 0, 1);
            mul(TR, transformMat, TR);
            Vec4 BL = Vec4(0, 0, 0, 1);
            mul(BL, transformMat, BL);
            Vec4 BR = Vec4(charInfo.vertexDimensions.x, 0, 0, 1);
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
            mUvCoordBuffer.push_back(0);
            mUvCoordBuffer.push_back(0);
            //1
            mUvCoordBuffer.push_back(charInfo.uvDimensions.x);
            mUvCoordBuffer.push_back(0);
            //2
            mUvCoordBuffer.push_back(0);
            mUvCoordBuffer.push_back(charInfo.uvDimensions.y);
            //1
            mUvCoordBuffer.push_back(charInfo.uvDimensions.x);
            mUvCoordBuffer.push_back(0);
            //3
            mUvCoordBuffer.push_back(charInfo.uvDimensions.x);
            mUvCoordBuffer.push_back(charInfo.uvDimensions.y);
            //2
            mUvCoordBuffer.push_back(0);
            mUvCoordBuffer.push_back(charInfo.uvDimensions.y);

            //bool & color buffer
            for (uint32 i = 0; i < 6; ++i)
            {
                mIsHUDBuffer.push_back(float32(text->bIsHud));
                //rgba
                mColorBuffer.push_back(text->colorMultiplier);
            }
            if (it == _T('\n'))
            {
                offsetY -= text->font->getMaxLetterHeight() + text->verticalSpacing;
                ++line_counter;
                offsetX = text->horizontalTextOffset.at(line_counter);
            }
        }
    }
}

void SpriteBatch::sortSprites(SpriteSortingMode mode)
{
    switch (mode)
    {
    case SpriteSortingMode::BackToFront:
        std::sort(mSpriteQueue.begin(), mSpriteQueue.end(), [](SPtr<SpriteInfo> a, SPtr<SpriteInfo> b) -> bool
        {
            return a->transform->getWorldPosition().l < b->transform->getWorldPosition().l;
        });
        break;
    case SpriteSortingMode::FrontToBack:
        std::sort(mSpriteQueue.begin(), mSpriteQueue.end(), [](SPtr<SpriteInfo> a, SPtr<SpriteInfo> b) -> bool
        {
            return a->transform->getWorldPosition().l > b->transform->getWorldPosition().l;
        });
        break;
    case SpriteSortingMode::TextureID:
        std::sort(mSpriteQueue.begin(), mSpriteQueue.end(), [](SPtr<SpriteInfo> a, SPtr<SpriteInfo> b) -> bool
        {
            return a->textureID < b->textureID;
        });
        break;
    default:
        break;
    }
}

void SpriteBatch::addSpriteToQueue(SPtr<SpriteInfo> spriteInfo)
{
    mSpriteQueue.push_back(spriteInfo);
}

void SpriteBatch::addTextToQueue(SPtr<TextInfo> text)
{
    mTextQueue.push_back(text);
}

void SpriteBatch::setSpriteSortingMode(SpriteSortingMode mode)
{
    mSpriteSortingMode = mode;
}
