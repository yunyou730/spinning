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

Vec3i t0[3] = {Vec3i(10, 70),   Vec3i(50, 160),  Vec3i(70, 80)};
Vec3i t1[3] = {Vec3i(180, 50),  Vec3i(150, 1),   Vec3i(70, 180)};
Vec3i t2[3] = {Vec3i(180, 150), Vec3i(120, 160), Vec3i(130, 180)};

std::shared_ptr<Model> model = nullptr;
Vec3f gLightDir(0,0,-1);

void drawWireModelTest(RenderContext* renderContext)
{
    for(int faceIdx = 0;faceIdx < model->nfaces();faceIdx++)
    {
        std::vector<int> face = model->face(faceIdx);
        
        
        for(int j = 0;j < 3;j++)
        {
            Vec3f p0 = model->vert(face[j]);
            Vec3f p1 = model->vert(face[(j + 1) % 3]);
//                Vec3f p2 = model->vert(face[2]);
            
            p0.x = (p0.x + 1) * renderContext->width() / 2;
            p0.y = (p0.y + 1) * renderContext->height() / 2;
            
            p1.x = (p1.x + 1) * renderContext->width() / 2;
            p1.y = (p1.y + 1) * renderContext->height() / 2;
            
            line(renderContext,white,p0.x,p0.y,p1.x,p1.y);
        }
    }
}

void drawFlagColorModeModelTest(RenderContext* renderContext)
{
    Color colorArray[] = {white,red,green,blue,yellow};
    int colorLen = sizeof(colorArray) / sizeof(Color);
    
    for(int faceIdx = 0;faceIdx < model->nfaces();faceIdx++)
    {
        std::vector<int> face = model->face(faceIdx);
        Vec3i screenCoords[3];
        for(int i = 0;i < 3;i++)
        {
            Vec3f worldCoord = model->vert(face[i]);
            int sx = (worldCoord.x + 1) * renderContext->width() / 2.;
            int sy = (worldCoord.y + 1) * renderContext->height() / 2.;
            int sz = (worldCoord.z + 1) * renderContext->depth() / 2.;
            screenCoords[i] = Vec3i(sx,sy,sz);
        }
        triangleFill(renderContext,colorArray[faceIdx % colorLen],screenCoords[0],screenCoords[1],screenCoords[2]);
    }
}

void drawLightModelTest(RenderContext* renderContext,const Vec3f& lightDir)
{
    for(int faceIdx = 0;faceIdx < model->nfaces();faceIdx++)
    {
        std::vector<int> face = model->face(faceIdx);
        Vec3i screenCoords[3];
        Vec3f worldCoords[3];
        for(int i = 0;i < 3;i++)
        {
            Vec3f worldCoord = model->vert(face[i]);
            worldCoords[i] = worldCoord;
            
            int sx = (worldCoord.x + 1) * renderContext->width() / 2.;
            int sy = (worldCoord.y + 1) * renderContext->height() / 2.;
            int sz = (worldCoord.z + 1) * renderContext->depth() / 2.;
            screenCoords[i] = Vec3i(sx,sy,sz);
        }
        
        Vec3f normalDir = (worldCoords[2] - worldCoords[0]) ^ (worldCoords[1] - worldCoords[0]);
        normalDir.Normalize();
        
        float intensity = normalDir * lightDir;
        if(intensity > 0)
        {
            Color c(intensity*255, intensity*255, intensity*255, 255);
            triangleFill(renderContext,c,screenCoords[0],screenCoords[1],screenCoords[2]);
        }

    }
}

void drawTriangleTest(RenderContext* renderContext)
{
    triangleFill(renderContext,white,t0[0], t0[1], t0[2]);
    triangleFill(renderContext,red,t1[0], t1[1], t1[2]);
    triangleFill(renderContext,blue,t2[0], t2[1], t2[2]);
}


void drawLesson3(RenderContext* renderContext)
{
    // scene "2d mesh"
    line(renderContext,red,Vec2i(20, 34),   Vec2i(744, 400));
    line(renderContext,green,Vec2i(120, 434), Vec2i(444, 400));
    line(renderContext,blue,Vec2i(330, 463), Vec2i(594, 200));
    
    // screen line
    line(renderContext,white,Vec2i(10, 10), Vec2i(790, 10));

}

int main( int argc, char* args[] )
{
    model = std::make_shared<Model>("./res/obj/african_head.obj");
    
    AppFramework app(800,800,255);
    app.Init();
    app.RegisterDrawFunc([&](RenderContext* renderContext){
        drawTriangleTest(renderContext);
//        drawWireModelTest(renderContext,width,height);
//        drawFlagColorModeModelTest(renderContext,width,height);
//        drawLesson3(renderContext,width,height);
        
//        drawLightModelTest(renderContext,gLightDir);

    });
    app.MainLoop();
    app.Clean();
    
    
    return 0;
}

