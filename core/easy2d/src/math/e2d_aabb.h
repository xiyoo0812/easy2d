#ifndef AABB_H
#define AABB_H

#include "e2d_matrix.h"

namespace Easy2D
{
    //-----------------------------------------------
    class AABox2
    {
        //box structure
        Vec2 min;
        Vec2 max;
    public:
        //costructor
        AABox2(const Vec2& center, Vec2 size);
        AABox2();
        //destructor
        ~AABox2();
        //setting
        void setPoints(const std::vector<Vec2>& points);
        void setBox(const Vec2& center, Vec2 size);
        void setRegion(const AABox2& aabox);
        void addPoint(const Vec2& point);
        void addBox(const AABox2& aabox);
        //static init
        static AABox2 combine(const AABox2& box0, const AABox2& box1)
        {
            AABox2 out;
            out.addBox(box0);
            out.addBox(box1);
            return out;
        }
        template<typename... Args>
        static AABox2 combine(const AABox2& box0, const Args&... boxs)
        {
            AABox2 out = combine(box0, boxs...);
            return out;
        }
        //getter
        Vec2  getCenter() const
        {
            return (min + max) * 0.5;
        }
        Vec2  getSize() const
        {
            return (max - min) * 0.5;
        }
        const Vec2& getMax() const
        {
            return max;
        }
        const Vec2& getMin() const
        {
            return min;
        }
        void setMax(const Vec2& m)
        {
            max = m;
        }
        void setMin(const Vec2& m)
        {
            min = m;
        }
        Vec2& getMax()
        {
            return max;
        }
        Vec2& getMin()
        {
            return min;
        }
        //area
        float getArea() const
        {
            Vec2   size = max - min;
            return size.x * size.y;
        }
        //intersections
        bool  isIntersection(const Vec2& point) const;
        bool  isIntersection(const AABox2& aabb2) const;
        bool  isInside(const AABox2& point) const;
        bool  isInside(const Vec2& point) const;
        AABox2 applay(const Matrix4x4& m4) const;
    };

    class OBBox2
    {
    public:
        //box
        OBBox2()
        {
        }
        //init box from aabb
        OBBox2(const AABox2& aab)
        {
            set(aab);
        }
        //box init from vertex
        OBBox2(const std::vector<Vec2>& points)
        {
            set(points);
        }
        //box init from aabb + angle
        OBBox2(const Vec2& center, const Vec2& size, Angle angle)
        {
            set(center, size, angle);
        }
        //init obb
        void set(const Vec2& center, const Vec2& size, Angle angle);
        //from aabb
        void set(const AABox2& aabox);
        //from points
        void set(const std::vector<Vec2>& points);
        //applay transform
        OBBox2 applay(const Matrix4x4& m4) const;
        //Intersection
        bool  isIntersection(const Vec2& point) const;
        bool  isIntersection(const OBBox2& obb) const;
        bool  isIntersection(const AABox2& aab) const;
        //corner
        Vec2 getCorner(uchar i) const
        {
            return corner[i];
        }
        //get size
        Vec2 getSize() const
        {
            return Vec2((corner[0] - corner[1]).length(), (corner[1] - corner[2]).length());
        }
        //get center
        Vec2 getCenter() const
        {
            return (corner[0] + corner[1] + corner[2] + corner[3]) / 4.0f;
        }
        //get direction
        Vec2 getDir() const
        {
            return (corner[1] - corner[2]).getNormalize();
        }
        //get angle
        Angle getAngle() const
        {
            return getDir().direction();
        }
        //cast
        AABox2 toAABox2() const;

    private:
        // Corners of the box, where 0 is the lower left
        Vec2 corner[4];
        // Two edges of the box extended away from corner[0]
        Vec2 axis[2];
        /// origin[a] = corner[0].dot(axis[a]);
        float origin[2];
        //compute axes
        void computeAxes();
        //compute intersecation
        bool intersection1Way(const OBBox2& other) const;
        //aux for minimize problem
        static void calc2DCov(const Vector<Vec2>& points, Vec2& centroid, Mat4& cov2);
        static void calcEigenVectors2D(const Mat4& cov2, Vec2& v1, Vec2& v2);
    };
}

#endif
