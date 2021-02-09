// Author : Jean-Baptiste PERIN
// Date : 2021
//
// Build with OSDK: osdk_build.bat && osdk_execute.bat
//

#undef DEBUG

#include "lib.h"
#include "profile.h"

#include "colorimg.c"
#include "dda.c"
#include "tabTexelColor.c"
#include "raycast.c"
#include "scene.c"


#define SCREEN_WIDTH                    40
#define SCREEN_HEIGHT                   26

#define HIRES_SCREEN_ADDRESS            ((unsigned int)0xA000)
#define NB_LESS_LINES_4_COLOR           2

#define CHANGE_INK_TO_RED	            1		
#define CHANGE_INK_TO_GREEN	            2		
#define CHANGE_INK_TO_BLUE	            4		

#include "tables.c"

unsigned char *theAdr;
unsigned char *baseAdr;
unsigned int offTexture;
unsigned char renCurrentColor;
unsigned char running; // game state: 1 = Running, 0 = Leave.
#include "player.c"
void prepareRGB(){
    int ii;

    // parcours de lignes de 3 en 3
    for (ii=0; ii < (SCREEN_HEIGHT - NB_LESS_LINES_4_COLOR)*8;  ii+=3){
        poke (HIRES_SCREEN_ADDRESS+((ii)*SCREEN_WIDTH),CHANGE_INK_TO_RED);
        poke (HIRES_SCREEN_ADDRESS+((ii+1)*SCREEN_WIDTH),CHANGE_INK_TO_GREEN);
        poke (HIRES_SCREEN_ADDRESS+((ii+2)*SCREEN_WIDTH),CHANGE_INK_TO_BLUE);
    }
}

#include "iea2d.c"
#include "texel.c"
#include "sprite.c"




unsigned char *wallTexture[] = {texture_christmas, texture_logo};
unsigned char *ptrTexture;

void drawImage02(){
    int ii;

    signed char         idxScreenLine, idxScreenCol;
    unsigned char       height, texcolumn;

    PROFILE_ENTER(ROUTINE_DRAW02);

    idxScreenCol        = 1;
    ddaStartValue       = 0;
    ddaNbVal            = TEXTURE_HEIGHT;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));

    for (ii = 2; ii < NB_SLICES-1; ) {
        baseAdr             += 1;
        idxScreenCol        += 1;
        if (raywall[ii]!=255) {
            ptrTexture = wallTexture[raywall[ii]];

    // =====================================
    // ============ LEFT TEXEL
    // =====================================

            height              = (100-TableVerticalPos[ii])/4; // tabHeight[ii];
            texcolumn           = tabTexCol[ii]&31; // modulo 32
            offTexture          = multi32[texcolumn];

            
            
            idxScreenLine       = 32 - height;

            ddaNbStep           = height<<1;

            

            ddaInit();

            while (idxScreenLine < 0){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 

            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]); 

            do {
                (*ddaStepFunction)();

                // colorEvenSquare(bufimg[multi40[ddaCurrentValue] + texcolumn]);
                renCurrentColor = ptrTexture[offTexture + ddaCurrentValue];
                colorLeftTexel();

                idxScreenLine   += 1;
                theAdr          += 120;

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < 64));
        }

        ii++;
        idxScreenCol        += 1;
        if (raywall[ii]!=255) {
            ptrTexture = wallTexture[raywall[ii]];

    // =====================================
    // ============ RIGHT TEXEL
    // =====================================
            height              = (100-TableVerticalPos[ii])/4; // tabHeight[ii];
            texcolumn           = tabTexCol[ii]&31;  // modulo 32
            offTexture          = multi32[texcolumn];
            

            idxScreenLine       = 32 - height;

            ddaNbStep           = height<<1;

            ddaInit();

            while (idxScreenLine < 0){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 

            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]);
            
            do {
                (*ddaStepFunction)();

                // colorOddSquare(bufimg[multi40[ddaCurrentValue] + texcolumn]);
                renCurrentColor = ptrTexture[offTexture + ddaCurrentValue];
                colorRightTexel();

                idxScreenLine   += 1;
                theAdr          += 120;

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < 64));
        }
        ii++;
    }
    PROFILE_LEAVE(ROUTINE_DRAW02);
   
}
void initCamera(){
    glCamPosX               = 3; // -62; // 39;  //6; // 
    glCamPosY               = 3; //- 62; // -25; //11; // 
    glCamRotZ               = 32; // 64; //80; // 
    RayLeftAlpha            = glCamRotZ + tabRayAngles[0];
    // RayRightAlpha           = glCamRotZ - tabRayAngles[0];
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
void rayInitCasting(){
    unsigned char ii;
    for (ii=0; ii< NB_SLICES; ii++) {
        rayzbuffer[ii]      = 255;
        raywall[ii]         = 255;
    }
}

void detailPoints(){
    unsigned char idxPoint;

    for (idxPoint = 0; idxPoint < rayNbPoints; idxPoint ++) {
        printf ("point %d [%d %d], a= %d\n", idxPoint, lPointsX[idxPoint], lPointsY[idxPoint], lAngle[idxPoint]);
    }
}
void textZBuffer () {
    unsigned char ii, jj;
    for (jj=0; jj< 10; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], rayzbuffer[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], rayzbuffer[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], rayzbuffer[(jj)+20] , TableVerticalPos[jj+20]);
    }
    for (jj=30; jj< 40; jj++)  {
        printf ("%d|%d|%d|%d\n", (jj), raywall[(jj)], rayzbuffer[(jj)], TableVerticalPos[jj]);
     }
}
void textCol () {
    unsigned char ii, jj;
    for (jj=0; jj< 10; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
    }
    get();
    for (jj=30; jj< 40; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
     }
     get();
}

void gameLoop() {

    while (running) {

        player ();

        rayInitCasting();
        rayProcessPoints();
        rayProcessWalls();
        memset(HIRES_SCREEN_ADDRESS, 64, 8000); // 5120 = 0xB400 (std char) - 0xA000 (hires screen)
        prepareRGB();
        drawImage02();
        printf("(X=%d Y=%d) [a=%d]\n", glCamPosX, glCamPosY, glCamRotZ);
    }
}

// #undef DEBUG

void main(){


    printf ("DEBUT\n");
    initCamera();
    initScene (scene_00);



    ProfilerInitialize();
    ProfilerNextFrame();

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

#ifdef DEBUG
    // detailPoints(); 
    // get();
    // textZBuffer ();
    // get();
    textCol ();
    get();
#endif

    hires();
    prepareRGB();

    drawImage02();

    displaySprite02(40, 40);

	ProfilerDisplay();	
    ProfilerTerminate();
    printf("Done\n");



    running = 1;
    gameLoop();
	
}

// #define LORES_SCREEN_ADDRESS            ((unsigned int)0xBB80)
// #define STANDARD_CHARSET_ADDRESS        ((unsigned int)0xB400)
// #define ALTERNATE_CHARSET_ADDRESS       ((unsigned int)0xB800)
// #define STANDARD_HIRES_CHARSET_ADDRESS  ((unsigned int)0x9800)

// #define CHANGE_INK_TO_BLACK	            0		
// #define CHANGE_INK_TO_YELLOW	        3		
// #define CHANGE_INK_TO_MAGENTA           5			
// #define CHANGE_INK_TO_CYAN	            6		
// #define CHANGE_INK_TO_WHITE	            7	


// #define USE_STANDARD_CHARSET    	                    8		
// #define USE_ALTERNATE_CHARSET	                        9		
// #define USE_DOUBLE_SIZE_STANDARD_CHARSET	            10		
// #define USE_DOUBLE_SIZE_ALTERNATE_CHARSET	            11		
// #define USE_DOUBLE_SIZE_BLINKING_STANDARD_CHARSET       12		
// #define USE_DOUBLE_SIZE_BLINKING_ALTERNATE_CHARSET      13		
// #define USE_BLINKING_STANDARD_CHARSET	                14		
// #define USE_BLINKING_ALTERNATE_CHARSET	                15		
// // Change Paper (background) color	
// #define CHANGE_PAPER_TO_BLACK			                16		
// #define CHANGE_PAPER_TO_RED	                            17		
// #define CHANGE_PAPER_TO_GREEN	                        18		
// #define CHANGE_PAPER_TO_YELLOW	                        19		
// #define CHANGE_PAPER_TO_BLUE	                        20		
// #define CHANGE_PAPER_TO_MAGENTA	                        21		
// #define CHANGE_PAPER_TO_CYAN	                        22		
// #define CHANGE_PAPER_TO_WHITE	                        23		
// // Video control attributes	
// #define SWITCH_TO_TEXT_MODE_60HZ		                24		
// #define SWITCH_TO_TEXT_MODE_50HZ		                26		
// #define SWITCH_TO_HIRES_MODE_60HZ	                    28		
// #define SWITCH_TO_HIRES_MODE_50HZ                       30		

// /*
//  * VISIBILITY LIMITS
//  */
// #define ANGLE_MAX 0xC0
// #define ANGLE_VIEW 0xE0


// unsigned int multi40[] = {
//         0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600
//         , 640, 680, 720, 760, 800, 840, 880, 920, 960, 1000, 1040, 1080, 1120, 1160, 1200, 1240
//         // , 1280, 1320, 1360, 1400, 1440, 1480, 1520, 1560, 1600, 1640, 1680, 1720, 1760, 1800, 1840, 1880
//         // , 1920, 1960, 2000, 2040, 2080, 2120, 2160, 2200, 2240, 2280, 2320, 2360, 2400, 2440, 2480, 2520
//         // , 2560, 2600, 2640, 2680, 2720, 2760, 2800, 2840, 2880, 2920, 2960, 3000, 3040, 3080, 3120, 3160
//         // , 3200, 3240, 3280, 3320, 3360, 3400, 3440, 3480, 3520, 3560, 3600, 3640, 3680, 3720, 3760, 3800
//         // , 3840, 3880, 3920, 3960, 4000, 4040, 4080, 4120, 4160, 4200, 4240, 4280, 4320, 4360, 4400, 4440
//         // , 4480, 4520, 4560, 4600, 4640, 4680, 4720, 4760, 4800, 4840, 4880, 4920, 4960, 5000, 5040, 5080
//         // , 5120, 5160, 5200, 5240, 5280, 5320, 5360, 5400, 5440, 5480, 5520, 5560, 5600, 5640, 5680, 5720
//         // , 5760, 5800, 5840, 5880, 5920, 5960, 6000, 6040, 6080, 6120, 6160, 6200, 6240, 6280, 6320, 6360
//         // , 6400, 6440, 6480, 6520, 6560, 6600, 6640, 6680, 6720, 6760, 6800, 6840, 6880, 6920, 6960, 7000
//         // , 7040, 7080, 7120, 7160, 7200, 7240, 7280, 7320, 7360, 7400, 7440, 7480, 7520, 7560, 7600, 7640
//         // , 7680, 7720, 7760, 7800, 7840, 7880, 7920, 7960
//         };

// unsigned int multi27[] = {
//         0, 27, 54, 81, 108, 135, 162, 189, 216, 243, 270, 297, 324, 351, 378, 405
//         , 432, 459, 486, 513, 540, 567, 594, 621, 648, 675, 702, 729, 756, 783, 810, 837
//         , 864, 891, 918, 945, 972, 999, 1026, 1053};


// unsigned char idxWall[] = {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//         , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//         , 0, 0, 0, 0, 0, 0, 0, 0};

// line in [0..65] column in [0..79]
// void colorSquare(unsigned char line, unsigned char column, unsigned char theColor){

//     unsigned char r, g, b;
//     unsigned char *adr;

//     PROFILE_ENTER(ROUTINE_COLORSQUARE);
//     // retrieve the color components from the color value
//     r = (theColor>>4)& 0x03;
//     g = (theColor>>2)& 0x03;
//     b = (theColor)& 0x03;

//     // compute the start adress of the screen square to color
//     //adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + (line*3)*SCREEN_WIDTH + (column>>1));
//     adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(line<<1) + line] + (column>>1));

//     if ((column&0x01) == 0){
//         *adr |= encodeHColor[r];
//         adr += SCREEN_WIDTH;
//         *adr |= encodeHColor[g];
//         adr += SCREEN_WIDTH;
//         *adr |= encodeHColor[b];
//     } else {
//         *adr |= encodeLColor[r];
//         adr += SCREEN_WIDTH;
//         *adr |= encodeLColor[g];
//         adr += SCREEN_WIDTH;
//         *adr |= encodeLColor[b];
//     }

//     PROFILE_LEAVE(ROUTINE_COLORSQUARE);
// }

// void drawImage01(){
//     int ii, jj;

//     signed char idxScreenLine, idxScreenCol;
//     unsigned char height, texcolumn;

//     PROFILE_ENTER(ROUTINE_DRAW01);
//     for (ii = 0; ii < 40; ii++) {
//         height          = tabHeight[ii];
//         texcolumn       = tabTexCol[ii];
//         idxScreenCol    = 10+ii;

//         ddaStartValue       = 0;
//         ddaNbStep           = 2*height;
//         ddaNbVal            = TEXTURE_HEIGHT;

//         ddaInit();
//         idxScreenLine       = 32 - height;
//         // printf ("%d %d\n", ddaCurrentValue, idxScreenLine);
//         if ((idxScreenLine >=0) && (idxScreenLine < 64)) {
//             colorSquare(idxScreenLine, idxScreenCol, bufimg[multi40[ddaCurrentValue] + texcolumn]);
//         }
//         while (ddaCurrentValue < ddaEndValue) {
//             (*ddaStepFunction)(); 
//             // printf ("%d\n", ddaCurrentValue, idxScreenLine);
//             if ((idxScreenLine >=0) && (idxScreenLine < 64)) {
//                 colorSquare(idxScreenLine, idxScreenCol, bufimg[multi40[ddaCurrentValue] + texcolumn]);
//             }
//             idxScreenLine   += 1;
//         }
//     }
//     PROFILE_LEAVE(ROUTINE_DRAW01);
// }


