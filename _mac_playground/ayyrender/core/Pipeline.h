#pragma once

#include "Camera.h"

#define AYY_NS_BEGIN    namespace ayy {
#define AYY_NS_END      }

#define SAFE_DELETE(ptr)    {if(ptr != nullptr) { delete ptr;ptr = nullptr;}}

AYY_NS_BEGIN

struct Vertex
{
    Vec4    pos;            // local model pos
    Color   color;
    
    Vertex(const Vec4& pos,const Color& color):pos(pos),color(color){}
    
//    Vec4    worldPos;       // local pos crossed by WorldMatrix
    Vec4    transformedPos; // pos producted by MVP
    Vec4    ndcPos;         // pos transformedPos * 1/w
    Vec3f   screenPos;      // pos which ndcPos -> screen
};

template<typename T>
struct FrameBuffer;

class Pipeline
{
public:
    Pipeline(int viewportWidth,int viewportHeight);
    ~Pipeline();
    
    Camera* GetCamera() { return _camera;}
    
    void WriteColor(int x,int y,const Color& color);
    void WriteZ(int x,int y,float value);
    
    FrameBuffer<Color>*     GetFrameBuffer() const { return _frameBuffer;}
    FrameBuffer<float>*     GetZBuffer() const { return _zBuffer;}
    
    Color& GetClearColor() { return _clearColor;}
    void SetClearColor(const Color& color) {_clearColor = color;}
    
    void ClearBuffer();
    
    void GetSize(int& width,int &height) const { width = _width;height = _height;}
    
protected:
    Camera*                 _camera         = nullptr;
    FrameBuffer<Color>*     _frameBuffer    = nullptr;
    FrameBuffer<float>*     _zBuffer        = nullptr;
    Color                   _clearColor;
    
    const int _width,_height;
};

template<typename T>
struct FrameBuffer
{
    FrameBuffer(int width,int height,const T& defaultValue)
        :rowCnt(height)
        ,colCnt(width)
    {
        data = new T*[height];
        for(int row = 0;row < height;row++)
        {
            data[row] = new T[width];
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
        delete[] data;
    }
    
    T& Get(int x,int y) const
    {
        if(y < 0 || y >= rowCnt || x < 0 || x >= colCnt)
            throw new std::runtime_error("over data bound");
        return data[y][x];
    }
    
    void Set(int x,int y,const T& value)
    {
        if(y < 0 || y >= rowCnt || x < 0 || x >= colCnt)
        {
            return;
        }
        data[y][x] = value;
    }
    
public:
    T** data = nullptr;
    const int rowCnt,colCnt;
};

AYY_NS_END
