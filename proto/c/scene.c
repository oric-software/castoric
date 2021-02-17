
// [ref texture_file2buffer]
#include "texture_bluestone.h"
#include "texture_christmas.h"
#include "texture_redbrick.h"
#include "texture_logo.h"

// [ref scene_describe]
signed char scene_00[] = {

    /* nbPoints = */ 4, /* nbWall = */ 4
	, -6, -6	 	// P0
	, -6,  6		// P1
	,  6,  6		// P2
	,  6, -6		// P3
	, 0, 1   // W0
	, 1, 2   // W1
	, 2, 3   // W2
	, 3, 0   // W2

};

unsigned char *wallTexture[] = {
	texture_bluestone		// W0
	, texture_christmas		// W1
	, texture_redbrick		// W2
	, texture_logo			// W3
};
