#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "SDL_gpu.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Basic numerical types START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// unsigned integers
typedef uint8_t u8;     // 1-byte unsigned integer
typedef uint16_t u16;   // 2-byte unsigned integer
typedef uint32_t u32;   // 4-byte unsigned integer
typedef uint64_t u64;   // 8-byte unsigned integer
// signed integers
typedef int8_t s8;      // 1-byte signed integer
typedef int16_t s16;    // 2-byte signed integer
typedef int32_t s32;    // 4-byte signed integer
typedef int64_t s64;    // 8-byte signed integer
// float & double
typedef float_t f32;    // 4-byte floating point number
typedef double_t f64;   // 8-byte floating point number

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Basic numerical types END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#include "defs.h"
#include "enums.h"
#include "structs.h"
