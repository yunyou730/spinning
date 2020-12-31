#include "renderer.hpp"
#include "RenderContext.hpp"
#include <cstdint>
#include <fstream>
#include <vector>

void line(RenderContext* ctx,const Color& color,int x0,int y0,int x1,int y1)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    
    bool bSteep = dy > dx;
    
    if(!bSteep)
    {
        if(x0 > x1)
        {
            std::swap(x0,x1);
            std::swap(y0,y1);
        }
        
        float dis = x1 - x0;
        for(int x = x0;x <= x1;x++)
        {
            float t = (x - x0) / dis;
            int y = y0 + (y1 - y0) * t;
            ctx->SetPixel(x,y,color);
        }
    }
    else
    {
        if(y0 > y1)
        {
            std::swap(y0,y1);
            std::swap(x0,x1);
        }
        float dis = y1 - y0;
        for(int y = y0;y < y1;y++)
        {
            float t = (y - y0) / dis;
            int x = x0 + (x1 - x0) * t;
            ctx->SetPixel(x,y,color);
        }
    }
}

void line(RenderContext* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2)
{
    line(ctx,color,p1.x,p1.y,p2.x,p2.y);
}

void triangle(RenderContext* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2,const Vec2<int>& p3)
{
    line(ctx,color,p1,p2);
    line(ctx,color,p2,p3);
    line(ctx,color,p3,p1);
}
