#pragma once
#include "math.hpp"

class Camera
{
public:
    Camera(int viewPortWidth,int viewportHeight);
private:
    void InitUVN();
public:

    Matrix<4>  ViewMatrix();
    Matrix<4>   ProjectionMatrix();
    Matrix<4>   ViewportMatrix();
    
public:
    bool CheckBackFace(const Vec3f& normalDir);
    
public:
    // uvn base data
    Vec3f    _eye;
    Vec3f    _target;
    Vec3f    _up;
    
    // viewport size
    int     _viewportWidth;
    int     _viewportHeight;
    
    // 视距 用于 projection matrix
    float   _viewDistance;
};
