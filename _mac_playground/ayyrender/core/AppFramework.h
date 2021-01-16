#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include <map>
#include "Pipeline.h"

AYY_NS_BEGIN

class Pipeline;
class AppFramework
{
public:
    AppFramework(int width,int height);
    ~AppFramework();
    
    void MainLoop();
    void Clean();
    
    void RegisterDrawFunc(std::function<void(Pipeline*)> func)
    {
        _drawFunc = func;
    }
    
    void RegisterUpdateFunc(std::function<void(AppFramework* app,float)> func)
    {
        _updateFunc = func;
    }
    
    bool QueryKeyState(SDL_KeyCode keyCode);
    
protected:
    
    void InitSDL(int width,int height);
    void InitKeyState();
    
    void ClearBuffer();
    void PresentFramebuffer();
    
private:
    SDL_Window*     _window     = nullptr;
    SDL_Renderer*   _renderer   = nullptr;
    Pipeline*       _pipeline   = nullptr;
    
    std::function<void(AppFramework* app,float deltaTime)>    _updateFunc = nullptr;
    std::function<void(Pipeline*)>          _drawFunc = nullptr;
    
    std::map<SDL_KeyCode,bool>  _keyStateMap;
};
AYY_NS_END
