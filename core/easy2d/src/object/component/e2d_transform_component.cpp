#include "e2d_transform_component.h"
#include "graphics/e2d_graphics_mgr.h"
#include "object/e2d_entity.h"
#include "math/e2d_math.h"

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
    //checkForUpdate(true);
}

void TransformComponent::translate(const Vec2& translation)
{
    mLocalPt.x = translation.x;
    mLocalPt.y = translation.y;
    mChanged = true;
}

void TransformComponent::translate(float32 x, float32 y)
{
    translate(Vec2(x, y));
}

void TransformComponent::translateX(float32 x)
{
    mLocalPt.x = x;
    mChanged = true;
}

void TransformComponent::translateY(float32 y)
{
    mLocalPt.y = y;
    mChanged = true;
}

void TransformComponent::move(const Vec2& translation)
{
    mLocalPt.x += translation.x;
    mLocalPt.y += translation.y;
    mChanged = true;
}

void TransformComponent::move(float32 x, float32 y)
{
    mLocalPt.x += x;
    mLocalPt.y += y;
    mChanged = true;
}

void TransformComponent::moveX(float32 x)
{
    mLocalPt.x += x;
    mChanged = true;
}

void TransformComponent::moveY(float32 y)
{
    mLocalPt.y += y;
    mChanged = true;
}

void TransformComponent::rotate(float32 rotation)
{
    mRotation = rotation;
    mChanged = true;
}

void TransformComponent::scale(const Vec2& scale)
{
    mScale = scale;
    mChanged = true;
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
    mScale.x = x;
    mChanged = true;
}

void TransformComponent::scaleY(float32 y)
{
    mScale.y = y;
    mChanged = true;
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

const Vec2& TransformComponent::getWorldPosition()
{
    return mWorldPt;
}

const Vec2& TransformComponent::getLocalPosition()
{
    return mLocalPt;
}

float32 TransformComponent::getRotation() const
{
    return mRotation;
}

const Vec2& TransformComponent::getScale()
{
    return mScale;
}

void TransformComponent::setAnchor(const Vec2& anchor)
{
    setAnchorX(anchor.x);
    setAnchorY(anchor.y);
}

void TransformComponent::setAnchor(float32 x, float32 y)
{
    setAnchorX(x);
    setAnchorY(y);
}

void TransformComponent::setAnchorX(float32 x)
{
    if (x >= 0.0f && x <= 1.0f)
    {
        mAnchorPt.x = x;
        mChanged = true;
    }
}

void TransformComponent::setAnchorY(float32 y)
{
    if (y >= 0.0f && y <= 1.0f)
    {
        mAnchorPt.y = y;
        mChanged = true;
    }
}

void TransformComponent::setDimensions(float32 x, float32 y)
{
    mDimensions.x = x;
    mDimensions.y = y;
}

void TransformComponent::setDimensions(const Vec2& dimensions)
{
    mDimensions = dimensions;
}

void TransformComponent::setDimensionsX(float32 x)
{
    mDimensions.x = x;
}

void TransformComponent::setDimensionsY(float32 y)
{
    mDimensions.y = y;
}

const Vec2& TransformComponent::getDimensions() const
{
    return mDimensions;
}

float32 TransformComponent::getWidth() const
{
    return mDimensions.x;
}

float32 TransformComponent::getHeight() const
{
    return mDimensions.y;
}

const Mat4& TransformComponent::getWorldMatrix() const
{
    return mWorld;
}

void TransformComponent::updateTransform()
{
    for (auto child : getMaster()->getChildren())
    {
        child->getTransform()->setChanged(mChanged);
    }
    Vec3 transPos(mLocalPt.x, mLocalPt.y, 0);
    transPos.y = GraphicsManager::getInstance()->getWindowHeight() - transPos.y;
    Vec3 centerPos(mAnchorPt.x * mDimensions.x, mAnchorPt.y * mDimensions.y, 0);
    Mat4 matRot, matTrans, matScale, matC;
    matTrans = Easy2D::translate(transPos - centerPos);
    matRot = Easy2D::toMat4(Quat(Vec3(0, 0, mRotation)));
    matScale = Easy2D::scale(Vec3(mScale.x, mScale.y, 1.0f));

    mWorld = matTrans * matRot * matScale;
    auto parent = getMaster()->getParent();
    if (parent != nullptr)
    {
        mWorld = parent->getTransform()->getWorldMatrix() * mWorld;
    }
    Easy2D::getTranslation(mWorld, mWorldPt);

    if (mMirroredX || mMirroredY)
    {
        mWorld *= Easy2D::translate(mDimensions.x / 2.0f, mDimensions.y / 2.0f, 0);
        if (mMirroredX)
        {
            if (mMirroredY)
            {
                mWorld *= Easy2D::scale(Vec3(-1, -1, 1));
            }
            else
            {
                mWorld *= Easy2D::scale(Vec3(-1, 1, 1));
            }
        }
        else
        {
            mWorld *= Easy2D::scale(Vec3(1, -1, 1));
        }
        mWorld *= Easy2D::translate(mDimensions.x / -2.0f, mDimensions.y / -2.0f, 0);
    }
}

void TransformComponent::update(const uint32& escapeMs)
{
    if (mChanged)
    {
        updateTransform();
        mChanged = false;
    }
}
