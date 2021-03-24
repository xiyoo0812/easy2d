#include "e2d_aabb.h"
#include "e2d_math.h"

/* Easy2D */
using namespace Easy2D;

/* AABBox */
AABox2::AABox2(const Vec2& center, Vec2 size)
{
    setBox(center, size);
}

AABox2::AABox2()
{
    //bad init
    min = Vec2::MAX;
    max = -Vec2::MAX;
}

AABox2::~AABox2()
{

}

void AABox2::setPoints(const std::vector<Vec2>& points)
{
    min = Vec2::MAX;
    max = -Vec2::MAX;
    for (auto& point : points)
    {
        max.x = std::max(point.x, max.x);
        max.y = std::max(point.y, max.y);
        min.x = std::min(point.x, min.x);
        min.y = std::min(point.y, min.y);
    }
}

void AABox2::setBox(const Vec2& center, Vec2 size)
{
    size.abs();
    min = center - size * 0.5;
    max = center + size * 0.5;
}

void AABox2::addPoint(const Vec2& p)
{
    //found box                      m______
    min.x = Math::min(min.x, p.x);  //  |\    |
    min.y = Math::min(min.y, p.y);  //  | \.c |
    max.x = Math::max(max.x, p.x);  //  |   \ |
    max.y = Math::max(max.y, p.y);  //  |____\|M
}

void AABox2::addBox(const AABox2& p)
{
    addPoint(p.getMin());
    addPoint(p.getMax());
}

void AABox2::setRegion(const AABox2& p)
{
    //found box                             m______
    min.x = Math::max(min.x, p.min.x);      //  |\    |
    min.y = Math::max(min.y, p.min.y);      //  | \.c |
    max.x = Math::min(max.x, p.max.x);      //  |   \ |
    max.y = Math::min(max.y, p.max.y);      //  |____\|M
}

bool AABox2::isIntersection(const Vec2& point) const
{
    if (max.x < min.x || max.y < min.y)
    {
        return false;
    }
    auto cdiff = (getCenter() - point).getAbs();
    auto size = getSize();
    return  cdiff.x <= size.x && cdiff.y <= size.y;
}

bool AABox2::isIntersection(const AABox2& aabb2) const
{
    if (max.x < min.x || max.y < min.y || aabb2.max.x < aabb2.min.x || aabb2.max.y < aabb2.min.y)
    {
        return false;
    }
    auto cdiff = (getCenter() - aabb2.getCenter()).getAbs();
    auto ssum = getSize() + aabb2.getSize();
    return  cdiff.x <= ssum.x && cdiff.y <= ssum.y;
}

bool  AABox2::isInside(const Vec2& point) const
{
    return isIntersection(point);
}

bool  AABox2::isInside(const AABox2& box) const
{
    if (max.x < min.x || max.y < min.y || box.max.x < box.min.x || box.max.y < box.min.y)
    {
        return false;
    }
    return box.min.x <= min.x &&
        box.min.y <= min.y &&
        box.max.x >= max.x &&
        box.max.y >= max.y;
}

AABox2 AABox2::applay(const Matrix4x4& m4) const
{
    //new box
    AABox2 newbox;
    //size
    Vec2 hsize = (max - min) * .5;
    Vec2 center = m4.mul2D((max + min) * .5);
    //rotscale
    Vec2 up = m4.mul2D(Vec2(hsize.x, hsize.y)) - m4.getTranslation2D();
    Vec2 down = m4.mul2D(Vec2(hsize.x, -hsize.y)) - m4.getTranslation2D();
    up.abs();
    down.abs();
    //final size
    Vec2 fhsize;
    fhsize.x = Math::max(up.x, down.x);
    fhsize.y = Math::max(up.y, down.y);
    //set
    newbox.setBox(center, fhsize * 2.0);
    //return
    return newbox;
}

/* OBBox2 */
//init obb
void OBBox2::set(const Vec2& center, const Vec2& size, Angle angle)
{
    angle += Angle::degree(90);
    Vec2 on_x(angle.cos(), angle.sin());
    Vec2 on_y(-on_x.y, on_x.x);
    on_x *= size.x * 0.5f;
    on_y *= size.y * 0.5f;
    corner[0] = center - on_x - on_y;
    corner[1] = center + on_x - on_y;
    corner[2] = center + on_x + on_y;
    corner[3] = center - on_x + on_y;
    computeAxes();
}

//from aabb
void OBBox2::set(const AABox2& aabox)
{
    set(aabox.getCenter(), aabox.getSize() * 2.0f, Angle::radian(0));
}

//from points
void OBBox2::set(const std::vector<Vec2>& points)
{
    //centroid
    Vec2 centroid;
    //calc C
    Mat4 cov2;
    calc2DCov(points, centroid, cov2);
    //calc eigen(C)
    Vec2 basis[2];
    calcEigenVectors2D(cov2, basis[0], basis[1]);
    //R=|v1,v2|
    Radian rotation(std::atan2(basis[0].x, basis[1].y));
    //min max
    Vec2 vmax(-Vec2::MAX);
    Vec2 vmin(Vec2::MAX);
    float* max = ((float*)(vmax));
    float* min = ((float*)(vmin));
    //calc projection
    for (const Vec2& p : points)
    {
        Vec2 diff = p - centroid;
        for (uchar i = 0; i != 2; ++i)
        {
            float length = diff.dot(basis[i]);
            if (length > max[i])
                max[i] = length;
            else if (length < min[i])
                min[i] = length;
        }
    }

    // compute center, extents
    Vec2 center = centroid;
    Vec2 extents;
    for (uchar i = 0; i != 2; ++i)
    {
        center += 0.5f * (min[i] + max[i]) * basis[i];
        ((float*)(extents))[i] = 0.5f * (max[i] - min[i]);
    }
    //set OBB
    set(center, extents, rotation);
}

//applay transform
OBBox2 OBBox2::applay(const Matrix4x4& m4) const
{
    OBBox2 newbox(*this);
    newbox.corner[0] = m4.mul2D(newbox.corner[0]);
    newbox.corner[1] = m4.mul2D(newbox.corner[1]);
    newbox.corner[2] = m4.mul2D(newbox.corner[2]);
    newbox.corner[3] = m4.mul2D(newbox.corner[3]);
    newbox.computeAxes();
    return newbox;
}

//intersection
bool OBBox2::isIntersection(const Vec2& point) const
{
    for (uint a = 0; a != 2; ++a)
    {
        float t = corner[0].dot(axis[a]);
        float p = point.dot(axis[a]);
        // Find the extent of box 2 on axis a
        double tMin = t;
        double tMax = t;
        //find max min
        for (uint c = 1; c != 4; ++c)
        {
            t = corner[c].dot(axis[a]);

            if (t < tMin)
            {
                tMin = t;
            }
            else if (t > tMax)
            {
                tMax = t;
            }
        }
        //in projection?
        if ((tMin > p) || (tMax < p)) return false;
    }
    //point is in all axis
    return true;
}

bool OBBox2::isIntersection(const OBBox2& obb) const
{
    return intersection1Way(obb) && obb.intersection1Way(*this);
}

bool OBBox2::isIntersection(const AABox2& aab) const
{
    return OBBox2(aab).isIntersection(*this);
}

//cast
AABox2 OBBox2::toAABox2() const
{
    AABox2 box;
    box.addPoint(corner[0]);
    box.addPoint(corner[1]);
    box.addPoint(corner[2]);
    box.addPoint(corner[3]);
    return box;
}

//compute axes
void OBBox2::computeAxes()
{
    axis[0] = corner[1] - corner[0];
    axis[1] = corner[3] - corner[0];
    // Make the length of each axis 1/edge length so we know any
    // dot product must be less than 1 to fall within the edge.
    for (int a = 0; a < 2; ++a)
    {
        axis[a] /= axis[a].squaredLength();
        origin[a] = corner[0].dot(axis[a]);
    }
}

//compute intersecation
bool OBBox2::intersection1Way(const OBBox2& other) const
{
    for (uint a = 0; a != 2; ++a)
    {
        float t = other.corner[0].dot(axis[a]);
        // Find the extent of box 2 on axis a
        float tMin = t;
        float tMax = t;

        for (uint c = 1; c != 4; ++c)
        {
            t = other.corner[c].dot(axis[a]);
            if (t < tMin)
            {
                tMin = t;
            }
            else if (t > tMax)
            {
                tMax = t;
            }
        }
        // We have to subtract off the origin
        // See if [tMin, tMax] intersects [0, 1]
        if ((tMin > 1 + origin[a]) || (tMax < origin[a]))
            // There was no intersection along this dimension;
            // the boxes cannot possibly overlap.
            return false;
    }
    // There was no dimension along which there is no intersection.
    // Therefore the boxes overlap.
    return true;
}

//static
void OBBox2::calc2DCov(const std::vector<Vec2>& points, Vec2& centroid, Mat4& cov2)
{
    for (const Vec2& p : points) centroid += p;
    if (points.size() > 1) centroid /= points.size();

    // compute the (co)variances
    Vec2 var;
    float covXY = 0;
    for (const Vec2& p : points)
    {
        Vec2 diff = p - centroid;
        var.x += diff.x * diff.x;
        var.y += diff.y * diff.y;
        covXY += diff.x * diff.y;
    }
    //normalize
    if (points.size() > 1)
    {
        var.x /= points.size();
        var.y /= points.size();
        covXY /= points.size();
    }
    //to matrix
    Mat4 C;
    cov2(0, 0) = var.x;
    cov2(1, 1) = var.y;
    cov2(1, 0) = cov2(0, 1) = covXY;
}

void OBBox2::calcEigenVectors2D(const Mat4& cov2, Vec2& v1, Vec2& v2)
{
    //alias
    const float& a = cov2(0, 0);
    const float& b = cov2(1, 0);
    const float& c = cov2(0, 1);
    const float& d = cov2(1, 1);
#define eqF(x,y,z) (std::abs(x-y)<z)
#define eqFE(x,y)  eqF(x,y,0.0001)
    //3 case
    if (eqFE(b, 0.0) && eqFE(c, 0.0))
    {
        v1 = Vec2(1, 0);
        v2 = Vec2(0, 1);
        return;
    }
    //calc det (determinant) & t (trace)
    float det = a * d - b * c;
    float t = a + b;
    //calc l1 & l2 (Eigen values)
    float lp = fmodf(((t * t) / 4 - det), 0.5);
    float l1 = t / 2 + lp;
    float l2 = t / 2 - lp;
    //case 1
    if (!eqFE(c, 0.0))
    {
        v1 = Vec2(l1 - d, c);
        v2 = Vec2(l2 - d, c);
        return;
    }
    //case 2
    //if(!eqFE(b,0.0))
    {
        v1 = Vec2(b, l1 - a);
        v2 = Vec2(b, l2 - a);
        return;
    }
}
