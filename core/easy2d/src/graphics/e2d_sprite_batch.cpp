#include "e2d_sprite_batch.h"
#include "e2d_font.h"

/* Easy2D */
using namespace Easy2D;

SpriteBatch::SpriteBatch() : Singleton<SpriteBatch>()
{
}

SpriteBatch::~SpriteBatch(void)
{
    delete mShaderPtr;
}

void SpriteBatch::initialize()
{
    //Set Shader and shader variables
    String vShader(_T("Shaders/VertexPosColTexShader.vert"));
    String fShader(_T("Shaders/VertexPosColTexShader.frag"));

    mShaderPtr = new Shader(vShader, fShader);
    mUVID = mShaderPtr->getAttribLocation("texCoord");
    mIsHUDID = mShaderPtr->getAttribLocation("isHUD");
    mVertexID = mShaderPtr->getAttribLocation("position");
    mColorID = mShaderPtr->getAttribLocation("colorMultiplier");
    mScalingID = mShaderPtr->getUniformLocation("scaleMatrix");
    mProjectionID = mShaderPtr->getUniformLocation("projectionMatrix");
    mViewInverseID = mShaderPtr->getUniformLocation("viewInverseMatrix");
    mTextureSamplerID = mShaderPtr->getUniformLocation("textureSampler");
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
    mShaderPtr->bind();
    //[TODO] Test android!
    glEnableVertexAttribArray(mVertexID);
    glEnableVertexAttribArray(mUVID);
    glEnableVertexAttribArray(mIsHUDID);
    glEnableVertexAttribArray(mColorID);
    //Create Vertexbuffer
    sortSprites(mSpriteSortingMode);
    createSpriteQuads();
    //Set uniforms
    glUniform1i(mTextureSamplerID, 0);
    float scaleValue = ScaleSystem::GetInstance()->GetScale();
    Mat4 scaleMat = Scale(scaleValue, scaleValue, 0);
    glUniformMatrix4fv(mScalingID, 1, GL_FALSE, ToPointerValue(scaleMat));
    const Mat4& viewInverseMat = GraphicsManager::GetInstance()->GetViewInverseMatrix();
    glUniformMatrix4fv(mViewInverseID, 1, GL_FALSE, ToPointerValue(viewInverseMat));
    const Mat4& projectionMat = GraphicsManager::GetInstance()->GetProjectionMatrix();
    glUniformMatrix4fv(mProjectionID, 1, GL_FALSE, ToPointerValue(projectionMat));
}

void SpriteBatch::drawSprites()
{
    uint32 batchStart(0);
    uint32 batchSize(0);
    GLuint texture(0);
    for (const SpriteInfo* currentSprite : mSpriteQueue)
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
        glVertexAttribPointer(mVertexID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mVertexBuffer.at(0)));
        glVertexAttribPointer(mUVID, 2, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mUvCoordBuffer.at(0)));
        glVertexAttribPointer(mIsHUDID, 1, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mIsHUDBuffer.at(0)));
        glVertexAttribPointer(mColorID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mColorBuffer.at(0)));
        glDrawArrays(GL_TRIANGLES, start * 6, size * 6);
    }
}

void SpriteBatch::end()
{
    //Unbind attributes and buffers
    glDisableVertexAttribArray(mVertexID);
    glDisableVertexAttribArray(mUVID);
    glDisableVertexAttribArray(mIsHUDID);
    glDisableVertexAttribArray(mColorID);
    mShaderPtr->unbind();
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
    int32 startIndex(0);
    for (const TextInfo* text : mTextQueue)
    {
        GLuint* textures = text->font->GetTextures();
        const char* start_line = text->text.c_str();
        for (int32 i = 0; start_line[i] != 0; ++i)
        {
            if (start_line[i] > FIRST_REAL_ASCII_CHAR)
            {
                glBindTexture(GL_TEXTURE_2D, textures[start_line[i]]);
                //Set attributes and buffers
                glVertexAttribPointer(mVertexID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mVertexBuffer.at(0)));
                glVertexAttribPointer(mUVID, 2, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mUvCoordBuffer.at(0)));
                glVertexAttribPointer(mIsHUDID, 1, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mIsHUDBuffer.at(0)));
                glVertexAttribPointer(mColorID, 4, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&mColorBuffer.at(0)));
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

    for (const SpriteInfo* sprite : mSpriteQueue)
    {
        //Push back all vertices
        Mat4 transformMat = Transpose(sprite->transformPtr->GetWorldMatrix());
        Vec4 TL = Vec4(0, sprite->vertices.y, 0, 1);
        Mul(TL, transformMat, TL);
        Vec4 TR = Vec4(sprite->vertices.x, sprite->vertices.y, 0, 1);
        Mul(TR, transformMat, TR);
        Vec4 BL = Vec4(0, 0, 0, 1);
        Mul(BL, transformMat, BL);
        Vec4 BR = Vec4(sprite->vertices.x, 0, 0, 1);
        Mul(BR, transformMat, BR);
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
    for (const TextInfo* text : mTextQueue)
    {
        //Variables per textcomponent
        Mat4 transformMat, offsetMatrix;
        const Mat4& worldMat = text->transformPtr->GetWorldMatrix();
        int32 line_counter(0);
        int32 offsetX(text->horizontalTextOffset.at(line_counter));
        int32 offsetY(0);
        int32 fontHeight(text->font->GetMaxLetterHeight() + text->font->GetMinLetterHeight());
        for (auto it : text->text)
        {
            const CharacterInfo& charInfo = text->font->GetCharacterInfo(static_cast<uchar>(it));
            offsetMatrix = Translate(Vec3(offsetX, offsetY + charInfo.letterDimensions.y + text->textHeight - fontHeight, 0));
            offsetX += charInfo.letterDimensions.x;

            transformMat = Transpose(worldMat * offsetMatrix);

            Vec4 TL = Vec4(0, charInfo.vertexDimensions.y, 0, 1);
            Mul(TL, transformMat, TL);
            Vec4 TR = Vec4(charInfo.vertexDimensions.x, charInfo.vertexDimensions.y, 0, 1);
            Mul(TR, transformMat, TR);
            Vec4 BL = Vec4(0, 0, 0, 1);
            Mul(BL, transformMat, BL);
            Vec4 BR = Vec4(charInfo.vertexDimensions.x, 0, 0, 1);
            Mul(BR, transformMat, BR);
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
                offsetY -= text->font->GetMaxLetterHeight() + text->verticalSpacing;
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
        std::sort(mSpriteQueue.begin(), mSpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
        {
            return a->transformPtr->GetWorldPosition().l < b->transformPtr->GetWorldPosition().l;
        });
        break;
    case SpriteSortingMode::FrontToBack:
        std::sort(mSpriteQueue.begin(), mSpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
        {
            return a->transformPtr->GetWorldPosition().l > b->transformPtr->GetWorldPosition().l;
        });
        break;
    case SpriteSortingMode::TextureID:
        std::sort(mSpriteQueue.begin(), mSpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
        {
            return a->textureID < b->textureID;
        });
        break;
    default:
        break;
    }
}

void SpriteBatch::addSpriteToQueue(const SpriteInfo* spriteInfo)
{
    mSpriteQueue.push_back(spriteInfo);
}

void SpriteBatch::addTextToQueue(const TextInfo* text)
{
    mTextQueue.push_back(text);
}

void SpriteBatch::setSpriteSortingMode(SpriteSortingMode mode)
{
    mSpriteSortingMode = mode;
}
