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


