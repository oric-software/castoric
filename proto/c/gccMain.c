// Author : Jean-Baptiste PERIN
// Date : 2021
//
// Build with GCC: gcc -o a.out gccMain.c && a.out
//

#include <stdio.h>

#include "profile.h"

#include "colorimg.c"
#include "dda.c"
#include "tables.c"
#include "tabTexelColor.c"
#include "raycast.c"
#include "scene.c"


// #define PROFILE_ENTER(x)
// #define PROFILE_LEAVE(x)
#define HIRES_SCREEN_ADDRESS            ((unsigned int)0xA000)

void initCamera(){
    glCamPosX               = 3; // 0; // -62; // 39;  //
    glCamPosY               = 3; // 0; //- 62; // -25; //
    glCamRotZ               = 32; // 32; // 64; //
    RayLeftAlpha            = glCamRotZ + tabRayAngles[0];
    // RayRightAlpha           = glCamRotZ - tabRayAngles[0];
}

void rayInitCasting(){
    unsigned char ii;
    for (ii=0; ii< NB_SLICES; ii++) {
        rayzbuffer[ii]      = 255;
        raywall[ii]         = 255;
    }
}


void textCol () {
    unsigned char ii, jj;
    for (jj=0; jj< 10; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
    }

    for (jj=30; jj< 40; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
     }
}

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

void initScene (signed char sceneData[]){
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
	}
    precalculateWallsAngle();
}

#include "iea2d.c"
#define max(x,y)          (((x)<(y))?(y):(x))
#define min(x,y)          (((x)<(y))?(x):(y))


#define SCREEN_WIDTH                    80
#define SCREEN_HEIGHT                   64

void displaySprite(unsigned char column, unsigned char height){

    signed char scrColIdx, scrLinIdx;

    // unsigned char start_column, end_column, nb_column;
    // start_column    = max(VIEWPORT_LEFT_COLUMN, column-height/2);
    // end_column      = min(VIEWPORT_RIGHT_COLUMN, column + height/2);
    // nb_column       = height/2;

    scrColIdx          = column - height/2;
    scrLinIdx          = SCREEN_HEIGHT/ 2 - height/2;

    iea1StartValue       = 0;
    iea1NbVal            = TEXTURE_HEIGHT;
    iea1NbStep           = height;
    iea1Init();

    do {
        iea2StartValue       = 0;
        iea2NbVal            = TEXTURE_HEIGHT;
        iea2NbStep           = height;
        iea2Init();
        do {
            printf ("%d %d, %d %d\n", scrLinIdx, scrColIdx, iea1CurrentValue, iea2CurrentValue);
            (*iea2StepFunction)();
            scrColIdx   += 1;
        } while (iea2CurrentValue <= iea2EndValue);
        (*iea1StepFunction)();
        scrLinIdx      += 1;
        scrColIdx      = column - height/2;
    } while (iea1CurrentValue <= iea1EndValue);
}


unsigned int            offTexture;
unsigned char           *theAdr;

#include "texel.c"

#include "sprite.c"

void main(){

    printf ("DEBUT\n");
    initCamera();
    initScene (scene_00);

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

    // textCol ();

    displaySprite02(3, 20);

    printf ("FIN\n");
}
