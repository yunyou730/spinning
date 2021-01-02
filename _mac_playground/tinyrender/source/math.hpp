#pragma once
#include <cmath>

template<typename T>
struct Vec3;

template<typename T>
struct Vec2
{
    T x,y;
    Vec2():x(0),y(0) {}
    Vec2(T x,T y):x(x),y(y){}
    
    template<typename TOther>
    Vec2(const Vec3<TOther>& other)
    {
        x = (T)other.x;
        y = (T)other.y;
    }
    
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

template<typename T>
struct Vec3
{
    T x,y,z;
    Vec3(T x,T y,T z):x(x),y(y),z(z) {}
    Vec3():x(0),y(0),z(0) {}
    
    void operator=(const Vec3<T>& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    
    Vec3<T> operator+(const Vec3<T>& other)
    {
        Vec3<T> result;
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;
        return result;
    }
    
    Vec3<T> operator-(const Vec3<T>& other)
    {
        Vec3<T> result;
        result.x = x - other.x;
        result.y = y - other.y;
        result.z = z - other.z;
        return result;
    }
    
    template<typename FT>
    Vec3<T> operator*(FT number)
    {
        Vec3<T> result;
        result.x = x * number;
        result.y = y * number;
        result.z = z * number;
        return result;
    }
    
    // Dot Product
    T operator*(const Vec3<T>& other)
    {
        T result = x * other.x + y * other.y + z * other.z;
        return result;
    }
    
    // Cross Product
    Vec3<T> operator^(const Vec3<T>& other)
    {
        Vec3<T> result;
        result.x = y * other.z - other.y * z;
        result.y = z * other.x - x * other.z;
        result.z = x * other.y - other.x * y;
        return result;
    }
    
    float Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    Vec3<T>& Normalize()
    {
        float factor = 1.0f/Length();
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }
};

typedef Vec2<int> Vec2i;
typedef Vec2<int> Vec2f;
typedef Vec3<float> Vec3f;

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
