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
        enum TransformType : byte
        {
            NONE = 0,
            TRANSLATION = 1,
            ROTATION = 2,
            SCALE = 4,
            ALL = 7
        };

        TransformComponent();
        ~TransformComponent();

        virtual void initialize();

        void draw();
        void update(const uint32& escapeMs);
        void setChanged(uchar changed);

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
        float32 getWorldRotation();
        float32 getLocalRotation() const;
        const Vec2& getWorldScale();
        const Vec2& getLocalScale();

        void setAnchor(const Vec2& anchor);
        void setAnchor(float32 x, float32 y);
        void setAnchorX(float32 x);
        void setAnchorY(float32 y);

        void setDimensions(float32 x, float32 y);
        void setDimensions(const Vec2& dimensions);
        void setDimensionsX(float32 x);
        void setDimensionsY(float32 y);

        const Mat4& getWorldMatrix() const;

    private:
        void checkForUpdate(const bool force = false);
        void commonUpdate();
        void singleUpdate(Mat4& world);

        Mat4 mWorld = {};
        uchar mChanged = 0;
        bool mMirroredX = false, mMirroredY = false;
        float32 mWorldRotation = 0, mLocalRotation = 0;
        Vec2 mWorldPt {0, 0}, mLocalPt { 0, 0 }, mWorldScale{ 1,1 }, mLocalScale{ 1,1 }, mAnchorPt{ 0, 0 };

    public:
        inline static String GUID = "transform";
    };
}

#endif
