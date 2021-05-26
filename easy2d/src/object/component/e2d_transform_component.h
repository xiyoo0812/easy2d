#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "object/e2d_component.h"
#include "math\e2d_pos.h"

namespace Easy2D
{
    class Object;

    class TransformEvent : public Event
    {
    public:
        TransformEvent() : Event(GUID) {}
        inline static String GUID = BUILD_SGUID();
    };

    class TransformComponent final : public Component
    {
    public:
        TransformComponent();
        ~TransformComponent();

        virtual void initialize();

        void update(const uint32& escapeMs);

        void translate(const Vec2& translation);
        void translate(float32 x, float32 y);
        void translateX(float32 x);
        void translateY(float32 y);

        void move(const Vec2& translation);
        void move(float32 x, float32 y);
        void moveX(float32 x);
        void moveY(float32 y);

        const Vec2& getAbsolute();
        const Vec2& getPosition();

        void scale(const Vec2& scale);
        void scale(float32 x, float32 y);
        void scale(float32 u);
        void scaleX(float32 x);
        void scaleY(float32 y);
        const Vec2& getScale();

        void mirror(bool x, bool y);
        void mirrorX(bool x);
        void mirrorY(bool y);

        float32 getRotation() const;
        void rotate(float32 rotation);

        void setAnchor(const Vec2& anchor);
        void setAnchor(float32 x, float32 y);
        void setAnchorX(float32 x);
        void setAnchorY(float32 y);

        void setSize(float32 x, float32 y);
        void setSize(const Vec2& size);
        void setSizeX(float32 x);
        void setSizeY(float32 y);
        float32 getWidth() const;
        float32 getHeight() const;
        const Vec2& getSize() const;
        const Mat4& getWorldMatrix() const;

        void setDockerAlign(DockerAlign align);
        DockerAlign getDockerAlign() const;

    private:
        void updateTransform();
        const Vec2& getDockerSize() const;
        float32 transDockerX(float32 x);
        float32 transDockerY(float32 y);

        Mat4 mWorld = {};
        float32 mRotation = 0;
        bool mMirroredX = false, mMirroredY = false;
        DockerAlign mDockerAlign = DockerAlign::LeftTop;
        Vec2 mAbsolute{ 0, 0 }, mPostion{ 0, 0 }, mAnchor{ 0, 0 }, mScale{ 1,1 }, mSize{ 1, 1 };

    public:
        inline static String GUID = "transform";
    };
}

#endif
