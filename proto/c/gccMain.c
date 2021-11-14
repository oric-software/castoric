// Author : Jean-Baptiste PERIN
// Date : 2021
//
// Build with GCC: gcc -o a.out gccMain.c && a.out
//
#include <stdio.h>

#include "config.h"


#include "raycast.c"
#include "collision.c"
#include "scene.c"
#include "game.c"
// #include "iea2d.c"


#define max(x,y)          (((x)<(y))?(y):(x))
#define min(x,y)          (((x)<(y))?(x):(y))




unsigned int            offTexture;
unsigned char           *theAdr;
unsigned char           *baseAdr;


#include "texel.c"


#include "drawWalls.c"

#ifdef USE_SPRITE
#include "texture_sfront.h"
#include "texture_sback.h"
#include "texture_sleft.h"
#include "texture_sright.h"
#include "dichobuf.c"
#include "engine.c"
#include "dist.c"
#include "sprite.c"
#include "texture_key.h"
#include "texture_tree.h"
#endif



void initCamera(){
    rayCamPosX               = -3; // 0; // -62; // 39;  //
    rayCamPosY               = -9; // 0; //- 62; // -25; //
    rayCamRotZ               = 64; // 32; // 64; //
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

    signed char alpha;
    unsigned char res;   
    int ii; 
 
    printf ("DEBUT\n");
    initCamera();

    initScene (scene_00, texture_00);

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

//     textCol ();

//     printf ("DEBUT\n");
    
//     alpha           = ATAN2(1, 0);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(2, 0);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(-1, 0);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(-2, 0);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(0, 1);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(0, 2);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(0, -1);
//     printf ("result = %d\n", alpha);
//     alpha           = ATAN2(0, -2);
//     printf ("result = %d\n", alpha);
//     // drawWalls();
// #ifdef USE_SPRITE    
//     drawSprite (0, 0, texture_aKey);
// #endif // USE_SPRITE

// Input : objPosX/Y, rayCamPosX/Y
// Ouptut : True False


//     if (res = isVisibleSprite ()){
// #ifdef __GNUC__ 
//         printf ("sprite is visible\n");
// #endif   
//     }
//     printf ("%d \n", res);

    // drawSprite (0, 0, texture_aKey);

    engInitObjects();
    // engAddObject(OBJ_KEY, 3, 3, 0);
    // objTexture[0] = texture_aKey;
    engAddObject(OBJ_TREE, 0, -3, 0);
    objTexture[0] = texture_tree;

    dichoInit();
    engPulse();

    ii= dichoNbVal;
    while (ii >0) {
        ii -= 1;
        // printf("%d\t", tabDichoIdxs[ii]);
        engCurrentObjectIdx = tabDichoIdxs[ii];
        drawSprite (); //objPosX[engCurrentObjectIdx], objPosY[engCurrentObjectIdx], objTexture[engCurrentObjectIdx]);
    }

    
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

