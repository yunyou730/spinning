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
    
    void RegisterDrawFunc(std::function<void(AppFramework*)> func)
    {
        _drawFunc = func;
    }
    
    void RegisterUpdateFunc(std::function<void(AppFramework* app,float)> func)
    {
        _updateFunc = func;
    }
    
    bool QueryKeyState(SDL_KeyCode keyCode);
    
    
    Pipeline* GetPipeline() { return _pipeline;}
    
    void Draw(int x,int y,const Color& color);
    void WriteZ(int x,int y,float value);
    
public:
    SDL_Texture* GetTexture() { return _texture;}
    
protected:
    
    void InitSDL(int width,int height);
    void InitKeyState();
    
    void BeginDraw();
    void EndDraw();
    
    
    int GetPixelIndex(int row,int col,int pitch);
    
private:
    SDL_Window*     _window     = nullptr;
    SDL_Renderer*   _renderer   = nullptr;
    SDL_Texture*    _texture    = nullptr;
    
    const SDL_PixelFormatEnum   _pixelFormat;
    SDL_PixelFormat*    _format = nullptr;
    
    
    Pipeline*       _pipeline   = nullptr;
    
    std::function<void(AppFramework* app,float deltaTime)>    _updateFunc = nullptr;
    std::function<void(AppFramework* app)>          _drawFunc = nullptr;
    
    std::map<SDL_KeyCode,bool>  _keyStateMap;
    
    
    int     _width,_height;
};
AYY_NS_END
