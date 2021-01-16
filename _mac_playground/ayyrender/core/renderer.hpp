#pragma once

#include "math.hpp"
//#include "RenderContext.hpp"
#include "Pipeline.h"

using namespace ayy;

void drawPoint(Pipeline* pipeline,const Color& color,int x,int y);

void line(Pipeline* pipeline,const Color& color,int x0,int y0,int x1,int y1);

void line(Pipeline* pipeline,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2);
void triangle(Pipeline* pipeline,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2,const Vec2<int>& p3);

void triangleFill(Pipeline* pipeline,
                           const Color& color,
                           const Vec3i& p1,
                           const Vec3i& p2,
                           const Vec3i& p3);

void triangleFill(Pipeline* pipeline,const Vertex& v1,const Vertex& v2,const Vertex& v3);
