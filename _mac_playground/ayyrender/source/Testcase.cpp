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
    _actor._yaw += deltaYaw;
    
    // move object
    float dis = 0.5f * deltaTime;
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

void Testcase::Draw(Pipeline* pipeline)
{
    Color col(255,0,0,255);
    
    Matrix<4> mvp = pipeline->GetCamera()->ProjectionMatrix()
                        * pipeline->GetCamera()->ViewMatrix()
                        * _actor.WorldMatrix();
    Matrix<4> mvpViewport = pipeline->GetCamera()->ViewportMatrix() * mvp;
    
    for(int faceIndex = 0;faceIndex < _actor.FaceCount();faceIndex++)
    {
        std::vector<Vertex> vertice = _actor.GetFaceAtIndex(faceIndex);
        
        for(int i = 0;i < vertice.size();i++)
        {
            Vertex& vertex = vertice[i];
            vertex.transformedPos = mvpViewport * vertex.pos;
            vertex.transformedPos = vertex.transformedPos * (1/vertex.transformedPos.w);
        }
        
        Vec3f v1 = vertice[1].transformedPos - vertice[0].transformedPos;
        Vec3f v2 = vertice[2].transformedPos - vertice[1].transformedPos;
        Vec3f normalDir = (v1 ^ v2).Normalize();
        if(pipeline->GetCamera()->CheckBackFace(normalDir))
        {
            triangle(pipeline,col,vertice[0].transformedPos,vertice[1].transformedPos,vertice[2].transformedPos);
//            triangleFill(ctx,vertice[0],vertice[1],vertice[2]);
        }
    }
}
