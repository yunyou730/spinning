#pragma once
#include "Geometric.h"

using namespace ayy;

class Cube : public Geometric
{

private:
    virtual void InitVertices() override
    {
        float size = 1.0f;
        
        Vertex a(Vec4(-size,-size, size,1.),red);
        Vertex b(Vec4( size,-size, size,1.),green);
        Vertex c(Vec4(-size, size, size,1.),blue);
        Vertex d(Vec4( size, size, size,1.),yellow);
        
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
};
