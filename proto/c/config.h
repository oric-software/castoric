#ifndef CONFIG_H
#define CONFIG_H


#ifdef __GNUC__

#define     USE_C_DDA
#define     USE_C_PREDRAW
#define     USE_C_TOTO

#else

#undef     USE_C_DDA
#undef     USE_C_PREDRAW
#undef     USE_C_TOTO

#endif

#endif // CONFIG_H