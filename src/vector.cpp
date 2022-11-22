#include <laml/vector.hpp>

namespace rh::laml {

	// vec2
	vec2::vec2() : x(0), y(0) {
	}

	vec2::vec2(scalar _x, scalar _y) : x(_x), y(_y) {
	}

	vec2::vec2(const vec2& other) {
		this->x = other.x;
		this->y = other.y;
	}

	// pointer to underlying data
	const scalar* vec2::ptr() const {
		return &x;
	}

	// access like an array
	scalar& vec2::operator[](size_t idx) {
		return *(&x + idx);
	}

	const scalar& vec2::operator[](size_t idx) const {
		return *(&x + idx);
	}


	// vec3
	vec3::vec3() : x(0), y(0), z(0) {
	}

	vec3::vec3(scalar _x, scalar _y, scalar _z) : x(_x), y(_y), z(_z) {
	}

	vec3::vec3(const vec3& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	// pointer to underlying data
	const scalar* vec3::ptr() const {
		return &x;
	}

	// access like an array
	scalar& vec3::operator[](size_t idx) {
		return *(&x + idx);
	}

	const scalar& vec3::operator[](size_t idx) const {
		return *(&x + idx);
	}

	// vec4
	vec4::vec4() : x(0), y(0), z(0), w(0) {
	}

	vec4::vec4(scalar _x, scalar _y, scalar _z, scalar _w) : x(_x), y(_y), z(_z), w(_w) {
	}

	vec4::vec4(const vec4& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	// pointer to underlying data
	const scalar* vec4::ptr() const {
		return &x;
	}

	// access like an array
	scalar& vec4::operator[](size_t idx) {
		return *(&x + idx);
	}

	const scalar& vec4::operator[](size_t idx) const {
		return *(&x + idx);
	}
}