// Inpired by Rax https://github.com/raxrax/oricAsciiTank



// objects
#define OBJ_DOOR 1
#define OBJ_LAMP 2
#define OBJ_SOLDIER 3

unsigned char   objType     [OBJECTS_MAX];
unsigned char   objActive   [OBJECTS_MAX];
signed char     objPosX     [OBJECTS_MAX];
signed char     objPosY     [OBJECTS_MAX];
signed char *   objData     [OBJECTS_MAX];
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
signed char soldierData [] = {-64};
void soldierUpdate();


signed  char doorData[] = {0}; // state 0 : close,  1..6 : opening, 7: opened , 
unsigned char idObjDoor;
void doorUpdate();


void engObjectPulse()
{
    switch (objType[engCurrentObjectIdx])
    {
        case OBJ_DOOR:
            doorUpdate();
            break;
        case OBJ_LAMP:
            computeLogDistance();
            dichoInsert (engCurrentObjectIdx, objLogDistance[engCurrentObjectIdx]);
            break;
        case OBJ_SOLDIER:
            soldierUpdate();
            break;
    }
}

#ifdef USE_C_ENGINEPULSE
void engPulse() {
    for (engCurrentObjectIdx = 0; engCurrentObjectIdx < OBJECTS_MAX; engCurrentObjectIdx++) {
        if (objActive[engCurrentObjectIdx]) {
            engObjectPulse();
        }
    }

}
#endif // USE_C_ENGINEPULSE

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


void doorUpdate()
{
	signed char ex = objPosX[engCurrentObjectIdx];
    signed char ey = objPosY[engCurrentObjectIdx];
    signed char state = *(objData[engCurrentObjectIdx]);
    if (state != 0 && state < 7) {
        state ++;
        scene_00[26] ++;
        *(objData[engCurrentObjectIdx])=state;
        initScene (scene_00, texture_00);
    }
    if (state == 7) objActive[engCurrentObjectIdx]=0;
}

void soldierUpdate()
{
    // unsigned char ldist;
    unsigned char displaystate;
    signed char direction;
    signed char sex, sey;
	signed char ex = objPosX[engCurrentObjectIdx];
    signed char ey = objPosY[engCurrentObjectIdx];
    direction = *(objData[engCurrentObjectIdx]);
    if (ey == 60) { //(ex == 24) 
        if (direction == -64){
            ey --;
        } else {
            direction += 16;
        }
    } else if (ey == -3) {
        if (direction == 64){
            ey ++;
        } else {
            direction += 16;
        }
    } else {
        if (direction == -64){
            ey --;
        } else {
            ey ++;;
        }
    }
    *(objData[engCurrentObjectIdx]) = direction;
    // sex = ex;
    // sey = ey;
    // direction = *(objData[engCurrentObjectIdx]);
    // if (-112 >= direction) {
    //     ex--;
    // } else if ((-112 < direction) && (-80 >= direction)) {
    //     ex--; ey--;
    // } else if ((-80 < direction) && (-48 >= direction)) {
    //     ey--;
    // } else if ((-48 < direction) && (-16 >= direction)) {
    //     ex++; ey--;
    // } else if ((-16 < direction) && (16 >= direction)) {
    //     ex++;
    // } else if ((16 < direction) && (48 >= direction)) {
    //     ex++; ey++;
    // } else if ((48 < direction) && (80 >= direction)) {
    //     ey++;
    // } else if ((80 < direction) && (112 >= direction)) {
    //     ex--; ey++;
    // } else {
    //     ex--;
    // }
    // if (isInWall(ex, ey)) {
    //      direction += 16;
    //      *(objData[engCurrentObjectIdx]) = direction;
    //      ex = sex;
    //      ey = sey;
    // }
    objPosX[engCurrentObjectIdx] = ex;
    objPosY[engCurrentObjectIdx] = ey;
    // ldist = computeLogDist (ex, ey);
    computeLogDistance();
    dichoInsert (engCurrentObjectIdx, objLogDistance[engCurrentObjectIdx]);

    // computeRelativeOrientation (*(objData[engCurrentObjectIdx]));
#ifdef USE_SPRITE    
    displaystate = computeRelativeOrientation (direction, rayCamRotZ);
    switch (displaystate) {
        case 0:
            objTexture[engCurrentObjectIdx] = texture_soldier_back; // ptrTextureSoldierBack;
            break;
        case 1:
            objTexture[engCurrentObjectIdx] = texture_soldier_left; // ptrTextureSoldierRight;
            break;
        case 2:
            objTexture[engCurrentObjectIdx] = texture_soldier_front; // ptrTextureSoldierFront;
            break;
        case 3:
            objTexture[engCurrentObjectIdx] = texture_soldier_right; // ptrTextureSoldierLeft;
            break;
    }
#endif
    refreshNeeded = 1;
}
#ifdef USE_C_ENGINEPULSE
void engInitObjects()
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; i++) objActive[i] = 0;
}
#endif USE_C_ENGINEPULSE

void engAddObject(char type, signed char x, signed char y, signed char *data)
{
    for (engCurrentObjectIdx = 0; engCurrentObjectIdx < OBJECTS_MAX; engCurrentObjectIdx++)
    {
        if (objActive[engCurrentObjectIdx] == 0) break;
    }
    if (engCurrentObjectIdx != OBJECTS_MAX) {
        objActive[engCurrentObjectIdx] = 1;
        objType[engCurrentObjectIdx] = type;
        objPosX[engCurrentObjectIdx] = x;
        objPosY[engCurrentObjectIdx] = y;
        objData[engCurrentObjectIdx] = data;
    };

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