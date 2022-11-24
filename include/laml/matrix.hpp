#ifndef __LAML_MATRIX_H
#define __LAML_MATRIX_H

#include <utility>
#include <ostream>

#include <laml/vector.hpp>
#include <laml/data_types.hpp>

namespace rh::laml {
    
	// COLUMN-MAJOR MATRIX
	template<typename T, size_t rows, size_t cols>
	struct Matrix {
		static_assert((rows > 0) && (cols > 0), "Matrix cannot be zero-size in either direction");

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
		
		// Initialize with single value for all diagonal
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

	// Printing function
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
	template<typename T, size_t rows1, size_t cols1, size_t rows2, size_t cols2,
		class V = typename std::enable_if<cols1==rows2, T>::type>
	Matrix<T, rows1, cols2> mul(const Matrix<T, rows1, cols1>& m1, const Matrix<T, rows2, cols2>& m2) {
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