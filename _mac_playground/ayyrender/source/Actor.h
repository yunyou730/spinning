#pragma once
#include "../core/Pipeline.h"

using namespace ayy;

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

