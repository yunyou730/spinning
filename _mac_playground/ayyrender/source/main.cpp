#include <stdio.h>
#include "AppFramework.h"
#include "renderer.hpp"
#include <vector>
#include "math.hpp"

class Testcase
{
public:
    Testcase()
    {
        InitIndice();
        InitUVN();
        InitViewport();
        _viewDistance = 1.0f;
    }
    
    std::vector<Vec4>*  GetVertices()
    {
        return &_vertices;
    }
    
    
    int TriangleCount()
    {
        return _vertices.size() / 3;
    }
    
    void InitIndice()
    {
        float size = 1.0f;
        // front vertices
        Vec4 a(-size,-size, size,1.);
        Vec4 b( size,-size, size,1.);
        Vec4 c(-size, size, size,1.);
        Vec4 d( size, size, size,1.);
        
        // back vertices
        Vec4 e(-size,-size,-size,1.);
        Vec4 f( size,-size,-size,1.);
        Vec4 g(-size, size,-size,1.);
        Vec4 h( size, size,-size,1.);
        
        // front
        _vertices.push_back(a);
        _vertices.push_back(b);
        _vertices.push_back(c);
        _vertices.push_back(b);
        _vertices.push_back(d);
        _vertices.push_back(c);
        
        // back
        _vertices.push_back(e);
        _vertices.push_back(f);
        _vertices.push_back(g);
        _vertices.push_back(f);
        _vertices.push_back(h);
        _vertices.push_back(g);
        
        // right
        _vertices.push_back(b);
        _vertices.push_back(f);
        _vertices.push_back(d);
        _vertices.push_back(f);
        _vertices.push_back(h);
        _vertices.push_back(d);
        
        // left
        _vertices.push_back(e);
        _vertices.push_back(a);
        _vertices.push_back(g);
        _vertices.push_back(a);
        _vertices.push_back(g);
        _vertices.push_back(c);
    }
    
    void InitUVN()
    {
        // eye
        _eye.x = 0;_eye.y = 0;  _eye.z = 4;
        // look target
        _target.x = 0;  _target.y = 0;  _target.z = 0;
        // up
        _up.x = 0;  _up.y = 1;  _up.z = 0;
    }
    
    void InitViewport()
    {
        _viewportWidth = 800;
        _viewportHeight = 800;
    }
    
    Matrix<4>   WorldMatrix()
    {
        Matrix<4>   mat;
        mat.Identity();
        mat.Set(0,3,_pos.x);
        mat.Set(1,3,_pos.y);
        mat.Set(2,3,_pos.z);
        
        
        
        return mat;
    }
    
    Matrix<4>  ModelViewMatrix()
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
    
    Matrix<4>   ProjectionMatrix()
    {
        // @miao @todo
        Matrix<4>   mat;
        mat.Identity();
        mat.Set(3,2,-1.f/_viewDistance);
        mat.Set(3,3,0.0f);
        return mat;
    }
    
    Matrix<4>   ViewportMatrix()
    {
        Matrix<4>   mat;
        mat.Identity();
        
        float alpha = 0.5 * _viewportWidth - 0.5f;
        float beta = 0.5 * _viewportHeight - 0.5f;
        mat.Set(0,0,alpha);
        mat.Set(1,1,-beta);
        mat.Set(0,3,alpha);
        mat.Set(1,3,beta);
        return mat;
    }
    
    
public:
    // uvn base data
    Vec3f    _eye;
    Vec3f    _target;
    Vec3f    _up;
    
    // vertice data
    std::vector<Vec4>  _vertices;
    
    // viewport size
    int     _viewportWidth;
    int     _viewportHeight;
    
    // 视距 用于 projection matrix
    float   _viewDistance;
    
    Vec3f   _pos;
    float   _rotateByLocalY = 0.0f;
};


void Test()
{
    Matrix<4>   mat1(std::vector<float>{
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
    });
    mat1.dump();
    
    Matrix<4>   mat2(std::vector<float>{
        0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
    });
    mat2.dump();
    
    Matrix<4> mat3 = mat1 * mat2;
    mat3.dump();
}

int main( int argc, char* args[] )
{
    Testcase testcase;
    
    Vec4 p1(-3,6.55,-12,1);
    Vec4 p2 = p1;
    p1.dump();
    p1 = testcase.WorldMatrix() * p1;
    p1 = testcase.ModelViewMatrix() * p1;
    p1 = testcase.ProjectionMatrix() * p1;
    p1.dump();
    
    p2.dump();
    Matrix<4> mat =
    testcase.ProjectionMatrix() *
    testcase.ModelViewMatrix() *
    testcase.WorldMatrix();
    p2 = mat * p2;
    p2.dump();

//    if(true)
//    {
//        return 0;
//    }

    AppFramework app(800,800,255);
    app.Init();
    app.RegisterUpdateFunc([&](float deltaTime) {
        float dis = 0.5f * deltaTime;
        
        // move object
        if(app.QueryKeyState(SDL_KeyCode::SDLK_a))
        {
            testcase._pos.x -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_d))
        {
            testcase._pos.x += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_w))
        {
            testcase._pos.y += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_s))
        {
            testcase._pos.y -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_q))
        {
            testcase._pos.z -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_e))
        {
            testcase._pos.z += dis;
        }
        
        // move camera
        if(app.QueryKeyState(SDL_KeyCode::SDLK_UP))
        {
            testcase._eye.y += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_DOWN))
        {
            testcase._eye.y -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_LEFT))
        {
            testcase._eye.x -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_RIGHT))
        {
            testcase._eye.x += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_SLASH))
        {
            testcase._eye.z += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_BACKSLASH))
        {
            testcase._eye.z -= dis;
        }
        
    });
    
    app.RegisterDrawFunc([&](RenderContext* ctx){
        // 闪烁了一下 是因为 ztest 没通过...
//        triangleFill(ctx,Color(255,255,0,255),Vec3i(0,0),Vec3i(400,800),Vec3i(800,0));
//        triangle(ctx,Color(255,0,0,255),Vec2i(0,0),Vec2i(400,800),Vec2i(800,0));
        
        std::vector<Vec2i> transformedVertices;
        Matrix<4> mv  = testcase.ModelViewMatrix() * testcase.WorldMatrix();
        Matrix<4> mvp = testcase.ProjectionMatrix() * mv;
        
        std::vector<Vec4>* vertices = testcase.GetVertices();
        for(int vertexIndex = 0;vertexIndex < vertices->size();vertexIndex++)
        {
            Vec4 point = (*vertices)[vertexIndex];
            point = mvp * point;
            point = testcase.ViewportMatrix() * point;
            point = point * (1.f/point.w);
            point.y = testcase._viewportHeight - point.y;
            
            transformedVertices.push_back(Vec2i(point.x / point.w,point.y / point.w));
        }
        
        Color col(255,0,0,255);
        for(int triangleIndex = 0;triangleIndex < testcase.TriangleCount();triangleIndex++)
        {
            int vIndex = triangleIndex * 3;
            triangle(ctx,col,transformedVertices[vIndex],
                                transformedVertices[vIndex + 1],
                                transformedVertices[vIndex + 2]);
        }
    });
    app.MainLoop();
    app.Clean();
    
    return 0;
}
