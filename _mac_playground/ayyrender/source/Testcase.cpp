//
//  Testcase.cpp
//  ayyrender
//
//  Created by bytedance on 2021/1/16.
//

#include "Testcase.h"
#include "Actor.h"
#include "renderer.hpp"

Testcase::Testcase()
{
    
}

Testcase::~Testcase()
{
}

void Testcase::Update(AppFramework* app,float deltaTime)
{
    float deltaYaw = 60 * deltaTime;
//    _actor._yaw += deltaYaw;
    
    // move object
    float dis = 1.f * deltaTime;
    if(app->QueryKeyState(SDL_KeyCode::SDLK_a))
    {
        _actor._pos.x -= dis;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_d))
    {
        _actor._pos.x += dis;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_w))
    {
        _actor._pos.y += dis;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_s))
    {
        _actor._pos.y -= dis;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_q))
    {
        _actor._pos.z -= dis;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_e))
    {
        _actor._pos.z += dis;
    }
    
    // move camera
    /*
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
     */
}

void Testcase::Draw(AppFramework* ctx)
{
    Color col(255,0,0,255);
    
    Matrix<4> mvp = ctx->GetPipeline()->GetCamera()->ProjectionMatrix()
                        * ctx->GetPipeline()->GetCamera()->ViewMatrix()
                        * _actor.WorldMatrix();
    
    Matrix<4> viewportMatrix = ctx->GetPipeline()->GetCamera()->ViewportMatrix();
    
    for(int faceIndex = 0;faceIndex < _actor.FaceCount();faceIndex++)
    {
        std::vector<Vertex> vertice = _actor.GetFaceAtIndex(faceIndex);
        
        for(int i = 0;i < vertice.size();i++)
        {
            Vertex& vertex = vertice[i];
            
//            vertex.worldPos = _actor.WorldMatrix() * vertex.pos;
            vertex.transformedPos = mvp * vertex.pos;
            vertex.ndcPos = vertex.transformedPos * (1/vertex.transformedPos.w);
            vertex.screenPos = viewportMatrix * vertex.ndcPos;
        }
        
        Vec3f v1 = vertice[1].ndcPos - vertice[0].ndcPos;
        Vec3f v2 = vertice[2].ndcPos - vertice[1].ndcPos;
        Vec3f normalDir = (v1 ^ v2).Normalize();
        if(ctx->GetPipeline()->GetCamera()->CheckBackFace(normalDir))
        {
            triangle(ctx,col,vertice[0].screenPos,vertice[1].screenPos,vertice[2].screenPos);
//            triangleFill(ctx,vertice[0],vertice[1],vertice[2]);
        }
    }
}
