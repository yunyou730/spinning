#pragma once
#include "math.hpp"

class RenderContext
{
public:
    RenderContext(int width,int height,int depth);
    virtual ~RenderContext();
    
    
    virtual void SetPixel(int x,int y,const Color& color) = 0;
    
    
    int width() const {return _width;}
    int height() const {return _height;}
    int depth() const {return _depth;}
    
    
    bool ZTest(int x,int y,float zValue);
    void SetZValue(int x,int y,float zValue);
    float GetZValue(int x,int y);
    
    void ClearFrameBuffer();
    void ClearZBuffer();
    
protected:
    int     _width;
    int     _height;
    int     _depth;
    float*            _zbuffer = nullptr;
};
