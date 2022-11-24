#include <laml/laml.hpp>

#include<iostream>
#include <iomanip>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	std::cout << "Laml version string: " << laml::GetVersionString() << std::endl;
	std::cout << " Version Major: " << laml::GetVersionMajor() << std::endl;
	std::cout << " Version Minor: " << laml::GetVersionMinor() << std::endl;
	std::cout << " Version Patch: " << laml::GetVersionPatch() << std::endl;
	std::cout << std::endl;

	std::cout << "2x2 case:" << std::endl;
	laml::Mat2 mat2(6.0f, 5.0f, 1.0f, 10.0f);
	float d2 = laml::det(mat2);
	std::cout << std::endl;

	std::cout << "3x3 case:" << std::endl;
	laml::Mat3 mat3(6.0f, 8.0f, 9.0f, 2.0f, 6.0f, 6.0f, 4.0f, 10.0f, 1.0f);
	float d3 = laml::det(mat3);
	std::cout << std::endl;

	printf("det(mat2) = %.3f\n", d2);
	printf("det(mat3) = %.3f\n", d3);

	laml::Matrix<float, 4, 4> mm;
	float d4 = laml::det(mm);
	printf("det(mat4) = %.3f\n", d4);

	return 0;
}