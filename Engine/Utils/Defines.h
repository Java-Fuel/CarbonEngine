
#ifndef DEFINES_H
#define DEFINES_H

// Integer Defines
typedef long i64;
typedef int i32;
typedef short i16;
typedef char i8;

// Byte Defines
typedef bool b8;

// Float Defines
typedef float f32;
typedef double f64;

// Platform Definitions
#define WIN32 1

#if defined(WIN32) || defined(__WIN32__) || defined(__WIN32)
#define ENGINE_PLATFORM WIN32
#endif


#endif