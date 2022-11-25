#ifndef __LAML_QUATERNION_H
#define __LAML_QUATERNION_H

#include <ostream>

namespace rh::laml {
    
#pragma warning(disable : 4201) // complains about unnammed union structs
    template<typename T>
    struct Quaternion {

		typedef T Type;

		union {
			T _data[4];
			struct { T x, y, z, w; };
		};

		constexpr inline size_t num_elements() const { return 4; }

		// Default constructor
		constexpr Quaternion() : _data{ 0, 0, 0, 1.0 } {}

		// Construct with float array
		Quaternion(const float* in_data) : _data{static_cast<T>(in_data[0]), static_cast<T>(in_data[1]), static_cast<T>(in_data[2]), static_cast<T>(in_data[3])} {}

		// Initialize with list of components
		constexpr Quaternion(T _x, T _y, T _z, T _w) noexcept : _data{ _x, _y, _z, _w } {}

		//// access like an array
		T& operator[](size_t idx) {
			return _data[idx];
		}
		const T& operator[](size_t idx) const {
			return _data[idx];
		}

		const T* data() const { return _data; }
		T* data() { return _data; }
    };
#pragma warning(default : 4201)

	// Printing functions
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Quaternion<T>& quat) {
		return os << "<" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ">";
	}

	template<typename T>
	void print(const Quaternion<T>& quat) {
		printf("<%.2f, %.2f, %.2f, %.2f>", quat.x, quat.y, quat.z, quat.w);
	}
	template<typename T>
	void print(const Quaternion<T>& quat, const char* fmt) {
		printf("<");
		for (size_t n = 0; n < 4; n++) {
			printf(fmt, quat[n]);
			if (n != 3)
				printf(", ");
		}
		printf(">");
	}

	/* Scaling operators
	 * typename T needs to implement: *,/
	 * These are all component-wise operations
	 * */
	template<typename T>
	Quaternion<T> operator*(const Quaternion<T>& quat, const T& factor) {
		Quaternion<T> res;
		for (size_t n = 0; n < 4; n++) {
			res[n] = quat[n] * factor;
		}
		return res;
	}

	template<typename T>
	Quaternion<T> operator/(const Quaternion<T>& vec, const T& factor) {
		Quaternion<T> res;
		for (size_t n = 0; n < 4; n++) {
			res[n] = vec[n] / factor;
		}
		return res;
	}

	// Free functions
	template<typename T>
	T length_sq(const Quaternion<T>& quat) {
		return (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) + (quat.w * quat.w);
	}

	template<typename T>
	T length(const Quaternion<T>& quat) {
		return static_cast<T>(sqrt(length_sq(quat)));
	}

	template<typename T>
	Quaternion<T> normalize(const Quaternion<T>& quat) {
		T mag = length(quat);
		return (quat / mag);
	}

	// Weird quaternion functions
	template<typename T>
	Quaternion<T> inverse(const Quaternion<T>& quat) {
		return Quaternion<T>(quat.x, quat.w, quat.z, quat.w);
	}

	template<typename T>
	Quaternion<T> mul(const Quaternion<T>& q1, const Quaternion<T>& q2) {
		// Hamilton operator

		// really bad, but easy implementation that doe ssome vector math using Vector<T,3>s 
		Vector<T, 3> v1(q1.x, q1.y, q1.z);
		Vector<T, 3> v2(q2.x, q2.y, q2.z);
		Vector<T, 3> v = v1*q2.w + v2*q1.w + laml::cross(v1, v2);

		return Quaternion<T>(v.x, v.y, v.z, q1.w * q2.w - laml::dot(v1, v2));
	}
}

#endif // __LAML_QUATERNION_H