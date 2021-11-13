#ifndef CONFIG_H
#define CONFIG_H

#include "constants.h"

#define USE_SPRITE
#define USE_GENERIC_COLLISION

#ifdef __GNUC__

#define     USE_C_DDA
#define     USE_C_PREDRAW
#define     USE_C_TOTO
#define     USE_C_DRAWWALLS
#define     USE_C_RAYCAST
#define     USE_C_VIEWPORT
#define     USE_C_PROCESS_POINT
#define     USE_C_ZBUFFWALLS
#define     USE_C_EXP
#define     USE_C_3TRIGO
#define     USE_C_DISTOFFSETSLICES
#define     USE_C_GENERIC_COLLISION
#define     USE_C_COLORTEXEL
#define     USE_C_DICHOBUF
#define     USE_C_SPRITE

#else

#undef     USE_C_DDA
#undef     USE_C_PREDRAW
#undef     USE_C_TOTO
#undef     USE_C_DRAWWALLS
#undef     USE_C_RAYCAST
#undef     USE_C_VIEWPORT
#undef     USE_C_PROCESS_POINT
#undef     USE_C_ZBUFFWALLS
#undef     USE_C_EXP
#undef     USE_C_DISTOFFSETSLICES
#define    USE_ASM_LOGTRIGO
#undef     USE_C_3TRIGO
#undef     USE_C_GENERIC_COLLISION
#undef     USE_C_COLORTEXEL
#undef     USE_C_DICHOBUF
#undef     USE_C_SPRITE
#endif

#endif // CONFIG_H