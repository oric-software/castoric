// Author : Jean-Baptiste PERIN
// Date : 2021
//
// Build with OSDK: osdk_build.bat && osdk_execute.bat
//

#undef DEBUG

#include "lib.h"
#include "profile.h"
#include "config.h"

#include "raycast.c"
#include "scene.c"

#include "game.c"
#include "collision.c"
#ifndef PROFILER_ENABLE
#include "player.c"
#endif // PROFILER_ENABLE
#include "texel.c"
#include "keyboard_c.c"
#include "viewport.c"
#include "vertcolbuf.c"
#include "drawWalls.c"

#ifdef USE_SPRITE
#include "texture_sfront.h"
#include "texture_sback.h"
#include "texture_sleft.h"
#include "texture_sright.h"
#endif // USE_SPRITE
#include "dichobuf.c"
#include "engine.c"
#ifdef USE_SPRITE
#include "dist.c"
#include "sprite.c"
#include "texture_key.h"
#include "texture_tree.h"
#endif // USE_SPRITE

#define CHANGE_INK_TO_RED	            1		
#define CHANGE_INK_TO_GREEN	            2		
#define CHANGE_INK_TO_BLUE	            4		

extern unsigned char 	kernel_cs;
extern unsigned char 	kernel_s;

extern unsigned char 	kernel_fraction;
extern unsigned char 	kernel_beat;
extern unsigned char 	kernel_tempo;
extern unsigned char 	nbE_keybuf;

void prepareRGB(){
    int ii;

    // parcours de lignes de 3 en 3
    for (ii=0; ii < (TEXT_SCREEN_HEIGHT - NB_LESS_LINES_4_COLOR)*8;  ii+=3){
        poke (HIRES_SCREEN_ADDRESS+((ii)*NEXT_SCANLINE_INCREMENT),CHANGE_INK_TO_RED);
        poke (HIRES_SCREEN_ADDRESS+((ii+1)*NEXT_SCANLINE_INCREMENT),CHANGE_INK_TO_GREEN);
        poke (HIRES_SCREEN_ADDRESS+((ii+2)*NEXT_SCANLINE_INCREMENT),CHANGE_INK_TO_BLUE);
    }
}


// [ref camera_situation]
void initCamera(){
    rayCamPosX               = 0;
    rayCamPosY               = -8; 
    rayCamRotZ               = 64;
    RayLeftAlpha            = rayCamRotZ + HALF_FOV_FIX_ANGLE;
}


#ifdef DEBUG
#include "debug.c"
#endif


#ifndef PROFILER_ENABLE
void keyPressed(unsigned char c){
	// printf ("kp: %x, ", c);
    if (c == keyForward) {
            forward(); 
            refreshNeeded   = 1;
    } else if (c == keyBackward) {
            backward();
            refreshNeeded   = 1;
    } else if (c == keyTurnLeft) {
            rayCamRotZ      += ROT_ANGLE_STEP;
            RayLeftAlpha    = rayCamRotZ + HALF_FOV_FIX_ANGLE;
            refreshNeeded   = 1;
    } else if (c == keyTurnRight) {
            rayCamRotZ      -= ROT_ANGLE_STEP; 
            RayLeftAlpha    = rayCamRotZ + HALF_FOV_FIX_ANGLE;
            refreshNeeded   = 1;
    } else if (c == keyStraffeRight) {
            refreshNeeded           = 1;
            shiftRight();
    } else if (c == keyStraffeLeft) {
            refreshNeeded           = 1;
            shiftLeft();
    } else if (c == keyQuit) {
            running = 0;
    } else if (c ==  0x20) {
        if ((rayCamPosY <= -4) && (doorState == 2)){
            doorState = 1;
        }
    }

}

void keyReleased(unsigned char c){
	// printf ("kr: %x, ", c);
}

void lsys(){
	unsigned char c;
	while (nbE_keybuf != 0) {
		if ((c=get_keyevent()) & 0x80){
			keyReleased (c & 0x7F);
		} else {
			keyPressed (c);
		}
	}
}
#else
void lsys(){
    refreshNeeded           = 1;
}
#endif // PROFILER_ENABLE

void gameLoop() {

#ifdef USE_SPRITE
    engInitObjects();
    engAddObject(OBJ_TREE, 0, 0, 0);
    objTexture[0] = texture_tree;
    // engAddObject(OBJ_TREE, 0, 11, 0);
    // objTexture[1] = texture_tree;
    // engAddObject(OBJ_KEY, 9, -6, 0);
    // objTexture[2] = texture_aKey;
    engAddObject(OBJ_SOLDIER, 0, -4, 0);
    objTexture[1] = texture_smily_back;
#endif // USE_SPRITE

	kernelInit();
	osmeInit();

    ProfilerInitialize();

    while (running) {

        ProfilerNextFrame();
        PROFILE_ENTER(ROUTINE_GLOBAL);
        
        doke(630,0);

        if ((doorState==1) && (scene_00[2+4*2] != 6)) {
            scene_00[2+4*2] ++;
            scene_00[2+5*2] ++;
            if (scene_00[2+4*2] == 6) doorState = 0;
            initScene (scene_00, texture_00);
            refreshNeeded = 1;
        } else {
            // player ();
            lsys();
        }

        dichoInit();
        engPulse();

#ifdef PROFILER_ENABLE
        if ((objPosX[1] == 0) && (objPosY[1] == -5)) running = 0;
#endif // PROFILER_ENABLE

        if (refreshNeeded) {
            rayInitCasting();

            rayProcessPoints();
            rayProcessWalls();

            // clearViewport();
            PROFILE_ENTER(ROUTINE_DRAWWALLS);
            drawWalls();
#ifdef USE_SPRITE
//             // logdist(signed char posX, signed char posY) 
//             if ((rayCamPosX == 0) && (rayCamPosY == 0)){
//                 if (hasKey == 0) {
//                     zap();
//                 }
//                 // hasKey = 1;
//             }
//             if (! hasKey) drawSprite (0, 0, texture_aKey);
            // drawSprites ();
#endif
            PROFILE_LEAVE(ROUTINE_DRAWWALLS);
            refreshNeeded = 0;
            printf("\n(X=%d Y=%d) [a=%d] [t=%d]\n\n", rayCamPosX, rayCamPosY, rayCamRotZ, 65535-deek(630));
            if (hasKey) printf ("Key");
        }


        // for (ii = 0; ii <= VIEWPORT_HEIGHT; ii++) {
        //     drawTexelOnScreen (ii, 40-VIEWPORT_WIDTH/2, 63);
        //     drawTexelOnScreen (ii, 40+VIEWPORT_WIDTH/2, 63);
        // }
        // for (ii=0 ; ii < VIEWPORT_WIDTH/2; ii++){
        //     drawTexelOnScreen (VIEWPORT_HEIGHT, 40+ii, 63);
        //     drawTexelOnScreen (VIEWPORT_HEIGHT, 40-ii, 63);
        // }
        PROFILE_LEAVE(ROUTINE_GLOBAL);
        
        ProfilerDisplay();
    }
    ProfilerTerminate();    
    kernelEnd();
}

void main(){

    printf ("DEBUT\n");

    // [res camera_situation]]
    initCamera();
    
    // [ref scene_load]
    initScene (scene_00, texture_00);
    hasKey = 0;
    doorState == 2;
#ifdef DEBUG

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

    detailPoints(); 
    get();
    textZBuffer ();
    get();
    textCol ();
    get();
#endif

    hires();
    prepareRGB();

#ifdef DEBUG
    drawWalls();
    // drawSprite (6, 6, texture_pillar);
#endif
    running = 1;
    refreshNeeded           = 1;
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
//     //adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + (line*3)*NEXT_SCANLINE_INCREMENT + (column>>1));
//     adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(line<<1) + line] + (column>>1));

//     if ((column&0x01) == 0){
//         *adr |= encodeHColor[r];
//         adr += NEXT_SCANLINE_INCREMENT;
//         *adr |= encodeHColor[g];
//         adr += NEXT_SCANLINE_INCREMENT;
//         *adr |= encodeHColor[b];
//     } else {
//         *adr |= encodeLColor[r];
//         adr += NEXT_SCANLINE_INCREMENT;
//         *adr |= encodeLColor[g];
//         adr += NEXT_SCANLINE_INCREMENT;
//         *adr |= encodeLColor[b];
//     }

//     PROFILE_LEAVE(ROUTINE_COLORSQUARE);
// }

// void drawImage01(){
//     int ii, jj;

//     signed char idxScreenLine, idxScreenCol;
//     unsigned char height, spriteTexColumn;

//     PROFILE_ENTER(ROUTINE_DRAW01);
//     for (ii = 0; ii < 40; ii++) {
//         height          = tabHeight[ii];
//         spriteTexColumn       = tabTexCol[ii];
//         idxScreenCol    = 10+ii;

//         ddaStartValue       = 0;
//         ddaNbStep           = 2*height;
//         ddaNbVal            = TEXTURE_SIZE;

//         ddaInit();
//         idxScreenLine       = 32 - height;
//         // printf ("%d %d\n", ddaCurrentValue, idxScreenLine);
//         if ((idxScreenLine >=0) && (idxScreenLine < 64)) {
//             colorSquare(idxScreenLine, idxScreenCol, bufimg[multi40[ddaCurrentValue] + spriteTexColumn]);
//         }
//         while (ddaCurrentValue < ddaEndValue) {
//             (*ddaStepFunction)(); 
//             // printf ("%d\n", ddaCurrentValue, idxScreenLine);
//             if ((idxScreenLine >=0) && (idxScreenLine < 64)) {
//                 colorSquare(idxScreenLine, idxScreenCol, bufimg[multi40[ddaCurrentValue] + spriteTexColumn]);
//             }
//             idxScreenLine   += 1;
//         }
//     }
//     PROFILE_LEAVE(ROUTINE_DRAW01);
// }


