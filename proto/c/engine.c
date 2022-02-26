// Inpired by Rax https://github.com/raxrax/oricAsciiTank

#define OBJECTS_MAX 8

// objects
#define OBJ_KEY 1
#define OBJ_TREE 2
#define OBJ_SOLDIER 3

unsigned char   objType     [OBJECTS_MAX];
unsigned char   objActive   [OBJECTS_MAX];
signed char     objPosX     [OBJECTS_MAX];
signed char     objPosY     [OBJECTS_MAX];
char *          objData     [OBJECTS_MAX];
unsigned char * objTexture  [OBJECTS_MAX];


// logarithm distance of object
unsigned char   objLogDistance  [OBJECTS_MAX];
// angle of object relatively to camera position
signed char   objAlpha  [OBJECTS_MAX];
// angle of object relatively to camera axe of view
signed char   objAngle  [OBJECTS_MAX];



// // Height of object on screen
// unsigned char   objHeight  [OBJECTS_MAX];
// // Center column of object on screen
// unsigned char   objColumn  [OBJECTS_MAX];


// static unsigned char engNbObject;
unsigned char engCurrentObjectIdx;

// void itemUpdate();
// char soldier_data [] = {32};
void soldierUpdate();



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

// void objComputeData(){
//     signed char     alpha;
//     objLogDistance  [engCurrentObjectIdx] = computeLogDist (objPosX[engCurrentObjectIdx], objPosY[engCurrentObjectIdx]);
//     alpha = ATAN2(objPosY[engCurrentObjectIdx]-rayCamPosY, objPosX[engCurrentObjectIdx]-rayCamPosX);
//     objAngle [engCurrentObjectIdx]        = alpha-rayCamRotZ;
//     // objColumn [engCurrentObjectIdx]       = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle [engCurrentObjectIdx]+rayCamRotZ];
//     // objHeight [engCurrentObjectIdx]       = dist2hh(objLogDistance  [engCurrentObjectIdx]);
// }



void engObjectPulse()
{
    switch (objType[engCurrentObjectIdx])
    {
        case OBJ_KEY:
            computeLogDistance();
            if (! hasKey) dichoInsert (engCurrentObjectIdx, objLogDistance[engCurrentObjectIdx]); 
            break;
        case OBJ_TREE:
            computeLogDistance();
            dichoInsert (engCurrentObjectIdx, objLogDistance[engCurrentObjectIdx]);
            break;
        case OBJ_SOLDIER:
            soldierUpdate();
            break;
    }
}

void engPulse() {
    for (engCurrentObjectIdx = 0; engCurrentObjectIdx < OBJECTS_MAX; engCurrentObjectIdx++) {
        if (objActive[engCurrentObjectIdx]) {
            engObjectPulse();
        }
    }

    // {
    //     asm (
    //         "ldy #17: sty _engCurrentObjectIdx:"
    //         "engPulseLoop:"
    //             "lda _objActive, y:"
    //             "beq EndIfObjectIsActive:"
    //                 "jsr _engObjectPulse:"
    //             "EndIfObjectIsActive:"
    //             "dec _engCurrentObjectIdx: ldy _engCurrentObjectIdx: bpl engPulseLoop:"
    //         "engPulseEndLoop:"
    //     );
    // }
}


unsigned char computeRelativeOrientation (signed char direction, signed char rayCamRotZ);
// void keyUpdate()
// {
// 	// unsigned char ex = objPosX[engCurrentObjectIdx];
//     // unsigned char ey = objPosY[engCurrentObjectIdx];
//     // printf ("key pulse\n");
//     // ldist = computeLogDist (objPosX[engCurrentObjectIdx], objPosY[engCurrentObjectIdx]);
//     dichoInsert (engCurrentObjectIdx, computeLogDist (objPosX[engCurrentObjectIdx], objPosY[engCurrentObjectIdx]));

//     objTexture[engCurrentObjectIdx] = texture_aKey;
//     // objPosX[engCurrentObjectIdx] = ex;
//     // objPosY[engCurrentObjectIdx] = ey;
// }


void soldierUpdate()
{
    // unsigned char ldist;
    unsigned char displaystate;
    signed char direction;
    signed char sex, sey;
	signed char ex = objPosX[engCurrentObjectIdx];
    signed char ey = objPosY[engCurrentObjectIdx];
    sex = ex;
    sey = ey;
    direction = *(objData[engCurrentObjectIdx]);
    if (-112 >= direction) {
        ex--;
    } else if ((-112 < direction) && (-80 >= direction)) {
        ex--; ey--;
    } else if ((-80 < direction) && (-48 >= direction)) {
        ey--;
    } else if ((-48 < direction) && (-16 >= direction)) {
        ex++; ey--;
    } else if ((-16 < direction) && (16 >= direction)) {
        ex++;
    } else if ((16 < direction) && (48 >= direction)) {
        ex++; ey++;
    } else if ((48 < direction) && (80 >= direction)) {
        ey++;
    } else if ((80 < direction) && (112 >= direction)) {
        ex--; ey++;
    } else {
        ex--;
    }
    if (isInWall(ex, ey) || ((abs(ex-rayCamPosX)<2) && (abs(ey-rayCamPosY)<2)) ) {
         direction += 16;
         *(objData[engCurrentObjectIdx]) = direction;
         ex = sex;
         ey = sey;
    }
    objPosX[engCurrentObjectIdx] = ex;
    objPosY[engCurrentObjectIdx] = ey;
    // ldist = computeLogDist (ex, ey);
    if (abs(ey) > 6) {
        running = 0;
        isWon = 1;
        return ; 
    }
    computeLogDistance();
    dichoInsert (engCurrentObjectIdx, objLogDistance[engCurrentObjectIdx]);

    // computeRelativeOrientation (*(objData[engCurrentObjectIdx]));
#ifdef USE_SPRITE    
    displaystate = computeRelativeOrientation (direction, rayCamRotZ);
    switch (displaystate) {
        case 0:
            objTexture[engCurrentObjectIdx] = texture_smily_back; // ptrTextureSoldierBack;
            break;
        case 1:
            objTexture[engCurrentObjectIdx] = texture_smily_left; // ptrTextureSoldierRight;
            break;
        case 2:
            objTexture[engCurrentObjectIdx] = texture_smily_front; // ptrTextureSoldierFront;
            break;
        case 3:
            objTexture[engCurrentObjectIdx] = texture_smily_right; // ptrTextureSoldierLeft;
            break;
    }
#endif
    refreshNeeded = 1;
}

void engInitObjects()
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; i++) objActive[i] = 0;
    // {asm(
    //     "ldy #17:"
    //     "lda #0:"
    //     "loopEngInitObjects:"
    //     "sta _objActive, y:dey:bpl loopEngInitObjects:"
    // );}
}

void engAddObject(char type, signed char x, signed char y, char *data)
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; i++)
    {
        if (objActive[i] == 0)
        {
            objActive[i] = 1;
            objType[i] = type;
            objPosX[i] = x;
            objPosY[i] = y;
            objData[i] = data;
            return;
        }
    }
}

// void engDeleteObject(unsigned char objectNumber) {
//     objActive[objectNumber] = 0;
// }

// void engDeleteAllObjects(unsigned char objectType) {
//     unsigned char i;
//     for (i = 0; i < OBJECTS_MAX; i++)
//         if (1 == objActive[i] && objectType == objType[i])
//             objActive[i] = 0;
// }


// void main () {
//     int ii;
//     printf ("coucou\n");
//     engInitObjects();
//     engAddObject(OBJ_KEY, 3, 3, 0);
//     engAddObject(OBJ_SOLDIER, 3, -3, soldier_data);
//     for (ii=0 ; ii < 4; ii++){
//         engPulse();
//     }
// }