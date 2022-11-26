#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include <laml/laml.hpp>

namespace rh::laml::transform {

	template<typename T>
	void create_projection_orthographic(Matrix<T, 4, 4>& mat, T left, T right, T bottom, T top, T znear, T zfar) {
		laml::fill(mat, static_cast<T>(0.0));

		const T one = static_cast<T>(1.0);
		const T two = static_cast<T>(2.0);

		mat[0][0] = two / (right - left);
		mat[1][1] = two / (top - bottom);
		mat[2][2] = two / (zfar - znear);

		mat[3][0] = -(right + left) / (right - left);
		mat[3][1] = -(top + bottom) / (top - bottom);
		mat[3][2] = -(zfar + znear) / (zfar - znear);

		mat[3][3] = one;
	}

	template<typename T>
	void create_projection_perspective(Matrix<T, 4, 4>& mat, T vertical_fov, T aspect_ratio, T znear, T zfar) {
		laml::fill(mat, static_cast<T>(0.0));

		const T tan_half = static_cast<T>(tan(vertical_fov * constants::deg2rad / 2.0));
		const T one = static_cast<T>(1.0);
		const T two = static_cast<T>(2.0);

		mat[0][0] = one / (aspect_ratio * tan_half);
		mat[1][1] = one / tan_half;
		mat[2][2] = -(zfar + znear) / (zfar - znear);
		mat[2][3] = -one;
		mat[3][2] = -two * zfar * znear / (zfar - znear);
	}

	template<typename T, size_t size>
	Vector<T, size> transform_point(const Matrix<T, size, size>& mat, const Vector<T, size> vec) {
		// DUMB DUMB DUMB, god I hate this x.x
		static_assert(false, "fix this immediately");
		Matrix<T, size, 1> vec_m;
		for (size_t i = 0; i < size; i++) {
			vec_m[0][i] = vec[i];
		}
		Matrix<T,size,1> res_m = mul(mat, vec_m);

		Vector<T, size> res;
		for (size_t i = 0; i < size; i++) {
			res[i] = res_m[0][i];
		}
		return res;
	}
}

#endif