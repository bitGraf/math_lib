#include <laml/laml.hpp>

#include <stdio.h>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	printf("laml version %s\n\n", laml::getVersionString());

	laml::Vec2 v2(2.0f, 3.5f);
	laml::Vec3 v3(1.0f, 2.0f, 3.0f);
	laml::Vec4 v4(1.0f, 2.0f, 3.0f, 4.0f);

	printf("(v2[0],v2[1]) = (%.2f %.2f)\n", v2[0], v2[1]);
	printf("(v3[0],v3[1],v3[2]) = (%.2f %.2f,%.2f)\n", v3[0], v3[1], v3[2]);
	printf("(v4[0],v4[1],v4[2],v4[3]) = (%.2f %.2f,%.2f,%.2f)\n", v3[0], v3[1], v3[2],v4[2]);

	printf("\n");

	printf("(v2.x,v2.y) = (%.2f %.2f)\n", v2.x, v2.y);
	printf("(v3.x,v3.y,v3.z) = (%.2f %.2f,%.2f)\n", v3.x, v3.y, v3.z);
	printf("(v4.x,v4.y,v4.z,v4.w) = (%.2f %.2f,%.2f,%.2f)\n", v4.x, v4.y, v4.z, v4.w);

	//system("pause");

	return 0;
}