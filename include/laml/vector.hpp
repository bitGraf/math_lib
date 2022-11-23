#ifndef __LAML_VECTOR_H
#define __LAML_VECTOR_H

#include <utility>

#include <laml/data_types.hpp>

namespace rh::laml {

	template<size_t ...> struct Sequence {};

	template<size_t N, size_t ...sequence> struct GenerateSequence :
		GenerateSequence<N - 1, N - 1, sequence...> {};

	template<size_t ...sequence> struct GenerateSequence<0, sequence...> {
		typedef Sequence<sequence...> Type;
	};

	template<typename T, size_t size>
	struct Vector { 
		static_assert(size > 0, "Vector cannot be zero-size");

		typedef T Type;
		constexpr inline size_t num_elements() const { return size; }

		// Default constructor
		constexpr Vector() : _data{0} {}

		// Construct with float array
		Vector(const float* in_data) {
			for (size_t n = 0; n < size; n++) {
				_data[n] = static_cast<T>(in_data[n]);
			}
		}

		// Initialize with list of components
		template<class... U, class V = typename std::enable_if<sizeof...(U) + 1 == size, T>::type>
		constexpr Vector(T first, U... next) noexcept : _data{ first, next... } {}

		// Initialize with single value for all components
		//template<class U, class V = typename std::enable_if<std::is_same<T, U>::value && size != 1, T>::type>
		//constexpr explicit Vector(U value) noexcept : Vector(typename GenerateSequence<size>::Type{}, value) {}

		// access like an array
		T& operator[](size_t idx) {
			return _data[idx];
		}
		const T& operator[](size_t idx) const {
			return _data[idx];
		}

		/* Operators
		* typename T needs to implement: +,-,*,/,==
		* These are all component-wise operations
		* */
		Vector<T,size> operator+(const Vector<T,size>& other) const {
			Vector<T,size> res;
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] + other[n];
			}
			return res;
		}
		Vector<T, size> operator-(const Vector<T, size>& other) const {
			Vector<T, size> res;
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] - other[n];
			}
			return res;
		}
		Vector<T, size> operator*(const Vector<T, size>& other) const {
			Vector<T, size> res;
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] * other[n];
			}
			return res;
		}
		Vector<T, size> operator/(const Vector<T, size>& other) const {
			Vector<T, size> res;
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] / other[n];
			}
			return res;
		}
		bool operator==(const Vector<T, size>& other) const {
			for (size_t n = 0; n < size; n++) {
				if (_data[n] != other[n]) return false;
			}
			return true;
		}

		// scalar operators
		Vector<T, size> operator*(const T& factor) const {
			Vector<T, size> res;
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] * factor;
			}
			return res;
		}
		Vector<T, size> operator/(const T& factor) const {
			Vector<T, size> res;
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] / factor;
			}
			return res;
		}

		// comparison operators
		Vector<bool, size> operator>(const Vector<T,size>& other) const {
			Vector<bool, size> res; // fill with falses?
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] > other[n];
			}
			return res;
		}
		Vector<bool, size> operator<(const Vector<T, size>& other) const {
			Vector<bool, size> res; // fill with falses?
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] < other[n];
			}
			return res;
		}
		Vector<bool, size> operator>=(const Vector<T, size>& other) const {
			Vector<bool, size> res; // fill with falses?
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] >= other[n];
			}
			return res;
		}
		Vector<bool, size> operator<=(const Vector<T, size>& other) const {
			Vector<bool, size> res; // fill with falses?
			for (size_t n = 0; n < size; n++) {
				res[n] = _data[n] <= other[n];
			}
			return res;
		}

		const T* data() const { return _data; }
		T* data() { return _data; }

	private:
		T _data[size];
	};

	// Free functions
	template<typename T, size_t size>
	T dot(const Vector<T, size>& v1, const Vector<T, size>& v2) {
		T res = 0;
		for (size_t n = 0; n < size; n++) {
			res = res + (v1[n] * v2[n]);
		}
		return res;
	}

	template<typename T>
	Vector<T,3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) {
		Vector<T, 3> res;
		res[0] = v1[1] * v2[2] - v1[2] * v2[1];
		res[1] = v1[2] * v2[0] - v1[0] * v2[2];
		res[2] = v1[0] * v2[1] - v1[1] * v2[0];
		return res;
	}

	template<typename T, size_t size>
	T length_sq(const Vector<T, size>& v) {
		T res = 0;
		for (size_t n = 0; n < size; n++) {
			res = res + (v[n] * v[n]);
		}
		return res;
	}

	template<typename T, size_t size>
	T length(const Vector<T, size>& v) {
		return static_cast<T>(sqrt(length_sq(v)));
	}

	template<typename T, size_t size>
	Vector<T,size> normalize(const Vector<T, size>& v) {
		T mag = length(v);
		return (v / mag);
	}

	template<typename T, size_t size>
	T min(const Vector<T, size>& v) {
		T min_val = v[0];
		for (size_t n = 1; n < size; n++) {
			if (v[n] < min_val) min_val = v[n];
		}
		return min_val;
	}

	template<typename T, size_t size>
	T max(const Vector<T, size>& v) {
		T max_val = v[0];
		for (size_t n = 1; n < size; n++) {
			if (v[n] > max_val) max_val = v[n];
		}
		return max_val;
	}

	template<typename T, size_t size>
	Vector<T, size> abs(const Vector<T, size>& v) {
		Vector<T, size> res;
		for (size_t n = 0; n < size; n++) {
			res[n] = v[n] > static_cast<T>(0.0) ? v[n] : -v[n];
		}
		return res;
	}

	template<typename T, size_t size>
	Vector<T, size> clamp(const Vector<T, size>& v, T min_val, T max_val) {
		Vector<T, size> res;
		for (size_t n = 0; n < size; n++) {
			res[n] = v[n] > max_val ? max_val : (v[n] < min_val ? min_val : v[n]);
		}
		return res;
	}

	template<typename T, size_t size>
	Vector<T,size> lerp(const Vector<T, size>& v1, const Vector<T, size>& v2, T factor) {
		return v2 * factor + v1 * (static_cast<T>(1.0) - factor);
	}

	template<size_t size>
	bool any(const Vector<bool, size>& v) {
		for (size_t n = 0; n < size; n++) {
			if (v[n]) return true;
		}
		return false;
	}
	template<size_t size>
	bool all(const Vector<bool, size>& v) {
		for (size_t n = 0; n < size; n++) {
			if (!v[n]) return false;
		}
		return true;
	}

	// Specializations
#if 0
#pragma warning(disable : 4201) // complains about unnammed union structs
	template<typename T> struct Vector<T, 2> {
		constexpr Vector() : data{0,0} {}
		constexpr Vector(T _x, T _y) : data{ _x,_y } {}

		union {
			T data[2];
			struct { T x, y; };
		};

		T& operator[](size_t idx) {
			return data[idx];
		}
		const T& operator[](size_t idx) const {
			return data[idx];
		}
	};

	template<typename T> struct Vector<T, 3> {
		constexpr Vector() : data{ 0,0,0 } {}
		constexpr Vector(T _x, T _y, T _z) : data{ _x,_y,_z } {}

		union {
			T data[3];
			struct { T x, y, z; };
		};

		T& operator[](size_t idx) {
			return data[idx];
		}
		const T& operator[](size_t idx) const {
			return data[idx];
		}
	};

	template<typename T> struct Vector<T, 4> {
		constexpr Vector() : data{ 0,0,0,0 } {}
		constexpr Vector(T _x, T _y, T _z, T _w) : data{ _x,_y,_z,_w } {}

		union {
			T data[4];
			struct { T x, y, z, w; };
		};

		T& operator[](size_t idx) {
			return data[idx];
		}
		const T& operator[](size_t idx) const {
			return data[idx];
		}
	};
#pragma warning(default : 4201)
#endif


	// Useful shorthands
	typedef Vector<float, 2> Vec2;
	typedef Vector<float, 3> Vec3;
	typedef Vector<float, 4> Vec4;

	typedef Vector<double, 2> Vec2_highp;
	typedef Vector<double, 3> Vec3_highp;
	typedef Vector<double, 4> Vec4_highp;

}

#endif // __LAML_VECTOR_H