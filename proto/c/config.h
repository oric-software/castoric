#ifndef CONFIG_H
#define CONFIG_H

#include "constants.h"

#undef USE_SPRITE

#ifdef __GNUC__

#define     USE_C_DDA
#define     USE_C_PREDRAW
#define     USE_C_TOTO
#define     USE_C_DRAWWALLS
#define     USE_C_RAYCAST
#define     USE_C_VIEWPORT

#else

#undef     USE_C_DDA
#undef     USE_C_PREDRAW
#undef     USE_C_TOTO
#undef     USE_C_DRAWWALLS
#undef     USE_C_RAYCAST
#undef     USE_C_VIEWPORT
#endif

#endif // CONFIG_H