#include <laml/laml.hpp>

#include <stdio.h>
#include<iostream>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	printf("laml version %s\n\n", laml::getVersionString());

	laml::Vec2 v1(0.0f, 3.5f);
	laml::Vec2 v2(2.5f, -1.0f);
	laml::Vec3 v3(1.0f, 2.0f, -2.5f);
	laml::Vec3 v4(2.5f, -1.0f, 0.5f);

	// Operators
	std::cout << (v1 + v2) << " = " << v1 << " + " << v2 << std::endl;
	std::cout << (v1 - v2) << " = " << v1 << " - " << v2 << std::endl;
	std::cout << (v1 * v2) << " = " << v1 << " * " << v2 << std::endl;
	std::cout << (v1 / v2) << " = " << v1 << " / " << v2 << std::endl;
	std::cout << std::endl;

	// Free functions
	std::cout << dot(v1, v2)   << " = " << v1 << " * " << v2 << std::endl;
	std::cout << cross(v3, v4) << " = " << v3 << " x " << v4 << std::endl;
	
	std::cout << length_sq(v3) << " = " << "sum{" << v3 << "," << v3 << "}" << std::endl;
	std::cout << length(v3)    << " = " << "sqrt_sum{" << v3 << "," << v3 << "}" << std::endl;
	std::cout << normalize(v3) << " = " << "||" << v3 << "||" << std::endl;
	std::cout << std::endl;
	
	
	std::cout << v3 << std::endl;
	v3 = normalize(v3);
	std::cout << v3 << std::endl;
	std::cout << std::endl;
	
	// min/max/clamp/lerp
	laml::Vec4 v5(2.5f, -2.25f, 7.5f, 7.5001f);
	std::cout << v5 << std::endl;
	std::cout << "min(v5) = " << min(v5) << std::endl;
	std::cout << "max(v5) = " << max(v5) << std::endl;
	std::cout << "abs(v5) = " << abs(v5) << std::endl;
	std::cout << std::endl;
	
	std::cout << "v1 = " << v1 << std::endl;
	std::cout << "v2 = " << v2 << std::endl;
	for (float f = 0.0f; f < 1.05f; f += 0.1f) {
		printf(" [%.2f] = ", f); 
		std::cout << lerp(v1, v2, f) << std::endl;
	}
	printf("Clamped between 1.0 and 2.0\n");
	for (float f = 0.0f; f < 1.05f; f += 0.1f) {
		printf(" [%.2f] = ", f); 
		std::cout << clamp(lerp(v1, v2, f), 1.0f, 2.0f) << std::endl;
	}
	std::cout << std::endl;
	
	// initialize with float array
	float data[] = { 0.12f, 12.31f, 8.3f, 1.31f, 131.2f, 0.31f, 2.83f, 18.9f, 7.31f };
	laml::Vector<float, 9> data_vec(data);
	auto _data = data_vec.data();// get underlying data
	for (size_t n = 0; n < data_vec.num_elements(); n++) {
		printf("[%7.3f] -> [%7.3f]|[%7.3f]\n", data[n], (float)data_vec[n], (float)_data[n]);
	}
	std::cout << std::endl;
	
	std::cout << "v3 = " << v3 << std::endl;
	std::cout << "v4 = " << v4 << std::endl;
	std::cout << "v4 > v3 = " << (v4 > v3) << std::endl;
	std::cout << std::endl;
	
	printf("any(v4 > v3) = %s", any(v4 > v3) ? "true" : "false");
	printf("all(v4 > v3) = %s", all(v4 > v3) ? "true" : "false");
	std::cout << std::endl;
	
	laml::Vector<int, 5> iv1(1, 2, 3, 4, 5);
	laml::Vector<int, 5> iv2(4, 2, 1, 3, 5);
	std::cout << "iv1 = " << iv1 << std::endl;
	std::cout << "iv2 = " << iv2 << std::endl;

	return 0;
}