#ifndef SPRITEVATCH_H
#define SPRITEVATCH_H

#include "base/e2d_color.h"
#include "e2d_program.h"

namespace Easy2D
{
    class TextInfo;
    class SpriteInfo;
    class SpriteBatch final : public Singleton<SpriteBatch>
    {
    public:
        friend Singleton<SpriteBatch>;

        enum SpriteSortingMode
        {
            BackToFront,
            FrontToBack,
            TextureID
        };

        void initialize();
        void flush();
        void addTextToQueue(SPtr<TextInfo> text);
        void addSpriteToQueue(SPtr<SpriteInfo> spriteInfo);
        void setSpriteSortingMode(SpriteSortingMode mode);

    private:
        SpriteBatch();
        ~SpriteBatch();

        void begin();
        void end();
        void drawSprites();
        void drawTextSprites();
        void createTextQuads();
        void createSpriteQuads();
        void sortSprites(SpriteSortingMode mode);
        void flushSprites(uint32 start, uint32 size, uint32 texture);

        static const uint32 BATCHSIZE = 50;
        static const uint32 UV_AMOUNT = 12;
        static const uint32 VERTEX_AMOUNT = 18;
        static const uint32 FIRST_REAL_ASCII_CHAR = 31;

        Vector<Vec4> mVertexBuffer;
        Vector<Color> mColorBuffer;
        Vector<float32> mIsHUDBuffer;
        Vector<float32> mUvCoordBuffer;
        Vector<SPtr<TextInfo>> mTextQueue;
        Vector<SPtr<SpriteInfo>> mSpriteQueue;

        SPtr<Program> mProgram = nullptr;
        GLuint mVertexID = 0, mTexCoordID = 0, mHUDID = 0;
        GLuint mTexSamplerID = 0, mColorID = 0, mScaleID = 0, mViewID = 0, mProjID = 0;

        SpriteSortingMode mSpriteSortingMode = BackToFront;
    };
}

#endif
