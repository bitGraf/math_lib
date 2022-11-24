#include <gtest/gtest.h>

#include <laml/matrix.hpp>
#include <random>

TEST(Constructors, Matrix) {
	/* Constructors:
	* default
	* single-value
	*/

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	for (size_t N = 0; N < 1000; N++) {
		float f1 = dis(gen);
		float f2 = dis(gen);
		float f3 = dis(gen);
		float f4 = dis(gen);
		float f5 = dis(gen);
		float f6 = dis(gen);
		float f7 = dis(gen);
		float f8 = dis(gen);

		rh::laml::Matrix<float, 2, 2> mat1;
		mat1[0][0] = f1;
		mat1[0][1] = f2;
		mat1[1][0] = f3;
		mat1[1][1] = f4;

		rh::laml::Matrix<float, 2, 2> mat2;
		mat2[0][0] = f5;
		mat2[0][1] = f6;
		mat2[1][0] = f7;
		mat2[1][1] = f8;

		rh::laml::Matrix<float, 2, 2> mat3 = rh::laml::mul(mat1, mat2);
		
		EXPECT_FLOAT_EQ(mat3[0][0], mat1[0][0] * mat2[0][0] + mat1[1][0] * mat2[0][1]);
		EXPECT_FLOAT_EQ(mat3[0][1], mat1[0][1] * mat2[0][0] + mat1[1][1] * mat2[0][1]);

		EXPECT_FLOAT_EQ(mat3[1][0], mat1[0][0] * mat2[1][0] + mat1[1][0] * mat2[1][1]);
		EXPECT_FLOAT_EQ(mat3[1][1], mat1[0][1] * mat2[1][0] + mat1[1][1] * mat2[1][1]);
	}
}