#include "Camera.h"

Camera::Camera()
{
    InitUVN();
    InitViewport();
    _viewDistance = 1.0f;
}

void Camera::InitUVN()
{
    // eye
    _eye.x = 0;_eye.y = 0;  _eye.z = 4;
    // look target
    _target.x = 0;  _target.y = 0;  _target.z = 0;
    // up
    _up.x = 0;  _up.y = 1;  _up.z = 0;
}

void Camera::InitViewport()
{
    _viewportWidth = 800;
    _viewportHeight = 800;
}


Matrix<4>  Camera::ViewMatrix()
{
    // 注意 ！ 这里必须也是 右手坐标系， 也就是说 n 向量 对应的 z 向量 ，要是 eye - target !!而不是 target - eye !!!
    // 并且 ！ 向量叉乘 的 方向， 符合 右手 原则 ！！
    Vec3f n = (_eye - _target).Normalize(); // camera z
    Vec3f u = (_up ^ n).Normalize();    // camera x
    Vec3f v = (n ^ u).Normalize();      // camera y
    
    Matrix<4>   mat;
    mat.Identity();
    
    mat.Set(0,0,u.x);
    mat.Set(0,1,u.y);
    mat.Set(0,2,u.z);

    mat.Set(1,0,v.x);
    mat.Set(1,1,v.y);
    mat.Set(1,2,v.z);
    
    mat.Set(2,0,n.x);
    mat.Set(2,1,n.y);
    mat.Set(2,2,n.z);
    
    mat.Set(0,3,-_eye.x);
    mat.Set(1,3,-_eye.y);
    mat.Set(2,3,-_eye.z);
    
    return mat;
}

Matrix<4>   Camera::ProjectionMatrix()
{
    Matrix<4>   mat;
    mat.Identity();
    mat.Set(3,2,-1.f/_viewDistance);
//        mat.Set(3,3,0.0f);
    return mat;
}

Matrix<4>   Camera::ViewportMatrix()
{
    Matrix<4>   mat;
    mat.Identity();
    
    float alpha = 0.5 * _viewportWidth - 0.5f;
    float beta = 0.5 * _viewportHeight - 0.5f;
    mat.Set(0,0,alpha);
    mat.Set(1,1,beta);
    mat.Set(0,3,alpha);
    mat.Set(1,3,beta);
    return mat;
}

bool Camera::CheckFaceNormalDir(const Vec3f& normalDir)
{
    Vec3f lookDir = (_target - _eye).Normalize();
    float dot = (lookDir * normalDir);
    return dot < 0;
}
 
