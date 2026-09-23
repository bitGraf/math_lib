#ifndef __LAML_DATA_TYPES_H
#define __LAML_DATA_TYPES_H

#include <stdint.h>
#include <stddef.h>

/* Delete constructors/copy functions explicitly
 * ~T()						destructor
 * T(const T&)				copy constructor
 * T& operator=(const T&)	copy assignment operator
 * T(T&&)					move constructor
 * T& operator=(T&&)		move assignment operator
 */
#define LAML_DELETE_CTRS(class_name) \
~class_name() = delete; \
class_name(const class_name&) = delete; \
class_name& operator=(const class_name&) = delete; \
class_name(class_name&&) = delete; \
class_name& operator=(class_name&&) = delete;

#ifndef LAML_TYPES
#define LAML_TYPES
    typedef int8_t  int8;
    typedef int16_t int16;
    typedef int32_t int32;
    typedef int64_t int64;
    
    typedef uint8_t  uint8;
    typedef uint16_t uint16;
    typedef uint32_t uint32;
    typedef uint64_t uint64;
    
    typedef float  f32;
    typedef double f64;

	typedef f32 real_t;
#endif // #ifdef LAML_TYPES

#endif // __LAML_DATA_TYPES_H
