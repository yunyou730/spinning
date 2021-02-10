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
    int segmentHeight = arr[1].y - arr[0].y + 1;    // avoid div 0
    for(int y = arr[0].y;y <= arr[1].y;y++)
    {
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[0].y) / segmentHeight;
        
        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec3i B = arr[0] + (arr[1] - arr[0]) * beta;
        
        scanLine(y,A,B);
    }
    
    // triangle upper part
    segmentHeight = arr[2].y - arr[1].y + 1;    // +1 avoid div 0
    for(int y = arr[1].y;y <= arr[2].y;y++)
    {
        float alpha = (float)(y - arr[0].y) / totalHeight;
        float beta = (float)(y - arr[1].y) / segmentHeight;
        
        Vec3i A = arr[0] + (arr[2] - arr[0]) * alpha;
        Vec3i B = arr[1] + (arr[2] - arr[1]) * beta;
        
        scanLine(y,A,B);
    }
}

static Vertex LerpVertex(Vertex& v1,Vertex& v2,float t)
{
    Vertex r;
    
    r.screenPos = v1.screenPos + (v2.screenPos - v1.screenPos) * t;
    
    /*
    r.color.r = Lerp<int>(v1.color.r,v2.color.r,t);
    r.color.g = Lerp<int>(v1.color.g,v2.color.g,t);
    r.color.b = Lerp<int>(v1.color.b,v2.color.b,t);
    r.color.a = Lerp<int>(v1.color.a,v2.color.a,t);
    */
    
    
    r.color.r = Lerp<float>(v1.color.r,v2.color.r,t);
    r.color.g = Lerp<float>(v1.color.g,v2.color.g,t);
    r.color.b = Lerp<float>(v1.color.b,v2.color.b,t);
    r.color.a = Lerp<float>(v1.color.a,v2.color.a,t);
    
    return r;
}

/*
 这个函数有问题，会导致 有 “缝隙”
 */
void triangleFill(AppFramework* ctx,const Vertex& v1,const Vertex& v2,const Vertex& v3)
{
    std::vector<Vertex> arr = {v1,v2,v3};
    std::sort(arr.begin(),arr.end(),[](const Vertex& lh,const Vertex& rh)->bool{
        return lh.screenPos.y < rh.screenPos.y;
    });
    float totalHeight = arr[2].screenPos.y - arr[0].screenPos.y;
    if(totalHeight <= 0)
        return;
    
    auto scanline = [&](int y,Vertex v1,Vertex v2)
    {
        if(v1.screenPos.x > v2.screenPos.x)
        {
            std::swap(v1,v2);
        }
        
        for(int x = v1.screenPos.x;x <= v2.screenPos.x;x++)
        {
            float t = (float)(x - v1.screenPos.x) / (float)(v2.screenPos.x - v1.screenPos.x);
            Vertex v = LerpVertex(v1,v2,t);
            ctx->Draw(x,y,v.color);
        }
    };
    // @todo
    /*
        临时 根据 2d 坐标，计算一个 2d 的重心坐标
        然后根据重心坐标 ， 做颜色差值
     
        然后再 尝试直接做 纹理映射，看看有没有扭曲
     
     如果有的话，再考虑 重心坐标有没有其他 差值 的 办法
     */
    
    int segmentHeight = arr[1].screenPos.y - arr[0].screenPos.y;
    if(segmentHeight > 0)
    {
        for(int y = arr[0].screenPos.y;y <= arr[1].screenPos.y;y++)
        {
            float pctOfFar  = (float)(y - arr[0].screenPos.y) / totalHeight;
            float pctOfNear = (float)(y - arr[0].screenPos.y) / segmentHeight;
            if(pctOfFar >= 0 && pctOfNear >= 0)
            {
                Vertex v1 = LerpVertex(arr[0],arr[2],pctOfFar);
                Vertex v2 = LerpVertex(arr[0],arr[1],pctOfNear);
                scanline(y,v1,v2);
            }
        }
    }
    
    segmentHeight = arr[2].screenPos.y - arr[1].screenPos.y;
    if(segmentHeight > 0)
    {
        for(int y = arr[1].screenPos.y;y <= arr[2].screenPos.y;y++)
        {
            float pctOfFar  = (float)(y - (int)arr[0].screenPos.y) / totalHeight;
            float pctOfNear = (float)(y - (int)arr[1].screenPos.y) / segmentHeight;
            
            if(pctOfFar >= 0 && pctOfNear >= 0)
            {
                Vertex v1 = LerpVertex(arr[0],arr[2],pctOfFar);
                Vertex v2 = LerpVertex(arr[1],arr[2],pctOfNear);
                
                scanline(y,v1,v2);
            }
        }
    }

}
