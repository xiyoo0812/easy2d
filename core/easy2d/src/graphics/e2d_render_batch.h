#ifndef SPRITEVATCH_H
#define SPRITEVATCH_H

#include "base/e2d_color.h"
#include "e2d_program.h"
#include "e2d_render_object.h"

namespace Easy2D
{
    class RenderBatch final : public Singleton<RenderBatch>
    {
    public:
        friend Singleton<RenderBatch>;

        void initialize();
        void addRenderQueue(SPtr<RenderObject> object);
        void setSortingMode(RenderSortingMode mode);
        void flush();

    private:
        RenderBatch();
        ~RenderBatch();

        void begin();
        void end();
        void build();
        void draw();
        void sort();
        void createSpriteQuad(SPtr<RenderSprite> sprite);
        void createTextQuad(SPtr<RenderText> text, Vec2 offset, Color color);
        void drawTexture(uint32 start, uint32 size, uint32 texture);

        static const uint32 BATCHSIZE = 50;
        static const uint32 UV_AMOUNT = 12;
        static const uint32 VERTEX_AMOUNT = 18;
        static const uint32 FIRST_REAL_ASCII_CHAR = 31;

        Vector<Vec4> mVertexBuffer;
        Vector<Color> mColorBuffer;
        Vector<float32> mIsHUDBuffer;
        Vector<float32> mUvCoordBuffer;
        Vector<GLuint> mTextureQueue;
        Vector<SPtr<RenderObject>> mRenderQueue;

        SPtr<Program> mProgram = nullptr;
        GLuint mVertexID = 0, mTexCoordID = 0, mHUDID = 0;
        GLuint mTexSamplerID = 0, mColorID = 0, mScaleID = 0, mViewID = 0, mProjID = 0;

        RenderSortingMode mSortingMode = RenderSortingMode::BackFront;
    };
}

#endif
