#ifndef __LAML_MATRIX_H
#define __LAML_MATRIX_H

#include <utility>
#include <ostream>

#include <laml/vector.hpp>
#include <laml/data_types.hpp>
//#include <laml/Matrix2.hpp>

#include <iostream>

namespace rh::laml {
    
	// COLUMN-MAJOR MATRIX
	template<typename T, size_t rows, size_t cols>
	struct Matrix {
		static_assert((rows != 0) && (cols != 0), "Matrix cannot be zero-size in either direction");

		typedef T Type;

		constexpr inline size_t num_rows() const { return rows; }
		constexpr inline size_t num_cols() const { return cols; }

		//// Default constructor
		constexpr Matrix() : _data{} {}

		//// Construct with float array
		//Vector(const float* in_data) {
		//	for (size_t n = 0; n < size; n++) {
		//		_data[n] = static_cast<T>(in_data[n]);
		//	}
		//}
		
		// Initialize with list of components
		//template<class... U, class V = typename std::enable_if<sizeof...(U) + 1 == cols*rows, T>::type>
		//constexpr Matrix(T first, U... next) noexcept : _data{ first, next... } {}
		
		// Initialize with single value for all diagonal - Not really a constructor tho..
		template<class V = typename std::enable_if<rows != 1 && rows==cols, T>::type>
		Matrix(T value) {
			for (size_t n = 0; n < rows; n++) {
				_data[n][n] = value;
			}
		}
		
		// access like an array
		Vector<T,rows>& operator[](size_t idx) {
			return _data[idx];
		}
		const Vector<T, rows>& operator[](size_t idx) const {
			return _data[idx];
		}
		
		//const T* data() const { return _data; }
		//T* data() { return _data; }
		//
		laml::Vector<T, rows> _data[cols];
	};

	// Printing functions
	template<typename T, size_t rows, size_t cols>
	std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols>& mat) {
		os << "[";
		for (size_t col = 0; col < cols; col++) {
			os << mat[col];
			if (col != (cols - 1))
				os << ", ";
		}
		os << "]";
		return os;
	}

	template<typename T, size_t rows, size_t cols>
	void print(const Matrix<T, rows, cols>& mat) {
		printf("[");
		for (size_t col = 0; col < cols; col++) {
			print(mat[col]);
			if (col != (cols - 1))
				printf(", ");
		}
		printf("]");
	}
	template<typename T, size_t rows, size_t cols>
	void print(const Matrix<T, rows, cols>& mat, const char* fmt) {
		printf("[");
		for (size_t col = 0; col < cols; col++) {
			print(mat[col], fmt);
			if (col != (cols - 1))
				printf(", ");
		}
		printf("]");
	}

	/* Component-wise operators
	 * typename T needs to implement: +,-,*,/
	 * These are all component-wise operations
	 * */
	template<typename T, size_t rows, size_t cols>
	Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols>& mat, const Matrix<T, rows, cols>& other) {
		Matrix<T, rows, cols> res;
		for (size_t n = 0; n < cols; n++) {
			res[n] = mat[n] + other[n];
		}
		return res;
	}

	template<typename T, size_t rows, size_t cols>
	Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols>& mat, const Matrix<T, rows, cols>& other) {
		Matrix<T, rows, cols> res;
		for (size_t n = 0; n < cols; n++) {
			res[n] = mat[n] - other[n];
		}
		return res;
	}

	template<typename T, size_t rows, size_t cols>
	Matrix<T, rows, cols> operator*(const Matrix<T, rows, cols>& mat, const Matrix<T, rows, cols>& other) {
		Matrix<T, rows, cols> res;
		for (size_t n = 0; n < cols; n++) {
			res[n] = mat[n] * other[n];
		}
		return res;
	}

	template<typename T, size_t rows, size_t cols>
	Matrix<T, rows, cols> operator/(const Matrix<T, rows, cols>& mat, const Matrix<T, rows, cols>& other) {
		Matrix<T, rows, cols> res;
		for (size_t n = 0; n < cols; n++) {
			res[n] = mat[n] / other[n];
		}
		return res;
	}

	/* Scaling operators
	 * typename T needs to implement: *,/
	 * These are all component-wise operations
	 * */
	template<typename T, size_t rows, size_t cols>
	Matrix<T, rows, cols> operator*(const Matrix<T, rows, cols>& mat, const T& factor) {
		Matrix<T, rows, cols> res;
		for (size_t n = 0; n < cols; n++) {
			res[n] = mat[n] * factor;
		}
		return res;
	}

	template<typename T, size_t rows, size_t cols>
	Matrix<T, rows, cols> operator/(const Matrix<T, rows, cols>& mat, const T& factor) {
		Matrix<T, rows, cols> res;
		for (size_t n = 0; n < cols; n++) {
			res[n] = mat[n] / factor;
		}
		return res;
	}

	// Free functions
	// Slow multiply (triple for-loop). Make specialiazations for common-use cases
	template<typename T, size_t rows1, size_t cols1, size_t rows2, size_t cols2,
		class V = typename std::enable_if<cols1==rows2, T>::type>
	Matrix<T, rows1, cols2> mul(const Matrix<T, rows1, cols1>& m1, const Matrix<T, rows2, cols2>& m2) {
		//std::cout << "SLOW MUL [" << rows1 << "," << cols1 << "]x[" << rows2 << "," << cols2 << "]" << std::endl;
		Matrix<T, rows1, cols2> res;
		for (size_t col = 0; col < cols2; col++) {
			for (size_t row = 0; row < rows1; row++) {
				for (size_t n = 0; n < cols1; n++) {
					res[col][row] = res[col][row] + m1[n][row] * m2[col][n];
				}
			}
		}
		return res;
	}

	// inverse - NOT FULLY IMPLEMENTED FOR ALL CASES
	template<typename T, size_t rows, size_t cols,
	class V = typename std::enable_if<rows==cols, T>::type>
	Matrix<T, rows, cols> inverse(const Matrix<T, rows, cols>& mat) {
		printf("MATRIX INVERSE NOT IMPLEMENTED FOR THE %dx%d case!\n", (int)rows, (int)cols);
		Matrix<T, rows, cols> res;
		mat;
		return res;
	}

	// determinant - recusrive method for arbitrary square matrix
	template<typename T, size_t size>
	T det(const Matrix<T, size, size>& mat) {
		std::cout << "Recursive determinant func!" << std::endl;
		// create the minor matrices of rank size-1
		// expand along the first column
		T res = 0;
		for (size_t n = 0; n < size; n++) {
			T scalar = mat[0][n] * (n % 2 == 0 ? static_cast<T>(1.0) : static_cast<T>(-1));
			Matrix<T, size - 1, size - 1> minor;
			for (size_t i = 0; i < size - 1; i++) {
				size_t new_i = i+1; // always expand along the first column
				for (size_t j = 0; j < size - 1; j++) {
					size_t new_j = (j + 1 > n) ? j + 1 : j;

					minor[i][j] = mat[new_i][new_j];
				}
			}

			// calculate dterminants of minor matrices "recursively"
			// not techncally recursive, since templates tho :)
			res = res + det(minor) * scalar;
		}
		return res;
	}

	// determinant - 3x3 case
	template<typename T>
	T det(const Matrix<T, 3, 3>& mat) {
		return mat[0][0]*mat[1][1]*mat[2][2] - 
			   mat[0][0]*mat[1][2]*mat[2][1] - 
			   mat[0][1]*mat[1][0]*mat[2][2] + 
			   mat[0][1]*mat[1][2]*mat[2][0] + 
			   mat[0][2]*mat[1][0]*mat[2][1] - 
			   mat[0][2]*mat[1][1]*mat[2][0];
	}
	// determinant - 2x2 case
	template<typename T>
	T det(const Matrix<T, 2, 2>& mat) {
		return mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
	}
	// determinant - 1x1 case
	template<typename T>
	T det(const Matrix<T, 1, 1>& mat) {
		return mat[0][0];
	}


	// Specializations
#if 0
#pragma warning(disable : 4201) // complains about unnammed union structs
	template<typename T> struct Matrix<T, 2> {
		constexpr Vector() : _data{ 0,0 } {}
		constexpr Vector(T _x, T _y) : _data{ _x,_y } {}
		constexpr Vector(T _x) : _data{ _x,_x } {}
		Vector(const float* in_data) : _data{ in_data[0], in_data[1] } {}

		union {
			T _data[2];
			struct { T x, y; };
		};

		T& operator[](size_t idx) {
			return _data[idx];
		}
		const T& operator[](size_t idx) const {
			return _data[idx];
		}
	};
#pragma warning(default : 4201)
#endif


	// Useful shorthands
	typedef Matrix<float, 2, 2> Mat2;
	typedef Matrix<float, 3, 3> Mat3;
	typedef Matrix<float, 4, 4> Mat4;

	typedef Matrix<double, 2, 2> Mat2_highp;
	typedef Matrix<double, 3, 3> Mat3_highp;
	typedef Matrix<double, 4, 4> Mat4_highp;
}

#endif // __LAML_MATRIX_H