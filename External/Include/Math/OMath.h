#pragma once
namespace OMath {
	constexpr float pi_f = 3.14159265f;					// PI float
	constexpr double pi_d = 3.1415926535897932;			// PI double
	constexpr double pi_2 = 1.57079632679489661923;		// PI divided by 2
	constexpr double pi_4 = 0.785398163397448309616;	// PI divided by 4

	constexpr double e = 2.71828182845904523536;		// e double
	constexpr double log2e = 1.44269504088896340736;	// log2(e)
	constexpr double log10e = 0.434294481903251827651;	// log10(e)

	constexpr double sqrt2 = 1.41421356237309504880;	// sqrt(2)

	template <typename T>
	inline T Clamp(const T& value, const T& min, const T& max) {
		if (value < min) { 
			return min; 
		}
		else if (value > max) { 
			return max; 
		}

		return value;
	}

	template <typename T>
	inline auto Squared(const T& value) noexcept {
		return value * value;
	}

	template <typename T>
	T Lerp(const T& start, const T& end, const T& percentage) {
		return start + percentage * (end - percentage);
	}

	template <typename T>
	T Min(const T& first, const T& second) {
		return first < second ? first : second;
	}

	template <typename T>
	T Max(const T& first, const T& second) {
		return first > second ? first : second;
	}

	template <typename T>
	T Abs(const T& value) {
		if (value < 0) {
			return value * -1;
		}
		return value;
	}
}