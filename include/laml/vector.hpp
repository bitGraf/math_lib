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

		// Default constructor
		constexpr Vector() : data{0} {}

		// Initialize with list of components
		template<class... U, class V = typename std::enable_if<sizeof...(U) + 1 == size, T>::type>
		constexpr Vector(T first, U... next) noexcept : data{ first, next... } {}

		// Initialize with single value for all components
		//template<class U, class V = typename std::enable_if<std::is_same<T, U>::value && size != 1, T>::type>
		//constexpr explicit Vector(U value) noexcept : Vector(typename GenerateSequence<size>::Type{}, value) {}

		// access like an array
		T& operator[](size_t idx) {
			return data[idx];
		}
		const T& operator[](size_t idx) const {
			return data[idx];
		}

		T data[size];
	};

	// Specializations
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


	// Useful shorthands
	typedef Vector<float, 2> Vec2;
	typedef Vector<float, 3> Vec3;
	typedef Vector<float, 4> Vec4;

	typedef Vector<double, 2> Vec2_highp;
	typedef Vector<double, 3> Vec3_highp;
	typedef Vector<double, 4> Vec4_highp;

}

#endif // __LAML_VECTOR_H