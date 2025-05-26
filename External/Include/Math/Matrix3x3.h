#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

namespace OMath {
	template <class T>
	class Matrix3x3 {
	public:
		Matrix3x3<T>();
		Matrix3x3<T>(const Matrix3x3<T>& matrix);
		Matrix3x3<T>(const Matrix4x4<T>& matrix);
		void operator=(const Matrix3x3<T>& matrix);
		void operator=(const Matrix4x4<T>& matrix);

		const T& operator()(const unsigned int row, const unsigned int column) const;
		T& operator()(const unsigned int row, const unsigned int column);

		static Matrix3x3<T> CreateRotationAroundX(T angleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(T angleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(T angleInRadians);

		static Matrix3x3<T> Transpose(const Matrix3x3<T>& matrixToTranspose);

	private:
		T mmObjects[3][3];
	};

	template <class T> 
	T& Matrix3x3<T>::operator()(const unsigned int row, const unsigned int column) {
		static_assert(row < 3 && column < 3 && "Trying to access elements out of range");

		return mmObjects[row - 1][column - 1];
	}

	template <class T> 
	const T& Matrix3x3<T>::operator()(const unsigned int row, const unsigned int column) const {
		static_assert(row < 3 && column < 3 && "Trying to access elements out of range");

		return mmObjects[row - 1][column - 1];
	}

	template <class T> 
	void Matrix3x3<T>::operator=(const Matrix3x3<T>& matrix) {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				mmObjects[row - 1][column - 1] = matrix(row, column);
			}
		}
	}

	template <class T> 
	Matrix3x3<T> operator+(const Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		Matrix3x3<T> tempMatrix;
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				tempMatrix(row, column) = matrix0(row, column) + matrix1(row, column);
			}
		}
		return tempMatrix;
	}

	template <class T> 
	Matrix3x3<T> operator-(const Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		Matrix3x3<T> tempMatrix;
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				tempMatrix(row, column) = matrix0(row, column) - matrix1(row, column);
			}
		}
		return tempMatrix;
	}

	template <class T> 
	Matrix3x3<T> operator*(const Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		Matrix3x3<T> tempMatrix;

		for (T i = 1; i <= 3; i++) {
			for (T j = 1; j <= 3; j++) {
				tempMatrix(i, j) = matrix0(i, 1) * matrix1(1, j) + matrix0(i, 2) * matrix1(2, j) + matrix0(i, 3) * matrix0(3, j);
			}
		}

		return tempMatrix;
	}

	template <class T> 
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& matrix) {
		Vector3<T> tempVector;
		tempVector.x = aVector.x * matrix(1, 1) + aVector.y * matrix(2, 1) + aVector.z * matrix(3, 1);
		tempVector.y = aVector.x * matrix(1, 2) + aVector.y * matrix(2, 2) + aVector.z * matrix(3, 2);
		tempVector.z = aVector.x * matrix(1, 3) + aVector.y * matrix(2, 3) + aVector.z * matrix(3, 3);
		return tempVector;
	}

	template <class T> 
	Vector3<T> operator*(const Matrix3x3<T>& matrix, const Vector3<T>& aVector) {
		Vector3<T> tempVector;
		tempVector.x = aVector.x * matrix(1, 1) + aVector.y * matrix(2, 1) + aVector.z * matrix(3, 1);
		tempVector.y = aVector.x * matrix(1, 2) + aVector.y * matrix(2, 2) + aVector.z * matrix(3, 2);
		tempVector.z = aVector.x * matrix(1, 3) + aVector.y * matrix(2, 3) + aVector.z * matrix(3, 3);
		return tempVector;
	}

	template <class T> 
	void operator+=(Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				matrix0(row, column) += matrix1(row, column);
			}
		}
	}

	template <class T> 
	void operator-=(Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				matrix0(row, column) -= matrix1(row, column);
			}
		}
	}

	template <class T> 
	void operator*=(Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		Matrix3x3<T> tempMatrix;

		for (T row = 1; row <= 3; row++) {
			for (T column = 1; column <= 3; column++) {
				tempMatrix(row, column) = matrix0(row, 1) * matrix1(1, column) + matrix0(row, 2) * matrix1(2, column) + matrix0(row, 3) * matrix1(3, column);
			}
		}
		matrix0 = tempMatrix;
	}

	template <class T> 
	bool operator==(const Matrix3x3<T>& matrix0, const Matrix3x3<T>& matrix1) {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				if (matrix0(row, column) != matrix1(row, column)) {
					return false;
				}
			}
		}
		return true;
	}

	template<class T> 
	inline Matrix3x3<T>::Matrix3x3() {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				if (row == column) {
					mObjects[row - 1][column - 1] = 1;
				} else {
					mObjects[row - 1][column - 1] = 0;
				}
			}
		}
	}
	template<class T> 
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& matrix) {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				mObjects[row - 1][column - 1] = matrix(row, column);
			}
		}
	}

	template<class T> 
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& matrix) {
		for (int row = 1; row <= 3; row++) {
			for (int column = 1; column <= 3; column++) {
				mObjects[row - 1][column - 1] = matrix(row, column);
			}
		}
	}

	template<class T> 
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T angleInRadians) {
		Matrix3x3<T> temp;
		temp(2, 2) = std::cos(angleInRadians);
		temp(2, 3) = std::sin(angleInRadians);
		temp(3, 2) = -std::sin(angleInRadians);
		temp(3, 3) = std::cos(angleInRadians);

		return temp;
	}
	template<class T> 
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T angleInRadians) {
		Matrix3x3<T> temp;
		temp(1, 1) = std::cos(angleInRadians);
		temp(1, 3) = -std::sin(angleInRadians);
		temp(3, 1) = std::sin(angleInRadians);
		temp(3, 3) = std::cos(angleInRadians);

		return temp;
	}
	template<class T> 
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T angleInRadians) {
		Matrix3x3<T> temp;
		temp(1, 1) = std::cos(angleInRadians);
		temp(1, 2) = std::sin(angleInRadians);
		temp(2, 1) = -std::sin(angleInRadians);
		temp(2, 2) = std::cos(angleInRadians);

		return temp;
	}

	template<class T> 
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& matrixToTranspose) {
		Matrix3x3<T> temp = Matrix3x3<T>(matrixToTranspose);

		temp(2, 1) = matrixToTranspose(1, 2);
		temp(1, 2) = matrixToTranspose(2, 1);

		temp(3, 1) = matrixToTranspose(1, 3);
		temp(1, 3) = matrixToTranspose(3, 1);

		temp(3, 2) = matrixToTranspose(2, 3);
		temp(2, 3) = matrixToTranspose(3, 2);

		return temp;
	}

	typedef Matrix3x3<float> Matrix3x3f;
	typedef Matrix3x3<double> Matrix3x3d;
	typedef Matrix3x3<int> Matrix3x3i;
}