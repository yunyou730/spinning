#include "MyGL.h"

MyGL::MyGL(const Vec3f& eye,const Vec3f& center,const Vec3f& up,
    float vx,float vy,float vw,float vh)
    :_eye(eye)
    ,_center(center)
    ,_up(up)
    ,_viewportX(vx)
    ,_viewportY(vy)
    ,_viewportW(vw)
    ,_viewportH(vh)
{
    
}

void MyGL::CalcMatrics()
{
    Viewport(_viewportX,_viewportY,_viewportW,_viewportH);
    Projection(-1./(_eye - _center).Length());  // @miao @todo
    LookAt(_eye,_center,_up);
}

void MyGL::Viewport(int x,int y,int w,int h)
{
    float depth = 255;
    _viewport.Identity();
    
    _viewport.Set(0,0,w / 2.f);
    _viewport.Set(1,1,h / 2.f);
    _viewport.Set(2,2,depth / 2.f);
    
    _viewport.Set(0,3,x + w / 2.f);
    _viewport.Set(1,3,y + h / 2.f);
    _viewport.Set(2,3,depth / 2.f);
    
}

void MyGL::Projection(float ceoff)
{
    _projection.Identity();
    _projection.Set(3,2,ceoff);
}

void MyGL::LookAt(Vec3f& eye,Vec3f& center,Vec3f& up)
{
    Vec3f z = (eye - center).Normalize();
    Vec3f x = (up ^ z).Normalize();
    Vec3f y = (z ^ x).Normalize();
    _modelView.Identity();
    
    
    _modelView.Set(0,0,x.x);
    _modelView.Set(0,1,x.y);
    _modelView.Set(0,2,x.z);
    
    _modelView.Set(1,0,y.x);
    _modelView.Set(1,1,y.y);
    _modelView.Set(1,2,y.z);
    
    _modelView.Set(2,0,z.x);
    _modelView.Set(2,1,z.y);
    _modelView.Set(2,2,z.z);
    
    _modelView.Set(0,3,-center.x);
    _modelView.Set(1,3,-center.y);
    _modelView.Set(2,3,-center.z);
    
}
