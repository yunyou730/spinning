//
//  AppFramework.cpp
//  tinyrender
//
//  Created by bytedance on 2021/1/1.
//

#include "AppFramework.h"
#include <stdexcept>

AYY_NS_BEGIN
AppFramework::AppFramework(int width,int height)
    :_width(width)
    ,_height(height)
    ,_pixelFormat(SDL_PIXELFORMAT_RGBA8888)
{
    _pipeline = new Pipeline(width,height);
//    _pipeline->SetClearColor(Color(255,0,0,255));
    InitSDL(width,height);
    InitKeyState();
}

AppFramework::~AppFramework()
{
    delete _pipeline;
}

void AppFramework::InitSDL(int width,int height)
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error(SDL_GetError());
    }
    else
    {
//        Uint32 windowFlag = SDL_WINDOW_SHOWN;// | SDL_WINDOW_FULLSCREEN;
//        windowFlag |= SDL_WINDOW_MAXIMIZED;
        
        Uint32 windowFlag = SDL_WINDOW_SHOWN;// | SDL_WINDOW_RESIZABLE;// | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED;
        
        _window = SDL_CreateWindow( "SDL Tutorial",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width,
                                   height,
                                   windowFlag);
        
        if( _window == NULL )
        {
            throw std::runtime_error(SDL_GetError());
        }
        
        _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        _texture = SDL_CreateTexture(_renderer,_pixelFormat,SDL_TEXTUREACCESS_STREAMING,width,height);
        _format = SDL_AllocFormat(_pixelFormat);
    }
    
}

void AppFramework::InitKeyState()
{
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_ESCAPE,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_w,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_s,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_a,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_d,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_q,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_e,false));
    
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_UP,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_DOWN,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_LEFT,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_RIGHT,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_SLASH,false));
    _keyStateMap.insert(std::make_pair(SDL_KeyCode::SDLK_BACKSLASH,false));
}

void AppFramework::MainLoop()
{
    bool quit = false;
    SDL_Event e;
    
    Uint32 sTicks = SDL_GetTicks();
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch(e.type)
            {
                case SDL_KEYDOWN:
                    {
                        SDL_KeyCode keyCode = (SDL_KeyCode)e.key.keysym.sym;
                        if(e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = true;
                            break;
                        }
                        else if(_keyStateMap.find(keyCode) != _keyStateMap.end())
                        {
                            _keyStateMap[keyCode] = true;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    {
                        SDL_KeyCode keyCode = (SDL_KeyCode)e.key.keysym.sym;
                        if(_keyStateMap.find(keyCode) != _keyStateMap.end())
                        {
                            _keyStateMap[keyCode] = false;
                        }
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        

        
        Uint32 nextTick = SDL_GetTicks();
        float deltaTime = (nextTick - sTicks) / 1000.f;
        sTicks = nextTick;
        
        // logic
        if(_updateFunc != nullptr)
        {
            _updateFunc(this,deltaTime);
        }
        
        // draw
        BeginDraw();
        if(_drawFunc != nullptr)
        {
            _drawFunc(this);
        }
        EndDraw();
    }
}

void AppFramework::BeginDraw()
{
    _pipeline->ClearBuffer();
}

void AppFramework::EndDraw()
{
    void* pixels = nullptr;
    int pitch  = 0;
    
    SDL_LockTexture(_texture,nullptr,&pixels,&pitch);
    
    for(int y = 0;y < _height;y++)
    {
        int screenY = _height - 1 - y;
        for(int x = 0;x < _width;x++)
        {
            Color& color = _pipeline->GetColor(x,y);
            Uint32 col = SDL_MapRGBA(_format,color.r,color.g,color.b,color.a);
            int index = GetPixelIndex(x,screenY,pitch);
            ((Uint32*)pixels)[index] = col;
        }
    }
    
    SDL_UnlockTexture(_texture);
    SDL_RenderCopy(_renderer,_texture,NULL,NULL);
    SDL_RenderPresent(_renderer);
}

void AppFramework::Clean()
{
    _drawFunc = nullptr;
    _updateFunc = nullptr;
    
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyTexture(_texture);
    SDL_DestroyWindow(_window);
    
    SDL_Quit();
}

bool AppFramework::QueryKeyState(SDL_KeyCode keyCode)
{
    auto it = _keyStateMap.find(keyCode);
    if(it != _keyStateMap.end())
    {
        return it->second;
    }
    return false;
}

void AppFramework::Draw(int x,int y,const Color& color)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        return;
    
    // fill frame buffer
    auto frameBuffer = _pipeline->GetFrameBuffer();
    frameBuffer->Set(x,y,color);
}

int AppFramework::GetPixelIndex(int x,int y,int pitch)
{
    int index = y * (pitch / 4) + x;
    return index;
}

void AppFramework::WriteZ(int x,int y,float value)
{
    
}

AYY_NS_END
