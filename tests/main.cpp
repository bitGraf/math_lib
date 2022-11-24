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

	laml::Mat2 mat2(6.0f, 5.0f, 1.0f, 10.0f);
	laml::Mat3 mat3(6.0f, 8.0f, 9.0f, 2.0f, 6.0f, 6.0f, 4.0f, 10.0f, 1.0f);
	laml::Mat4 mat4(2.0f, 7.0f, 8.0f, 3.0f, 2.0f, 8.0f, 9.0f, 7.0f, 8.0f, 3.0f, 6.0f, 4.0f, 5.0f, 2.0f, 7.0f, 6.0f);

	printf("mat2 = ");
	print(mat2, "%.1f");
	printf("\nmat3 = ");
	print(mat3, "%.1f");
	printf("\nmat4 = ");
	print(mat4, "%.1f");
	printf("\n");

	// calc inverses
	printf("det(mat2) = ");
	std::cout<<(laml::det(mat2));
	printf("\ndet(mat3) = ");
	std::cout << (laml::det(mat3));
	printf("\ndet(mat4) = ");
	std::cout << (laml::det(mat4));
	printf("\n");
	printf("\n");

	// check inverses are correct!
	print(laml::mul(laml::inverse(mat2), mat2), "%.0f"); printf("\n");
	print(laml::mul(laml::inverse(mat3), mat3), "%.0f"); printf("\n");
	print(laml::mul(laml::inverse(mat4), mat4), "%.0f"); printf("\n");
	printf("\n");

	laml::Matrix<float, 2, 2> min_mat = laml::minor(mat3, 2, 2);
	std::cout << mat3 << std::endl;
	std::cout << min_mat << std::endl;
	printf("\n");

	std::cout << "Testing:\n";
	laml::Matrix<float, 3, 3> mtest(1.0f, 0.0f, -1.0f, 3.0f, 5.0f, 3.0f, 2.0f, 1.0f, 0.0f);
	std::cout << laml::inverse(mtest) << " = inv(" << mtest << ")" << std::endl;
	std::cout << std::endl;

	std::cout << "Testing 4x4 inv:\n";
	laml::Matrix<float, 4, 4> A(1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
	laml::Matrix<float, 4, 4> A_inv = laml::inverse(A);
	std::cout << "A      = " << A << std::endl;
	std::cout << "inv(A) = " << A_inv << std::endl;
	std::cout << std::endl;

	return 0;
}