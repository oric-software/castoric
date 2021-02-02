
#include <stdio.h>

#include "profile.h"

#include "colorimg.c"
#include "dda.c"
#include "tabTexelColor.c"
#include "raycast.c"
#include "scene.c"


// #define PROFILE_ENTER(x)
// #define PROFILE_LEAVE(x)

void initCamera(){
    glCamPosX               = 6; // 0; // -62; // 39;  //
    glCamPosY               = 11; // 0; //- 62; // -25; //
    glCamRotZ               = 80; // 32; // 64; //
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
void main(){


    printf ("DEBUT\n");
    initCamera();
    initScene (scene_00);

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

    textCol ();

    printf ("FIN\n");
	
}
