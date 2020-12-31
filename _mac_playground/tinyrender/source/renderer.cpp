#include "renderer.hpp"

void line(TGAImage& image,const TGAColor& color,int x0,int y0,int x1,int y1)
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
        for(int x = x0;x <= x1;x++)
        {
            float t = (x - x0) / (float)(x1 - x0);
            int y = y0 + (y1 - y0) * t;
            image.set(x,y,color);
        }
    }
    else
    {
        if(y0 > y1)
        {
            std::swap(y0,y1);
            std::swap(x0,x1);
        }
        for(int y = y0;y < y1;y++)
        {
            float t = (y - y0) / (float)(y1 - y0);
            int x = x0 + (x1 - x0) * t;
            image.set(x,y,color);
        }
    }
}
