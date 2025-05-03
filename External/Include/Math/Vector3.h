#pragma once
namespace OMath {
	template <class T>
	class Vector3 {
	public:
		Vector3<T>();
		Vector3<T>(const T& x, const T& y, const T& z);
		Vector3<T>(const Vector3<T>& vector) = default;
		~Vector3<T>() = default;

		Vector3<T>& operator=(const Vector3<T>& vector) = default;

		// Returns the squared length of the vector
		T LengthSqrd() const;

		// Returns the length of the vector
		T Length() const;

		// Returns the normalized value of the vector
		Vector3<T> GetNormalized() const;

		// Normalizes the vector
		void Normalize();

		// Returns the dot product of the current vector and the given vector
		T Dot(const Vector3<T>& vector) const;

		// Returns the cross product of this and given vector
		Vector3<T> Cross(const Vector3<T>& vector) const;

		T mX;
		T mY;
		T mZ;
	};
	template<class T>
	inline Vector3<T>::Vector3() : mX(0), mY(0), mZ(0) {}

	template<class T>
	inline Vector3<T>::Vector3(const T& x, const T& y, const T& z) : mX(x), mY(y), mZ(z) {}

	template<class T>
	inline T Vector3<T>::LengthSqrd() const {
		return mX * mX + mY * mY + mZ * mZ;
	}

	template<class T>
	inline T Vector3<T>::Length() const {
		return static_cast<T>(sqrt(LengthSqrd()));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const {
		Vector3<T> vec(mX, mY, mZ);
		vec.Normalize();
		return vec;
	}

	template<class T>
	inline void Vector3<T>::Normalize() {
		Vector3<T> vec(mX, mY, mZ);
		if (mX + mY != 0) {
			const auto length = vec.Length();
			mX = vec.mX / length;
			mY = vec.mY / length;
			mZ = vec.mZ / length;
		}
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& vector) const {
		return mX * vector.mX + mY * vector.mY + mZ * vector.mZ;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& vector) const {
		return { 
			mY * vector.mZ - mZ * vector.mY,
			mZ * vector.mX - mX * vector.mZ,
			mX * vector.mY - mY * vector.mX
		};
	}

	template <class T>
	Vector3<T> operator+(const Vector3<T>& vector0, const Vector3<T>& vector1) {
		return { vector0.mX + vector1.mX, vector0.mY + vector1.mY, vector0.mZ + vector1.mZ };
	}

	template <class T>
	void operator+=(Vector3<T>& vector0, const Vector3<T>& vector1) {
		vector0.mX += vector1.mX;
		vector0.mY += vector1.mY;
		vector0.mZ += vector1.mZ;
	}


	template <class T>
	Vector3<T> operator-(const Vector3<T>& vector0, const Vector3<T>& vector1) {
		return { vector0.mX - vector1.mX, vector0.mY - vector1.mY, vector0.mZ - vector1.mZ };
	}

	template <class T>
	void operator-=(Vector3<T>& vector0, const Vector3<T>& vector1) {
		vector0.mX -= vector1.mX;
		vector0.mY -= vector1.mY;
		vector0.mZ -= vector1.mZ;
	}

	template <class T>
	Vector3<T> operator*(const Vector3<T>& vector0, const Vector3<T>& vector1) {
		return { vector0.mX * vector1.mX, vector0.mY * vector1.mY, vector0.mZ * vector1.mZ };
	}

	template <class T>
	void operator*=(Vector3<T>& vector0, const Vector3<T>& vector1) {
		vector0.mX *= vector1.mX;
		vector0.mY *= vector1.mY;
		vector0.mZ *= vector1.mZ;
	}

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int> Vector3fi;
	typedef Vector3<unsigned int> Vector3ui;
}