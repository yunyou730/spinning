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
                           const Vec3i& p1,
                           const Vec3i& p2,
                           const Vec3i& p3)
{
    std::vector<Vec3i> arr = {p1,p2,p3};
    std::sort(arr.begin(),arr.end(),[](const Vec3i& lh,const Vec3i rh)->bool{
        return lh.y < rh.y;
    });
    
    int totalHeight = arr[2].y - arr[0].y;
    // prevent div 0 error
    if(totalHeight <= 0)
    {
//        throw std::runtime_error("total height is 0!");
        return;
    }
    
    // triangle lower part
    for(int y = arr[0].y;y <= arr[1].y;y++)
    {
        int segmentHeight = arr[1].y - arr[0].y + 1;    // avoid div 0
//        if(segmentHeight == 0)
//            throw std::runtime_error("div 0!");
        
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[0].y) / segmentHeight;
        
        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec3i B = arr[0] + (arr[1] - arr[0]) * beta;
        
        if(A.x > B.x) std::swap(A,B);
        for(int x = A.x;x <= B.x;x++)
        {
            float phi = (B.x == A.x) ? 1.f : (float)(x - A.x) / (float)(B.x - A.x);
            Vec3i p = A + (B - A) * phi;    // calc for z test
            if(ctx->ZTest(x,y,p.z))
            {
                ctx->SetZValue(x,y,p.z);
                ctx->SetPixel(x,y,color);
            }
        }
    }
    
    // triangle upper part
    for(int y = arr[1].y;y <= arr[2].y;y++)
    {
        int segmentHeight = arr[2].y - arr[1].y + 1;    // +1 avoid div 0
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[1].y) / segmentHeight;
        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec3i B = arr[1] + (arr[2] - arr[1]) * beta;
        if(A.x > B.x) std::swap(A,B);
        for(int x = A.x;x <= B.x;x++)
        {
            float phi = (B.x == A.x) ? 1.f : (float)(x - A.x) / (float)(B.x - A.x);
            Vec3i p = A + (B - A) * phi;    // calc for z test
            if(ctx->ZTest(x,y,p.z))
            {
                ctx->SetZValue(x,y,p.z);
                ctx->SetPixel(x,y,color);
            }
        }
    }
    
}
