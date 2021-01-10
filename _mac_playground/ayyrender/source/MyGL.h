#pragma once
#include "math.hpp"

class MyGL
{
public:    
    MyGL(const Vec3f& eye,const Vec3f& center,const Vec3f& up,
        float vx,float vy,float vw,float vh);
    
    void CalcMatrics();
    
    Matrix<4>   ModelView() const { return _modelView;}
    Matrix<4>   Viewport() const { return _viewport;}
    Matrix<4>   Projection() const { return _projection;}
private:
    void Viewport(int x,int y,int w,int h);
    void Projection(float ceoff);
    void LookAt(Vec3f& eye,Vec3f& center,Vec3f& up);
    
protected:
    Vec3f   _eye;
    Vec3f   _center;
    Vec3f   _up;
    
    float   _viewportX,_viewportY,_viewportW,_viewportH;
    
    Matrix<4>   _modelView;
    Matrix<4>   _viewport;
    Matrix<4>   _projection;
};
