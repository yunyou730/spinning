#include <stdio.h>
#include "AppFramework.h"
#include "renderer.hpp"
#include <vector>
#include "math.hpp"
#include "Camera.h"

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
        
        Vertex a(Vec4(-size,-size, size,1.),red);
        Vertex b(Vec4( size,-size, size,1.),red);
        Vertex c(Vec4(-size, size, size,1.),red);
        Vertex d(Vec4( size, size, size,1.),red);
        
        Vertex e(Vec4(-size,-size, -size,1.),red);
        Vertex f(Vec4( size,-size, -size,1.),red);
        Vertex g(Vec4(-size, size, -size,1.),red);
        Vertex h(Vec4( size, size, -size,1.),red);
        
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
    std::vector<Vertex>*  GetVertices()
    {
        return &_vertices;
    }
    
    int FaceCount()
    {
        return static_cast<int>(_vertices.size()) / 3;
    }
    
    std::vector<Vertex> GetFaceAtIndex(int index)
    {
        if(index >= FaceCount())
        {
            throw std::runtime_error("invalid face index");
        }
        std::vector<Vertex> vertice;
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
    std::vector<Vertex> _vertices;
    
    // pos
    Vec3f   _pos;
    
    // rotation
    float   _pitch  = 0.0f;     // rotate by local x
    float   _yaw    = 0.0f;     // rotate by local y
    float   _roll   = 0.0;      // rotate by local z
};

struct Shader
{
    Vec4 vertex()
    {
        Vec4 gl_Position;
        return gl_Position;
    }
};


int main( int argc, char* args[] )
{
    Camera testcase;
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
            std::vector<Vertex> vertice = actor.GetFaceAtIndex(faceIndex);
            
            for(int i = 0;i < vertice.size();i++)
            {
                Vertex& vertex = vertice[i];
                vertex.pos = mvpViewport * vertex.pos;
                vertex.pos = vertex.pos * (1/vertex.pos.w);
            }
            
            Vec3f v1 = vertice[1].pos - vertice[0].pos;
            Vec3f v2 = vertice[2].pos - vertice[1].pos;
            Vec3f normalDir = (v1 ^ v2).Normalize();
            if(testcase.CheckFaceNormalDir(normalDir))
            {
                triangle(ctx,col,vertice[0].pos,vertice[1].pos,vertice[2].pos);
            }
        }
    });
    app.MainLoop();
    app.Clean();
    
    return 0;
}
