#include <laml/laml.hpp>
#include <laml/Matrix2.hpp>

#include<iostream>
#include <iomanip>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	laml::Mat2 mat1; // zeros
	mat1[0][0] = 1.7f;
	mat1[0][1] = 4.1f;
	mat1[1][0] = 9.8f;
	mat1[1][1] = 3.7f;
	laml::Mat2 mat2(1.5f); // diag
	laml::Mat3 mat3;
	mat3[0] = laml::Vec3(1.0f, 2.0f, 3.0f); // columns
	mat3[1] = laml::Vec3(4.0f, 5.0f, 6.0f);
	mat3[2] = laml::Vec3(7.0f, 8.0f, 9.0f);

	// component-wise operators
	std::cout << "component-wise operators" << std::endl;
	std::cout << (mat1 + mat2) << " = " << mat1 << " + " << mat2 << std::endl;
	std::cout << (mat1 - mat2) << " = " << mat1 << " - " << mat2 << std::endl;
	std::cout << (mat1 * mat2) << " = " << mat1 << " x " << mat2 << std::endl;
	std::cout << (mat1 / mat2) << " = " << mat1 << " / " << mat2 << std::endl;
	std::cout << std::endl;

	// scaling operatios
	std::cout << "mat3 = " << mat3 << std::endl;
	std::cout << mat3 * 1.5f << " = " << mat3 << " x " << 1.5f << std::endl;
	std::cout << mat3 / 2.0f << " = " << mat3 << " / " << 2.0f << std::endl;
	std::cout << std::endl;

	// matrix multiplication
	std::cout << "mat1 = " << mat1 << std::endl;
	std::cout << "mat2 = " << mat2 << std::endl;
	std::cout << laml::mul(mat1, mat2) << " = " << mat1 << " * " << mat2 << std::endl;
	std::cout << std::endl;

	// weird mul
	laml::Matrix<float, 2, 2> rot;
	rot[0][0] = 0;
	rot[0][1] = -1;
	rot[1][0] = 1;
	rot[1][1] = 0;
	laml::Matrix<float, 2, 1> vec;
	vec[0][0] = 2.5f;
	vec[0][1] = -1.0f;

	std::cout << mul(rot, vec) << " = " << rot << " * " << vec << std::endl;
	std::cout << std::endl;

	std::cout << mat1 << std::endl;
	std::cout << mat2 << std::endl;
	std::cout << laml::mul(mat1, mat2) << std::endl;
	std::cout << std::endl;

	laml::Mat2 mat1_alt(1.7f, 4.1f, 9.8f, 3.7f); // zeros
	std::cout << mat1 << " = " << mat1_alt << std::endl;
	std::cout << std::endl;
	mat1_alt.num_rows();

	return 0;
}