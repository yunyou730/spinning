#pragma once
#include <SDL2/SDL.h>
#include "SDLRenderContext.hpp"
#include <functional>
#include <map>

class AppFramework
{
public:
    AppFramework(int width,int height,int depth);
    ~AppFramework();
    
    void Init();
    void MainLoop();
    void Clean();
    
    void RegisterDrawFunc(std::function<void(RenderContext*)> func)
    {
        _drawFunc = func;
    }
    
    void RegisterUpdateFunc(std::function<void(float)> func)
    {
        _updateFunc = func;
    }
    
    
    bool QueryKeyState(SDL_KeyCode keyCode);
    
protected:
    
    void InitSDL();
    void InitKeyState();
    
    
    
private:
    SDL_Window*     _window         = nullptr;
    SDL_Renderer*   _renderer       = nullptr;
    RenderContext*  _context        = nullptr;
    
    const int _width    = 0;
    const int _height   = 0;
    const int _depth    = 0;
    
    std::function<void(float deltaTime)>    _updateFunc = nullptr;
    std::function<void(RenderContext*)>     _drawFunc = nullptr;
    
    std::map<SDL_KeyCode,bool>  _keyStateMap;
};
