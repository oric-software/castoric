
// Anle of the object relatively to camera's orientation (in fixed angular format)
// signed char     objAngle;

signed char     objAngleRight;
signed char     objAngleLeft;

// // logarithmic distance betwen object and camera
// unsigned char   objLogDist;

// // Height of object representation on screen (in texel)
// unsigned char   objHeight;


signed char     objX;
signed char     objY;


// // Input : objX/Y, rayCamPosX/Y
// // Oupt : objAngle, objLogDist, objHeight
// unsigned char computeLogDist (){

//     signed char     deltaX, deltaY;
//     signed char     alpha;
//     unsigned char   log2Delta;
//     unsigned int    log2dist;
//     // signed char     column;

//     deltaX          = objX-rayCamPosX;
//     deltaY          = objY-rayCamPosY;

//     if ((deltaX == 0) && (deltaY == 0)){
//         objHeight = 0;
//         objLogDist = 0;
//         return 0;
//     }
    
//     alpha           = ATAN2(deltaY, deltaX);
//     objAngle           = alpha-rayCamRotZ;
//     // column = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle];
//     if (abs(deltaX) > abs(deltaY)) {
//         log2Delta = log2_tab[(unsigned char)(abs(deltaX))];
//         objLogDist = log2Delta + (unsigned int)tab_1overcos[(unsigned char)alpha];
//     } else {
//         log2Delta = log2_tab[(unsigned char)(abs(deltaY))];
//         objLogDist = log2Delta + (unsigned int)tab_1oversin[(unsigned char)alpha];
//     }
//     objHeight = dist2hh(objLogDist);
//     return (objLogDist);
// }


// compute orientation relatively to the camera
// param dir : 
unsigned char computeRelativeOrientation (signed char dirP, signed char dirC) {
    unsigned char res;
    signed char reldiff;
    unsigned char absdiff;

    reldiff  = dirP - dirC + 32;
    absdiff = (unsigned char)(reldiff);

    res = absdiff >> 6;
    return res;
}

#ifdef USE_C_3TRIGO
signed char tab3Sin[] ={
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

signed char tab3Cos[] = {
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
#else
extern signed char tab3Sin[];
extern signed char tab3Cos[];

#endif // USE_C_3TRIGO

signed char     visi_beta;
signed char visi_incX, visi_incY;
signed char visi_angleRight, visi_angleLeft;

// 0 not visible, 1 center visible, 2 only right side visible, 3 only left side visible
unsigned char visi_SpriteVisibility;
    

#ifdef USE_C_SPRITEVISIBILITY
void elaborateSpriteVisibility(void) {

    visi_SpriteVisibility = 0;

    if (abs(objAngle[engCurrentObjectIdx]) < HALF_FOV_FIX_ANGLE){
        visi_SpriteVisibility = 1;
        return;
    }

    visi_beta            = objAlpha[engCurrentObjectIdx] - 64; 

    visi_incX            = tab3Cos[(unsigned char)visi_beta];
    visi_incY            = tab3Sin[(unsigned char)visi_beta];

    visi_angleRight          = ATAN2(objY+visi_incY - rayCamPosY, objX+visi_incX - rayCamPosX)-rayCamRotZ;
    visi_angleLeft           = ATAN2(objY-visi_incY - rayCamPosY, objX-visi_incX - rayCamPosX)-rayCamRotZ;

    if (abs(visi_angleRight) < HALF_FOV_FIX_ANGLE) {
        objAngleRight = visi_angleRight;
        visi_SpriteVisibility = 2;
        return;
    }
    if (abs(visi_angleLeft) < HALF_FOV_FIX_ANGLE){
        objAngleLeft = visi_angleLeft;
        visi_SpriteVisibility = 3;
        return;
    }
}
#else
extern void elaborateSpriteVisibility();
#endif


// Input : objX/Y, rayCamPosX/Y
// Ouptut : objAngle, objAngleRight, objAngleLeft
unsigned char isVisibleSprite (){

    
    elaborateSpriteVisibility();

    return visi_SpriteVisibility;
}




#ifdef USE_C_COMPUTELOGDIST

signed char     disDeltaX, disDeltaY;
unsigned char   disLog2Delta;
unsigned char   disLogDistance;

// Input : objPosX/Y[engCurrentObjectIdx], rayCamPosX/Y
// Oupt : objAngle, objLogDistance
void computeLogDistance (){


    disDeltaX          = objPosX[engCurrentObjectIdx]-rayCamPosX;
    disDeltaY          = objPosY[engCurrentObjectIdx]-rayCamPosY;

    if ((disDeltaX == 0) && (disDeltaY == 0)){
        objLogDistance[engCurrentObjectIdx] = 0;
        objAngle[engCurrentObjectIdx] = 0;
        return ;
    }
    
    objAlpha[engCurrentObjectIdx]  = ATAN2(disDeltaY, disDeltaX);
    objAngle[engCurrentObjectIdx]           = objAlpha[engCurrentObjectIdx]-rayCamRotZ;

    if (abs(disDeltaX) > abs(disDeltaY)) {
        disLog2Delta = log2_tab[(unsigned char)(abs(disDeltaX))];
        disLogDistance = disLog2Delta + (unsigned int)tab_1overcos[(unsigned char)objAlpha[engCurrentObjectIdx]];
    } else {
        disLog2Delta = log2_tab[(unsigned char)(abs(disDeltaY))];
        disLogDistance = disLog2Delta + (unsigned int)tab_1oversin[(unsigned char)objAlpha[engCurrentObjectIdx]];
    }
    // Compute distance to view Plane because it is the one used to 
    if (disLogDistance < tab_1overcos[(unsigned char)objAngle[engCurrentObjectIdx]]) {
        objLogDistance[engCurrentObjectIdx] =  tab_1overcos[(unsigned char)objAngle[engCurrentObjectIdx]]  - disLogDistance ;
    } else {
        objLogDistance[engCurrentObjectIdx] =  disLogDistance - tab_1overcos[(unsigned char)objAngle[engCurrentObjectIdx]];
    }
}
#endif // USE_C_COMPUTELOGDIST
