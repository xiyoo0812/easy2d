#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "math/e2d_rect.h"
#include "object/e2d_component.h"

namespace Easy2D
{
    class Object;

    class TransformEvent : public Event
    {
    public:
        TransformEvent() : Event(GUID) {}
        inline static String GUID = "transform_event";
    };

    class TransformComponent final : public Component
    {
    public:
        TransformComponent();
        ~TransformComponent();

        virtual bool setup(SPtr<Entity> master);

        virtual void update(const uint32& escapeMs);

        void translate(const Vec2& translation);
        void translate(float32 x, float32 y);
        void translateX(float32 x);
        void translateY(float32 y);

        void move(const Vec2& translation);
        void move(float32 x, float32 y);
        void moveX(float32 x);
        void moveY(float32 y);

        void scale(const Vec2& scale);
        void scale(float32 x, float32 y);
        void scale(float32 u);
        void scaleX(float32 x);
        void scaleY(float32 y);

        void mirror(bool x, bool y);
        void mirrorX(bool x);
        void mirrorY(bool y);

        const Rect getRect() const;
        const Vec2& getScale() const;
        const Vec2& getAbsolute() const;
        const Vec2& getPosition() const;
        bool isInRect(const Vec2& pos) const;

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

        Vec2 getInnerPos(const Vec2& pos);

    private:
        void updateTransform();
        void updateFulllAlign();
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
