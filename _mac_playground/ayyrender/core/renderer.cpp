#include "renderer.hpp"
#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>

void drawPoint(AppFramework* ctx,const Color& color,int x,int y)
{
    ctx->Draw(x,y,color);
}

void line(AppFramework* ctx,const Color& color,int x0,int y0,int x1,int y1)
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
            ctx->Draw(x,y,color);
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
            ctx->Draw(x,y,color);
        }
    }
}

void line(AppFramework* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2)
{
    line(ctx,color,p1.x,p1.y,p2.x,p2.y);
}

void triangle(AppFramework* ctx,const Color& color,const Vec2<int>& p1,const Vec2<int>& p2,const Vec2<int>& p3)
{
    line(ctx,color,p1,p2);
    line(ctx,color,p2,p3);
    line(ctx,color,p3,p1);
}

void triangleFill(AppFramework* ctx,
                           const Color& color,
                           const Vec3i& p1,
                           const Vec3i& p2,
                           const Vec3i& p3)
{
    std::vector<Vec3i> arr = {p1,p2,p3};
    std::sort(arr.begin(),arr.end(),[](const Vec3i& lh,const Vec3i& rh)->bool{
        return lh.y < rh.y;
    });
    
    int totalHeight = arr[2].y - arr[0].y;
    // prevent div 0 error
    if(totalHeight <= 0)
    {
//        throw std::runtime_error("total height is 0!");
        return;
    }
    
    auto scanLine = [&](int y,Vec3i& A,Vec3i& B)
    {
        if(A.x > B.x) std::swap(A,B);
        for(int x = A.x;x <= B.x;x++)
        {
            ctx->Draw(x,y,color);
        }
    };
    
    // triangle lower part
    for(int y = arr[0].y;y <= arr[1].y;y++)
    {
        int segmentHeight = arr[1].y - arr[0].y + 1;    // avoid div 0
        
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[0].y) / segmentHeight;
        
        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec3i B = arr[0] + (arr[1] - arr[0]) * beta;
        
        scanLine(y,A,B);
    }
    
    // triangle upper part
    for(int y = arr[1].y;y <= arr[2].y;y++)
    {
        int segmentHeight = arr[2].y - arr[1].y + 1;    // +1 avoid div 0
        
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[1].y) / segmentHeight;
        
        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec3i B = arr[1] + (arr[2] - arr[1]) * beta;
        
        scanLine(y,A,B);
    }
}


static Color LerpColor(const Color& a,const Color& b,float pct)
{
    Color result(Lerp(a.r,b.r,pct),Lerp(a.g,b.g,pct),Lerp(a.b,b.b,pct),Lerp(a.a,b.a,pct));
    return result;
}

void triangleFill(AppFramework* app,const Vertex& v1,const Vertex& v2,const Vertex& v3)
{
    std::vector<Vertex> arr = {v1,v2,v3};
    std::sort(arr.begin(),arr.end(),[](const Vertex& lh,const Vertex& rh)->bool{
        return lh.transformedPos.y < rh.transformedPos.y;
    });
    int totalHeight = arr[2].transformedPos.y - arr[0].transformedPos.y;
    if(totalHeight <= 0)
    {
        return;
    }
    
    
    // triangle lower part
    for(int y = arr[0].transformedPos.y;y <= arr[1].transformedPos.y;y++)
    {
        int segmentHeight = arr[1].transformedPos.y - arr[0].transformedPos.y + 1;    // avoid div 0
        
        float alpha = (float)(y - arr[0].transformedPos.y) / totalHeight;
        float beta = (float)(y - arr[0].transformedPos.y) / segmentHeight;
        
//        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
//        Vec3i B = arr[0] + (arr[1] - arr[0]) * beta;
//        
//        scanLine(y,A,B);
    }
    
}