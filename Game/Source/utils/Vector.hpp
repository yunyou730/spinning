#pragma once

namespace ayy
{
	template<typename T>
	struct Vector4
	{
		Vector4() :x(0), y(0), z(0), w(0) {}
		Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
		Vector4(T _x, T _y, T _z) : x(_x), y(_y), z(_z), w(0) {}

		void operator = (const Vector4<T>& other) {
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		void operator = (const Vector4<T>&& other) {
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		union {
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
		};
	};

	template<typename T>
	struct Vector2 {
		Vector2() :x(0),y(0) {}
		Vector2(const T& x, const T& y) : x(x), y(y) {}

		void operator = (const Vector2& other)
		{
			x = other.x;
			y = other.y;
		}

		void operator = (const Vector2&& other)
		{
			x = other.x;
			y = other.y;
		}

		T x, y;
	};
}

