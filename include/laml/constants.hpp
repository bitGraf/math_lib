#ifndef __LAML_CONSTANTS_H
#define __LAML_CONSTANTS_H

#include <laml.config.h>

namespace rh::laml {

	namespace constants {
#ifdef LAML_HIGH_PRECISION
		const scalar pi = 3.14159265358979323846;
		const scalar deg2rad = pi / 180.0;
		const scalar rad2deg = 180.0 / pi;
#else
		const scalar pi = 3.14159265358979323846f;
		const scalar deg2rad = pi / 180.0f;
		const scalar rad2deg = 180.0f / pi;
#endif
	}
}

#endif