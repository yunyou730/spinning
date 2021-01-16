#include "Pipeline.h"

AYY_NS_BEGIN
Pipeline::Pipeline(int viewportWidth,int viewportHeight)
    :_width(viewportWidth)
    ,_height(viewportHeight)
{
    _camera = new Camera(_width,_height);
    _frameBuffer = new FrameBuffer<Color>(_width,_height,white);
    _zBuffer = new FrameBuffer<float>(_width,_height,0.f);
}

Pipeline::~Pipeline()
{
    SAFE_DELETE(_camera);
    SAFE_DELETE(_frameBuffer);
    SAFE_DELETE(_zBuffer);
}

void Pipeline::WriteColor(int x,int y,const Color& color)
{
    _frameBuffer->Set(x,y,color);
}

void Pipeline::WriteZ(int x,int y,float value)
{
    _zBuffer->Set(x,y,value);
}

void Pipeline::ClearBuffer()
{
    for(int y = 0;y < _height;y++)
    {
        for(int x = 0;x < _width;x++)
        {
            _frameBuffer->Set(x,y,_clearColor);
            _zBuffer->Set(x,y,0.f);
        }
    }
}

AYY_NS_END
