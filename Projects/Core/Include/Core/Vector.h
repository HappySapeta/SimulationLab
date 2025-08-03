#pragma once
#include <cmath>
#include <sstream>
#include <string>
#include <raylib/raylib.h>

namespace SL
{
	template<typename Type>
	struct TVec2 : Vector2
	{
		static_assert(std::is_arithmetic_v<Type>, "TVec2 can only be used with arithmetic types!");

	public:

		constexpr TVec2()
		{
			x = 0;
			y = 0;
		}
		
		constexpr TVec2(const Type XComponent, const Type YComponent)
		{
			x = XComponent;
			y = YComponent;
		}

		template<typename OtherType, typename = std::enable_if<std::is_convertible_v<OtherType, Type>>>
		constexpr explicit TVec2(const TVec2<OtherType>& Other)
		{
			x = static_cast<Type>(Other.x);
			y = static_cast<Type>(Other.y);
		}
	
	public:

		static const TVec2 Left;
		static const TVec2 Right;
		static const TVec2 Up;
		static const TVec2 Down;

	public:
		
		Type GetLength() const { return std::hypot(x, y); }

		TVec2 GetNormal(const double Tolerance = 0.00001) const
		{
			const Type Length = GetLength();
			if(Length < Tolerance)
			{
				return {0, 0};
			}
			
			return TVec2{x / Length, y / Length};
		}

		void Normalize(const double Tolerance = 0.00001)
		{
			*this = GetNormal(Tolerance);
		}

		constexpr Type Dot(const TVec2& Other) const { return x * Other.x + y * Other.y; }
		constexpr Type Cross(const TVec2& Other) const { return x * Other.y - y * Other.x; }
		
		constexpr TVec2 operator+(const TVec2& Other) const { return {x + Other.x, y + Other.y}; }
		constexpr TVec2 operator-(const TVec2& Other) const { return {x - Other.x, y - Other.y}; }
		constexpr TVec2 operator-() const { return {-x, -y}; }
		
		constexpr TVec2 operator*(const Type Scalar) const { return {x * Scalar, y * Scalar}; }
		constexpr friend TVec2 operator*(const Type Scalar, const TVec2& Vector) { return Vector.operator*(Scalar); }

		constexpr TVec2 operator/(const Type Scalar) const
		{
			if(Scalar == 0)
			{
				return {0, 0};
			}
			return {x / Scalar, y / Scalar};
		}

		constexpr bool operator==(const TVec2 &Other) const
		{
			return Equals(*this, Other);
		}
		static constexpr bool Equals(const TVec2& A, const TVec2& B, const Type Tolerance = 0.00001)
		{
			Type XError = abs(A.x - B.x);
			Type YError = abs(A.y - B.y);
			return XError <= Tolerance && YError <= Tolerance;
		}
		
		constexpr bool operator!=(const TVec2& Other) const { return !(*this == Other); }

		explicit operator std::string() const { return ToString(); }
		std::string ToString() const
		{
			std::ostringstream Oss;
			Oss << "(" << x << "," << y << ")";
			return Oss.str();
		}
	};

	template<typename Type>
	const TVec2<Type> TVec2<Type>::Left{-1, 0};

	template<typename T>
	const TVec2<T> TVec2<T>::Right{1, 0};

	template<typename T>
	const TVec2<T> TVec2<T>::Up{0, 1};

	template<typename T>
	const TVec2<T> TVec2<T>::Down {0, -1};

	template<typename Type>
	struct TVec3 : Vector3
	{
		static_assert(std::is_arithmetic_v<Type>, "TVec3 can only be used with arithmetic types!");

	public:

		constexpr TVec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		constexpr TVec3(const Type XComponent, const Type YComponent, const Type ZComponent)
		{
			x = XComponent;
			y = YComponent;
			z = ZComponent;
		}
		
		template<typename OtherType, typename = std::enable_if_t<std::is_convertible_v<OtherType, Type>>>
		constexpr explicit TVec3(const TVec3<OtherType>& Other)
		{
			x = static_cast<Type>(Other.x);
			y = static_cast<Type>(Other.y);
			z = static_cast<Type>(Other.z);
		}
		
	public:

		static const TVec3 Zero;
		static const TVec3 Left;
		static const TVec3 Right;
		static const TVec3 Up;
		static const TVec3 Down;
		static const TVec3 Forward;
		static const TVec3 Back;

	public:

		static TVec3 Cross(const TVec3& A, const TVec3& B)
		{
			return
			{
				A.y * B.z - A.z * B.y,
				A.z * B.x - A.x * B.z,
				A.x * B.y - A.y * B.x
			};
		}

		Type GetLength() const { return std::hypot(x, y, z); }

		TVec3 GetNormal(const double Tolerance = 0.00001) const
		{
			const Type Length = GetLength();
			if(Length < Tolerance)
			{
				return {0, 0, 0};
			}
			
			return TVec3{x / Length, y / Length, z / Length};
		}

		void Normalize(const double Tolerance = 0.00001)
		{
			const Type Length = GetLength();
			if(Length < Tolerance)
			{
				x = y = z = 0;
				return;
			}
			
			x /= Length;
			y /= Length;
			z /= Length;
		}
		
		constexpr Type Dot(const TVec3& Other) const { return x * Other.x + y * Other.y + z * Other.z; }

		constexpr TVec3 Cross(const TVec3 &Other) const
		{
			return Cross(*this, Other);
		}

		constexpr TVec3 operator+(const TVec3& Other) const { return {x + Other.x, y + Other.y, z + Other.z}; }
		constexpr TVec3 operator-(const TVec3& Other) const { return {x - Other.x, y - Other.y, z - Other.z}; }
		constexpr TVec3 operator-() const { return {-x, -y, -z}; }

		constexpr TVec3 operator*(const Type Scalar) const { return {x * Scalar, y * Scalar, z * Scalar}; }
		constexpr friend TVec3 operator*(const Type Scalar, const TVec3& Vector) { return Vector.operator*(Scalar);}
		constexpr TVec3 operator/(const Type Scalar) const
		{
			if(Scalar == 0)
			{
				return {0, 0, 0};
			}
			return {x / Scalar, y / Scalar, z / Scalar};
		}

		constexpr bool operator==(const TVec3 &Other) const
		{
			return Equals(*this, Other);
		}
		static constexpr bool Equals(const TVec3& A, const TVec3& B, const Type tolerance = 0.00001)
		{
			Type XError = abs(A.x - B.x);
			Type YError = abs(A.y - B.y);
			Type ZError = abs(A.z - B.z);
			return XError <= tolerance && YError <= tolerance && ZError <= tolerance;
		}
		
		constexpr bool operator!=(const TVec3& Other) const { return !(*this == Other); }
		
		explicit operator std::string() const { return ToString(); }
		std::string ToString() const
		{
			std::ostringstream Oss;
			Oss << "(" << x << "," << y << "," << z << ")";
			return Oss.str();
		}
	};

	template<typename T>
	const TVec3<T> TVec3<T>::Zero{0, 0, 0};
	
	template<typename T>
	const TVec3<T> TVec3<T>::Left{-1, 0, 0};

	template<typename T>
	const TVec3<T> TVec3<T>::Right{1, 0, 0};

	template<typename T>
	const TVec3<T> TVec3<T>::Up{0, 0, 1};

	template<typename T>
	const TVec3<T> TVec3<T>::Down{0, 0, -1};

	template<typename T>
	const TVec3<T> TVec3<T>::Forward{0, 1, 0};

	template<typename T>
	const TVec3<T> TVec3<T>::Back{0, -1, 0};
}

namespace SL
{
	// Two-dimensional vector. Type - float.
	using Vec2 = TVec2<float>;
	
	// Two-dimensional vector. Type - double.
	using Vec2d = TVec2<double>;
	
	// Three-dimensional vector. Type - float.
	using Vec3 = TVec3<float>;
	
	// Three-dimensional vector. Type - double.
	using Vec3d = TVec3<double>;
}