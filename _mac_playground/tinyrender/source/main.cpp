#include <stdio.h>
#include "../source/SDLRenderContext.hpp"
#include <new>
#include <memory>
#include "renderer.hpp"
#include "../source/math.hpp"
#include "AppFramework.hpp"
#include <functional>

Vec2<int> p1(60,72);
Vec2<int> p2(70,85);
Vec2<int> p3(73,65);


Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

//Vec2i t0[3] = {Vec2i(0, 0),   Vec2i(50, 100),  Vec2i(100, 0)};

int main( int argc, char* args[] )
{
    AppFramework app(400,300);
    app.Init();
    app.RegisterDrawFunc([](RenderContext* renderContext){
//        line(renderContext,red,p1,p2);
//        triangleWithColorSide(renderContext,white,p1,p2,p3);
        
        triangleWithColorSide(renderContext,white,t0[0], t0[1], t0[2]);
        triangleWithColorSide(renderContext,red,t1[0], t1[1], t1[2]);
        triangleWithColorSide(renderContext,blue,t2[0], t2[1], t2[2]);
    });
    app.MainLoop();
    app.Clean();
    
    
    return 0;
}

