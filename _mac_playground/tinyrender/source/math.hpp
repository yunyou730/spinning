#pragma once

template<typename T>
struct Vec2
{
    T x,y;
    Vec2():x(0),y(0) {}
    Vec2(T x,T y):x(x),y(y){}
    
    Vec2<T> operator+(const Vec2<T>& other)
    {
        Vec2<T> result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }
    
    Vec2<T> operator-(const Vec2<T>& other)
    {
        Vec2<T> result;
        result.x = x - other.x;
        result.y = y - other.y;
        return result;
    }
    
    template<typename FT>
    Vec2<T> operator*(FT number)
    {
        Vec2<T> result;
        result.x = x * number;
        result.y = y * number;
        return result;
    }
    
};

typedef Vec2<int> Vec2i;

struct Color
{
    Color(){}
    Color(int r,int g,int b,int a):r(r),g(g),b(b),a(a){}
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;
};


// temp globals
const Color white    = Color(255,255,255,255);
const Color red      = Color(255,0,0,255);
const Color green    = Color(0,255,0,255);
const Color blue     = Color(0,0,255,255);
const Color yellow   = Color(255,255,0,255);
