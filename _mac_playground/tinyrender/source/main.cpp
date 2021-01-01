#include <stdio.h>
#include "../source/SDLRenderContext.hpp"
#include <new>
#include <memory>
#include "renderer.hpp"
#include "../source/math.hpp"
#include "AppFramework.hpp"
#include <functional>


// temp globals
const Color white    = Color(255,255,255,255);
const Color red      = Color(255,0,0,255);
const Color green    = Color(0,255,0,255);
const Color blue     = Color(0,0,255,255);
const Color yellow   = Color(255,255,0,255);

Vec2<int> p1(60,72);
Vec2<int> p2(70,85);
Vec2<int> p3(73,65);

int main( int argc, char* args[] )
{
    AppFramework app(400,300);
    app.Init();
    app.RegisterDrawFunc([](RenderContext* renderContext){
        line(renderContext,red,p1,p2);
    });
    app.MainLoop();
    app.Clean();
    return 0;
}

