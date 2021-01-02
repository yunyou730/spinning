#pragma once
#include "math.hpp"

class RenderContext
{
public:
    RenderContext(int width,int height,int depth);
    virtual ~RenderContext();
    
    virtual void ClearFrameBuffer() = 0;
    virtual void ClearZBuffer() = 0;
    
    virtual void SetPixel(int x,int y,const Color& color) = 0;
    virtual bool ZTest(int x,int y,int zValue) = 0;
    virtual void SetZValue(int x,int y,int zValue) = 0;
    virtual int GetZValue(int x,int y) = 0;
    
    int width() const {return _width;}
    int height() const {return _height;}
    int depth() const {return _depth;}
    
protected:
    int     _width;
    int     _height;
    int     _depth;
};
