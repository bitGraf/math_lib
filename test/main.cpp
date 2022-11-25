#include <laml/laml.hpp>

#include<iostream>
#include <iomanip>
#include <random>

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) x
#endif

using namespace rh;

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	laml::Mat4 ortho_proj;
	laml::transform::create_projection_orthographic(ortho_proj, -1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 10.0f);
	laml::Mat4 persp_proj;
	laml::transform::create_projection_perspective(persp_proj, 50.0f, 1.0f, 0.01f, 10.0f);

	std::cout << ortho_proj << std::endl;
	std::cout << persp_proj << std::endl;

	return 0;
}