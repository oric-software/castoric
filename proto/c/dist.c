
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


// Input : objX/Y, rayCamPosX/Y
// Ouptut : objAngle, objAngleRight, objAngleLeft
// 0 not visible, 1 center visible, 2 only right side visible, 3 only left side visible
unsigned char isVisibleSprite (){

    // signed char     deltaX, deltaY;
    // signed char     alpha;
    signed char     beta;
    signed char incX, incY;
    // signed char RightX, RightY, LeftX, LeftY;
    // signed char alphaRight, alphaLeft;
    signed char angleRight, angleLeft;
    
    // deltaX          = objX-rayCamPosX;
    // deltaY          = objY-rayCamPosY;

    // if ((deltaX == 0) && (deltaY == 0)){
    //     return 0;
    // }
    // alpha           = ATAN2(deltaY, deltaX);
    // objAngle           = alpha-rayCamRotZ;
    if (abs(objAngle[engCurrentObjectIdx]) < HALF_FOV_FIX_ANGLE){
        return 1;
    }

    beta            = objAlpha[engCurrentObjectIdx] - 64; 

    incX            = tab3Cos[(unsigned char)beta];
    incY            = tab3Sin[(unsigned char)beta];

    // RightX          = objX+incX;
    // RightY          = objY+incY;

    // LeftX           = objX-incX;
    // LeftY           = objY-incY;

    // deltaX          = RightX - rayCamPosX;
    // deltaY          = RightY - rayCamPosY;
    // alphaRight           = ATAN2(deltaY, deltaX);


    // deltaX          = LeftX - rayCamPosX;
    // deltaY          = LeftY - rayCamPosY;
    // alphaLeft           = ATAN2(deltaY, deltaX);


    // angleRight          = alphaRight-rayCamRotZ;
    // angleLeft           = alphaLeft-rayCamRotZ;

    angleRight          = ATAN2(objY+incY - rayCamPosY, objX+incX - rayCamPosX)-rayCamRotZ;
    angleLeft           = ATAN2(objY-incY - rayCamPosY, objX-incX - rayCamPosX)-rayCamRotZ;


    if (abs(angleRight) < HALF_FOV_FIX_ANGLE) {
        objAngleRight = angleRight;
        return 2;
    }
    if (abs(angleLeft) < HALF_FOV_FIX_ANGLE){
        objAngleLeft = angleLeft;
        return 3;
    }
    return 0;
}



#ifdef USE_C_COMPUTELOGDIST
// Input : objPosX/Y[engCurrentObjectIdx], rayCamPosX/Y
// Oupt : objAngle, objLogDistance
void computeLogDistance (){

    signed char     deltaX, deltaY;
    // signed char     alpha;
    unsigned char   log2Delta;
    unsigned int    log2dist;

    deltaX          = objPosX[engCurrentObjectIdx]-rayCamPosX;
    deltaY          = objPosY[engCurrentObjectIdx]-rayCamPosY;

    if ((deltaX == 0) && (deltaY == 0)){
        objLogDistance[engCurrentObjectIdx] = 0;
        objAngle[engCurrentObjectIdx] = 0;
        return ;
    }
    
    objAlpha[engCurrentObjectIdx]  = ATAN2(deltaY, deltaX);
    objAngle[engCurrentObjectIdx]           = objAlpha[engCurrentObjectIdx]-rayCamRotZ;

    if (abs(deltaX) > abs(deltaY)) {
        log2Delta = log2_tab[(unsigned char)(abs(deltaX))];
        objLogDistance[engCurrentObjectIdx] = log2Delta + (unsigned int)tab_1overcos[(unsigned char)objAlpha[engCurrentObjectIdx]];
    } else {
        log2Delta = log2_tab[(unsigned char)(abs(deltaY))];
        objLogDistance[engCurrentObjectIdx] = log2Delta + (unsigned int)tab_1oversin[(unsigned char)objAlpha[engCurrentObjectIdx]];
    }

}
#endif // USE_C_COMPUTELOGDIST
