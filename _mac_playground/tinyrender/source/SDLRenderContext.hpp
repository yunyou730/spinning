#pragma once

#include <SDL2/SDL.h>
#include "RenderContext.hpp"

class SDLRenderContext : public RenderContext
{
public:
    SDLRenderContext(SDL_Renderer* sdlRenderer,int width,int height,int depth);
    virtual ~SDLRenderContext();
    
    virtual void SetPixel(int x,int y,const Color& color) override;

    virtual bool ZTest(int x,int y,int zValue) override;
    virtual void SetZValue(int x,int y,int zValue) override;
    virtual int GetZValue(int x,int y) override;
    
protected:

    
protected:
    SDL_Renderer* _sdlRenderer = nullptr;
    int*            _zbuffer = nullptr;
};
