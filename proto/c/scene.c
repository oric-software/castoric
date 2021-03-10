
// [ref texture_file2buffer]
//#include "texture_christmas.h"
#include "texture_bluestone.h"
#include "texture_redbrick.h"
#include "texture_ceologo.h"
#include "texture_oriclogo.h"
#include "texture_purplestone.h"
#include "texture_greystone.h"

unsigned char wallTexture_high[NB_MAX_WALL] ;
unsigned char wallTexture_low[NB_MAX_WALL] ;

// [ref scene_describe]
signed char scene_00[] = {

    /* nbPoints = */ 11, /* nbWall = */ 12
	, -12, -12	 	// P0
	, -12,  12		// P1
	,  12,  12		// P2
	,  12, -12		// P3
    ,  -6,  -6     // P4       
    ,   0,  -6     // P5       
    ,  -6,   0     // P6       
    ,   0,   0     // P7       
    ,   6,   0     // P8
    ,   0,   6     // P9
    ,   6,   6     // P10
	, 0, 1   // W0
	, 1, 2   // W1
	, 2, 3   // W2
	, 3, 0   // W3
	, 4, 5   // W4
	, 6, 4   // W5
	, 5, 7   // W6
	, 7, 6   // W7
	, 8, 7   // W8
	, 7, 9   // W9
	, 8, 10  // W10
	, 9, 10  // W11

};

// [ref texture_file2buffer]
unsigned char *texture_00[]= {
	texture_bluestone		// W0
	, texture_bluestone		// W1
	, texture_redbrick		// W2
	, texture_redbrick    // W3
	, texture_purplestone   // W4
	, texture_purplestone			// W5
	, texture_ceologo			// W6
	, texture_oriclogo			// W7
	, texture_greystone			// W8
	, texture_greystone			// W9
	, texture_purplestone			// W10
	, texture_purplestone			// W11

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
