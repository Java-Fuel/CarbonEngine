
#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>


// Integer Defines
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

// Unsigned Integer Defines
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

// Byte Defines
typedef uint8_t b8; // Unsigned

// Float Defines
typedef float f32;
typedef double f64;

// Platform Definitions
#define WIN32 1

#if defined(WIN32) || defined(__WIN32__) || defined(__WIN32)
#define ENGINE_PLATFORM WIN32
#endif


#endif