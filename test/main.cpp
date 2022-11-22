#include <laml/laml.hpp>

#include <iostream>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	printf("laml version %s\n", laml::getVersionString());

	laml::vec2 v1{ 1.0f, 2.0f };
	laml::vec3 v2{ 1.0f, 2.0f, 3.0f };
	laml::vec4 v3{ 1.0f, 2.0f, 3.0f, 4.0f };
	printf("v1 = (%.2f %.2f)\n", v1.x, v1.y);
	printf("v2 = (%.2f %.2f %.2f)\n", v2.x, v2.y, v2.z);
	printf("v3 = (%.2f %.2f %.2f %.2f)\n", v3.x, v3.y, v3.y, v3.w);

	system("pause");

	return 0;
}