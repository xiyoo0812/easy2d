#include "e2d_camera_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_graphics_mgr.h"
#include "graphics/e2d_scale_system.h"
#include "object/e2d_camera.h"
#include "object/e2d_scene.h"
#include "math/e2d_math.h"


/* Easy2D */
using namespace Easy2D;

CameraComponent::CameraComponent()
    : Component(CameraComponent::GUID)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::initialize()
{
    mAspectRatio = GraphicsManager::getInstance()->getViewportAspectRatio();;
    //calc ortho matrix
    if (mOrthoProjection)
    {
        if (mSize <= 0)
        {
            mSize = GraphicsManager::getInstance()->getViewportHeight();
        }
        mProjection = matrixOrtho(mSize * mAspectRatio * mZoom, mSize * mZoom, mNearPlane, mFarPlane);
    }
    //calc perspective matrix
    else
    {
        mProjection = matrixPerspectiveFOV(mFOV, mAspectRatio, mNearPlane, mFarPlane);
    }
}

void CameraComponent::update(const uint32& escapeMs)
{
    auto pos = getTransform()->getWorldPosition();
    Vec3 eyeVec = Vec3(pos, 0);
    eyeVec.x /= (ScaleSystem::getInstance()->getWorkingResolution().x / 2.0f);
    eyeVec.y /= (ScaleSystem::getInstance()->getWorkingResolution().y / 2.0f);

    Vec3 lookAtVec, upVec;
    Mat4 rotTransform;

    float32 rotDegrees = getTransform()->getRotation();
    rotDegrees = radiansToDegrees(rotDegrees);
    Quat rotation(Vec3(0, 0, rotDegrees));

    rotTransform = toMat4(rotation);

    //Only Vec4 * mat4  possible
    Vec4 vLookTemp = Vec4(0, 0, 1, 0) * transpose(rotTransform);
    Vec4 vUpVecTemp = Vec4(0, 1, 0, 0) * transpose(rotTransform);

    //put them into a Vec3
    lookAtVec = Vec3(vLookTemp.x, vLookTemp.y, vLookTemp.z);
    upVec = Vec3(vUpVecTemp.x, vUpVecTemp.y, vUpVecTemp.z);

    //Calculate the viewmatrix and inverse
    mView = matrixLookAt(eyeVec, (eyeVec + lookAtVec), upVec);
    mViewInverse = transpose(mView);
}

void CameraComponent::setFieldOfView(float32 fov)
{
    mFOV = fov;
}

void CameraComponent::setOrthoSize(float32 size)
{
    mSize = size;
}

void CameraComponent::setNearClippingPlane(float32 nearPlane)
{
    mNearPlane = nearPlane;
}

void CameraComponent::setFarClippingPlane(float32 farPlane)
{
    mFarPlane = farPlane;
}

void CameraComponent::setActive()
{
    auto scene = getScene();
    if (scene == nullptr)
    {
        LOG_ERROR << _T("Can't set camera active, add this camera to a scene first!");
    }
    else
    {
        scene->setActiveCamera(std::dynamic_pointer_cast<Camera>(mMaster.lock()));
    }
}

bool CameraComponent::isActive() const
{
    return mActive;
}

void CameraComponent::activate()
{
    mActive = true;
}

void CameraComponent::deactivate()
{
    mActive = false;
}

void CameraComponent::setZoom(float32 zoom)
{
    mZoom = zoom;
    mProjection = matrixOrtho(mSize * mAspectRatio * mZoom, mSize * mZoom, mNearPlane, mFarPlane);
}

float32 CameraComponent::getZoom() const
{
    return mZoom;
}

const Mat4& CameraComponent::getView() const
{
    return mView;
}

const Mat4& CameraComponent::getProjection() const
{
    return mProjection;
}

const Mat4& CameraComponent::getViewInverse() const
{
    return mViewInverse;
}

Mat4 CameraComponent::getProjectionViewInverse() const
{
    return mProjection * mViewInverse;
}

Mat4 CameraComponent::matrixPerspectiveFOV(float32 fovY, float32 ratio, float32 nearPlane, float32 farPlane)
{
    float32 viewSpaceWidth, viewSpaceHeight;
    viewSpaceHeight = cotan(fovY / 2);
    viewSpaceWidth = viewSpaceHeight * ratio;
    Mat4 matPerspective(
        viewSpaceWidth, 0, 0, 0,
        0, viewSpaceHeight, 0, 0,
        0, 0, farPlane / (farPlane - nearPlane), 1,
        0, 0, -nearPlane * farPlane / (farPlane - nearPlane), 0
    );
    return matPerspective;
}

Mat4 CameraComponent::matrixOrtho(float32 width, float32 height, float32 nearPlane, float32 farPlane)
{
    /*
    float ortho[16] = {
        2.0f / (right - left), 0, 0, -(right + left) / (right - left),
        0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom),
        0, 0, -2.0f / (far - near), -(far + near) / (far - near),
        0, 0, 0, 1
    };
    */
    //opengl standard is -1 to 1 --> 2 width
    Mat4 matOrtho(
        2 / width, 0, 0, -1,
        0, 2 / height, 0, -1,
        0, 0, -2 / (farPlane - nearPlane), 0,
        0, 0, 0, 1
    );
    return matOrtho;
}

Mat4 CameraComponent::matrixLookAt(const Vec3& eye, const Vec3& at, const Vec3& up)
{
    Vec3 xAxis, yAxis, zAxis;
    zAxis = normalize(at - eye);
    xAxis = normalize(cross(up, zAxis));
    yAxis = cross(zAxis, xAxis);
    Mat4 matLookAt(
        xAxis.x, yAxis.x, zAxis.x, 0,
        xAxis.y, yAxis.y, zAxis.y, 0,
        xAxis.z, yAxis.z, zAxis.z, 0,
        -dot(xAxis, eye), -dot(yAxis, eye), -dot(zAxis, eye), 1
    );
    return matLookAt;
}

void CameraComponent::translate(const Vec2& translation)
{
    const Vec2& offset = ScaleSystem::getInstance()->getWorkingResolution();
    auto finalPos = translation - offset / 2.0f;
    getTransform()->translate(finalPos);
}

void CameraComponent::translate(float32 x, float32 y)
{
    translate(Vec2(x, y));
}

void CameraComponent::translateX(float32 x)
{
    const Vec2& offset = ScaleSystem::getInstance()->getWorkingResolution();
    auto finalPos = x - offset.x / 2.0f;
    getTransform()->translateX(finalPos);
}

void CameraComponent::translateY(float32 y)
{
    const Vec2& offset = ScaleSystem::getInstance()->getWorkingResolution();
    auto finalPos = y - offset.y / 2.0f;
    getTransform()->translateY(finalPos);
}

void CameraComponent::convertScreenToWorld(Vec2& posInOut)
{
    posInOut += getTransform()->getWorldPosition();
}
