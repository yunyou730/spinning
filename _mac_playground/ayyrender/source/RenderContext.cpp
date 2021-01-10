//
//  RenderContext.cpp
//  tinyrender
//
//  Created by bytedance on 2021/1/1.
//

#include "RenderContext.hpp"
#include <stdexcept>

RenderContext::RenderContext(int width,int height,int depth)
    :_width(width)
    ,_height(height)
    ,_depth(depth)
{
    _zbuffer = new float[width * height];
    ClearZBuffer();
}

RenderContext::~RenderContext()
{
    if(_zbuffer != nullptr)
    {
        delete[] _zbuffer;
        _zbuffer = nullptr;
    }
}

bool RenderContext::ZTest(int x,int y,float zValue)
{
    if(x < 0 || x >= _width)
        return false;
    if(y < 0 || y >= _height)
        return false;
    
    if(GetZValue(x,y) < zValue)
    {
        return true;
    }
    return false;
}

void RenderContext::SetZValue(int x,int y,float zValue)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        throw std::runtime_error("over bound");
    _zbuffer[x + y * _width] = zValue;
}

float RenderContext::GetZValue(int x,int y)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        throw std::runtime_error("over bound");
    
    return _zbuffer[x + y * _width];
}

void RenderContext::ClearFrameBuffer()
{
    
}

void RenderContext::ClearZBuffer()
{
    for(int x = 0;x < _width;x++)
    {
        for(int y = 0;y < _height;y++)
        {
            SetZValue(x,y,std::numeric_limits<float>::lowest());
        }
    }
}

