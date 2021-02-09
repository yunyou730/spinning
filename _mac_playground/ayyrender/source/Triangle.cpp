//
//  Triangle.cpp
//  ayyrender
//
//  Created by bytedance on 2021/2/9.
//

#include "Triangle.h"

void Triangle::InitVertices()
{
    float size = 1.0f;
    
    Vertex a(Vec4(-size,-size, size,1.),red);
    Vertex b(Vec4( size,-size, size,1.),green);
    Vertex c(Vec4(-size, size, size,1.),blue);
    
    // front
    _vertices.push_back(a);
    _vertices.push_back(b);
    _vertices.push_back(c);
}
