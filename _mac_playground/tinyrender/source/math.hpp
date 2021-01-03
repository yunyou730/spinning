#pragma once
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <vector>

//template<typename T>
//struct Vec3;

template<typename T>
struct Vec2
{
    T x,y;
    Vec2():x(0),y(0) {}
    Vec2(T x,T y):x(x),y(y){}
    
//    template<typename TOther>
//    Vec2(const Vec3<TOther>& other)
//    {
//        x = (T)other.x;
//        y = (T)other.y;
//    }
    
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
    Vec3(T x,T y):x(x),y(y),z(0) {}
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
typedef Vec3<int> Vec3i;

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


struct Vec4
{
    union
    {
        struct{
            float x,y,z,w;
        };
        float data[4];
    };
    
    Vec4() { x = y = z = w = 0;}
    Vec4(float x,float y,float z,float w):x(x),y(y),z(z),w(w) {}
    Vec4(const std::vector<float>& vec) {
        if(vec.size() != 4)
            throw std::runtime_error("count error");
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
        data[3] = vec[3];
    }
    
    float operator[](int index)
    {
        return data[index];
    }
    
    void dump()
    {
        printf("----\n[%.3f,%.3f,%.3f,%.3f]\n",x,y,z,w);
    }
};
//
//template<int n>
//struct Vector
//{
//    float raw[n];
//
//    Vector()
//    {
//        for(int i = 0;i < n;i++)
//        {
//            raw[i] = 0;
//        }
//    }
//
//    float x() const {
//        if(n < 1)
//            throw std::runtime_error("dimension error");
//        return raw[0];
//    };
//
//    void x(float val) {
//
//    }
//
//};


// matrix
template<int n>
struct Matrix
{
    float data[n][n];
    
    Matrix()
    {
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                data[r][c] = 0;
            }
        }
    }
    
    Matrix(const std::vector<float>& values)
    {
        Fill(values);
    }
    
    void Fill(const std::vector<float>& values)
    {
        if(values.size() != n * n)
            throw std::runtime_error("invalid element count");
        
        int idx = 0;
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                data[r][c] = values[idx++];
            }
        }
    }
    
    inline float Get(int row,int col) const
    {
        if(row < 0 || row >= n || col < 0 || col >= n)
            throw std::runtime_error("matrix over bound");
        return data[row][col];
    }
    
    void Set(int row,int col,float value)
    {
        if(row < 0 || row >= n || col < 0 || col >= n)
            throw std::runtime_error("matrix over bound");
        data[row][col] = value;
    }
    
    void Identity()
    {
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                data[r][c] = (r == c) ? 1 : 0;
            }
        }
    }
    
    // @miao @todo
    // testing...
    Vec4 operator*(const Vec4& vec)
    {
        if(n != 4)
            throw std::runtime_error("dimension not match!");
        
        Vec4 result;
        
        for(int r = 0;r < 4;r++)
        {
            result.data[r] = data[r][0] * vec.x + data[r][1] * vec.y + data[r][2] * vec.z + data[r][3] * vec.w;
        }
//        result.x = data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * vec.w;
//        result.y = data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * vec.w;
//        result.z = data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * vec.w;
//        result.w = data[3][0] * vec.x + data[3][1] * vec.y + data[3][2] * vec.z + data[3][3] * vec.w;
        
        return result;
    }
    
    // test done
    Matrix<n> operator*(float number)
    {
        Matrix<n> result;
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                result.Set(r,c,Get(r,c) * number);
            }
        }
        return result;
    }
    
    // test done
    void operator*=(float number)
    {
        Matrix<n> result;
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                Set(r,c,Get(r,c) * number);
            }
        }
        return *this;
    }
    
    // test done
    Matrix<n> operator*(const Matrix<n>& other)
    {
        Matrix<n> result;
        for(int row = 0;row < n;row++)
        {
            for(int col = 0;col < n;col++)
            {
                int counter = 0;
                for(int k = 0;k < n;k++)
                {
                    counter += data[row][k] * other.data[k][col];
                }
                result.data[row][col] = counter;
            }
        }
        return result;
    }
    
    void dump()
    {
        printf("----\n");
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                printf("%.3f\t",data[r][c]);
            }
            printf("\n");
        }
        printf("----\n");
    }
};
