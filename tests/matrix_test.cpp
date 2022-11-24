#include <gtest/gtest.h>

#include <laml/matrix_base.hpp>
#include <random>

#include "test_config.h"

TEST(Constructors, Matrix2) {
	/* Constructors:
	* default
	* single-value
	*/

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	for (size_t N = 0; N < NUM_LOOPS; N++) {
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

TEST(Constructors, Matrix3) {
	/* Constructors:
	* default
	* single-value
	*/

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	for (size_t N = 0; N < NUM_LOOPS; N++) {
		float f1 = dis(gen);
		float f2 = dis(gen);
		float f3 = dis(gen);
		float f4 = dis(gen);
		float f5 = dis(gen);
		float f6 = dis(gen);
		float f7 = dis(gen);
		float f8 = dis(gen);
		float f9 = dis(gen);

		float g1 = dis(gen);
		float g2 = dis(gen);
		float g3 = dis(gen);
		float g4 = dis(gen);
		float g5 = dis(gen);
		float g6 = dis(gen);
		float g7 = dis(gen);
		float g8 = dis(gen);
		float g9 = dis(gen);

		rh::laml::Matrix<float, 3, 3> mat1;
		mat1[0][0] = f1;
		mat1[0][1] = f2;
		mat1[0][2] = f3;
		mat1[1][0] = f4;
		mat1[1][1] = f5;
		mat1[1][2] = f6;
		mat1[2][0] = f7;
		mat1[2][1] = f8;
		mat1[2][2] = f9;

		rh::laml::Matrix<float, 3, 3> mat2;
		mat2[0][0] = g1;
		mat2[0][1] = g2;
		mat2[0][2] = g3;
		mat2[1][0] = g4;
		mat2[1][1] = g5;
		mat2[1][2] = g6;
		mat2[2][0] = g7;
		mat2[2][1] = g8;
		mat2[2][2] = g9;

		rh::laml::Matrix<float, 3, 3> mat3 = rh::laml::mul(mat1, mat2);

		EXPECT_FLOAT_EQ(mat3[0][0], mat1[0][0] * mat2[0][0] + mat1[1][0] * mat2[0][1] + mat1[2][0] * mat2[0][2]); // col 1
		EXPECT_FLOAT_EQ(mat3[0][1], mat1[0][1] * mat2[0][0] + mat1[1][1] * mat2[0][1] + mat1[2][1] * mat2[0][2]);
		EXPECT_FLOAT_EQ(mat3[0][2], mat1[0][2] * mat2[0][0] + mat1[1][2] * mat2[0][1] + mat1[2][2] * mat2[0][2]);

		EXPECT_FLOAT_EQ(mat3[1][0], mat1[0][0] * mat2[1][0] + mat1[1][0] * mat2[1][1] + mat1[2][0] * mat2[1][2]); // col 2
		EXPECT_FLOAT_EQ(mat3[1][1], mat1[0][1] * mat2[1][0] + mat1[1][1] * mat2[1][1] + mat1[2][1] * mat2[1][2]);
		EXPECT_FLOAT_EQ(mat3[1][2], mat1[0][2] * mat2[1][0] + mat1[1][2] * mat2[1][1] + mat1[2][2] * mat2[1][2]);

		EXPECT_FLOAT_EQ(mat3[2][0], mat1[0][0] * mat2[2][0] + mat1[1][0] * mat2[2][1] + mat1[2][0] * mat2[2][2]); // col 3
		EXPECT_FLOAT_EQ(mat3[2][1], mat1[0][1] * mat2[2][0] + mat1[1][1] * mat2[2][1] + mat1[2][1] * mat2[2][2]);
		EXPECT_FLOAT_EQ(mat3[2][2], mat1[0][2] * mat2[2][0] + mat1[1][2] * mat2[2][1] + mat1[2][2] * mat2[2][2]);
	}
}