#pragma once
#include <SDL2/SDL.h>
#include "SDLRenderContext.hpp"
#include <functional>

class AppFramework
{
public:
    AppFramework(int width,int height);
    ~AppFramework();
    
    void Init();
    void MainLoop();
    void Clean();
    
    void RegisterDrawFunc(std::function<void(RenderContext* renderContext,int width,int height)> func)
    {
        _drawFunc = func;
    }
    
private:
    SDL_Window*     _window         = nullptr;
    SDL_Renderer*   _renderer       = nullptr;
    RenderContext*  _context        = nullptr;
    
    const int _width    = 0;
    const int _height   = 0;
    
    std::function<void(RenderContext*,int width,int height)>   _drawFunc = nullptr;
};