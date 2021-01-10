#pragma once

//#include "tgaimage.h"
#include "math.hpp"
#include "RenderContext.hpp"

void line(RenderContext* ctx,const Color& color,int x0,int y0,int x1,int y1);
void line(RenderContext* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2);
void triangle(RenderContext* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2,const Vec2<int>& p3);

void triangleFill(RenderContext* ctx,
                           const Color& color,
                           const Vec2i& p1,
                           const Vec2i& p2,
                           const Vec2i& p3);
