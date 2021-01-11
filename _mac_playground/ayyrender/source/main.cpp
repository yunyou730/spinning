#include <stdio.h>
#include "AppFramework.h"
#include "renderer.hpp"
#include <vector>

class Testcase
{
public:
    Testcase()
    {
        InitIndice();
        InitUVN();
        InitViewport();
        _viewDistance = 3.0f;
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
        // front vertices
        Vec4 a(-0.5,-0.5, 0.5,1.);
        Vec4 b( 0.5,-0.5, 0.5,1.);
        Vec4 c(-0.5, 0.5, 0.5,1.);
        Vec4 d( 0.5, 0.5, 0.5,1.);
        
        // back vertices
        Vec4 e(-0.5,-0.5,-0.5,1.);
        Vec4 f( 0.5,-0.5,-0.5,1.);
        Vec4 g(-0.5, 0.5,-0.5,1.);
        Vec4 h( 0.5, 0.5,-0.5,1.);
        
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
        return mat;
    }
    
    Matrix<4>  ModelViewMatrix()
    {
        Matrix<4>   mat;
        mat.Identity();
        return mat;
    }
    
    Matrix<4>   ProjectionMatrix()
    {
        Matrix<4>   mat;
        mat.Identity();
        return mat;
    }
    
    Matrix<4>   ViewportMatrix()
    {
        Matrix<4>   mat;
        mat.Identity();
        return mat;
    }
    
    
public:
    // uvn base data
    Vec4    _eye;
    Vec4    _target;
    Vec4    _up;
    
    // vertice data
    std::vector<Vec4>  _vertices;
    
    // viewport size
    int     _viewportWidth;
    int     _viewportHeight;
    
    // 视距 用于 projection matrix
    float   _viewDistance;
};

int main( int argc, char* args[] )
{
    Testcase testcase;
    
    
    AppFramework app(800,800,255);
    app.Init();
    app.RegisterUpdateFunc([&](float deltaTime) {
        
    });
    
    app.RegisterDrawFunc([&](RenderContext* ctx){
        // 闪烁了一下 是因为 ztest 没通过...
//        triangleFill(ctx,Color(255,255,0,255),Vec3i(0,0),Vec3i(400,800),Vec3i(800,0));
//        triangle(ctx,Color(255,0,0,255),Vec2i(0,0),Vec2i(400,800),Vec2i(800,0));
        
        std::vector<Vec2i> transformedVertices;
        
        std::vector<Vec4>* vertices = testcase.GetVertices();
        for(int vertexIndex = 0;vertexIndex < vertices->size();vertexIndex++)
        {
            Vec4 point = (*vertices)[vertexIndex];
            point = testcase.WorldMatrix() * point;
            point = testcase.ModelViewMatrix() * point;
            point = testcase.ProjectionMatrix() * point;
            point = testcase.ModelViewMatrix() * point;
            
            transformedVertices.push_back(Vec2i(point.x,point.y));
        }
        
//        transformedVertices[0].x = 0;
//        transformedVertices[0].y = 0;
//
//        transformedVertices[1].x = 200;
//        transformedVertices[1].y = 300;
//
//        transformedVertices[2].x = 300;
//        transformedVertices[2].y = 50;
        
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

