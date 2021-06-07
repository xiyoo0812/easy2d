#include "e2d_camera.h"
#include "component/e2d_camera_component.h"


/* Easy2D */
using namespace Easy2D;

Camera::Camera(const String& name) : Entity(name)
{
}

Camera::~Camera()
{
}

bool Camera::setup()
{
    if (!Entity::setup())
    {
        LOG_WARN << _T("Camera::setup: Entity setup failed!");
        return false;
    }
    mCamera = createComponent<CameraComponent>();
    if (nullptr == mCamera)
    {
        LOG_WARN << _T("Camera::setup: create CameraComponent failed!");
        return false;
    }
    return true;
}

void Camera::translate(const Vec2& translation)
{
    mCamera->translate(translation);
}

void Camera::translate(float32 x, float32 y)
{
    mCamera->translate(x, y);
}

void Camera::translateX(float32 x)
{
    mCamera->translateX(x);
}

void Camera::translateY(float32 y)
{
    mCamera->translateY(y);
}

void Camera::activate()
{
    mCamera->activate();
}
void Camera::deactivate()
{
    mCamera->deactivate();
}

void Camera::convertScreenToWorld(Vec2& posInOut)
{
    mCamera->convertScreenToWorld(posInOut);
}
