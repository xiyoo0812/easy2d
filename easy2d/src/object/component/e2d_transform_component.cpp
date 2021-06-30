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

bool TransformComponent::setup(SPtr<Entity> master)
{
    setMaster(master);
    return true;
}

void TransformComponent::translate(const Vec2& translation)
{
    mPostion.x = translation.x;
    mPostion.y = translation.y;
    mbChanged = true;
}

void TransformComponent::translate(float32 x, float32 y)
{
    translate(Vec2(x, y));
}

void TransformComponent::translateX(float32 x)
{
    mPostion.x = x;
    mbChanged = true;
}

void TransformComponent::translateY(float32 y)
{
    mPostion.y = y;
    mbChanged = true;
}

void TransformComponent::move(const Vec2& translation)
{
    mPostion.x += translation.x;
    mPostion.y += translation.y;
    mbChanged = true;
}

void TransformComponent::move(float32 x, float32 y)
{
    mPostion.x += x;
    mPostion.y += y;
    mbChanged = true;
}

void TransformComponent::moveX(float32 x)
{
    mPostion.x += x;
    mbChanged = true;
}

void TransformComponent::moveY(float32 y)
{
    mPostion.y += y;
    mbChanged = true;
}

void TransformComponent::rotate(float32 rotation)
{
    mRotation = rotation;
    mbChanged = true;
}

void TransformComponent::scale(const Vec2& scale)
{
    mScale = scale;
    mbChanged = true;
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
    mbChanged = true;
}

void TransformComponent::scaleY(float32 y)
{
    mScale.y = y;
    mbChanged = true;
}

void TransformComponent::scaleTemp(float32 x, float32 y)
{
    mScaletmp.x = x;
    mScaletmp.y = y;
    mbChanged = true;
}

void TransformComponent::scaleTemp(float32 v)
{
    scaleTemp(v, v);
}

void TransformComponent::mirror(bool x, bool y)
{
    mMirroredX = x;
    mMirroredY = y;
    mbChanged = true;
}

void TransformComponent::mirrorX(bool x)
{
    mMirroredX = x;
    mbChanged = true;
}

void TransformComponent::mirrorY(bool y)
{
    mMirroredY = y;
    mbChanged = true;
}

bool TransformComponent::isInRect(const Vec2& pos) const
{
    Vec2 local = screen2Local(pos);
    return true;
    //turn Easy2D::posInRect(mLocal, mSize, local);
}

Vec2 TransformComponent::screen2Local(const Vec2& pos) const
{
    auto gm = GraphicsManager::instance();
    auto viewport = gm->getViewport();
    auto view = gm->getViewInverseMatrix();
    auto proj = gm->getProjectionMatrix();
    auto model = view * mWorld;
    float mouseX = pos.x / (viewport.z * 0.5f) - 1;
    float mouseY = pos.y / (viewport.w * 0.5f) - 1;
    glm::mat4 invVP = glm::inverse(proj * model);
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;
    return Vec2(worldPos.x, worldPos.y);
}

Vec2 TransformComponent::screen2Ratio(const Vec2& pos) const
{
    return screen2Local(pos);
}

const Vec2& TransformComponent::getPosition() const
{
    return mPostion;
}

float32 TransformComponent::getRotation() const
{
    return mRotation;
}

const Vec2& TransformComponent::getScale() const
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
        mbChanged = true;
    }
}

void TransformComponent::setAnchorY(float32 y)
{
    if (y >= 0.0f && y <= 1.0f)
    {
        mAnchor.y = y;
        mbChanged = true;
    }
}

void TransformComponent::setSize(float32 x, float32 y)
{
    if (x != mSize.x || y != mSize.y)
    {
        mSize.x = x;
        mSize.y = y;
        mbChanged = true;
        mMaster.lock()->onSizeChanged(mSize);
    }
}

void TransformComponent::setSize(const Vec2& size)
{
    setSize(size.x, size.y);
}

void TransformComponent::setSizeX(float32 x)
{
    setSize(x, mSize.y);
}

void TransformComponent::setSizeY(float32 y)
{
    setSize(mSize.x, y);
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

const VertixRect& TransformComponent::getVertices() const
{
    return mVertices;
}

void TransformComponent::updateTransform()
{
    Mat4 transWorld{};
    auto parent = getMaster()->getParent();
    if (parent != nullptr)
    {
        transWorld *= parent->getTransform()->getWorldMatrix();
    }
    float32 offsetx = mAnchor.x * mSize.x;
    float32 offsety = mAnchor.y * mSize.y;
    float32 dockx = transDockerX(mPostion.x);
    float32 docky = transDockerY(mPostion.y);
    transWorld *= Easy2D::translate(dockx - offsetx, docky - offsety, 0);
    transWorld *= Easy2D::translate(offsetx, offsety, 0);
    if (mScale.x != 1.0f || mScale.y != 1.0f || mScaletmp.x != 1.0f || mScaletmp.y != 1.0f)
    {
        transWorld *= Easy2D::scale(Vec3(mScale.x * mScaletmp.x, mScale.y * mScaletmp.y, 1.0f));
    }
    if (mMirroredX || mMirroredY)
    {
        transWorld *= Easy2D::scale(Vec3(mMirroredX ? -1 : 1, mMirroredY  ? -1 : 1, 1));
    }
    transWorld *= Easy2D::translate(-offsetx, -offsety, 0);
    if (mRotation != 0)
    {
        transWorld *= Easy2D::translate(mSize.x / 2, mSize.y / 2, 0);
        transWorld *= Easy2D::toMat4(Quat(Vec3(0, 0, mRotation)));
        transWorld *= Easy2D::translate(mSize.x / -2, mSize.y / -2, 0);
    }
    mWorld = transWorld;
    //��������λ��
    mVertices = VertixRect(Vec2(0), mSize);
    mVertices.mul(Easy2D::transpose(transWorld));
}

void TransformComponent::update(const uint32& escapeMs)
{
    if (mbChanged)
    {
        updateFulllAlign();
        updateTransform();
        if (!mMaster.expired())
        {
            auto master = mMaster.lock();
            for (auto child : master->getChildren())
            {
                child->getTransform()->setChanged(true);
            }
            master->notifyTrigger(std::make_shared<TransformEvent>());
        }
        mbChanged = false;
    }
}

void TransformComponent::updateFulllAlign()
{
    if (mDockerAlign == DockerAlign::Full)
    {
        mPostion = Vec2(0, 0);
        mAnchor = Vec2(0.5, 0.5);
        mSize = getContentSize();
    }
}

void TransformComponent::setDockerAlign(DockerAlign align)
{
    mDockerAlign = align;
    updateFulllAlign();
    mbChanged = true;
}

DockerAlign TransformComponent::getDockerAlign() const
{
    return mDockerAlign;
}

float32 TransformComponent::transDockerX(float32 x)
{
    const Vec2& size = getContentSize();
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
    const Vec2& size = getContentSize();
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

const Vec2& TransformComponent::getContentSize() const
{
    if (!mMaster.expired())
    {
        auto parent = mMaster.lock()->getParent();
        if (parent)
        {
            return parent->getContentSize();
        }
    }
    return GraphicsManager::instance()->getDesignResolution();
}
