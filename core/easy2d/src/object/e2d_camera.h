#ifndef CAMERA_H
#define CAMERA_H

#include "e2d_entity.h"

namespace Easy2D
{
	class Camera : public Entity
	{
	public:
		Camera();
		Camera(const String& name);
		virtual ~Camera(void);

		virtual void initialize();
		virtual void translate(const Vec2& translation);
		virtual void translate(float32 x, float32 y);
		virtual void translateX(float32 x);
		virtual void translateY(float32 y);
		virtual void activate();
		virtual void deactivate();

		virtual void convertScreenToWorld(Vec2& posInOut);
	};
}

#endif
