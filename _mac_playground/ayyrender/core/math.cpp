#include "math.hpp"

const float PI = 3.1415926f;

float deg2Rad(float deg)
{
    return PI * deg / 180.f;
}

float rad2Deg(float rad)
{
    return 180.f / PI * rad;
}

Matrix<4> RotateByAxisX(float deg)
{
    float rad = deg2Rad(deg);
    Matrix<4>   mat;
    mat.Identity();
    
    float sinVal = sin(rad);
    float cosVal = cos(rad);
    mat.Set(1,1,cosVal);
    mat.Set(1,2,-sinVal);
    mat.Set(2,1,sinVal);
    mat.Set(2,2,cosVal);
    
    return mat;
}

Matrix<4> RotateByAxisY(float deg)
{
    float rad = deg2Rad(deg);
    Matrix<4>   mat;
    mat.Identity();
    
    float sinVal = sin(rad);
    float cosVal = cos(rad);
    mat.Set(0,0,cosVal);
    mat.Set(2,0,-sinVal);
    mat.Set(0,2,sinVal);
    mat.Set(2,2,cosVal);
    
    return mat;
}

Matrix<4> RotateByAxisZ(float deg)
{
    float rad = deg2Rad(deg);
    Matrix<4>   mat;
    mat.Identity();
    
    float sinVal = sin(rad);
    float cosVal = cos(rad);
    mat.Set(0,0,cosVal);
    mat.Set(0,1,-sinVal);
    mat.Set(1,0,sinVal);
    mat.Set(1,1,cosVal);
    
    return mat;
}

float Lerp(float a,float b,float pct)
{
    if(a > b) std::swap(a,b);
    return a + (b - a) * pct;
}

extern Vec3f TriangleBarycentricCoordinate(const Vec2f& a,const Vec2f& b,const Vec2f& c,const Vec2f& p)
{
    float ra =
    (-(p.x - b.x) * (c.y - b.y) + (p.y - b.y) * (c.x - b.x))
    /
    (-(a.x - b.x) * (c.y - b.y) + (a.y - b.y) * (c.x - b.x));
    
    
//
//    float rb = (-(p.x - c.x) * (a.y - c.y) + (p.y - c.y) * (a.x - c.x))
//    /
//    (-(b.x - c.x) * (a.y - c.y) * )
//    float rc = 1 - ra - rb;
//
//    Vec3f result(ra,rb,rc);
//    return result;
    return Vec3f();
}
