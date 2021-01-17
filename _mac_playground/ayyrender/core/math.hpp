#pragma once
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <iostream>

extern const float PI;

extern float deg2Rad(float deg);

extern float rad2Deg(float rad);

struct Vec4;

template<typename T>
struct Vec2
{
    T x,y;
    Vec2():x(0),y(0) {}
    Vec2(T x,T y):x(x),y(y){}
    
    template<typename TOther>
    Vec2(const TOther& other)
    {
        x = other.x;
        y = other.y;
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
    Vec3(T x,T y):x(x),y(y),z(0) {}
    Vec3(T x,T y,T z):x(x),y(y),z(z) {}
    Vec3():x(0),y(0),z(0) {}
    
    template<typename TOther>
    Vec3(const TOther& other)
    {
        x = (T)other.x;
        y = (T)other.y;
        z = (T)other.z;
    }
    
//    Vec3(const Vec3<T>& other) {
//        x = other.x;
//        y = other.y;
//        z = other.z;
//    }
    
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
    
    void operator += (const Vec3<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
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
    Vec3<T> operator ^(const Vec3<T>& other)
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
    
    Vec3<T> GetNormalize()
    {
        float factor = 1.0f/Length();
        Vec3<T> result(x * factor,y * factor,z * factor);
        return result;
    }
    
    void Dump()
    {
        std::cout << "[" << x << "," << y << "," << z << "]" << std::endl;
    }
};

typedef Vec2<int> Vec2i;
typedef Vec2<int> Vec2f;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

//
//float Distance(const Vec3f& v1,const Vec3f& v2)
//{
//////    float dis = (v1 - v2).Length();
////    float dis = 0;
////    return dis;
//    return 0;
//}

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
        if(vec.size() > 4)
            throw std::runtime_error("count error");
        
        for(int i = 0;i < 4;i++)
        {
            data[i] = i < vec.size() ? vec[i] : 0.0f;
        }
//        data[0] = vec[0];
//        data[1] = vec[1];
//        data[2] = vec[2];
//        data[3] = vec[3];
    }
    
    Vec4(const Vec3<float>& v3,float w)
        :x(v3.x)
        ,y(v3.y)
        ,z(v3.z)
        ,w(w)
    {

    }
    
    void operator=(const Vec4& other)
    {
        x = other.x; y = other.y; z = other.z; w = other.w;
    }
    
    float operator[](int index)
    {
        return data[index];
    }
    
    Vec4 operator+(const Vec4& other)
    {
        Vec4 result(x + other.x,y + other.y,z + other.z,w + other.w);
        return result;
    }
    
    Vec4 operator-(const Vec4& other)
    {
        Vec4 result(x - other.x,y - other.y,z - other.z,w - other.w);
        return result;
    }

    Vec4 operator*(float value)
    {
        Vec4 result = *this;
        result.x *= value;
        result.y *= value;
        result.z *= value;
        result.w *= value;
        return result;
    }

    Vec4 operator/(float value)
    {
        if(value == 0)
            throw std::runtime_error("div zero!");
        Vec4 result = *this;
        result.x /= value;
        result.y /= value;
        result.z /= value;
        result.w /= value;
        return result;
    }
    
    float Length()
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    
    void Normalize()
    {
        float len = Length();
        if(len == 0)
            throw new std::runtime_error("normalize 0 length vector!");
        
        x = x / len;
        y = y / len;
        z = z / len;
        w = w / len;
    }
    
    bool operator==(const Vec4& other)
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
    
    bool operator!=(const Vec4& other)
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }
    
    void dump()
    {
        printf("----\n[%.3f,%.3f,%.3f,%.3f]\n",x,y,z,w);
    }
};


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
        if(values.size() > n * n)
            throw std::runtime_error("invalid element count");
        
        int idx = 0;
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                data[r][c] = idx < n * n ? values[idx++] : 0.0f;
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
                float counter = 0;
                for(int k = 0;k < n;k++)
                {
                    counter += data[row][k] * other.data[k][col];
                }
                result.data[row][col] = counter;
            }
        }
        return result;
    }
    
    void operator=(const Matrix<n>& other)
    {
        for(int r = 0;r < n;r++)
        {
            for(int c = 0;c < n;c++)
            {
                data[r][c] = other.data[r][c];
            }
        }
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

extern Matrix<4> RotateByAxisX(float deg);
extern Matrix<4> RotateByAxisY(float deg);
extern Matrix<4> RotateByAxisZ(float deg);

/*
    a,b,c is 3 points of one triangle
    p is we are calculating point
 
    return shall be a barycentric coordinate,3 values be saved in Vec3f's each part
 */
extern Vec3f TriangleBarycentricCoordinate(const Vec2f& a,const Vec2f& b,const Vec2f& c,const Vec2f& p);

template<typename T>
T Lerp(T v1,T v2,float t)
{
    if(v1 == v2)
    {
        return v1;
    }
    T r;
    r = v1 + (v2 - v1) * t;
    return r;
}

