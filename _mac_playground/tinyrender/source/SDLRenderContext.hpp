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
    virtual bool ZTest(int x,int y,int zValue) override;
    
    void SetZValue(int x,int y,int zValue);
    int GetZValue(int x,int y);
    
protected:
    SDL_Renderer* _sdlRenderer = nullptr;
    int*            _zbuffer = nullptr;
};
