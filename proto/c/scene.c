
// [ref texture_file2buffer]
// #include "texture_christmas.h"
// #include "texture_bluestone.h"
// #include "texture_redbrick.h"
// #include "texture_logo.h"
#include "texture_bluewall.h"
#include "texture_metalwall.h"
#include "texture_door.h"
#include "texture_gridwall.h"
// #include "textures/texture_bigleaves.h"
// #include "textures/texture_bigsquares.h"
// #include "textures/texture_dentwall.h"

unsigned char wallTexture_high[NB_MAX_WALL] ;
unsigned char wallTexture_low[NB_MAX_WALL] ;

// [ref scene_describe]
signed char scene_00[] = {

    /* nbPoints = */ 60, /* nbWall = */ 58,
        -3, 12 , 	// P0
        -9, 12 , 	// P1
        -9, 0 , 	// P2
        -9, -12 , 	// P3
        -3, -12 , 	// P4
        3, -12 , 	// P5
        9, -12 , 	// P6
        9, 0 , 	// P7
        9, 12 , 	// P8
        3, 12 , 	// P9
        -3, 18 , // P10
        3, 18 , // P11
        -3, 15 , // P12
        3, 15 , // P13
		0, 0,    // P14
        -9, 18 , // P15
        -15, 18 , // P16
        -21, 18 , // P17
        -21, 15 , // P18
        -27, 15 , // P19
        -27, 18 , // P20
        -33, 18 , // P21
        -33, 24 , // P22
        -36, 24 , // P23
        -36, 30 , // P24
        -33, 30 , // P25
        -33, 36 , // P26
        -27, 36 , // P27
        -27, 39 , // P28
        -21, 39 , // P29
        -21, 36 , // P30
        -15, 36 , // P31
        -3, 36 , // P32
        -3, 39 , // P33
        3, 39 , // P34
        3, 36 , // P35
        15, 36 , // P36
        15, 48 , // P37
        15, 60 , // P38
        15, 66 , // P39
        27, 66 , // P40
        33, 66 , // P41
        33, 60 , // P42
        33, 54 , // P43
        33, 48 , // P44
        33, 42 , // P45
        33, 36 , // P46
        33, 30 , // P47
        33, 24 , // P48
        33, 18 , // P49
        33, 12 , // P50
        33, 6 , // P51
        33, 0 , // P52
        33, -6 , // P53
        33, -12 , // P54
        27, -12 , // P55
        15, -12 , // P56
        15, -6 , // P57
        15, 6 , // P58
        15, 18 , // P59

    0, 1, //	S0 = 6  Segment S0
    1, 2, //	S1 = 12 Segment S1
    2, 3, //	S2 = 12 Segment S2
    3, 4, //	S3 = 6  Segment S3
    4, 5, //	S4 = 6  Segment S4
    5, 6, //	S5 = 6  Segment S5
    6, 7, //	S6 = 12 Segment S6
    7, 8, //	S7 = 12 Segment S7
    8, 9, //	S8 = 6  Segment S8
    0, 10, //	S9 = 6  Segment S9
    9, 11, //	S10 = 6 Segment S10
    12, 13, //	doorS11 = 6 Segment S11
    10, 15, //	S12 = 6 Segment S12
    15, 16, //	S13 = 6 Segment S13
    16, 17, //	S14 = 6 Segment S14
    17, 18, //	S15 = 3 Segment S15
    18, 19, //	S16 = 6 Segment S16
    19, 20, //	S17 = 3 Segment S17
    20, 21, //	S18 = 6 Segment S18
    21, 22, //	S19 = 6 Segment S19
    22, 23, //	S20 = 3 Segment S20
    23, 24, //	S21 = 6 Segment S21
    24, 25, //	S22 = 3 Segment S22
    25, 26, //	S23 = 6 Segment S23
    26, 27, //	S24 = 6 Segment S24
    27, 28, //	S25 = 3 Segment S25
    28, 29, //	S26 = 6 Segment S26
    29, 30, //	S27 = 3 Segment S27
    30, 31, //	S28 = 6 Segment S28
    31, 32, //	S29 = 12    Segment S29
    32, 33, //	S30 = 3 Segment S30
    33, 34, //	S31 = 6 Segment S31
    34, 35, //	S32 = 3 Segment S32
    35, 36, //	S33 = 12    Segment S33
    36, 37, //	S34 = 12    Segment S34
    37, 38, //	S35 = 12    Segment S35
    38, 39, //	S36 = 6 Segment S36
    39, 40, //	S37 = 12    Segment S37
    40, 41, //	S38 = 6 Segment S38
    41, 42, //	S39 = 6 Segment S39
    42, 43, //	S40 = 6 Segment S40
    43, 44, //	S41 = 6 Segment S41
    44, 45, //	S42 = 6 Segment S42
    45, 46, //	S43 = 6 Segment S43
    46, 47, //	S44 = 6 Segment S44
    47, 48, //	S45 = 6 Segment S45
    48, 49, //	S46 = 6 Segment S46
    49, 50, //	S47 = 6 Segment S47
    50, 51, //	S48 = 6 Segment S48
    51, 52, //	S49 = 6 Segment S49
    52, 53, //	S50 = 6 Segment S50
    53, 54, //	S51 = 6 Segment S51
    54, 55, //	S52 = 6 Segment S52
    55, 56, //	S53 = 12    Segment S53
    56, 57, //	S54 = 6 Segment S54
    57, 58, //	S55 = 12    Segment S55
    58, 59, //	S56 = 12    Segment S56
    59, 11 //	S57 = 12    Segment S57

};

// [ref texture_file2buffer]
unsigned char *texture_00[]= {
	  texture_texture_bluewall // texture_texture_bluewall		// W0
	, texture_texture_bluewall // , texture_bigleaves		// W1
	, texture_texture_bluewall //, texture_bigsquares		// W2
	, texture_texture_bluewall // , texture_dentwall			// W3
	, texture_texture_bluewall // , texture_dentwall			// W4
	, texture_texture_bluewall // , texture_dentwall			// W5
	, texture_texture_bluewall // , texture_dentwall			// W6
	, texture_texture_bluewall // , texture_dentwall			// W7
	, texture_texture_bluewall // , texture_dentwall			// W8
	, texture_texture_metalwall // , texture_dentwall			// W9
	, texture_texture_metalwall // , texture_dentwall			// W10
	, texture_texture_door
	, texture_texture_bluewall // , texture_dentwall			// W12
	, texture_texture_bluewall // , texture_dentwall			// W13
	, texture_texture_bluewall // , texture_dentwall			// W14
	, texture_texture_metalwall // , texture_dentwall			// W15
	, texture_texture_door      // , texture_dentwall			// W16
	, texture_texture_metalwall // , texture_dentwall			// W17
	, texture_texture_bluewall // , texture_dentwall			// W18
	, texture_texture_bluewall // , texture_dentwall			// W19
	, texture_texture_metalwall // , texture_dentwall			// W20
	, texture_texture_door       // , texture_dentwall			// W21
	, texture_texture_metalwall // , texture_dentwall			// W22
	, texture_texture_bluewall // , texture_dentwall			// W23
	, texture_texture_bluewall // , texture_dentwall			// W24
	, texture_texture_metalwall // , texture_dentwall			// W25
	, texture_texture_door       // , texture_dentwall			// W26
	, texture_texture_metalwall // , texture_dentwall			// W27
	, texture_texture_bluewall // , texture_dentwall			// W28
	, texture_texture_bluewall // , texture_dentwall			// W29
	, texture_texture_metalwall // , texture_dentwall			// W30
	, texture_texture_door       // , texture_dentwall			// W31
	, texture_texture_metalwall // , texture_dentwall			// W32
	, texture_texture_bluewall // , texture_dentwall			// W33
	, texture_texture_bluewall // , texture_dentwall			// W34
	, texture_texture_bluewall // , texture_dentwall			// W35
	, texture_texture_bluewall // , texture_dentwall			// W36
	, texture_texture_bluewall // , texture_dentwall			// W37
	, texture_texture_bluewall // , texture_dentwall			// W38
	, texture_texture_gridwall // , texture_dentwall			// W39
	, texture_texture_bluewall // , texture_dentwall			// W40
	, texture_texture_gridwall // , texture_dentwall			// W41
	, texture_texture_bluewall // , texture_dentwall			// W42
	, texture_texture_gridwall // , texture_dentwall			// W43
	, texture_texture_bluewall // , texture_dentwall			// W44
	, texture_texture_gridwall // , texture_dentwall			// W45
	, texture_texture_bluewall // , texture_dentwall			// W46
	, texture_texture_gridwall // , texture_dentwall			// W47
	, texture_texture_bluewall // , texture_dentwall			// W48
	, texture_texture_gridwall // , texture_dentwall			// W49
	, texture_texture_bluewall // , texture_dentwall			// W50
	, texture_texture_gridwall // , texture_dentwall			// W51
	, texture_texture_bluewall // , texture_dentwall			// W52
	, texture_texture_bluewall // , texture_dentwall			// W53
	, texture_texture_bluewall // , texture_dentwall			// W54
	, texture_texture_bluewall // , texture_dentwall			// W55
	, texture_texture_bluewall // , texture_dentwall			// W56
	, texture_texture_bluewall // , texture_dentwall			// W57
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
