//
//  Quad.cpp
//  ayyrender
//
//  Created by bytedance on 2021/2/9.
//

#include "Quad.h"

using namespace ayy;

void Quad::InitVertices()
{
    float size = 1.0f;
    
    Vertex a(Vec4(-size,-size, size,1.5),red);
    Vertex b(Vec4( size,-size, size,1.5),green);
    Vertex c(Vec4(-size, size, size,1.5),blue);
    Vertex d(Vec4( size, size, size,1.5),yellow);
    
    // front
    _vertices.push_back(a);
    _vertices.push_back(b);
    _vertices.push_back(c);
    
    _vertices.push_back(b);
    _vertices.push_back(d);
    _vertices.push_back(c);

}
