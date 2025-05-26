#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace OMath {
	template <class T>
	class Matrix4x4 {
	public:
		Matrix4x4<T>();
		Matrix4x4<T>(const Matrix4x4<T>& matrix);
		void operator=(const Matrix4x4<T>& matrix);

		const T& operator()(const unsigned int row, const unsigned int column) const;
		T& operator()(const unsigned int row, const unsigned int column);

		static Matrix4x4<T> CreateRotationAroundX(T angleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(T angleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(T angleInRadians);

		static Matrix4x4<T> Transpose(const Matrix4x4<T>& matrixToTranspose);

		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& transform);

		static Matrix4x4<T> CreateScaleMatrix(const Vector3<T>& scaleVector);
		static Matrix4x4<T> CreateTranslationMatrix(const Vector3<T>& translationVector);

		/*	x - Roll
			y - pitch
			z - yaw */
		static Matrix4x4<T> CreateRotationMatrix(const Vector3<T>& rotationVector);
	private:
		T mObjects[4][4];
	};

	template <class T>
	T& Matrix4x4<T>::operator()(const unsigned int row, const unsigned int column) {
		static_assert(row < 4 && column < 4 && "Trying to access elements out of range");

		return mObjects[row - 1][column - 1];
	}

	template <class T>
	const T& Matrix4x4<T>::operator()(const unsigned int row, const unsigned int column) const {
		static_assert(row < 4 && column < 4 && "Trying to access elements out of range");

		return mObjects[row - 1][column - 1];
	}

	template <class T>
	void Matrix4x4<T>::operator=(const Matrix4x4<T>& matrix) {
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				mObjects[row - 1][column - 1] = matrix(row, column);
			}
		}
	}

	template <class T>
	Matrix4x4<T> operator+(const Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		Matrix4x4<T> tempMatrix;

		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				tempMatrix(row, column) = matrix0(row, column) + matrix1(row, column);
			}
		}
		return tempMatrix;
	}

	template <class T>
	Matrix4x4<T> operator-(const Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		Matrix4x4<T> tempMatrix;
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				tempMatrix(row, column) = matrix0(row, column) - matrix1(row, column);
			}
		}
		return tempMatrix;
	}

	template <class T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		Matrix4x4<T> tempMatrix;

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				tempMatrix(i, j) = matrix0(i, 1) * matrix1(1, j) + matrix0(i, 2) * matrix1(2, j) + matrix0(i, 3) *
					matrix1(3, j) + matrix0(i, 4) * matrix1(4, j);
			}
		}
		return tempMatrix;
	}

	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& matrix) {
		Vector4<T> tempVector;
		tempVector.x = aVector.x * matrix(1, 1) + aVector.y * matrix(2, 1) + aVector.z * matrix(3, 1) + aVector.w *
			matrix(4, 1);
		tempVector.y = aVector.x * matrix(1, 2) + aVector.y * matrix(2, 2) + aVector.z * matrix(3, 2) + aVector.w *
			matrix(4, 2);
		tempVector.z = aVector.x * matrix(1, 3) + aVector.y * matrix(2, 3) + aVector.z * matrix(3, 3) + aVector.w *
			matrix(4, 3);
		tempVector.w = aVector.x * matrix(1, 4) + aVector.y * matrix(2, 4) + aVector.z * matrix(3, 4) + aVector.w *
			matrix(4, 4);

		return tempVector;
	}

	template <class T>
	Vector4<T> operator*(const Matrix4x4<T>& matrix, const Vector4<T>& aVector) {
		Vector4<T> tempVector;
		tempVector.x = aVector.x * matrix(1, 1) + aVector.y * matrix(2, 1) + aVector.z * matrix(3, 1) + aVector.w *
			matrix(4, 1);
		tempVector.y = aVector.x * matrix(1, 2) + aVector.y * matrix(2, 2) + aVector.z * matrix(3, 2) + aVector.w *
			matrix(4, 2);
		tempVector.z = aVector.x * matrix(1, 3) + aVector.y * matrix(2, 3) + aVector.z * matrix(3, 3) + aVector.w *
			matrix(4, 3);
		tempVector.w = aVector.x * matrix(1, 4) + aVector.y * matrix(2, 4) + aVector.z * matrix(3, 4) + aVector.w *
			matrix(4, 4);

		return tempVector;
	}

	template <class T>
	void operator+=(Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				matrix0(row, column) += matrix1(row, column);
			}
		}
	}

	template <class T>
	void operator-=(Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				matrix0(row, column) -= matrix1(row, column);
			}
		}
	}

	template <class T>
	void operator*=(Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		Matrix4x4<T> tempMatrix;

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				tempMatrix(i, j) = matrix0(i, 1) * matrix1(1, j) + matrix0(i, 2) * matrix1(2, j) + matrix0(i, 3) *
					matrix1(3, j) + matrix0(i, 4) * matrix1(4, j);
			}
		}
		matrix0 = tempMatrix;
	}

	template <class T>
	bool operator==(const Matrix4x4<T>& matrix0, const Matrix4x4<T>& matrix1) {
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				if (matrix0(row, column) != matrix1(row, column)) {
					return false;
				}
			}
		}
		return true;
	}

	template <class T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& matrix) {
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				mObjects[row - 1][column - 1] = matrix(row, column);
			}
		}
	}

	template <class T>
	inline Matrix4x4<T>::Matrix4x4() {
		for (int row = 1; row <= 4; row++) {
			for (int column = 1; column <= 4; column++) {
				if (row == column) {
					mObjects[row - 1][column - 1] = 1;
				} else {
					mObjects[row - 1][column - 1] = 0;
				}
			}
		}
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T angleInRadians) {
		Matrix4x4<T> temp;
		temp(2, 2) = std::cos(angleInRadians);
		temp(2, 3) = std::sin(angleInRadians);
		temp(3, 2) = -std::sin(angleInRadians);
		temp(3, 3) = std::cos(angleInRadians);

		return temp;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T angleInRadians) {
		Matrix4x4<T> temp;
		temp(1, 1) = std::cos(angleInRadians);
		temp(1, 3) = -std::sin(angleInRadians);
		temp(3, 1) = std::sin(angleInRadians);
		temp(3, 3) = std::cos(angleInRadians);

		return temp;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T angleInRadians) {
		Matrix4x4<T> temp;
		temp(1, 1) = std::cos(angleInRadians);
		temp(1, 2) = std::sin(angleInRadians);
		temp(2, 1) = -std::sin(angleInRadians);
		temp(2, 2) = std::cos(angleInRadians);

		return temp;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& matrixToTranspose) {
		Matrix4x4<T> temp = Matrix4x4<T>(matrixToTranspose);

		temp(2, 1) = matrixToTranspose(1, 2);
		temp(1, 2) = matrixToTranspose(2, 1);

		temp(3, 1) = matrixToTranspose(1, 3);
		temp(1, 3) = matrixToTranspose(3, 1);

		temp(3, 2) = matrixToTranspose(2, 3);
		temp(2, 3) = matrixToTranspose(3, 2);

		temp(4, 1) = matrixToTranspose(1, 4);
		temp(1, 4) = matrixToTranspose(4, 1);

		temp(4, 2) = matrixToTranspose(2, 4);
		temp(2, 4) = matrixToTranspose(4, 2);

		temp(4, 3) = matrixToTranspose(3, 4);
		temp(3, 4) = matrixToTranspose(4, 3);

		return temp;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& transform) {
		Matrix4x4<T> newMatrix = transform;

		newMatrix(2, 1) = transform(1, 2);
		newMatrix(1, 2) = transform(2, 1);

		newMatrix(3, 1) = transform(1, 3);
		newMatrix(1, 3) = transform(3, 1);

		newMatrix(3, 2) = transform(2, 3);
		newMatrix(2, 3) = transform(3, 2);

		newMatrix(4, 1) = -transform(4, 1) * newMatrix(1, 1) - transform(4, 2) * newMatrix(2, 1) - transform(4, 3) *
			newMatrix(3, 1);
		newMatrix(4, 2) = -transform(4, 1) * newMatrix(1, 2) - transform(4, 2) * newMatrix(2, 2) - transform(4, 3) *
			newMatrix(3, 2);
		newMatrix(4, 3) = -transform(4, 1) * newMatrix(1, 3) - transform(4, 2) * newMatrix(2, 3) - transform(4, 3) *
			newMatrix(3, 3);

		return newMatrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateScaleMatrix(const Vector3<T>& aScaleVector) {
		Matrix4x4<T> result;
		result(1, 1) = aScaleVector.x;
		result(2, 2) = aScaleVector.y;
		result(3, 3) = aScaleVector.z;

		return result;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateTranslationMatrix(const Vector3<T>& aTranslationVector) {
		Matrix4x4<T> result;

		result(4, 1) = aTranslationVector.x;
		result(4, 2) = aTranslationVector.y;
		result(4, 3) = aTranslationVector.z;

		return result;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationMatrix(const Vector3<T>& rotationVector) {
		Matrix4x4<T> result;

		float cp = cosf(rotationVector.x);
		float sp = sinf(rotationVector.x);

		float cy = cosf(rotationVector.y);
		float sy = sinf(rotationVector.y);

		float cr = cosf(rotationVector.z);
		float sr = sinf(rotationVector.z);

		result(1, 1) = cr * cy + sr * sp * sy;
		result(1, 2) = sr * cp;
		result(1, 3) = sr * sp * cy - cr * sy;
		result(1, 4) = 0.0f;

		result(2, 1) = cr * sp * sy - sr * cy;
		result(2, 2) = cr * cp;
		result(2, 3) = sr * sy + cr * sp * cy;
		result(2, 4) = 0.0f;

		result(3, 1) = cp * sy;
		result(3, 2) = -sp;
		result(3, 3) = cp * cy;
		result(3, 4) = 0.0f;

		result(4, 1) = 0.0f;
		result(4, 2) = 0.0f;
		result(4, 3) = 0.0f;
		result(4, 4) = 1.0f;

		return result;
	}

	typedef Matrix4x4<float> Matrix4x4f;
	typedef Matrix4x4<double> Matrix4x4d;
	typedef Matrix4x4<int> Matrix4x4i;
}