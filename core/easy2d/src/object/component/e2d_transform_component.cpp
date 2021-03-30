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
	CheckForUpdate(true);
	m_Invalidate = true;
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
	SetCenterPoint(centerPoint);
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

const pos& TransformComponent::GetWorldPosition()
{
	return mWorldPosition;
}

const pos& TransformComponent::GetLocalPosition()
{
	return mLocalPosition;
}

float32 TransformComponent::GetWorldRotation()
{
	return m_WorldRotation;
}

float32 TransformComponent::GetLocalRotation() const
{
	return mLocalRotation;
}

const Vec2& TransformComponent::GetWorldscale()
{
	return m_WorldScale;
}

const Vec2& TransformComponent::GetLocalscale()
{
	return mLocalScale;
}

void TransformComponent::SetCenterPoint(const Vec2& centerPoint)
{
	mCenterPosition = centerPoint;
}

void TransformComponent::SetCenterPoint(float32 x, float32 y)
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

void TransformComponent::SetDimensions(int32 x, int32 y)
{
	mDimensions.x = x;
	mDimensions.y = y;
}

void TransformComponent::SetDimensions(const iVec2& dimensions)
{
	mDimensions = dimensions;
}

void TransformComponent::SetDimensionsX(int32 x)
{
	mDimensions.x = x;
}

void TransformComponent::SetDimensionsY(int32 y)
{
	mDimensions.y = y;
}

void TransformComponent::SetDimensionsSafe(int32 x, int32 y)
{
	SetDimensionsXSafe(x);
	SetDimensionsYSafe(y);
}

void TransformComponent::SetDimensionsSafe(const iVec2& dimensions)
{
	SetDimensionsSafe(dimensions.x, dimensions.y);
}

void TransformComponent::SetDimensionsXSafe(int32 x)
{
	if(x > mDimensions.x)
	{
		mDimensions.x = x;
	}
	else if(x < mDimensions.x)
	{
		mMaster->RecalculateDimensions();
	}
}

void TransformComponent::SetDimensionsYSafe(int32 y)
{
	if(y > mDimensions.y)
	{
		mDimensions.y = y;
	}
	else if(y < mDimensions.y)
	{
		mMaster->RecalculateDimensions();
	}
}

const mat4 & TransformComponent::GetWorldMatrix() const
{
	return m_World;
}

void TransformComponent::CheckForUpdate(bool force)
{
	if(mChanged == TransformType::NONE && !force && !m_Invalidate
		&& !GraphicsManager::GetInstance()->GetHasWindowChanged())
	{
		return;
	}

	CommonUpdate();

	mChanged = TransformType::NONE;

	m_Invalidate = false;
}
	
void TransformComponent::CommonUpdate()
{
	for(auto child : GetParent()->GetChildren())
	{
		child->GetTransform()->IsChanged(true);
	}

	SingleUpdate(m_World);

	auto parent = mMaster->GetParent();
	if(parent != nullptr)
	{
		m_World = parent->GetTransform()->GetWorldMatrix() * m_World;
	}

	DecomposeMatrix(m_World, mWorldPosition, m_WorldScale, m_WorldRotation);

	if(mMirroredX)
	{
		mWorldPosition.x -= mDimensions.x;
	}

	if(mMirroredY)
	{
		mWorldPosition.y -= mDimensions.y;
	}
}
	
void TransformComponent::SingleUpdate(mat4 & world)
{
	mat4 matRot, matTrans, matScale, matC, matCI;

	matTrans = star::translate(mLocalPosition.pos3D());
	matRot   = ToMat4(quat(vec3(0, 0, mLocalRotation)));
	matScale = star::scale(vec3(mLocalScale.x, mLocalScale.y, 1.0f));
	
	vec3 centerPos(mCenterPosition.x, mCenterPosition.y, 0);
	matC = star::translate(-centerPos);

	world = matTrans * matRot * matScale * matC;

	if(mMirroredX || mMirroredY)
	{
		world *= star::translate(
			mDimensions.x / 2.0f,
			mDimensions.y / 2.0f,
			0
			);

		if(mMirroredX)
		{
			if(mMirroredY)
			{
				world *= star::scale(vec3(-1,-1,1));
			}
			else
			{
				world *= star::scale(vec3(-1,1,1));
			}
		}
		else
		{
			world *= star::scale(vec3(1,-1,1));
		}

		world *= star::translate(
			mDimensions.x / -2.0f,
			mDimensions.y / -2.0f,
			0
			);
	}
}

void TransformComponent::Update(const Context& context)
{
	CheckForUpdate();
}
	
void TransformComponent::Draw()
{

}

void TransformComponent::IsChanged(bool isChanged)
{
	mChanged = isChanged;
}

