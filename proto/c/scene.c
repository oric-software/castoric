
// [ref texture_file2buffer]
#include "texture_christmas.h"
#include "texture_bluestone.h"
#include "texture_redbrick.h"
#include "texture_logo.h"

unsigned char wallTexture_high[NB_MAX_WALL] ;
unsigned char wallTexture_low[NB_MAX_WALL] ;

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

// [ref texture_file2buffer]
unsigned char *texture_00[]= {
	texture_bluestone		// W0
	, texture_christmas		// W1
	, texture_redbrick		// W2
	, texture_logo			// W3
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
        wallTexture_high[jj]    = (unsigned char)((((int)(wallTexture[jj])&0xFF00) >> 8) & 0x00FF);
        wallTexture_low[jj]     = (unsigned char)(((int)(wallTexture[jj])&0x00FF));
	}
    precalculateWallsAngle();
}
