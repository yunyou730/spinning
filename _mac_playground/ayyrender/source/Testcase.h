//
//  Testcase.h
//  ayyrender
//
//  Created by bytedance on 2021/1/16.
//
#pragma once
#include "../core/AppFramework.h"
#include "Cube.h"
#include "Triangle.h"
#include "Quad.h"

using namespace ayy;
class Testcase
{
public:
    Testcase();
    ~Testcase();
    
    void Update(AppFramework* app,float deltaTime);
    void Draw(AppFramework* ctx);
    
    void TestDraw(AppFramework* ctx);
    
private:
    bool    _bCheckBackface = true;
    
    Cube        _actor;
//    Triangle        _actor;
//    Quad          _actor;
};
