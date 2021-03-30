#include "e2d_camera.h"


/* Easy2D */
using namespace Easy2D;

Camera::Camera(): Entity()
{
	AddComponent(new CameraComponent());
}

Camera::Camera(const String& name): Entity(name)
{
	AddComponent(new CameraComponent());
}

Camera::~Camera()
{
}

void Camera::initialize()
{
	
}

void Camera::translate(const Vec2& translation)
{
	getComponent<CameraComponent>(CameraComponent::GUID)->translate(translation);
}

void Camera::translate(float32 x, float32 y)
{
	getComponent<CameraComponent>(CameraComponent::GUID)->translate(x, y);
}

void Camera::translateX(float32 x)
{
	getComponent<CameraComponent>(CameraComponent::GUID)->translateX(x);
}

void Camera::translateY(float32 y)
{
	getComponent<CameraComponent>(CameraComponent::GUID)->translateY(y);
}

void Camera::activate()
{
	getComponent<CameraComponent>(CameraComponent::GUID)->activate();
}
void Camera::deactivate()
{
	getComponent<CameraComponent>(CameraComponent::GUID)->deactivate();
}

void Camera::convertScreenToWorld(Vec2& posInOut)
{
	getComponent<CameraComponent>(CameraComponent::GUID)->convertScreenToWorld(posInOut);
}
