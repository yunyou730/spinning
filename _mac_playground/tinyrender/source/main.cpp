#include <stdio.h>
#include "../source/SDLRenderContext.hpp"
#include <new>
#include <memory>
#include "renderer.hpp"
#include "../source/math.hpp"
#include "AppFramework.hpp"
#include <functional>
#include "../source/model.h"
#include <memory>

Vec2<int> p1(60,72);
Vec2<int> p2(70,85);
Vec2<int> p3(73,65);


Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

int main( int argc, char* args[] )
{
    std::shared_ptr<Model> model = std::make_shared<Model>("./res/obj/african_head.obj");
    
    AppFramework app(800,800);
    app.Init();
    app.RegisterDrawFunc([&](RenderContext* renderContext,int width,int height){
//        line(renderContext,red,p1,p2);
        
        /*
        triangleFill(renderContext,white,t0[0], t0[1], t0[2]);
        trniangleFill(renderContext,red,t1[0], t1[1], t1[2]);
        triangleFill(renderContext,blue,t2[0], t2[1], t2[2]);
         */
        
        for(int faceIdx = 0;faceIdx < model->nfaces();faceIdx++)
        {
            std::vector<int> face = model->face(faceIdx);
            
            Vec3f p0 = model->vert(face[0]);
            Vec3f p1 = model->vert(face[1]);
            Vec3f p2 = model->vert(face[2]);
            
            p0.x = (p0.x + 1) * width / 2;
            p0.y = (p0.y + 1) * height / 2;
            
            p1.x = (p1.x + 1) * width / 2;
            p1.y = (p1.y + 1) * height / 2;
            
            line(renderContext,white,p0.x,p0.y,p1.x,p1.y);
        }
        
        
    });
    app.MainLoop();
    app.Clean();
    
    
    return 0;
}

