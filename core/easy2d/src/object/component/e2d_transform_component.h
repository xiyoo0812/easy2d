#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "object/e2d_component.h"
#include "math\e2d_pos.h"

namespace Easy2D
{
    class Object;
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

        void rotate(float32 rotation);

        void scale(const Vec2& scale);
        void scale(float32 x, float32 y);
        void scale(float32 u);
        void scaleX(float32 x);
        void scaleY(float32 y);

        void mirror(bool x, bool y);
        void mirrorX(bool x);
        void mirrorY(bool y);

        const Vec2& getWorldPosition();
        const Vec2& getLocalPosition();
        float32 getRotation() const;
        const Vec2& getScale();

        void setAnchor(const Vec2& anchor);
        void setAnchor(float32 x, float32 y);
        void setAnchorX(float32 x);
        void setAnchorY(float32 y);

        void setDimensions(float32 x, float32 y);
        void setDimensions(const Vec2& dimensions);
        void setDimensionsX(float32 x);
        void setDimensionsY(float32 y);
        const Vec2& getDimensions() const;
        float32 getWidth() const;
        float32 getHeight() const;

        const Mat4& getWorldMatrix() const;

    private:
        void updateTransform();

        Mat4 mWorld = {};
        float32 mRotation = 0;
        bool mMirroredX = false, mMirroredY = false;
        Vec2 mWorldPt{ 0, 0 }, mLocalPt{ 0, 0 }, mScale{ 1,1 }, mAnchorPt{ 0, 0 }, mDimensions{ 0, 0 };

    public:
        inline static String GUID = "transform";
    };
}

#endif
