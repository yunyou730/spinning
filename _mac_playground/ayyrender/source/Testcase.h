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
//    Cube        _actor;
//    Triangle    _triangle;
    Triangle        _actor;
};
