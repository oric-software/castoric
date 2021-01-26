

#define                 USE_ANTIFISH

#define NB_SLICES       40
#define NB_MAX_WALL     32
#define NB_MAX_POINT    64

#define ANGLE_MAX       (signed char)0xC0
#define IS_FRONT(i)     (((lAngle[(i)] & ANGLE_MAX) == 0) || ((lAngle[(i)] & ANGLE_MAX) == ANGLE_MAX))
#define abs(x)          (((x)<0)?-(x):(x))


static signed char      RayAlpha  = 0;
static signed char      RayLeftAlpha;
static signed char      InterpAngleLeft;
static unsigned char    RaySliceIdx;
static unsigned char    InterpIdxLeft;
static unsigned char    RayNbSlice;
static unsigned int     RayDistance;
static unsigned int     RayWallLog;
static unsigned char    rayzbuffer[NB_SLICES];
static unsigned char*   tab_denom;
static unsigned char    raywall[NB_SLICES];
static unsigned char    RayCurrentWall;
static signed char      lWallsCosBeta[NB_MAX_WALL];
static unsigned char    RayIdXPoint1, RayIdXPoint2;
static signed char      lPointsX[NB_MAX_POINT];
static signed char      lPointsY[NB_MAX_POINT];
static unsigned char    lWallsPt1[NB_MAX_WALL];
static unsigned char    lWallsPt2[NB_MAX_WALL];
static signed char      lAngle[NB_MAX_POINT];
static unsigned char    isVisible[NB_MAX_POINT];
static unsigned char    isFront[NB_MAX_POINT];
static unsigned char    TableVerticalPos[NB_SLICES];

unsigned char           rayNbPoints;
unsigned char           rayNbWalls;

signed char             glCamPosX = 0;
signed char             glCamPosY = 0;
signed char             glCamRotZ = 0;



unsigned char atan_tab[] = {
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x02,0x02,0x02,
            0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
            0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
            0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
            0x03,0x03,0x03,0x03,0x03,0x04,0x04,0x04,
            0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
            0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
            0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
            0x07,0x07,0x07,0x07,0x07,0x07,0x08,0x08,
            0x08,0x08,0x08,0x08,0x09,0x09,0x09,0x09,
            0x09,0x0a,0x0a,0x0a,0x0a,0x0b,0x0b,0x0b,
            0x0b,0x0c,0x0c,0x0c,0x0c,0x0d,0x0d,0x0d,
            0x0d,0x0e,0x0e,0x0e,0x0e,0x0f,0x0f,0x0f,
            0x10,0x10,0x10,0x11,0x11,0x11,0x12,0x12,
            0x12,0x13,0x13,0x13,0x14,0x14,0x15,0x15,
            0x15,0x16,0x16,0x17,0x17,0x17,0x18,0x18,
            0x19,0x19,0x19,0x1a,0x1a,0x1b,0x1b,0x1c,
            0x1c,0x1c,0x1d,0x1d,0x1e,0x1e,0x1f,0x1f
};

unsigned char octant_adjust[] = {
        0x3F, // 0b00111111, //        ;; x+,y+,|x|>|y|
        0x00, // 0b00000000, //        ;; x+,y+,|x|<|y|
        0xC0, // 0b11000000, //        ;; x+,y-,|x|>|y|
        0xFF, // 0b11111111, //        ;; x+,y-,|x|<|y|
        0x40, // 0b01000000, //        ;; x-,y+,|x|>|y|
        0x7F, // 0b01111111, //        ;; x-,y+,|x|<|y|
        0xBF, // 0b10111111, //        ;; x-,y-,|x|>|y|
        0x80, // 0b10000000, //        ;; x-,y-,|x|<|y|
};

unsigned char tab_exp[] = {
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x0b, 0x0b, 
    0x0b, 0x0c, 0x0c, 0x0c, 0x0c, 0x0d, 0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x10, 
    0x10, 0x10, 0x11, 0x11, 0x11, 0x12, 0x12, 0x13, 0x13, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 0x16, 
    0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1c, 0x1d, 0x1d, 0x1e, 0x1f, 0x1f, 
    0x20, 0x21, 0x21, 0x22, 0x23, 0x24, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x29, 0x2a, 0x2b, 0x2c, 
    0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3b, 0x3c, 0x3d, 0x3f, 
    0x40, 0x41, 0x43, 0x44, 0x46, 0x47, 0x49, 0x4a, 0x4c, 0x4e, 0x4f, 0x51, 0x53, 0x55, 0x57, 0x59, 
    0x5b, 0x5c, 0x5f, 0x61, 0x63, 0x65, 0x67, 0x69, 0x6c, 0x6e, 0x70, 0x73, 0x75, 0x78, 0x7b, 0x7d, 
    0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x95, 0x98, 0x9c, 0x9f, 0xa2, 0xa6, 0xaa, 0xad, 0xb1, 
    0xb5, 0xb9, 0xbd, 0xc1, 0xc5, 0xca, 0xce, 0xd3, 0xd7, 0xdc, 0xe1, 0xe6, 0xeb, 0xf0, 0xf5, 0xfb
};

unsigned char tab_exp_extended[] = {
    0, 6, 11, 17, 23, 29, 36, 42, 
    48, 55, 62, 69, 76, 83, 91, 98, 
    106, 114, 122, 130, 139, 147, 156, 165, 
    175, 184, 194, 203, 214, 224, 234, 245, 255 /* FIXME Should be 256 */};

unsigned char tab_exp_extended2[] = {
    11, 23, 34, 46, 59, 71, 84, 97, 
    110, 124, 138, 152, 167, 181, 197, 212, 
    228, 244};

unsigned char tab_exp_extended3[] = {
    17, 34, 51, 69, 87, 105, 124, 143, 163, 183, 204, 225, 246};

// log2(x)*32 
unsigned char log2_tab[] = {
        0x00,0x00,0x20,0x32,0x40,0x4a,0x52,0x59,
        0x60,0x65,0x6a,0x6e,0x72,0x76,0x79,0x7d,
        0x80,0x82,0x85,0x87,0x8a,0x8c,0x8e,0x90,
        0x92,0x94,0x96,0x98,0x99,0x9b,0x9d,0x9e,
        0xa0,0xa1,0xa2,0xa4,0xa5,0xa6,0xa7,0xa9,
        0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,
        0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,
        0xb9,0xba,0xbb,0xbc,0xbd,0xbd,0xbe,0xbf,
        0xc0,0xc0,0xc1,0xc2,0xc2,0xc3,0xc4,0xc4,
        0xc5,0xc6,0xc6,0xc7,0xc7,0xc8,0xc9,0xc9,
        0xca,0xca,0xcb,0xcc,0xcc,0xcd,0xcd,0xce,
        0xce,0xcf,0xcf,0xd0,0xd0,0xd1,0xd1,0xd2,
        0xd2,0xd3,0xd3,0xd4,0xd4,0xd5,0xd5,0xd5,
        0xd6,0xd6,0xd7,0xd7,0xd8,0xd8,0xd9,0xd9,
        0xd9,0xda,0xda,0xdb,0xdb,0xdb,0xdc,0xdc,
        0xdd,0xdd,0xdd,0xde,0xde,0xde,0xdf,0xdf,
        0xdf,0xe0,0xe0,0xe1,0xe1,0xe1,0xe2,0xe2,
        0xe2,0xe3,0xe3,0xe3,0xe4,0xe4,0xe4,0xe5,
        0xe5,0xe5,0xe6,0xe6,0xe6,0xe7,0xe7,0xe7,
        0xe7,0xe8,0xe8,0xe8,0xe9,0xe9,0xe9,0xea,
        0xea,0xea,0xea,0xeb,0xeb,0xeb,0xec,0xec,
        0xec,0xec,0xed,0xed,0xed,0xed,0xee,0xee,
        0xee,0xee,0xef,0xef,0xef,0xef,0xf0,0xf0,
        0xf0,0xf1,0xf1,0xf1,0xf1,0xf1,0xf2,0xf2,
        0xf2,0xf2,0xf3,0xf3,0xf3,0xf3,0xf4,0xf4,
        0xf4,0xf4,0xf5,0xf5,0xf5,0xf5,0xf5,0xf6,
        0xf6,0xf6,0xf6,0xf7,0xf7,0xf7,0xf7,0xf7,
        0xf8,0xf8,0xf8,0xf8,0xf9,0xf9,0xf9,0xf9,
        0xf9,0xfa,0xfa,0xfa,0xfa,0xfa,0xfb,0xfb,
        0xfb,0xfb,0xfb,0xfc,0xfc,0xfc,0xfc,0xfc,
        0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfe,0xfe,
        0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff
};
// [255] + [round(32*math.log2(abs(1/math.sin(angle*math.pi/128)))) for angle in range (1,128)] + [round(32*math.log2(abs(1/math.sin(angle*math.pi/128)))) for angle in range (-127,1)]

unsigned char tab_1oversin[] ={
    255, 171, 139, 120, 107, 97, 89, 82, 
    75, 70, 65, 61, 57, 54, 50, 47, 
    44, 42, 39, 37, 35, 33, 31, 29, 
    27, 25, 24, 22, 21, 20, 18, 17, 
    16, 15, 14, 13, 12, 11, 10, 9, 
    9, 8, 7, 6, 6, 5, 5, 4, 
    4, 3, 3, 2, 2, 2, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 2, 2, 2, 3, 3, 
    4, 4, 5, 5, 6, 6, 7, 8, 
    9, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 20, 21, 22, 24, 25, 
    27, 29, 31, 33, 35, 37, 39, 42, 
    44, 47, 50, 54, 57, 61, 65, 70, 
    75, 82, 89, 97, 107, 120, 139, 171, 
    171, 139, 120, 107, 97, 89, 82, 75, 
    70, 65, 61, 57, 54, 50, 47, 44, 
    42, 39, 37, 35, 33, 31, 29, 27, 
    25, 24, 22, 21, 20, 18, 17, 16, 
    15, 14, 13, 12, 11, 10, 9, 9, 
    8, 7, 6, 6, 5, 5, 4, 4, 
    3, 3, 2, 2, 2, 1, 1, 1, 
    1, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 1, 
    1, 1, 2, 2, 2, 3, 3, 4, 
    4, 5, 5, 6, 6, 7, 8, 9, 
    9, 10, 11, 12, 13, 14, 15, 16, 
    17, 18, 20, 21, 22, 24, 25, 27, 
    29, 31, 33, 35, 37, 39, 42, 44, 
    47, 50, 54, 57, 61, 65, 70, 75, 
    82, 89, 97, 107, 120, 139, 171, 255
};

// [min(255,round(32*math.log2(abs(1/math.cos(angle*math.pi/128))))) for angle in range (0,128)] + [min(255,round(32*math.log2(abs(1/math.cos(angle*math.pi/128))))) for angle in range (-127,0)]
unsigned char tab_1overcos[]={
    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 2, 2, 2, 3, 3, 
    4, 4, 5, 5, 6, 6, 7, 8, 
    9, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 20, 21, 22, 24, 25, 
    27, 29, 31, 33, 35, 37, 39, 42, 
    44, 47, 50, 54, 57, 61, 65, 70, 
    75, 82, 89, 97, 107, 120, 139, 171, 
    255, 171, 139, 120, 107, 97, 89, 82, 
    75, 70, 65, 61, 57, 54, 50, 47, 
    44, 42, 39, 37, 35, 33, 31, 29, 
    27, 25, 24, 22, 21, 20, 18, 17, 
    16, 15, 14, 13, 12, 11, 10, 9, 
    9, 8, 7, 6, 6, 5, 5, 4, 
    4, 3, 3, 2, 2, 2, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 2, 2, 2, 3, 3, 
    4, 4, 5, 5, 6, 6, 7, 8, 
    9, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 20, 21, 22, 24, 25, 
    27, 29, 31, 33, 35, 37, 39, 42, 
    44, 47, 50, 54, 57, 61, 65, 70, 
    75, 82, 89, 97, 107, 120, 139, 171, 
    255, 171, 139, 120, 107, 97, 89, 82, 
    75, 70, 65, 61, 57, 54, 50, 47, 
    44, 42, 39, 37, 35, 33, 31, 29, 
    27, 25, 24, 22, 21, 20, 18, 17, 
    16, 15, 14, 13, 12, 11, 10, 9, 
    9, 8, 7, 6, 6, 5, 5, 4, 
    4, 3, 3, 2, 2, 2, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0
};

signed char             tabRayAngles[] = {
        40, 39, 38, 37, 35, 34, 33, 31, 29, 27, 25, 23, 21, 19, 16, 13
        , 11, 8, 5, 2, -2, -5, -8, -11, -13, -16, -19, -21, -23, -25, -27, -29
        , -31, -33, -34, -35, -37, -38, -39, -40};

unsigned char           tabAngle2Col[] = {
        0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10
        , 11, 11, 12, 12, 12, 13, 13, 14, 14, 14, 15, 15, 16, 16, 16, 17
        , 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 22
        , 22, 22, 23, 23, 23, 24, 24, 25, 25, 25, 26, 26, 27, 27, 27, 28
        , 28, 29, 29, 30, 30, 31, 31, 32, 33, 33, 34, 35, 36, 36, 37, 38
        , 39};

unsigned int            unfish[] = {
        27, 25, 24, 22, 20, 18, 17, 15, 13, 11, 9, 8, 6, 5, 4, 2
        , 2, 1, 0, 0, 0, 0, 1, 2, 2, 4, 5, 6, 8, 9, 11, 13
        , 15, 17, 18, 20, 22, 24, 25, 27};


unsigned char unlogd2hh[]= {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02
,0x03, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x07
,0x08, 0x09, 0x09, 0x0a, 0x0b, 0x0b, 0x0c, 0x0d
,0x0e, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x12, 0x13
,0x14, 0x15, 0x16, 0x16, 0x17, 0x18, 0x19, 0x1a
,0x1b, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21
,0x22, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28
,0x29, 0x2a, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
,0x30, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x35
,0x36, 0x37, 0x38, 0x39, 0x39, 0x3a, 0x3b, 0x3c
,0x3c, 0x3d, 0x3e, 0x3e, 0x3f, 0x40, 0x40, 0x41
,0x42, 0x42, 0x43, 0x44, 0x44, 0x45, 0x46, 0x46
,0x47, 0x47, 0x48, 0x48, 0x49, 0x4a, 0x4a, 0x4b
,0x4b, 0x4c, 0x4c, 0x4d, 0x4d, 0x4e, 0x4e, 0x4e
,0x4f, 0x4f, 0x50, 0x50, 0x51, 0x51, 0x51, 0x52
,0x52, 0x52, 0x53, 0x53, 0x54, 0x54, 0x54, 0x55
,0x55, 0x55, 0x56, 0x56, 0x56, 0x56, 0x57, 0x57
,0x57, 0x58, 0x58, 0x58, 0x58, 0x59, 0x59, 0x59
,0x59, 0x59, 0x5a, 0x5a, 0x5a, 0x5a, 0x5b, 0x5b
,0x5b, 0x5b, 0x5b, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c
,0x5c, 0x5d, 0x5d, 0x5d, 0x5d, 0x5d, 0x5d, 0x5d
,0x5e, 0x5e, 0x5e, 0x5e, 0x5e, 0x5e, 0x5e, 0x5e
,0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f
,0x5f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60
,0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61
,0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61
,0x61, 0x61, 0x61, 0x61, 0x62, 0x62, 0x62, 0x62
,0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62
};

unsigned char dist2hh(unsigned int x){
    if (x < 256) {
        return ((unsigned char)unlogd2hh[(unsigned char)(x)]);
    } else return 100;
}

unsigned int longexp(unsigned int x){
    if (x < 256) {
        return ((unsigned int)tab_exp[(unsigned char)(x)]);
    } else if (x < 289) {
        return ((unsigned int)tab_exp_extended[(unsigned char)(x-256)]) + 256;
    } else if (x < 307) {
        return ((unsigned int)tab_exp_extended2[(unsigned char)(x-289)]) + 512;
    } else if (x < 320) {
        return ((unsigned int)tab_exp_extended3[(unsigned char)(x-307)]) + 756;
    } else {
        return 0xFFFF;
    }
}

signed char ATAN2 (signed int ty, signed int tx){
    signed char     x, y;
    unsigned char   ix, iy;
    unsigned char   res_div;
    unsigned char   idx;
    unsigned char   noct;       // Octant number
    unsigned char   v;

    if ((abs(tx)>127) || (abs(ty)>127)) {
        x=tx/2;
        y=ty/2;
    }else{
        x=tx;
        y=ty;
    }
    noct = 0;
    if (x<0){
        ix = -x ; // (unsigned char)(x ^ 0xFF);
        noct |= 4;
    } else { 
        ix = (unsigned char)x;
    }
    if (y<0){
        iy = -y; // (unsigned char)(y ^ 0xFF);
        noct |= 2;
    }else{
        iy = (unsigned char)y;
    }
    res_div = (log2_tab[ix]) - (log2_tab [iy]);
    // printf ("ix = %d iy = %d; res_div = %d\n", ix, iy, res_div);
                  
    if (log2_tab[ix] >= log2_tab [iy]){
        idx = res_div ^ 0xFF;
        noct |= 1;

    } else {
        idx = res_div;
    } 

    v= atan_tab[idx];
    v ^= octant_adjust[noct];

    return (signed char)v;
}

void toto() {

    RayAlpha        = InterpAngleLeft; //tabRayAngles[InterpIdxLeft]-glCamRotZ;
    RaySliceIdx     = InterpIdxLeft;
    if (RayNbSlice == 0) return;

#ifdef DEBUG
    printf ("Wall %d from %d to %d, %d slice from (c=%d a=%d) to (c=%d, a=%d) \n", RayCurrentWall, RayIdXPoint1, RayIdXPoint2,
    RayNbSlice, RaySliceIdx,RayAlpha, RaySliceIdx+RayNbSlice, RayAlpha+tabRayAngles[RaySliceIdx+RayNbSlice]
    );
#endif
    while(1){
        RayDistance     = RayWallLog + (unsigned int)tab_denom[(unsigned char)RayAlpha];

#ifdef DEBUG
        printf ("RaySliceIdx = %d, RayAlpha = %d, RayDistance=%d\n", RaySliceIdx, RayAlpha, RayDistance);
#endif
        if (rayzbuffer[RaySliceIdx] > RayDistance){
            rayzbuffer[RaySliceIdx]     = RayDistance;
            raywall[RaySliceIdx]        = RayCurrentWall;
        } 
        if ((--RayNbSlice) == 0) break;
        RaySliceIdx     += 1;
        RayAlpha        = glCamRotZ + tabRayAngles[RaySliceIdx];

    }
}

void preDraw(){

    if (lWallsCosBeta[RayCurrentWall] == 0){    // Wall is O,y aligned   
        RayWallLog      = log2_tab[(unsigned char)(abs(lPointsX[RayIdXPoint1]-glCamPosX))];
        tab_denom       = tab_1overcos;
    } else {                                    // Wall is O,x aligned
        RayWallLog      = log2_tab[(unsigned char)(abs(lPointsY[RayIdXPoint1]-glCamPosY))];
        tab_denom       = tab_1oversin;
    }
}

#define ANGLE_TO_COL(x) tabAngle2Col[tabRayAngles[0]-lAngle[(x)]]

void drawFullCrossingWall(){

    preDraw();

    InterpAngleLeft     = RayLeftAlpha;
    RayNbSlice          = NB_SLICES;
    InterpIdxLeft       = 0;

    toto();
}

void drawFullVisibleWall(){

    preDraw();

    if (lAngle[RayIdXPoint1] > lAngle[RayIdXPoint2]){

        InterpIdxLeft       = ANGLE_TO_COL(RayIdXPoint1);
        InterpAngleLeft     = lAngle[RayIdXPoint1]+ glCamRotZ;
        RayNbSlice          = (ANGLE_TO_COL(RayIdXPoint2) - InterpIdxLeft)+1;
    } else {

        InterpIdxLeft       = ANGLE_TO_COL(RayIdXPoint2);
        InterpAngleLeft     = lAngle[RayIdXPoint2]+ glCamRotZ;
        RayNbSlice          = (ANGLE_TO_COL(RayIdXPoint1) - InterpIdxLeft)+1;
    }

    toto();
}


void drawLeftCuttingWall1Visible(){
    
    preDraw();

    InterpAngleLeft         = RayLeftAlpha;
    RayNbSlice              = ANGLE_TO_COL(RayIdXPoint1);
    InterpIdxLeft           = 0; 

    toto();
}
void drawLeftCuttingWall2Visible(){
    preDraw();

    InterpAngleLeft         = RayLeftAlpha;
    RayNbSlice              = ANGLE_TO_COL(RayIdXPoint2);
    InterpIdxLeft           = 0; 
    toto();
}

void drawRightCuttingWall1Visible(){
    preDraw();
    InterpIdxLeft           = ANGLE_TO_COL(RayIdXPoint1);
    InterpAngleLeft         = lAngle[RayIdXPoint1]+glCamRotZ;
    RayNbSlice              = (NB_SLICES - InterpIdxLeft)+1;
 
    toto();
}
void drawRightCuttingWall2Visible(){
    preDraw();
    InterpAngleLeft         = lAngle[RayIdXPoint2]+glCamRotZ;
    InterpIdxLeft           = ANGLE_TO_COL(RayIdXPoint2);
    RayNbSlice              = (NB_SLICES - InterpIdxLeft)+1;
    toto();
}

void rayProcessWalls() {

    for (RayCurrentWall = 0; RayCurrentWall < rayNbWalls; RayCurrentWall ++){
        RayIdXPoint1        = lWallsPt1[RayCurrentWall];
        RayIdXPoint2        = lWallsPt2[RayCurrentWall];

        if (isVisible[RayIdXPoint1]) {
            if (isVisible[RayIdXPoint2]) {
                drawFullVisibleWall();
            } else {
                // Point 1 is visible and Point 2 is not in FOV
                if (lAngle[RayIdXPoint1] > 0){
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                        drawLeftCuttingWall1Visible();
                    } else {
                        if (abs(lAngle[RayIdXPoint1] - lAngle[RayIdXPoint2]) > 127){
                            drawLeftCuttingWall1Visible();
                        } else {
                            drawRightCuttingWall1Visible();
                        }
                    }

                } else if (lAngle[RayIdXPoint1] < 0) {
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                        drawRightCuttingWall1Visible();
                    } else {
                        if (abs(lAngle[RayIdXPoint1] - lAngle[RayIdXPoint2]) > 127){
                            drawRightCuttingWall1Visible();
                        } else {
                            drawLeftCuttingWall1Visible();
                        }
                    }

                } else { // (lAngle[idxPt1] < 0)
                    if (lAngle[RayIdXPoint2] < 0) {
                        drawRightCuttingWall1Visible();
                    } else {
                        drawLeftCuttingWall1Visible();
                    }
                }
            }
        } else {
            if (isVisible[RayIdXPoint2]) {

                // Point 2 is visible and Point 1 is not in FOV
                if (lAngle[RayIdXPoint2] > 0){
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                        drawLeftCuttingWall2Visible();
                    } else {
                        if (abs(lAngle[RayIdXPoint2] - lAngle[RayIdXPoint1]) > 127){
                            drawLeftCuttingWall2Visible();
                        } else {
                            drawRightCuttingWall2Visible();
                        }
                    }
                } else if (lAngle[RayIdXPoint2] < 0) {
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                        drawRightCuttingWall2Visible();
                    } else {
                        if (abs(lAngle[RayIdXPoint2] - lAngle[RayIdXPoint1]) > 127){
                            drawRightCuttingWall2Visible();
                        } else {
                            drawLeftCuttingWall2Visible();
                        }
                    }
                } else { // (lAngle[idxPt1] == 0
                    if (lAngle[RayIdXPoint1] < 0) {
                        drawRightCuttingWall2Visible();
                    } else {
                        drawLeftCuttingWall2Visible();
                    }
                }
            } else {
                if (   (isFront[RayIdXPoint1] 
                    || isFront[RayIdXPoint2] )
                    && ((lAngle[RayIdXPoint1] & 0x80) != (lAngle[RayIdXPoint2] & 0x80)) 
                    && (abs(lAngle[RayIdXPoint2]) < 127 - abs(lAngle[RayIdXPoint1])) 
                ) {
                    drawFullCrossingWall();
                }
            }
        }
    }
    /* 
     * Change output from logarithmic scale to linear scale 
     */
    for (RaySliceIdx=0; RaySliceIdx<NB_SLICES; RaySliceIdx++){

#ifdef USE_ANTIFISH
        rayzbuffer[RaySliceIdx] -= unfish[RaySliceIdx];
#endif

        TableVerticalPos[RaySliceIdx] =dist2hh(rayzbuffer[RaySliceIdx]);
        rayzbuffer[RaySliceIdx] = longexp(rayzbuffer[RaySliceIdx]);        

    }
}

void rayProcessPoints() {

    for (RayIdXPoint1 = 0; RayIdXPoint1 < rayNbPoints; RayIdXPoint1 ++) {

        lAngle[RayIdXPoint1]        =  ATAN2(lPointsY[RayIdXPoint1]-glCamPosY, lPointsX[RayIdXPoint1]-glCamPosX) - glCamRotZ;

        isVisible[RayIdXPoint1]     = (abs(lAngle[RayIdXPoint1])<tabRayAngles[0])?1:0;
        isFront[RayIdXPoint1]       = IS_FRONT(RayIdXPoint1)?1:0;
    }
}