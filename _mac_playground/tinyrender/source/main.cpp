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
#include "../source/MyGL.h"

Vec2<int> p1(60,72);
Vec2<int> p2(70,85);
Vec2<int> p3(73,65);

Vec3i t0[3] = {Vec3i(10, 70),   Vec3i(200, 160),  Vec3i(70, 80)};
Vec3i t1[3] = {Vec3i(180, 50),  Vec3i(150, 1),   Vec3i(70, 180)};
Vec3i t2[3] = {Vec3i(180, 50,5), Vec3i(120, 160,1), Vec3i(130, 180,3)};

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
            
//            printf("face:[%d] pt[%d] z: %d\n",faceIdx,i,sz);
            
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

void TestMatrix()
{
    Matrix<4> matrix;
    matrix.dump();
    
    matrix.Identity();
    matrix.dump();
    
    matrix * 5;
    matrix.dump();
    
    Matrix<3> m1(std::vector<float>{1,-5,3,0,-2,6,7,2,-4});
    m1.dump();
    Matrix<3> m2(std::vector<float>{-8,6,1,7,0,-3,2,4,5});
    m2.dump();
    
    m1.Identity();
    m1.dump();
    
    Matrix<4> mat(std::vector<float>{1,0,0,1,0,1,0,1,0,0,1,3,0,0,0,1});
//    mat.Identity();
    Vec4 v(std::vector<float>{1,2,3,1});
    v.dump();
    v = mat * v;
    v.dump();
    
    
//    Vec4 v;
//    v.w = 0.5f;
//    printf("x");
}

int main( int argc, char* args[] )
{
    TestMatrix();
    
    /*
    model = std::make_shared<Model>("./res/obj/african_head.obj");
    
    AppFramework app(800,800,255);
    app.Init();
    app.RegisterDrawFunc([&](RenderContext* renderContext){
        
        renderContext->ClearZBuffer();

//        drawWireModelTest(renderContext,width,height);
        
        drawLightModelTest(renderContext,gLightDir);
        drawTriangleTest(renderContext);

    });
    app.MainLoop();
    app.Clean();
     */
    
    return 0;
}

