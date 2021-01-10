#pragma once

#include <SDL2/SDL.h>
#include "RenderContext.hpp"

class SDLRenderContext : public RenderContext
{
public:
    SDLRenderContext(SDL_Renderer* sdlRenderer,int width,int height,int depth);
    virtual ~SDLRenderContext();
    
    virtual void SetPixel(int x,int y,const Color& color) override;

    
protected:
    SDL_Renderer*   _sdlRenderer = nullptr;
};
