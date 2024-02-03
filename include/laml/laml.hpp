#ifndef __LAML_H
#define __LAML_H

// include all the standard headers anyone would need
#ifdef MADE_WITH_CMAKE
    #include <laml.config.h>
#endif

#include <laml/Data_types.hpp>

#include <laml/Vector.hpp>

#include <laml/Matrix_base.hpp>
#include <laml/Matrix2.hpp>
#include <laml/Matrix3.hpp>
#include <laml/Matrix4.hpp>

#include <laml/Quaternion.hpp>

#include <laml/Constants.hpp>
#include <laml/Transform.hpp>

#include <laml/Functions.hpp>

#endif //__LAML_H