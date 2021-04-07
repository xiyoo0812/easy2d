#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "object/e2d_component.h"

namespace Easy2D
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent();
        virtual ~CameraComponent();

        void draw();
        void update(const uint32 &escapeMs);
        virtual void initialize();

        void setFieldOfView(float32 fov);
        void setOrthoSize(float32 size);
        void setNearClippingPlane(float32 nearPlane);
        void setFarClippingPlane(float32 farPlane);

        void setActive();
        bool isActive() const;
        void activate();
        void deactivate();

        void setZoom(float32 zoom);
        float32 getZoom() const;

        const Mat4& getView() const;
        const Mat4& getProjection() const;
        const Mat4& getViewInverse() const;
        Mat4 getProjectionViewInverse() const;

        void translate(const Vec2& translation);
        void translate(float32 x, float32 y);
        void translateX(float32 x);
        void translateY(float32 y);

        void convertScreenToWorld(Vec2& posInOut);

    private:
        Mat4 matrixPerspectiveFOV(float32 FovY, float32 ratio, float32 nearPlane, float32 farPlane);
        Mat4 matrixOrtho(float32 width, float32 height, float32 nearPlane, float32 farPlane);
        Mat4 matrixLookAt(const Vec3& eye, const Vec3& at, const Vec3& up);

        Mat4 mProjection, mView, mViewInverse;

        float32 mFarPlane = 1000, mNearPlane = 10, mFOV = 60, mSize = 0, mZoom = 100, mAspectRatio = 0;

        bool mActive = true, mOrthoProjection = true;

    public:
        inline static String GUID = "camera";
    };
}

#endif
