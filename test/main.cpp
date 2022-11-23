#include <laml/laml.hpp>

#include <stdio.h>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

void print_vec(const laml::Vec2& vec) { printf("(%5.2f,%5.2f)", vec[0], vec[1]); }
void print_vec(const laml::Vec3& vec) { printf("(%5.1f,%5.1f,%5.1f)", vec[0], vec[1], vec[2]); }
void print_vec(const laml::Vec4& vec) { printf("(%5.1f,%5.1f,%5.1f,%5.1f)", vec[0], vec[1], vec[2], vec[3]); }
void print(float f) { printf("(%5.2f)", f); }

#define PLUS   printf(" + ");
#define MINUS  printf(" - ");
#define TIMES  printf(" x ");
#define DIVIDE printf(" / ");
#define EQUALS printf(" = ");
#define DOT printf(" * ");
#define CROSS printf(" X ");
#define NL printf("\n");

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	printf("laml version %s\n\n", laml::getVersionString());

	laml::Vec2 v1(0.0f, 3.5f);
	laml::Vec2 v2(2.5f, -1.0f);
	laml::Vec3 v3(1.0f, 2.0f, -2.5f);
	laml::Vec3 v4(2.5f, -1.0f, 0.5f);

	// Operators
	print_vec(v1 + v2); EQUALS print_vec(v1); PLUS  print_vec(v2); NL;
	print_vec(v1 - v2); EQUALS print_vec(v1); MINUS print_vec(v2); NL;
	print_vec(v1 * v2); EQUALS print_vec(v1); TIMES  print_vec(v2); NL;
	print_vec(v1 / v2); EQUALS print_vec(v1); DIVIDE print_vec(v2); NL;
	NL;

	// Free functions
	print(dot(v1, v2)); EQUALS print_vec(v1); DOT    print_vec(v2); NL;
	print_vec(cross(v3, v4)); EQUALS print_vec(v3); CROSS print_vec(v4); NL;
	print(length_sq(v3)); EQUALS printf("sum: "); print_vec(v3); DOT print_vec(v3); NL;
	print(length(v3)); EQUALS printf("sqsum: "); print_vec(v3); DOT print_vec(v3); NL;
	print_vec(normalize(v3)); EQUALS printf("|"); print_vec(v3); printf("|");

	NL;
	print_vec(v3); NL;
	v3 = normalize(v3);
	print_vec(v3); NL;
	NL;

	// min/max/clamp/lerp
	laml::Vec4 v5(2.5f, -2.25f, 7.5f, 7.5001f);
	print_vec(v5); NL;
	printf("min(v5) = %f\n", min(v5));
	printf("max(v5) = %f\n", max(v5));
	printf("abs(v5) = "); print_vec(abs(v5)); NL;
	NL;

	printf("v1 = "); print_vec(v1); NL;
	printf("v2 = "); print_vec(v2); NL;
	for (float f = 0.0f; f < 1.05f; f += 0.1f) {
		printf(" [%.2f] = ", f); print_vec(lerp(v1, v2, f)); NL;
	}
	printf("Clamped between 1.0 and 2.0\n");
	for (float f = 0.0f; f < 1.05f; f += 0.1f) {
		printf(" [%.2f] = ", f); print_vec(clamp(lerp(v1, v2, f), 1.0f, 2.0f)); NL;
	}
	NL;

	// initialize with float array
	float data[] = { 0.12f, 12.31f, 8.3f, 1.31f, 131.2f, 0.31f, 2.83f, 18.9f, 7.31f };
	laml::Vector<float, 9> data_vec(data);
	auto _data = data_vec.data();// get underlying data
	for (size_t n = 0; n < data_vec.num_elements(); n++) {
		printf("[%7.3f] -> [%7.3f]|[%7.3f]\n", data[n], (float)data_vec[n], (float)_data[n]);
	}
	NL;

	auto res = v4 > v3;
	printf("v3 = "); print_vec(v3); NL;
	printf("v4 = "); print_vec(v4); NL;
	printf("v4 > v3 = [");
	for (size_t n = 0; n < res.num_elements(); n++) {
		printf("%s ", res[n] ? "true" : "false");
	}
	printf("]\n");

	printf("any(v4 > v3) = %s", any(res) ? "true" : "false"); NL;
	printf("all(v4 > v3) = %s", all(res) ? "true" : "false"); NL;

	//system("pause");

	return 0;
}