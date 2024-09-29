#include <laml/laml.hpp>

#include <iostream>
#include <iomanip>
#include <random>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	// Vector2
	{
		laml::Vector2 v2_default;
		laml::Vector2 v2_components(1.0, 2.0);

		real_t float_array[] = {1.0, 2.0, 3.0, 4.0, 5.0};
		laml::Vector2 v2_array(float_array);

		real_t res1 = v2_components[0];
		real_t res2 = v2_components[1];
		v2_components[1]++;
		try {
			real_t res0 = v2_components[-1];
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}
		try {
			real_t res3 = v2_components[2];
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}

		const real_t* res_const = v2_components.data();
		real_t* res = v2_components.data();

		bool done = true;
	}


	// Vector3
	{
		laml::Vector3 v3_default;
		laml::Vector3 v3_components(1.0, 2.0, 3.0);

		real_t float_array[] = {1.0, 2.0, 3.0, 4.0, 5.0};
		laml::Vector3 v3_array(float_array);

		real_t res1 = v3_components[0];
		real_t res2 = v3_components[1];
		real_t res3 = v3_components[2];
		v3_components[1]++;
		try {
			real_t res = v3_components[-1];
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}
		try {
			real_t res = v3_components[2];
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}

		const real_t* res_const = v3_components.data();
		real_t* res = v3_components.data();

		bool done = true;
	}

	// Vector4
	{
		laml::Vector4 v4_default;
		laml::Vector4 v4_components(1.0, 2.0, 3.0, 4.0);

		real_t float_array[] = {1.0, 2.0, 3.0, 4.0, 5.0};
		laml::Vector4 v3_array(float_array);

		real_t res1 = v4_components[0];
		real_t res2 = v4_components[1];
		real_t res3 = v4_components[2];
		v4_components[1]++;
		try {
			real_t res = v4_components[-1];
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}
		try {
			real_t res = v4_components[2];
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}

		const real_t* res_const = v4_components.data();
		real_t* res = v4_components.data();

		bool done = true;
	}

	laml::Matrix2x2 m2x2;
	laml::Matrix3x3 m3x3;
	laml::Matrix4x4 m4x4;

	m4x4 + m4x4;
	
	laml::Quaternion q;

	return 0;
}