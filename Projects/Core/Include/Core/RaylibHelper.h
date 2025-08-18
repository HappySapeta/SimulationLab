#pragma once
#include <cmath>
#include <algorithm>
#include <raylib/raylib.h>



namespace SL
{
	inline Color operator*(const Color& Lhs, float Scalar)
	{
		Scalar = std::clamp(Scalar, 0.0f, 1.0f);
		return Color
		{
			static_cast<uint8_t>(std::lround(static_cast<float>(Lhs.r) * Scalar)),
			static_cast<uint8_t>(std::lround(static_cast<float>(Lhs.g) * Scalar)),
			static_cast<uint8_t>(std::lround(static_cast<float>(Lhs.b) * Scalar)),
			Lhs.a
		};
	}
	
	inline Color operator+(const Color& Lhs, const Color& Rhs)
	{
		return Color
			{
				static_cast<uint8_t>(std::clamp(Lhs.r + Rhs.r, 0, 255)),
				static_cast<uint8_t>(std::clamp(Lhs.g + Rhs.g, 0, 255)),
				static_cast<uint8_t>(std::clamp(Lhs.b + Rhs.b, 0, 255)),
				static_cast<uint8_t>(std::clamp(Lhs.a + Rhs.a, 0, 255))
			};
	}

	class ColorHelper
	{
	public:
		static Color Saturate(const Color& C, float Scalar)
		{
			Scalar = std::clamp(Scalar, 0.0f, 1.0f);
			return Color
			{
				static_cast<uint8_t>(std::lround(static_cast<float>(C.r) * Scalar)),
				static_cast<uint8_t>(std::lround(static_cast<float>(C.g) * Scalar)),
				static_cast<uint8_t>(std::lround(static_cast<float>(C.b) * Scalar)),
				C.a
			};
		}

		static Color Add(const Color& A, const Color& B)
		{
			return Color
			{
				static_cast<uint8_t>(std::clamp(A.r + B.r, 0, 255)),
				static_cast<uint8_t>(std::clamp(A.g + B.g, 0, 255)),
				static_cast<uint8_t>(std::clamp(A.b + B.b, 0, 255)),
				static_cast<uint8_t>(std::clamp(A.a + B.a, 0, 255))
			};
		}
		
		static Color InterpColor(const Color& A, const Color& B, float Step)
		{
			Step = std::clamp(Step, 0.0f, 1.0f);
			return (A * (1 - Step)) + (B * Step);
		}
	};
	
}
