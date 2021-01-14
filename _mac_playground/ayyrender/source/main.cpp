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
        InitUVN();
        InitViewport();
        _viewDistance = 1.0f;
    }

private:
    
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
    
public:

    Matrix<4>  ViewMatrix()
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
        Matrix<4>   mat;
        mat.Identity();
        mat.Set(3,2,-1.f/_viewDistance);
//        mat.Set(3,3,0.0f);
        return mat;
    }
    
    Matrix<4>   ViewportMatrix()
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
    
public:
    bool CheckFaceNormalDir(const Vec3f& normalDir)
    {
        Vec3f lookDir = (_target - _eye).Normalize();
        float dot = (lookDir * normalDir);
        return dot < 0;
    }
    
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

class Actor
{
public:
    Actor()
    {
        InitVertices();
    }

private:
    void InitVertices()
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
        _vertices.push_back(f);
        _vertices.push_back(e);
        _vertices.push_back(h);

        _vertices.push_back(e);
        _vertices.push_back(g);
        _vertices.push_back(h);

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
        _vertices.push_back(c);
        _vertices.push_back(g);
        
        // top
        _vertices.push_back(c);
        _vertices.push_back(d);
        _vertices.push_back(g);
        
        _vertices.push_back(d);
        _vertices.push_back(h);
        _vertices.push_back(g);
        
        // down
        _vertices.push_back(e);
        _vertices.push_back(f);
        _vertices.push_back(a);
        
        _vertices.push_back(f);
        _vertices.push_back(b);
        _vertices.push_back(a);
    }
    
public:
    std::vector<Vec4>*  GetVertices()
    {
        return &_vertices;
    }
    
    int FaceCount()
    {
        return static_cast<int>(_vertices.size()) / 3;
    }
    
    std::vector<Vec4> GetFaceAtIndex(int index)
    {
        if(index >= FaceCount())
        {
            throw std::runtime_error("invalid face index");
        }
        std::vector<Vec4> vertice;
        index = index * 3;
        vertice.push_back(_vertices[index]);
        vertice.push_back(_vertices[index + 1]);
        vertice.push_back(_vertices[index + 2]);
        return vertice;
    }
    
    Matrix<4>   WorldMatrix()
    {
        Matrix<4>   mat;
        mat.Identity();
        mat.Set(0,3,_pos.x);
        mat.Set(1,3,_pos.y);
        mat.Set(2,3,_pos.z);
        
        Matrix<4> matPitch = RotateByAxisX(_pitch);
        Matrix<4> matYaw = RotateByAxisY(_yaw);
        Matrix<4> matRoll = RotateByAxisZ(_roll);
        return mat * matRoll * matYaw * matPitch;
    }
        
public:
    // vertice
    std::vector<Vec4>  _vertices;
    
    // pos
    Vec3f   _pos;
    
    // rotation
    float   _pitch  = 0.0f;     // rotate by local x
    float   _yaw    = 0.0f;     // rotate by local y
    float   _roll   = 0.0;      // rotate by local z
};

void ShaderProgram()
{
    
}

int main( int argc, char* args[] )
{
    Testcase testcase;
    Actor actor;
    
    AppFramework app(800,800,255);
    app.Init();
    app.RegisterUpdateFunc([&](float deltaTime) {
        // yaw
        float deltaYaw = 60 * deltaTime;
        actor._yaw += deltaYaw;
        
        float deltaPitch = 45 * deltaTime;
        actor._pitch += deltaPitch;
        
        float dis = 0.5f * deltaTime;
        // move object
        if(app.QueryKeyState(SDL_KeyCode::SDLK_a))
        {
            actor._pos.x -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_d))
        {
            actor._pos.x += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_w))
        {
            actor._pos.y += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_s))
        {
            actor._pos.y -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_q))
        {
            actor._pos.z -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_e))
        {
            actor._pos.z += dis;
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
        Color col(255,0,0,255);
        
        Matrix<4> mvp = testcase.ProjectionMatrix() * testcase.ViewMatrix() * actor.WorldMatrix();
        Matrix<4> mvpViewport = testcase.ViewportMatrix() * mvp;
        
        for(int faceIndex = 0;faceIndex < actor.FaceCount();faceIndex++)
        {
            std::vector<Vec4> vertice = actor.GetFaceAtIndex(faceIndex);
            
            vertice[0].dump();
            vertice[1].dump();
            vertice[2].dump();
            
            for(int i = 0;i < vertice.size();i++)
            {
                Vec4& vertex = vertice[i];
                vertex = mvpViewport * vertex;
                vertex = vertex * (1/vertex.w);
            }
            
            vertice[0].dump();
            vertice[1].dump();
            vertice[2].dump();
            
            Vec3f v1 = vertice[1] - vertice[0];
            Vec3f v2 = vertice[2] - vertice[1];
            Vec3f normalDir = (v1 ^ v2).Normalize();
            if(testcase.CheckFaceNormalDir(normalDir))
            {
                triangle(ctx,col,vertice[0],vertice[1],vertice[2]);
            }
            
            
        }
    });
    app.MainLoop();
    app.Clean();
    
    return 0;
}
