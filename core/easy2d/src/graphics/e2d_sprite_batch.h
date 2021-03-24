#ifndef SPRITEVATCH_H
#define SPRITEVATCH_H

#include "base/e2d_color.h"
#include "base/e2d_singleton.h"
#include "e2d_shader.h"

namespace Easy2D
{
	class SpriteBatch final : public Singleton<SpriteBatch>
	{
	public:
		enum SpriteSortingMode
		{
			BackToFront,
			FrontToBack,
			TextureID
		};

		void initialize();
		void flush();
		void addTextToQueue(const TextInfo* text);
		void addSpriteToQueue(const SpriteInfo* spriteInfo);
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
		Vector<const TextInfo*> mTextQueue;
		Vector<const SpriteInfo*> mSpriteQueue;
		
		Shader* mShaderPtr = nullptr;	
		GLuint mVertexID = 0, mUVID = 0, mIsHUDID = 0;
		GLuint mTextureSamplerID = 0, mColorID = 0, mScalingID = 0, mViewInverseID = 0, mProjectionID = 0;

		SpriteSortingMode mSpriteSortingMode = BackToFront;
	};
}

#endif
