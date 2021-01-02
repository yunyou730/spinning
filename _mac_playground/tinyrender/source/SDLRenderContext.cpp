//
//  SDLRenderContext.cpp
//  tinyrender
//
//  Created by bytedance on 2021/1/1.
//

#include "SDLRenderContext.hpp"
#include <limits>
#include <stdexcept>

SDLRenderContext::SDLRenderContext(SDL_Renderer* sdlRenderer,int width,int height,int depth)
    :RenderContext(width,height,depth)
    ,_sdlRenderer(sdlRenderer)
{
    _zbuffer = new int[width * height];
    for(int x = 0;x < _width;x++)
    {
        for(int y = 0;y < _height;y++)
        {
            SetZValue(x,y,std::numeric_limits<float>::min());
        }
    }
}

SDLRenderContext::~SDLRenderContext()
{
    if(_zbuffer != nullptr)
    {
        delete[] _zbuffer;
        _zbuffer = nullptr;
    }
}

void SDLRenderContext::SetPixel(int x,int y,const Color& color)
{
    SDL_SetRenderDrawColor(_sdlRenderer, color.r, color.g, color.b, color.a);
    y = (_height - 1) - y;
    SDL_RenderDrawPoint(_sdlRenderer, x,y);
}

bool SDLRenderContext::ZTest(int x,int y,int zValue)
{
    if(x < 0 || x >= _width)
        return false;
    if(y < 0 || y >= _height)
        return false;
    
    if(GetZValue(x,y) <= zValue)
    {
        return true;
    }
    return false;
}

void SDLRenderContext::SetZValue(int x,int y,int zValue)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        throw std::runtime_error("over bound");
    _zbuffer[x + y * _width] = zValue;
}

int SDLRenderContext::GetZValue(int x,int y)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        throw std::runtime_error("over bound");
    
    return _zbuffer[x + y * _width];
}
