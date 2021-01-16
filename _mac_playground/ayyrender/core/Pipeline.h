#pragma once

#include "Camera.h"

#define AYY_NS_BEGIN    namespace ayy {
#define AYY_NS_END      }

#define SAFE_DELETE(ptr)    {if(ptr != nullptr) { delete ptr;ptr = nullptr;}}

AYY_NS_BEGIN

struct Vertex
{
    Vec4    pos;
    Color   color;
    
    Vertex(const Vec4& pos,const Color& color):pos(pos),color(color){}
    
    Vec4    transformedPos;
};


template<typename T>
struct FrameBuffer;

class Pipeline
{
public:
    Pipeline(int viewportWidth,int viewportHeight);
    ~Pipeline();
    
protected:
    Camera*                 _camera         = nullptr;
    FrameBuffer<int>*       _frameBuffer    = nullptr;
    FrameBuffer<float>*     _zBuffer        = nullptr;
};

template<typename T>
struct FrameBuffer
{
    FrameBuffer(int width,int height,const T& defaultValue)
        :rowCnt(height)
        ,colCnt(width)
    {
        for(int row = 0;row < height;row++)
        {
            data = new T[row];
            for(int col = 0;col < height;col++)
            {
                data[row][col] = defaultValue;
            }
        }
    }
    
    ~FrameBuffer()
    {
        for(int row = 0;row < rowCnt;row++)
        {
            delete[] data[row];
        }
    }
    
    T& Get(int row,int col) const
    {
        if(row < 0 || row >= rowCnt || col < 0 || col >= colCnt)
            throw new std::runtime_error("over data bound");
        return data[row][col];
    }
    
    void Set(int row,int col,const T& value)
    {
        if(row < 0 || row >= rowCnt || col < 0 || col >= colCnt)
            throw new std::runtime_error("over data bound");
        data[row][col] = value;
    }
    
public:
    T** data = nullptr;
    const int rowCnt,colCnt;
};

AYY_NS_END
