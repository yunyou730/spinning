//
//  Testcase.cpp
//  ayyrender
//
//  Created by bytedance on 2021/1/16.
//

#include "Testcase.h"
#include "renderer.hpp"

Testcase::Testcase()
{
    _actor.Init();
}

Testcase::~Testcase()
{
}

void Testcase::Update(AppFramework* app,float deltaTime)
{
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
    
    float rotateSpeed = 60 * deltaTime;
//    _actor._yaw += deltaYaw;
    if(app->QueryKeyState(SDL_KeyCode::SDLK_UP))
    {
        _actor._pitch += rotateSpeed;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_DOWN))
    {
        _actor._pitch -= rotateSpeed;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_LEFT))
    {
        _actor._roll += rotateSpeed;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_RIGHT))
    {
        _actor._roll -= rotateSpeed;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_SLASH))
    {
        _actor._yaw += rotateSpeed;
    }
    else if(app->QueryKeyState(SDL_KeyCode::SDLK_BACKSLASH))
    {
        _actor._yaw -= rotateSpeed;
    }
}

void Testcase::Draw(AppFramework* ctx)
{
//    Color col(255,0,0,255);
    
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
            vertex.transformedPos = mvp * vertex.pos;
            vertex.ndcPos = vertex.transformedPos * (1/vertex.transformedPos.w);
            vertex.screenPos = viewportMatrix * vertex.ndcPos;
        }
        
        Vec3f v1 = vertice[1].ndcPos - vertice[0].ndcPos;
        Vec3f v2 = vertice[2].ndcPos - vertice[1].ndcPos;
        Vec3f normalDir = (v1 ^ v2).Normalize();
        
        
        bool bDraw = true;
        if(_bCheckBackface)
        {
            bDraw = ctx->GetPipeline()->GetCamera()->CheckBackFace(normalDir);
        }
        
        if(bDraw)
        {
//            triangle(ctx,col,vertice[0].screenPos,vertice[1].screenPos,vertice[2].screenPos);
            /*
            printf("start dump surface =====\n");
            vertice[0].screenPos.Dump();
            vertice[1].screenPos.Dump();
            vertice[2].screenPos.Dump();
            */
            triangleFill(ctx,vertice[0],vertice[1],vertice[2]);
        }
    }
}

void Testcase::TestDraw(AppFramework* ctx)
{
    SDL_Texture* texture = ctx->GetTexture();
}
