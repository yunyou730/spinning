#include <stdio.h>
#include "../core/AppFramework.h"
#include "../core/renderer.hpp"
#include <vector>
#include "../core/math.hpp"
#include "../core/Camera.h"
#include "Actor.h"

using namespace ayy;

int main( int argc, char* args[] )
{
    const int viewportWidth     = 800;
    const int viewportHeight    = 800;
    Camera testcase(viewportWidth,viewportHeight);
    Actor actor;
    
    AppFramework app(viewportWidth,viewportHeight,255);
    app.Init();
    app.RegisterUpdateFunc([&](float deltaTime) {
        // yaw
        float deltaYaw = 60 * deltaTime;
        actor._yaw += deltaYaw;
        
        float deltaPitch = 45 * deltaTime;
        actor._pitch += deltaPitch;
        
        float dis = 0.5f * deltaTime;
        // move object
        if(app.QueryKeyState(SDL_KeyCode::SDLK_a))
        {
            actor._pos.x -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_d))
        {
            actor._pos.x += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_w))
        {
            actor._pos.y += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_s))
        {
            actor._pos.y -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_q))
        {
            actor._pos.z -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_e))
        {
            actor._pos.z += dis;
        }
        
        // move camera
        if(app.QueryKeyState(SDL_KeyCode::SDLK_UP))
        {
            testcase._eye.y += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_DOWN))
        {
            testcase._eye.y -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_LEFT))
        {
            testcase._eye.x -= dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_RIGHT))
        {
            testcase._eye.x += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_SLASH))
        {
            testcase._eye.z += dis;
        }
        else if(app.QueryKeyState(SDL_KeyCode::SDLK_BACKSLASH))
        {
            testcase._eye.z -= dis;
        }
    });
    
    app.RegisterDrawFunc([&](RenderContext* ctx){
        Color col(255,0,0,255);
        
        Matrix<4> mvp = testcase.ProjectionMatrix() * testcase.ViewMatrix() * actor.WorldMatrix();
        Matrix<4> mvpViewport = testcase.ViewportMatrix() * mvp;
        
        for(int faceIndex = 0;faceIndex < actor.FaceCount();faceIndex++)
        {
            std::vector<Vertex> vertice = actor.GetFaceAtIndex(faceIndex);
            
            for(int i = 0;i < vertice.size();i++)
            {
                Vertex& vertex = vertice[i];
                vertex.transformedPos = mvpViewport * vertex.pos;
                vertex.transformedPos = vertex.transformedPos * (1/vertex.transformedPos.w);
            }
            
            Vec3f v1 = vertice[1].transformedPos - vertice[0].transformedPos;
            Vec3f v2 = vertice[2].transformedPos - vertice[1].transformedPos;
            Vec3f normalDir = (v1 ^ v2).Normalize();
            if(testcase.CheckBackFace(normalDir))
            {
                triangle(ctx,col,vertice[0].transformedPos,vertice[1].transformedPos,vertice[2].transformedPos);
                triangleFill(ctx,vertice[0],vertice[1],vertice[2]);
            }
        }
    });
    app.MainLoop();
    app.Clean();
    
    return 0;
}
