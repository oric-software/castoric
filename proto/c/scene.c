
// [ref texture_file2buffer]
// #include "texture_christmas.h"
// #include "texture_bluestone.h"
// #include "texture_redbrick.h"
// #include "texture_logo.h"
#include "texture_bluewall.h"
// #include "textures/texture_bigleaves.h"
// #include "textures/texture_bigsquares.h"
// #include "textures/texture_dentwall.h"

unsigned char wallTexture_high[NB_MAX_WALL] ;
unsigned char wallTexture_low[NB_MAX_WALL] ;

// [ref scene_describe]
signed char scene_00[] = {

    /* nbPoints = */ 12, /* nbWall = */ 11
	, -3, 12	 	// P0
	, -9, 12		// P1
	, -9,  0		// P2
	, -9, -12		// P3
	, -3, -12	 	// P4
	,  3, -12		// P5
	,  9, -12		// P6
	,  9,  0		// P7
	,  9,  12		// P8
	,  3,  12		// P9
	, -3, 18		// P10
	,  3, 18		// P11

	, 0, 1   // W0
	, 1, 2   // W1
	, 2, 3   // W2
	, 3, 4   // W3
	, 4, 5   // W4
	, 5, 6   // W5
	, 6, 7   // W6
	, 7, 8   // W7
	, 8, 9   // W8
	, 0, 10  // W9
	, 9, 11  // W10

};

// [ref texture_file2buffer]
unsigned char *texture_00[]= {
	  texture_texture_bluewall // texture_texture_bluewall		// W0
	, texture_texture_bluewall // , texture_bigleaves		// W1
	, texture_texture_bluewall //, texture_bigsquares		// W2
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W3
};


// [ref scene_load]
void precalculateWallsAngle() {
    unsigned char idxWall, idxPt1, idxPt2;
    signed char dX, dY, angle;

    for (idxWall = 0; idxWall < rayNbWalls; idxWall ++) { 

        idxPt1 = lWallsPt1[idxWall];
        idxPt2 = lWallsPt2[idxWall];

        dX = lPointsX[idxPt2]-lPointsX[idxPt1];
        dY = lPointsY[idxPt2]-lPointsY[idxPt1];

        if (dX == 0) {
            lWallsCosBeta[idxWall] = 0;
        } else if (dY == 0) {
            if (dX > 0) {
                lWallsCosBeta[idxWall] = 32;
            } else {
                lWallsCosBeta[idxWall] = -32;
            }
        } else {
            /* 
             *  Not aligned walls not handled
             */
        }
    }
}

// [ref scene_describe] [ref scene_load]
void initScene (signed char sceneData[], unsigned char *wallTexture[]){
	unsigned int ii;
	unsigned char jj;

	ii=0;
	rayNbPoints = (unsigned char)sceneData[ii++];
	rayNbWalls = (unsigned char)sceneData[ii++];
	for (jj=0; jj < rayNbPoints; jj++){
		lPointsX[jj]= sceneData[ii++] ; lPointsY[jj] = sceneData[ii++];  // points 0
	}
	for (jj=0; jj < rayNbWalls; jj++){
		lWallsPt1[jj]= (unsigned char)(sceneData[ii++]) ; lWallsPt2[jj] = (unsigned char)(sceneData[ii++]);// points 0
#ifndef __GNUC__
        wallTexture_high[jj]    = (unsigned char)((((int)(wallTexture[jj])&0xFF00) >> 8) & 0x00FF);
        wallTexture_low[jj]     = (unsigned char)(((int)(wallTexture[jj])&0x00FF));
#endif		
	}
    precalculateWallsAngle();
}
