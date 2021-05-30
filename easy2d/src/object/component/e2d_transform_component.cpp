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
}

void TransformComponent::translate(const Vec2& translation)
{
    mPostion.x = translation.x;
    mPostion.y = translation.y;
    mChanged = true;
}

void TransformComponent::translate(float32 x, float32 y)
{
    translate(Vec2(x, y));
}

void TransformComponent::translateX(float32 x)
{
    mPostion.x = x;
    mChanged = true;
}

void TransformComponent::translateY(float32 y)
{
    mPostion.y = y;
    mChanged = true;
}

void TransformComponent::move(const Vec2& translation)
{
    mPostion.x += translation.x;
    mPostion.y += translation.y;
    mChanged = true;
}

void TransformComponent::move(float32 x, float32 y)
{
    mPostion.x += x;
    mPostion.y += y;
    mChanged = true;
}

void TransformComponent::moveX(float32 x)
{
    mPostion.x += x;
    mChanged = true;
}

void TransformComponent::moveY(float32 y)
{
    mPostion.y += y;
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
    mChanged = true;
}

void TransformComponent::mirrorX(bool x)
{
    mMirroredX = x;
    mChanged = true;
}

void TransformComponent::mirrorY(bool y)
{
    mMirroredY = y;
    mChanged = true;
}

const Vec2& TransformComponent::getAbsolute()
{
    return mAbsolute;
}

const Vec2& TransformComponent::getPosition()
{
    return mPostion;
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
        mAnchor.x = x;
        mChanged = true;
    }
}

void TransformComponent::setAnchorY(float32 y)
{
    if (y >= 0.0f && y <= 1.0f)
    {
        mAnchor.y = y;
        mChanged = true;
    }
}

void TransformComponent::setSize(float32 x, float32 y)
{
    if (x != mSize.x || y != mSize.y)
    {
        mSize.x = x;
        mSize.y = y;
        mChanged = true;
    }
}

void TransformComponent::setSize(const Vec2& size)
{
    if (mSize != size)
    {
        mSize = size;
        mChanged = true;
    }
}

void TransformComponent::setSizeX(float32 x)
{
    if (x != mSize.x)
    {
        mSize.x = x;
        mChanged = true;
    }
}

void TransformComponent::setSizeY(float32 y)
{
    if (y != mSize.y)
    {
        mSize.y = y;
        mChanged = true;
    }
}

const Vec2& TransformComponent::getSize() const
{
    return mSize;
}

float32 TransformComponent::getWidth() const
{
    return mSize.x;
}

float32 TransformComponent::getHeight() const
{
    return mSize.y;
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
    Vec3 transPos(transDockerX(mPostion.x), transDockerY(mPostion.y), 0);
    Vec3 centerPos(mAnchor.x * mSize.x, -mAnchor.y * mSize.y, 0);
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
    Easy2D::getTranslation(mWorld, mAbsolute);

    if (mMirroredX || mMirroredY)
    {
        mWorld *= Easy2D::translate(mSize.x / 2.0f, mSize.y / 2.0f, 0);
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
        mWorld *= Easy2D::translate(mSize.x / -2.0f, mSize.y / -2.0f, 0);
    }
}

void TransformComponent::update(const uint32& escapeMs)
{
    if (mChanged)
    {
        updateTransform();
        mMaster.lock()->notifyTrigger(std::make_shared<TransformEvent>());
        mChanged = false;
    }
}

void TransformComponent::setDockerAlign(DockerAlign align)
{
    mDockerAlign = align;
    if (align == DockerAlign::Full)
    {
        mPostion = Vec2(0, 0);
        mAnchor = Vec2(0.5, 0.5);
        mSize = getDockerSize();
    }
    mChanged = true;
}

DockerAlign TransformComponent::getDockerAlign() const
{
    return mDockerAlign;
}

float32 TransformComponent::transDockerX(float32 x)
{
    const Vec2& size = getDockerSize();
    switch (mDockerAlign)
    {
    case DockerAlign::Top:
    case DockerAlign::Center:
    case DockerAlign::Bottom:
        x += size.x / 2;
        break;
    case DockerAlign::Right:
    case DockerAlign::RightTop:
    case DockerAlign::RightBottom:
        x = size.x - x;
        break;
    case DockerAlign::Full:
        x = size.x / 2;
        break;
    default:
        return x;
    }
    return x;
}

float32 TransformComponent::transDockerY(float32 y)
{
    const Vec2& size = getDockerSize();
    switch (mDockerAlign)
    {
    case DockerAlign::Left:
    case DockerAlign::Center:
    case DockerAlign::Right:
        y += size.y / 2;
        break;
    case DockerAlign::Bottom:
    case DockerAlign::LeftBottom:
    case DockerAlign::RightBottom:
        y = size.y - y;
        break;
    case DockerAlign::Full:
        y = size.y / 2;
        break;
    default:
        return y;
    }
    return y;
}

const Vec2& TransformComponent::getDockerSize() const
{
    if (!mMaster.expired())
    {
        auto parent = mMaster.lock()->getParent();
        if (parent)
        {
            return parent->getSize();
        }
    }
    return GraphicsManager::getInstance()->getDesignResolution();
}