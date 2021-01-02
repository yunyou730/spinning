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
    _zbuffer = new float[width * height];
    ClearZBuffer();
}

SDLRenderContext::~SDLRenderContext()
{

}

void SDLRenderContext::SetPixel(int x,int y,const Color& color)
{
    SDL_SetRenderDrawColor(_sdlRenderer, color.r, color.g, color.b, color.a);
    y = (_height - 1) - y;
    SDL_RenderDrawPoint(_sdlRenderer, x,y);
}
