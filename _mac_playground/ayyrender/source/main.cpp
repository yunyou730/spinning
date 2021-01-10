#include <stdio.h>
#include "AppFramework.h"
#include "renderer.hpp"
#include <vector>

class Testcase
{
public:
    Testcase()
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
    
    
    void InitVertices()
    {
        
    }
    
    void InitUVN()
    {
        
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
};

int main( int argc, char* args[] )
{
    Testcase testcase;
    
    
    AppFramework app(800,800,255);
    app.Init();
    app.RegisterUpdateFunc([&](float deltaTime) {
        
    });
    
    app.RegisterDrawFunc([&](RenderContext* ctx){
        triangleFill(ctx,Color(255,255,0,255),Vec3i(0,0),Vec3i(400,800),Vec3i(800,0));
//        triangle(ctx,Color(255,0,0,255),Vec2i(0,0),Vec2i(400,800),Vec2i(800,0));
    });
    app.MainLoop();
    app.Clean();
    
    return 0;
}

