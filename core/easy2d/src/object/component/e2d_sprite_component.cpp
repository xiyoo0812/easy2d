#include "e2d_sprite_component.h"
#include "e2d_sprite_batch.h"

/* Easy2D */
using namespace Easy2D;

SpriteComponent::SpriteComponent(const String& filepath,const String& spriteName,uint32 widthSegments,uint32 heightSegments)
	: Component(), mFilePath(filepath), mSpriteName(spriteName)
{
	mSpriteInfo = std::make_shared<SpriteInfo>();
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::initialize()
{	
	TextureManager::getInstance()->loadTexture(mFilePath,mSpriteName);

	mDimensions.x = TextureManager::getInstance()->getTextureDimensions(mSpriteName).x / mWidthSegments;
	mDimensions.y =  TextureManager::getInstance()->getTextureDimensions(mSpriteName).y / mHeightSegments;

	getTransform()->setDimensionsSafe(mDimensions);

	createUVCoords();
	fillSpriteInfo();
}

void SpriteComponent::fillSpriteInfo()
{
	mSpriteInfo->transform = getTransform();
	mSpriteInfo->textureID = TextureManager::getInstance()->getTextureID(mSpriteName);
	mSpriteInfo->vertices = Vec2(mDimensions.x, mDimensions.y);
}

void SpriteComponent::createUVCoords()
{
	float32 startX = float32(mCurrentWidthSegment) /float32(mWidthSegments);
	float32 endX = 1.0f / mWidthSegments;
	float32 startY = float32(mCurrentHeightSegment) /float32(mHeightSegments);
	float32 endY = 1.0f / mHeightSegments;

	setUVCoords(vec4(startX, startY, endX, endY));
}

void SpriteComponent::setUVCoords(const vec4& coords)
{
	mSpriteInfo->uvCoords = coords;
}

void SpriteComponent::draw()
{
	SpriteBatch::getInstance()->addSpriteToQueue(mSpriteInfo);
}

void SpriteComponent::update(const uint32& escapeMs)
{
#ifdef ANDROID
	fillSpriteInfo();
#endif
}

bool SpriteComponent::checkCulling(float32 left,float32 right,float32 top,float32 bottom) const
{
	//Always draw hudObjects
	if(mSpriteInfo->bIsHud)
	{
		return true;
	}

	float32 spriteWidth, spriteHeight;

	pos objectPos = getTransform()->getWorldPosition();
	
	if(mSpriteInfo->bIsHud)
	{
		objectPos.x += left;
		objectPos.y += bottom;
	}

	spriteWidth = float32(GetWidth()) * getTransform()->getWorldScale().x;
	spriteHeight = float32(GetHeight()) * getTransform()->getWorldScale().y;
	float32 objRight = objectPos.x + spriteWidth;
	float32 objTop = objectPos.y + spriteHeight;

	return (objectPos.x <= right && objRight >= left) && (objectPos.y <= top && objTop >= bottom);
}

const String& SpriteComponent::getFilePath() const
{
	return mFilePath.string();
}

const String& SpriteComponent::getName() const
{
	return mSpriteName;
}

void SpriteComponent::setCurrentSegment(uint32 widthSegment, uint32 heightSegment)
{
	mCurrentWidthSegment = widthSegment;
	mCurrentHeightSegment = mHeightSegments - heightSegment - 1;
	createUVCoords();
}

void SpriteComponent::setColorMultiplier(const Color & color)
{
	mSpriteInfo->colorMultiplier = color;
}

void SpriteComponent::setHUDOptionEnabled(bool enabled)
{
	mSpriteInfo->bIsHud = enabled;
}

bool SpriteComponent::isHUDOptionEnabled() const
{
	return mSpriteInfo->bIsHud;
}

void SpriteComponent::setTexture(String& filepath,const String& spriteName,uint32 widthSegments,uint32 heightSegments)
{
	mDimensions.x = 0;
	mWidthSegments = widthSegments;
	mCurrentWidthSegment = 0;
	mDimensions.y = 0;
	mHeightSegments = heightSegments;
	mCurrentHeightSegment = 0;
	mFilePath = FilePath(filepath);
	mSpriteName = spriteName;

	TextureManager::getInstance()->loadTexture(mFilePath,mSpriteName);
	mDimensions.x = TextureManager::getInstance()->getTextureDimensions(mSpriteName).x / mWidthSegments;
	mDimensions.y =  TextureManager::getInstance()->getTextureDimensions(mSpriteName).y / mHeightSegments;
	
	getTransform()->setDimensionsSafe(mDimensions);
	
	createUVCoords();
	fillSpriteInfo();
}
