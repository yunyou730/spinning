//
//  AppFramework.cpp
//  tinyrender
//
//  Created by bytedance on 2021/1/1.
//

#include "AppFramework.hpp"
#include <stdexcept>

AppFramework::AppFramework(int width,int height)
    :_width(width)
    ,_height(height)
{
        
}

AppFramework::~AppFramework()
{
    
}

void AppFramework::Init()
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
    
    _context = new SDLRenderContext(_renderer,_width,_height);
}

void AppFramework::MainLoop()
{
    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch(e.type)
            {
                case SDL_KEYDOWN:
                    quit = true;
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
