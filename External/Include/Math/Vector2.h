#pragma once
#include <assert.h>

namespace OMath {
	template <class T>
	class Vector2 {
	public:
		Vector2<T>();
		Vector2<T>(const T& x, const T& y);
		Vector2<T>(const Vector2<T>& vector) = default;
		~Vector2<T>() = default;
		
		Vector2<T>& operator=(const Vector2<T>& vector) = default;

		// Returns the squared length of the vector
		T LengthSqrd() const;

		// Returns the length of the vector
		T Length() const;

		// Returns the normalized value of the vector
		Vector2<T> GetNormalized() const;

		// Normalizes the vector
		void Normalize();

		// Returns the dot product of the current vector and the given vector
		T Dot(const Vector2<T>& vector) const;

		T mX;
		T mY;
	};
	template<class T>
	inline Vector2<T>::Vector2() : mX(0), mY(0) {}

	template<class T>
	inline Vector2<T>::Vector2(const T& x, const T& y) : mX(x), mY(y) {}

	template<class T>
	inline T Vector2<T>::LengthSqrd() const {
		return mX * mX + mY * mY;
	}

	template<class T>
	inline T Vector2<T>::Length() const {
		return static_cast<T>(sqrt(LengthSqrd()));
	}

	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const {
		Vector2<T> vec(mX, mY);
		vec.Normalize();
		return vec;
	}

	template<class T>
	inline void Vector2<T>::Normalize() {
		Vector2<T> vec(mX, mY);
		if (mX + mY != 0) {
			const auto length = vec.Length();
			mX = vec.mX / length;
			mY = vec.mY / length;
		}
	}

	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& vector) const {
		return mX * vector.mX + mY * vector.mY;
	}

	template <class T>
	Vector2<T> operator+(const Vector2<T>& vector0, const Vector2<T>& vector1) {
		return { vector0.mX + vector1.mX, vector0.mY + vector1.mY };
	}

	template <class T>
	void operator+=(Vector2<T>& vector0, const Vector2<T>& vector1) {
		vector0.mX += vector1.mX;
		vector0.mY += vector1.mY;
	}


	template <class T>
	Vector2<T> operator-(const Vector2<T>& vector0, const Vector2<T>& vector1) {
		return { vector0.mX - vector1.mX, vector0.mY - vector1.mY };
	}

	template <class T>
	void operator-=(Vector2<T>& vector0, const Vector2<T>& vector1) {
		vector0.mX -= vector1.mX;
		vector0.mY -= vector1.mY;
	}

	template <class T>
	Vector2<T> operator*(const Vector2<T>& vector0, const Vector2<T>& vector1) {
		return { vector0.mX * vector1.mX, vector0.mY * vector1.mY };
	}

	template <class T>
	void operator*=(Vector2<T>& vector0, const Vector2<T>& vector1) {
		vector0.mX *= vector1.mX;
		vector0.mY *= vector1.mY;
	}

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2ui;
}