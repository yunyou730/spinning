#include <SDL2/SDL.h>
#include <stdio.h>
#include "../source/SDLRenderContext.hpp"
#include <new>
#include <memory>
#include "renderer.hpp"
#include "../source/math.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = nullptr;


RenderContext* context = nullptr;


bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        Uint32 windowFlag = SDL_WINDOW_SHOWN;// | SDL_WINDOW_FULLSCREEN;
//        windowFlag |= SDL_WINDOW_MAXIMIZED;
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlag);
        
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        

        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr)
        {
            return false;
        }
    }
    
    context = new SDLRenderContext(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    return success;
}

void close()
{
    if(context != nullptr)
        delete context;
    context = nullptr;
    
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    
    SDL_Quit();
}

// temp globals
const Color white    = Color(255,255,255,255);
const Color red      = Color(255,0,0,255);
const Color green    = Color(0,255,0,255);
const Color blue     = Color(0,0,255,255);
const Color yellow   = Color(255,255,0,255);

Vec2<int> p1(60,72);
Vec2<int> p2(70,85);
Vec2<int> p3(73,65);


void mainLoop()
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
        
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(gRenderer);
//        SDL_Rect fillRect = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
//        SDL_RenderFillRect(gRenderer, &fillRect);
        
        triangle(context,red,p1,p2,p3);
        
        SDL_RenderPresent(gRenderer);

    }
}

int main( int argc, char* args[] )
{
    init();
    mainLoop();
    close();
    return 0;
}

/*
#include <iostream>
#include "../source/tgaimage.h"
#include "renderer.hpp"
#include "../source/math.hpp"

const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);
const TGAColor green = TGAColor(0,255,0,255);
const TGAColor blue = TGAColor(0,0,255,255);
const TGAColor yellow = TGAColor(255,255,0,255);

int main(int argc, const char * argv[]) {
    
    TGAImage image(100,100,TGAImage::RGB);
    image.set(52,41,red);
    
//    line(image,red,0,0,80,30);
//    line(image,white,80,30,0,0);
//
//    line(image,white,0,0,20,100);
//    line(image,red,20,100,0,0);
    
//    triangle(image,red,Vec2<int>(5,30),Vec2<int>(30,40),Vec2<int>(20,70));
//    triangle(image,green,Vec2<int>(35,80),Vec2<int>(60,10),Vec2<int>(75,25));
//    triangle(image,blue,Vec2<int>(60,72),Vec2<int>(70,84),Vec2<int>(73,65));
//    triangle(image,green,Vec2<int>(60,72),Vec2<int>(70,85),Vec2<int>(73,65));
    
    Vec2<int> p1(60,72);
    Vec2<int> p2(70,85);
//    Vec2<int> p3(73,65);
//    triangle(image,yellow,Vec2<int>(60,72),Vec2<int>(70,85),Vec2<int>(73,65));
    
    line(image,yellow,p1,p2);
//    line(image,yellow,p2,p3);
//    line(image,yellow,p3,p1);
//    line(image,yellow,p1,p3);
        
    
    // @todo
    // 图形 api 换成 SDL2 尝试解决奇怪的 画线 黑屏 问题
//    image.set(60,72,yellow);
    image.set(70,85,red);
    
//  img.flip_vertically();
    image.write_tga_file("output.tga");

    return 0;
}
*/
