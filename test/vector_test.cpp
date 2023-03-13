#include <gtest/gtest.h>

#include <laml/Vector.hpp>
#include <random>

TEST(Specializations, Vector) {
	using namespace rh;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	float f1 = dis(gen);
	float f2 = dis(gen);

	float f3 = dis(gen);
	float f4 = dis(gen);
	float f5 = dis(gen);

	float f6 = dis(gen);
	float f7 = dis(gen);
	float f8 = dis(gen);
	float f9 = dis(gen);

	laml::Vec2 v2(f1, f2);
	v2.x = v2.y;
	v2.y = f1;
	EXPECT_FLOAT_EQ(v2.x, f2);
	EXPECT_FLOAT_EQ(v2.y, f1);

	laml::Vec3 v3(f3, f4, f5);
	v3.x = v3.y;
	v3.y = v3.z;
	v3.z = f3;
	EXPECT_FLOAT_EQ(v3.x, f4);
	EXPECT_FLOAT_EQ(v3.y, f5);
	EXPECT_FLOAT_EQ(v3.z, f3);

	laml::Vec4 v4(f6, f7, f8, f9);
	v4.x = v4.y;
	v4.y = v4.z;
	v4.z = v4.w;
	v4.w = f6;
	EXPECT_FLOAT_EQ(v4.x, f7);
	EXPECT_FLOAT_EQ(v4.y, f8);
	EXPECT_FLOAT_EQ(v4.z, f9);
	EXPECT_FLOAT_EQ(v4.w, f6);
}

TEST(Acessors, Vector) {
	using namespace rh;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	float f1 = dis(gen);
	float f2 = dis(gen);

	float f3 = dis(gen);
	float f4 = dis(gen);
	float f5 = dis(gen);

	float f6 = dis(gen);
	float f7 = dis(gen);
	float f8 = dis(gen);
	float f9 = dis(gen);

	laml::Vector<float, 2> vec2(f1, f2);
	EXPECT_FLOAT_EQ(vec2[0], f1);
	EXPECT_FLOAT_EQ(vec2[0], vec2._data[0]);
	EXPECT_FLOAT_EQ(vec2[1], f2);
	EXPECT_FLOAT_EQ(vec2[1], vec2._data[1]);

	laml::Vector<float, 3> vec3(f3, f4, f5);
	EXPECT_FLOAT_EQ(vec3[0], f3);
	EXPECT_FLOAT_EQ(vec3[0], vec3._data[0]);
	EXPECT_FLOAT_EQ(vec3[1], f4);
	EXPECT_FLOAT_EQ(vec3[1], vec3._data[1]);
	EXPECT_FLOAT_EQ(vec3[2], f5);
	EXPECT_FLOAT_EQ(vec3[2], vec3._data[2]);

	laml::Vector<float, 4> vec4(f6, f7, f8, f9);
	EXPECT_FLOAT_EQ(vec4[0], f6);
	EXPECT_FLOAT_EQ(vec4[0], vec4._data[0]);
	EXPECT_FLOAT_EQ(vec4[1], f7);
	EXPECT_FLOAT_EQ(vec4[1], vec4._data[1]);
	EXPECT_FLOAT_EQ(vec4[2], f8);
	EXPECT_FLOAT_EQ(vec4[2], vec4._data[2]);
	EXPECT_FLOAT_EQ(vec4[3], f9);
	EXPECT_FLOAT_EQ(vec4[3], vec4._data[3]);
}

// Test the constructors are working as intended
TEST(ConstructorTest, Vector2) {
	using namespace rh;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	float f1 = dis(gen);
	float f2 = dis(gen);
	float f3 = dis(gen);
	float f4 = dis(gen);
	float f5 = dis(gen);

	const size_t N = 2;

	{
		// default constructor
		laml::Vector<float, N> v_default;
		EXPECT_FLOAT_EQ(v_default._data[0], 0.0f);
		EXPECT_FLOAT_EQ(v_default._data[1], 0.0f);

		// Construct with float array
		float data[] = { f1, f2 };
		laml::Vector<float, N> v_floatArr(data);
		EXPECT_FLOAT_EQ(v_floatArr._data[0], f1);
		EXPECT_FLOAT_EQ(v_floatArr._data[1], f2);

		// Initialize with list of components
		laml::Vector<float, N> v_components(f3, f4);
		EXPECT_FLOAT_EQ(v_components._data[0], f3);
		EXPECT_FLOAT_EQ(v_components._data[1], f4);

		// Initialize with single value for all
		laml::Vector<float, N> v_single(f5);
		EXPECT_FLOAT_EQ(v_single._data[0], f5);
		EXPECT_FLOAT_EQ(v_single._data[1], f5);
	}
}
TEST(ConstructorTest, Vector3) {
	using namespace rh;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	float f1 = dis(gen);
	float f2 = dis(gen);
	float f3 = dis(gen);

	float f4 = dis(gen);
	float f5 = dis(gen);
	float f6 = dis(gen);

	float f7 = dis(gen);

	const size_t N = 3;

	{
		// default constructor
		laml::Vector<float, N> v_default;
		EXPECT_FLOAT_EQ(v_default._data[0], 0.0f);
		EXPECT_FLOAT_EQ(v_default._data[1], 0.0f);
		EXPECT_FLOAT_EQ(v_default._data[2], 0.0f);

		// Construct with float array
		float data[] = { f1, f2, f3 };
		laml::Vector<float, N> v_floatArr(data);
		EXPECT_FLOAT_EQ(v_floatArr._data[0], f1);
		EXPECT_FLOAT_EQ(v_floatArr._data[1], f2);
		EXPECT_FLOAT_EQ(v_floatArr._data[2], f3);

		// Initialize with list of components
		laml::Vector<float, N> v_components(f4, f5, f6);
		EXPECT_FLOAT_EQ(v_components._data[0], f4);
		EXPECT_FLOAT_EQ(v_components._data[1], f5);
		EXPECT_FLOAT_EQ(v_components._data[2], f6);

		// Initialize with single value for all
		laml::Vector<float, N> v_single(f7);
		EXPECT_FLOAT_EQ(v_single._data[0], f7);
		EXPECT_FLOAT_EQ(v_single._data[1], f7);
		EXPECT_FLOAT_EQ(v_single._data[2], f7);
	}
}

TEST(ConstructorTest, Vector4) {
	using namespace rh;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis(-100000.0, 100000.0);
	float f1 = dis(gen);
	float f2 = dis(gen);
	float f3 = dis(gen);
	float f4 = dis(gen);

	float f5 = dis(gen);
	float f6 = dis(gen);
	float f7 = dis(gen);
	float f8 = dis(gen);

	float f9 = dis(gen);

	const size_t N = 4;

	{
		// default constructor
		laml::Vector<float, N> v_default;
		EXPECT_FLOAT_EQ(v_default._data[0], 0.0f);
		EXPECT_FLOAT_EQ(v_default._data[1], 0.0f);
		EXPECT_FLOAT_EQ(v_default._data[2], 0.0f);
		EXPECT_FLOAT_EQ(v_default._data[3], 0.0f);

		// Construct with float array
		float data[] = { f1, f2, f3, f4 };
		laml::Vector<float, N> v_floatArr(data);
		EXPECT_FLOAT_EQ(v_floatArr._data[0], f1);
		EXPECT_FLOAT_EQ(v_floatArr._data[1], f2);
		EXPECT_FLOAT_EQ(v_floatArr._data[2], f3);
		EXPECT_FLOAT_EQ(v_floatArr._data[3], f4);

		// Initialize with list of components
		laml::Vector<float, N> v_components(f5, f6, f7, f8);
		EXPECT_FLOAT_EQ(v_components._data[0], f5);
		EXPECT_FLOAT_EQ(v_components._data[1], f6);
		EXPECT_FLOAT_EQ(v_components._data[2], f7);
		EXPECT_FLOAT_EQ(v_components._data[3], f8);

		// Initialize with single value for all
		laml::Vector<float, N> v_single(f9);
		EXPECT_FLOAT_EQ(v_single._data[0], f9);
		EXPECT_FLOAT_EQ(v_single._data[1], f9);
		EXPECT_FLOAT_EQ(v_single._data[2], f9);
		EXPECT_FLOAT_EQ(v_single._data[3], f9);
	}
}