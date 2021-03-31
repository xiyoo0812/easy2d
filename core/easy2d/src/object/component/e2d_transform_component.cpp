#include "e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

TransformComponent::TransformComponent()
	: Component(TransformComponent::GUID)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::initialize()
{
	checkForUpdate(true);
}

void TransformComponent::translate(const Vec2& translation)
{
	mLocalPosition.x = translation.x;
	mLocalPosition.y = translation.y;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::translate(float32 x, float32 y)
{
	translate(Vec2(x, y));
}

void TransformComponent::translate(const Vec2& translation, lay l)
{
	mLocalPosition.x = translation.x;
	mLocalPosition.y = translation.y;
	mLocalPosition.l = l;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::translate(float32 x, float32 y, lay l)
{
	translate(Vec2(x, y), l);
}

void TransformComponent::translate(const pos& pos2D)
{
	mLocalPosition = pos2D;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::translateX(float32 x)
{
	mLocalPosition.x = x;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::translateY(float32 y)
{
	mLocalPosition.y = y;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::translateL(lay l)
{
	mLocalPosition.l = l;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::move(const Vec2& translation)
{
	mLocalPosition.x += translation.x;
	mLocalPosition.y += translation.y;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::move(float32 x, float32 y)
{
	mLocalPosition.x += x;
	mLocalPosition.y += y;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::moveX(float32 x)
{
	mLocalPosition.x += x;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::moveY(float32 y)
{
	mLocalPosition.y += y;
	mChanged |= TransformType::TRANSLATION;
}

void TransformComponent::rotate(float32 rotation)
{
	mLocalRotation = rotation;
	mChanged |= TransformType::ROTATION;
}

void TransformComponent::rotate(float32 rotation, const Vec2& centerPoint)
{
	mLocalRotation = rotation;
	setCenterPoint(centerPoint);
	mChanged |= TransformType::ROTATION;
}

void TransformComponent::scale(const Vec2& scale)
{
	mLocalScale = scale;
	mChanged |= TransformType::SCALE;
}

void TransformComponent::scale(float32 x, float32 y)
{
	scale(Vec2(x, y));
}

void TransformComponent::scale(float32 u)
{
	scale(Vec2(u, u));
}

void TransformComponent::scaleX(float32 x)
{
	mLocalScale.x = x;
	mChanged |= TransformType::SCALE;
}

void TransformComponent::scaleY(float32 y)
{
	mLocalScale.y = y;
	mChanged |= TransformType::SCALE;
}

void TransformComponent::mirror(bool x, bool y)
{
	mMirroredX = x;
	mMirroredY = y;
}

void TransformComponent::mirrorX(bool x)
{
	mMirroredX = x;
}

void TransformComponent::mirrorY(bool y)
{
	mMirroredY = y;
}

const pos& TransformComponent::getWorldPosition()
{
	return mWorldPosition;
}

const pos& TransformComponent::getLocalPosition()
{
	return mLocalPosition;
}

float32 TransformComponent::getWorldRotation()
{
	return mWorldRotation;
}

float32 TransformComponent::getLocalRotation() const
{
	return mLocalRotation;
}

const Vec2& TransformComponent::getWorldscale()
{
	return mWorldScale;
}

const Vec2& TransformComponent::getLocalscale()
{
	return mLocalScale;
}

void TransformComponent::setCenterPoint(const Vec2& centerPoint)
{
	mCenterPosition = centerPoint;
}

void TransformComponent::setCenterPoint(float32 x, float32 y)
{
	mCenterPosition.x = x;
	mCenterPosition.y = y;
}

void TransformComponent::SetCenterX(float32 x)
{
	mCenterPosition.x = x;
}

void TransformComponent::SetCenterY(float32 y)
{
	mCenterPosition.y = y;
}

void TransformComponent::setDimensions(int32 x, int32 y)
{
	mDimensions.x = x;
	mDimensions.y = y;
}

void TransformComponent::setDimensions(const Vec2& dimensions)
{
	mDimensions = dimensions;
}

void TransformComponent::setDimensionsX(int32 x)
{
	mDimensions.x = x;
}

void TransformComponent::setDimensionsY(int32 y)
{
	mDimensions.y = y;
}

void TransformComponent::setDimensionsSafe(int32 x, int32 y)
{
	setDimensionsXSafe(x);
	setDimensionsYSafe(y);
}

void TransformComponent::setDimensionsSafe(const Vec2& dimensions)
{
	setDimensionsSafe(dimensions.x, dimensions.y);
}

void TransformComponent::setDimensionsXSafe(int32 x)
{
	if(x > mDimensions.x)
	{
		mDimensions.x = x;
	}
	else if(x < mDimensions.x)
	{
		mMaster->recalculateDimensions();
	}
}

void TransformComponent::setDimensionsYSafe(int32 y)
{
	if(y > mDimensions.y)
	{
		mDimensions.y = y;
	}
	else if(y < mDimensions.y)
	{
		mMaster->recalculateDimensions();
	}
}

const Mat4& TransformComponent::getWorldMatrix() const
{
	return mWorld;
}

void TransformComponent::checkForUpdate(bool force)
{
	if(mChanged == TransformType::NONE && !force && !GraphicsManager::getInstance()->getHasWindowChanged())
	{
		return;
	}
	commonUpdate();
	mChanged = TransformType::NONE;
}
	
void TransformComponent::commonUpdate()
{
	for(auto child : getParent()->getChildren())
	{
		child->getTransform()->setChanged(mChanged);
	}
	singleUpdate(mWorld);
	auto parent = mMaster->getParent();
	if(parent != nullptr)
	{
		mWorld = parent->getTransform()->getWorldMatrix() * mWorld;
	}
	DecomposeMatrix(mWorld, mWorldPosition, mWorldScale, mWorldRotation);
	if(mMirroredX)
	{
		mWorldPosition.x -= mDimensions.x;
	}
	if(mMirroredY)
	{
		mWorldPosition.y -= mDimensions.y;
	}
}
	
void TransformComponent::singleUpdate(Mat4& world)
{
	Mat4 matRot, matTrans, matScale, matC, matCI;
	matTrans = Easy2D::translate(mLocalPosition.pos3D());
	matRot   = ToMat4(quat(Vec3(0, 0, mLocalRotation)));
	matScale = Easy2D::scale(Vec3(mLocalScale.x, mLocalScale.y, 1.0f));
	Vec3 centerPos(mCenterPosition.x, mCenterPosition.y, 0);
	matC = Easy2D::translate(-centerPos);

	world = matTrans * matRot * matScale * matC;

	if(mMirroredX || mMirroredY)
	{
		world *= Easy2D::translate(
			mDimensions.x / 2.0f,
			mDimensions.y / 2.0f,
			0
			);

		if(mMirroredX)
		{
			if(mMirroredY)
			{
				world *= Easy2D::scale(Vec3(-1,-1,1));
			}
			else
			{
				world *= Easy2D::scale(Vec3(-1,1,1));
			}
		}
		else
		{
			world *= Easy2D::scale(Vec3(1,-1,1));
		}

		world *= Easy2D::translate(
			mDimensions.x / -2.0f,
			mDimensions.y / -2.0f,
			0
			);
	}
}

void TransformComponent::update(const Context& context)
{
	checkForUpdate();
}
	
void TransformComponent::draw()
{

}

void TransformComponent::setChanged(uchar changed)
{
	mChanged = changed;
}

