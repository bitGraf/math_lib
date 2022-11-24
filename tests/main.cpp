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

	// matrix 3x3 specializations
	laml::Matrix<float, 3, 3> mat32(1.0f);
	std::cout << "eye(3) = " << mat32 << std::endl;
	std::cout << mat32 * mat32 << std::endl;
	std::cout << laml::mul(mat32, mat32) << std::endl;

	// inverse test
	laml::Matrix<float, 3, 3> A(2.f, -3.f, -2.f, 3.f, -3.f, 1.f, 4.f, -2.f, -1.f);
	laml::Matrix<float, 3, 3> inv_A(5.f, 1.f, -9.f, 7.f, 6.f, -8.f, 6.f, -8.f, 3.f);
	inv_A = inv_A / (-23.0f);
	std::cout << std::setprecision(1);
	std::cout << laml::mul(A, inv_A) << std::endl;
	std::cout << laml::mul(inv_A, A) << std::endl;

	printf("new print functions:\n");
	print(A); printf("\n");
	print(A, "%.1f"); printf("\n");
	print(A[2]); printf("\n");

	return 0;
}