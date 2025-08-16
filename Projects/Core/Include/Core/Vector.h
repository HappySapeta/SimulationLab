#pragma once
#include <raylib/raylib.h>
#include <cmath>
#include <sstream>
#include <string>

namespace SL
{
	struct Vec2 : Vector2
	{
	public:

		constexpr Vec2()
		{
			x = 0;
			y = 0;
		}
		
		constexpr Vec2(const float XComponent, const float YComponent)
		{
			x = XComponent;
			y = YComponent;
		}
	
	public:

		static const Vec2 North;
		static const Vec2 West;
		static const Vec2 South;
		static const Vec2 East;

	public:
		
		float GetLength() const { return std::hypot(x, y); }

		static float Distance(const Vec2& V1, const Vec2& V2)
		{
			return (V1 - V2).GetLength();
		}

		Vec2 GetNormal(const double Tolerance = 0.00001) const
		{
			const float Length = GetLength();
			if(Length < Tolerance)
			{
				return {0, 0};
			}
			
			return Vec2{x / Length, y / Length};
		}

		float GetHeadingAngle() const
		{
			const Vec2 Heading = GetNormal();
			return std::atan2f(Heading.y, Heading.x);
		}

		void Normalize(const double Tolerance = 0.00001)
		{
			*this = GetNormal(Tolerance);
		}

		constexpr float Dot(const Vec2& Other) const { return x * Other.x + y * Other.y; }
		constexpr float Cross(const Vec2& Other) const { return x * Other.y - y * Other.x; }
		
		constexpr Vec2 operator+(const Vec2& Other) const { return {x + Other.x, y + Other.y}; }
		constexpr Vec2 operator-(const Vec2& Other) const { return {x - Other.x, y - Other.y}; }
		constexpr Vec2 operator-() const { return {-x, -y}; }

		constexpr void operator+=(const Vec2& Other)
		{
			x += Other.x;
			y += Other.y;
		}

		constexpr void operator-=(const Vec2& Other)
		{
			x -= Other.x;
			y -= Other.y;
		}
		
		constexpr Vec2 operator*(const float Scalar) const { return {x * Scalar, y * Scalar}; }
		constexpr friend Vec2 operator*(const float Scalar, const Vec2& Vector) { return Vector.operator*(Scalar); }

		constexpr Vec2 operator/(const float Scalar) const
		{
			if(Scalar == 0)
			{
				return {0, 0};
			}
			return {x / Scalar, y / Scalar};
		}

		bool operator==(const Vec2 &Other) const
		{
			return Equals(*this, Other);
		}
		
		static bool Equals(const Vec2& A, const Vec2& B, const float Tolerance = 0.00001)
		{
			float XError = abs(A.x - B.x);
			float YError = abs(A.y - B.y);
			return XError <= Tolerance && YError <= Tolerance;
		}
		
		bool operator!=(const Vec2& Other) const { return !(*this == Other); }

		explicit operator std::string() const { return ToString(); }
		std::string ToString() const
		{
			std::ostringstream Oss;
			Oss << "(" << x << "," << y << ")";
			return Oss.str();
		}
	};

	const Vec2 North{0, 1};
	const Vec2 West{-1, 0};
	const Vec2 South{0, -1};
	const Vec2 East{1, 0};

	struct Vec3 : Vector3
	{
	public:

		constexpr Vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		constexpr Vec3(const float XComponent, const float YComponent, const float ZComponent)
		{
			x = XComponent;
			y = YComponent;
			z = ZComponent;
		}
		
	public:

		static const Vec3 Zero;
		static const Vec3 Left;
		static const Vec3 Right;
		static const Vec3 Up;
		static const Vec3 Down;
		static const Vec3 Forward;
		static const Vec3 Back;

	public:

		static constexpr Vec3 Cross(const Vec3& A, const Vec3& B)
		{
			return
			{
				A.y * B.z - A.z * B.y,
				A.z * B.x - A.x * B.z,
				A.x * B.y - A.y * B.x
			};
		}

		float GetLength() const { return std::hypot(x, y, z); }

		Vec3 GetNormal(const double Tolerance = 0.00001) const
		{
			const float Length = GetLength();
			if(Length < Tolerance)
			{
				return {0, 0, 0};
			}
			
			return Vec3{x / Length, y / Length, z / Length};
		}

		void Normalize(const double Tolerance = 0.00001)
		{
			const float Length = GetLength();
			if(Length < Tolerance)
			{
				x = y = z = 0;
				return;
			}
			
			x /= Length;
			y /= Length;
			z /= Length;
		}
		
		constexpr float Dot(const Vec3& Other) const { return x * Other.x + y * Other.y + z * Other.z; }

		constexpr Vec3 Cross(const Vec3 &Other) const
		{
			return Cross(*this, Other);
		}

		constexpr Vec3 operator+(const Vec3& Other) const { return {x + Other.x, y + Other.y, z + Other.z}; }
		constexpr Vec3 operator-(const Vec3& Other) const { return {x - Other.x, y - Other.y, z - Other.z}; }
		constexpr Vec3 operator-() const { return {-x, -y, -z}; }

		constexpr void operator+=(const Vec3& Other)
		{
			x += Other.x;
			y += Other.y;
			z += Other.z;
		}

		constexpr void operator-=(const Vec3& Other)
		{
			x -= Other.x;
			y -= Other.y;
			z -= Other.z;
		}

		constexpr Vec3 operator*(const float Scalar) const { return {x * Scalar, y * Scalar, z * Scalar}; }
		constexpr friend Vec3 operator*(const float Scalar, const Vec3& Vector) { return Vector.operator*(Scalar);}
		constexpr Vec3 operator/(const float Scalar) const
		{
			if(Scalar == 0)
			{
				return {0, 0, 0};
			}
			return {x / Scalar, y / Scalar, z / Scalar};
		}

		bool operator==(const Vec3 &Other) const
		{
			return Equals(*this, Other);
		}
		static bool Equals(const Vec3& A, const Vec3& B, const float tolerance = 0.00001)
		{
			float XError = abs(A.x - B.x);
			float YError = abs(A.y - B.y);
			float ZError = abs(A.z - B.z);
			return XError <= tolerance && YError <= tolerance && ZError <= tolerance;
		}
		
		bool operator!=(const Vec3& Other) const { return !(*this == Other); }
		
		explicit operator std::string() const { return ToString(); }
		std::string ToString() const
		{
			std::ostringstream Oss;
			Oss << "(" << x << "," << y << "," << z << ")";
			return Oss.str();
		}
	};

	const Vec3 Zero{0, 0, 0};
	const Vec3 Left{-1, 0, 0};
	const Vec3 Right{1, 0, 0};
	const Vec3 Up{0, 0, 1};
	const Vec3 Down{0, 0, -1};
	const Vec3 Forward{0, 1, 0};
	const Vec3 Back{0, -1, 0};

	static SL::Vec2 ToVec2(const Vector2& RayVec)
	{
		return SL::Vec2{RayVec.x, RayVec.y};
	}
}
