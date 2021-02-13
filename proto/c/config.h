#ifndef CONFIG_H
#define CONFIG_H

#include "constants.h"

#ifdef __GNUC__

#define     USE_C_DDA
#define     USE_C_PREDRAW
#define     USE_C_TOTO
#define     USE_C_DRAWWALLS

#else

#undef     USE_C_DDA
#undef     USE_C_PREDRAW
#undef     USE_C_TOTO
#define      USE_C_DRAWWALLS
#endif

#endif // CONFIG_H