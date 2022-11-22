#ifndef __LAML_VECTOR_H
#define __LAML_VECTOR_H

//#include <laml.config.h>
#include <laml/data_types.hpp>

namespace rh::laml {

	struct vec2;
	struct vec3;
	struct vec4;

	struct vec2 { 
		vec2();
		vec2(scalar _x, scalar _y);
		vec2(const vec2&); // copy constructor
		vec2(vec2&&) = delete; // move constructor
		~vec2() = default;


		// pointer to underlying data
		const scalar* ptr() const;

		// access like an array
		scalar& operator[](size_t idx);
		const scalar& operator[](size_t idx) const;

		//friend ::std::ostream& operator<<(std::ostream& os, const vec2& v);

		scalar x, y; 
	};

	struct vec3 {
		vec3();
		vec3(scalar _x, scalar _y, scalar _z);
		vec3(const vec3&); // copy constructor
		vec3(vec3&&) = delete; // move constructor
		~vec3() = default;


		// pointer to underlying data
		const scalar* ptr() const;

		// access like an array
		scalar& operator[](size_t idx);
		const scalar& operator[](size_t idx) const;

		//friend ::std::ostream& operator<<(std::ostream& os, const vec3& v);

		scalar x, y, z;
	};

	struct vec4 {
		vec4();
		vec4(scalar _x, scalar _y, scalar _z, scalar _w);
		vec4(const vec4&); // copy constructor
		vec4(vec4&&) = delete; // move constructor
		~vec4() = default;


		// pointer to underlying data
		const scalar* ptr() const;

		// access like an array
		scalar& operator[](size_t idx);
		const scalar& operator[](size_t idx) const;

		//friend ::std::ostream& operator<<(std::ostream& os, const vec4& v);

		scalar x, y, z, w;
	};

}

#endif // __LAML_VECTOR_H