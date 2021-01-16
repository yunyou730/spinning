#pragma once

#include "math.hpp"
#include "AppFramework.h"

using namespace ayy;

void drawPoint(AppFramework* ctx,const Color& color,int x,int y);

void line(AppFramework* ctx,const Color& color,int x0,int y0,int x1,int y1);

void line(AppFramework* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2);
void triangle(AppFramework* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2,const Vec2<int>& p3);

void triangleFill(AppFramework* ctx,
                           const Color& color,
                           const Vec3i& p1,
                           const Vec3i& p2,
                           const Vec3i& p3);

void triangleFill(AppFramework* ctx,const Vertex& v1,const Vertex& v2,const Vertex& v3);
