#include "renderer.hpp"
#include "RenderContext.hpp"
#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>

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


void triangleFill(RenderContext* ctx,
                           const Color& color,
                           const Vec2<int>& p1,
                           const Vec2<int>& p2,
                           const Vec2<int>& p3)
{
    std::vector<Vec2<int>> arr = {p1,p2,p3};
    std::sort(arr.begin(),arr.end(),[](const Vec2<int>& lh,const Vec2<int> rh)->bool{
        return lh.y < rh.y;
    });
    
    // triangle lower part
    int totalHeight = arr[2].y - arr[0].y;

    // prevent div 0 error
    if(totalHeight <= 0)
    {
//        throw std::runtime_error("total height is 0!");
        return;
    }
    
    for(int y = arr[0].y;y <= arr[1].y;y++)
    {
        int segmentHeight = arr[1].y - arr[0].y + 1;    // avoid div 0
//        if(segmentHeight == 0)
//            throw std::runtime_error("div 0!");
        
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[0].y) / segmentHeight;
        
        Vec2i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec2i B = arr[0] + (arr[1] - arr[0]) * beta;
        
//        ctx->SetPixel(A.x,y,red);
//        ctx->SetPixel(B.x,y,green);
        
        if(A.x > B.x)
        {
            std::swap(A,B);
        }
        for(int x = A.x;x <= B.x;x++)
        {
            ctx->SetPixel(x,y,color);
        }
    }
    
    // triangle upper part
    for(int y = arr[1].y;y <= arr[2].y;y++)
    {
        int segmentHeight = arr[2].y - arr[1].y + 1;    // +1 avoid div 0
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[1].y) / segmentHeight;
        Vec2i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec2i B = arr[1] + (arr[2] - arr[1]) * beta;
        if(A.x > B.x)
            std::swap(A,B);
        for(int x = A.x;x <= B.x;x++)
        {
            ctx->SetPixel(x,y,color);
        }
    }
    
}