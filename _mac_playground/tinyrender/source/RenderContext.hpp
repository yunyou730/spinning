#pragma once
#include "math.hpp"

class RenderContext
{
public:
    RenderContext(int w,int h);
    virtual ~RenderContext();
    
    virtual void SetPixel(int x,int y,const Color& color);
    
protected:
    int     _width;
    int     _height;
};
