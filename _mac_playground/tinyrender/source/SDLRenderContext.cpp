//
//  SDLRenderContext.cpp
//  tinyrender
//
//  Created by bytedance on 2021/1/1.
//

#include "SDLRenderContext.hpp"

SDLRenderContext::SDLRenderContext(SDL_Renderer* sdlRenderer,int width,int height)
    :RenderContext(width,height)
    ,_sdlRenderer(sdlRenderer)
{

}

void SDLRenderContext::SetPixel(int x,int y,const Color& color)
{
    SDL_SetRenderDrawColor(_sdlRenderer, color.r, color.g, color.b, color.a);
    y = (_height - 1) - y;
    SDL_RenderDrawPoint(_sdlRenderer, x,y);
}
