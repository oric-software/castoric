// Author : Jean-Baptiste PERIN
// Date : 2021
//
// Build with GCC: gcc -o a.out gccMain.c && a.out
//
#include <stdio.h>
#include "config.h"




#include "raycast.c"

#include "scene.c"


#include "iea2d.c"
#define max(x,y)          (((x)<(y))?(y):(x))
#define min(x,y)          (((x)<(y))?(x):(y))



unsigned int            offTexture;
unsigned char           *theAdr;
unsigned char           *baseAdr;


#define USE_C_COLORLEFTTEXEL
#define USE_C_COLORRIGHTTEXEL
#include "texel.c"


#include "drawWalls.c"

void initCamera(){
    rayCamPosX               = 3; // 0; // -62; // 39;  //
    rayCamPosY               = 3; // 0; //- 62; // -25; //
    rayCamRotZ               = 32; // 32; // 64; //
    RayLeftAlpha            = rayCamRotZ + HALF_FOV_FIX_ANGLE;
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




void main(){

    printf ("DEBUT\n");
    initCamera();

    initScene (scene_00);

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

    textCol ();

    drawWalls();
#ifdef USE_SPRITE    
    drawSprite (6, 6, texture_pillar);
#endif // USE_SPRITE
    printf ("FIN\n");
}





// void displaySprite(unsigned char column, unsigned char height){

//     signed char scrColIdx, scrLinIdx;

//     // unsigned char start_column, end_column, nb_column;
//     // start_column    = max(VIEWPORT_LEFT_COLUMN, column-height/2);
//     // end_column      = min(VIEWPORT_RIGHT_COLUMN, column + height/2);
//     // nb_column       = height/2;

//     scrColIdx          = column - height/2;
//     scrLinIdx          = SCREEN_HEIGHT/ 2 - height/2;

//     iea1StartValue       = 0;
//     iea1NbVal            = TEXTURE_SIZE;
//     iea1NbStep           = height;
//     iea1Init();

//     do {
//         iea2StartValue       = 0;
//         iea2NbVal            = TEXTURE_SIZE;
//         iea2NbStep           = height;
//         iea2Init();
//         do {
//             printf ("%d %d, %d %d\n", scrLinIdx, scrColIdx, iea1CurrentValue, iea2CurrentValue);
//             (*iea2StepFunction)();
//             scrColIdx   += 1;
//         } while (iea2CurrentValue <= iea2EndValue);
//         (*iea1StepFunction)();
//         scrLinIdx      += 1;
//         scrColIdx      = column - height/2;
//     } while (iea1CurrentValue <= iea1EndValue);
// }

