//
//  AppFramework.cpp
//  tinyrender
//
//  Created by bytedance on 2021/1/1.
//

#include "AppFramework.h"
#include <stdexcept>

AppFramework::AppFramework(int width,int height,int depth)
    :_width(width)
    ,_height(height)
    ,_depth(depth)
{
        
}

AppFramework::~AppFramework()
{
    
}

void AppFramework::Init()
{
    InitSDL();
    InitKeyState();
}

void AppFramework::InitSDL()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error(SDL_GetError());
    }
    else
    {
        Uint32 windowFlag = SDL_WINDOW_SHOWN;// | SDL_WINDOW_FULLSCREEN;
//        windowFlag |= SDL_WINDOW_MAXIMIZED;
        _window = SDL_CreateWindow( "SDL Tutorial",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   _width,
                                   _height,
                                   windowFlag);
        
        if( _window == NULL )
        {
            throw std::runtime_error(SDL_GetError());
        }
        
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (_renderer == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }
    
    _context = new SDLRenderContext(_renderer,_width,_height,_depth);
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
        
        SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(_renderer);
//        SDL_Rect fillRect = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
//        SDL_RenderFillRect(_renderer, &fillRect);
        
        Uint32 nextTick = SDL_GetTicks();
        float deltaTime = (nextTick - sTicks) / 1000.f;
        sTicks = nextTick;
        
        if(_updateFunc != nullptr)
        {
            _updateFunc(deltaTime);
        }
        
        if(_drawFunc != nullptr)
        {
            _drawFunc(_context);
        }
        SDL_RenderPresent(_renderer);
    }
}

void AppFramework::Clean()
{
    _drawFunc = nullptr;
    
    if(_context != nullptr)
        delete _context;
    _context = nullptr;
    
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
    
    SDL_DestroyWindow(_window);
    _window = nullptr;
    
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
