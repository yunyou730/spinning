#include <stdio.h>
#include "../source/SDLRenderContext.hpp"
#include <new>
#include <memory>
#include "renderer.hpp"
#include "../source/math.hpp"
#include "AppFramework.h"
#include <functional>
#include "../source/model.h"
#include <memory>
#include "../source/MyGL.h"

std::shared_ptr<Model> model = nullptr;
//Vec3f gLightDir(0,0,-1);

//float gViewportWidth = 800;
//float gViewportHeight = 800;
float gViewportWidth = 400;
float gViewportHeight = 400;

//Vec3f gEye(1,1,3);
Vec3f gEye(1,1,3);
Vec3f gCenter(0,0,0);
Vec3f gUp(0,1,0);

//float gTestFactor = 1./8;
//float gTestFactor2 = 3./4;

float gTestFactor = 1./8;
float gTestFactor2 = 3./4;


void drawLightModelTest(RenderContext* renderContext)
{
    // test
    MyGL my(gEye,gCenter,gUp,
            gViewportWidth * gTestFactor,
            gViewportHeight * gTestFactor,
            gViewportWidth * gTestFactor2,
            gViewportHeight * gTestFactor2);
    my.CalcMatrics();
    
    Vec3f lightDir = (gCenter - gEye).Normalize();
    
    // draw
    for(int faceIdx = 0;faceIdx < model->nfaces();faceIdx++)
    {
        std::vector<int> face = model->face(faceIdx);
        Vec3i screenCoords[3];
        Vec3f worldCoords[3];
        for(int i = 0;i < 3;i++)
        {
            Vec3f worldCoord = model->vert(face[i]);
            worldCoords[i] = worldCoord;
            
            Matrix<4>   mat = my.Viewport() * my.Projection() * my.ModelView();
            Vec4 glPos = Vec4(worldCoord,1);
            Vec4 pos = mat * glPos;
            screenCoords[i].x = pos.x ;
            screenCoords[i].y = pos.y ;
            screenCoords[i].z = pos.z ;
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
    
    m1 = m1 * m2;
    m1.dump();
    
    Matrix<4> mat(std::vector<float>{1,0,0,1,0,1,0,1,0,0,1,3,0,0,0,1});
    mat.Identity();
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
//    TestMatrix();
    
    model = std::make_shared<Model>("./res/obj/african_head.obj");
//    model = std::make_shared<Model>("./res/Pikachu_OBJ/Pikachu.obj");
    
    AppFramework app(gViewportWidth,gViewportHeight,255);
    app.Init();
    
    app.RegisterUpdateFunc([&](float deltaTime) {
        
        float moveSpeed = 3.0f;
//        printf("fps:%d\n",(int)(1./deltaTime));
        if(app.QueryKeyState(SDL_KeyCode::SDLK_a))
        {
            gEye.x += deltaTime * moveSpeed;
        }
        else if(app.QueryKeyState(SDLK_d))
        {
            gEye.x -= deltaTime * moveSpeed;
        }
        else if(app.QueryKeyState(SDLK_w))
        {
            gEye.z -= deltaTime * moveSpeed;
        }
        else if(app.QueryKeyState(SDLK_s))
        {
            gEye.z += deltaTime * moveSpeed;
        }
        else if(app.QueryKeyState(SDLK_q))
        {
            gEye.y += deltaTime * moveSpeed;
        }
        else if(app.QueryKeyState(SDLK_e))
        {
            gEye.y -= deltaTime * moveSpeed;
        }
    });
    
    app.RegisterDrawFunc([&](RenderContext* renderContext){
        renderContext->ClearZBuffer();
        //drawLightModelTest(renderContext,gLightDir);
        drawLightModelTest(renderContext);
    });
    app.MainLoop();
    app.Clean();
    
    return 0;
}

