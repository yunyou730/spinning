//
//  Testcase.h
//  ayyrender
//
//  Created by bytedance on 2021/1/16.
//
#pragma once
#include "../core/AppFramework.h"
#include "Actor.h"

using namespace ayy;
class Testcase
{
public:
    Testcase();
    ~Testcase();
    
    void Update(AppFramework* app,float deltaTime);
    void Draw(AppFramework* ctx);
    
private:
    Actor _actor;
};
