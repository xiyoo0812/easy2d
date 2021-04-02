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
        void translate(const Vec2& translation, lay l);
        void translate(float32 x, float32 y, lay l);
        void translate(const Pos & pos2D);
        void translateX(float32 x);
        void translateY(float32 y);
        void translateL(lay l);

        void move(const Vec2& translation);
        void move(float32 x, float32 y);
        void moveX(float32 x);
        void moveY(float32 y);

        void rotate(float32 rotation);
        void rotate(float32 rotation, const Vec2& centerPoint);

        void scale(const Vec2& scale);
        void scale(float32 x, float32 y);
        void scale(float32 u);
        void scaleX(float32 x);
        void scaleY(float32 y);

        void mirror(bool x, bool y);
        void mirrorX(bool x);
        void mirrorY(bool y);

        const Pos& getWorldPosition();
        const Pos& getLocalPosition();
        float32 getWorldRotation();
        float32 getLocalRotation() const;
        const Vec2& getWorlScale();
        const Vec2& getLocalScale();

        void setCenterPoint(const Vec2 & centerPoint);
        void setCenterPoint(float32 x, float32 y);
        void setCenterX(float32 x);
        void setCenterY(float32 y);

        void setDimensions(int32 x, int32 y);
        void setDimensions(const Vec2 & dimensions);
        void setDimensionsX(int32 x);
        void setDimensionsY(int32 y);

        void setDimensionsSafe(int32 x, int32 y);
        void setDimensionsSafe(const Vec2 & dimensions);
        void setDimensionsXSafe(int32 x);
        void setDimensionsYSafe(int32 y);

        const Mat4& getWorldMatrix() const;

    private:
        void checkForUpdate(const bool force = false);
        void commonUpdate();
        void singleUpdate(Mat4& world);

        uchar mChanged;
        Pos mWorldPosition, mLocalPosition;
        float32 mWorldRotation, mLocalRotation;
        Vec2 mWorldScale, mLocalScale, mCenterPosition;
        bool mMirroredX;
        bool mMirroredY;
        Mat4 mWorld;

    public:
        inline static String GUID = "transform";
    };
}

#endif
