


#define ROT_ANGLE_STEP 16
/*    ___  _                           
 *   / _ \| |  __ _  _   _   ___  _ __ 
 *  / /_)/| | / _` || | | | / _ \| '__|
 * / ___/ | || (_| || |_| ||  __/| |   
 * \/     |_| \__,_| \__, | \___||_|   
 *                   |___/             
 */
// void forward();
// void shiftLeft();
// void backward();
// void shiftRight();

// // [ref camera_situation]

// void player () {
//     switch (key()) {
//     case 8:  // left 
//         rayCamRotZ += ROT_ANGLE_STEP;
//         RayLeftAlpha            = rayCamRotZ + HALF_FOV_FIX_ANGLE;
//         refreshNeeded           = 1;
//         break;
//     case 9:  // right 
//         rayCamRotZ -= ROT_ANGLE_STEP; 
//         RayLeftAlpha            = rayCamRotZ + HALF_FOV_FIX_ANGLE;
//         refreshNeeded           = 1;
//         break;
//     case 10:  // down
//         backward();refreshNeeded           = 1; break;
//     case 11:  // up
//         forward(); refreshNeeded           = 1;break;
//     // case 80:  // P        HEP !! DONT TOUCH THAT !!!
//     //     glCamPosZ += 1; break;
//     // case 59:  // ;       FORGET ABOUT IT !!
//     //     glCamPosZ -= 1; break;
//     case 81:  // Q
//         running = 0; break;
//     case 0x20:  // Space
//         if ((rayCamPosY <= -4) && (doorState == 2)){
//             doorState = 1;
//         }
//         break;
//     case 88:  // X
//         shiftLeft(); refreshNeeded           = 1;break;
//     case 0x43:  // C
//         shiftRight(); refreshNeeded           = 1;break;
//     default:
//         break;
//     }
// }
/*                          
 *   /\/\    ___  __   __  ___ 
 *  /    \  / _ \ \ \ / / / _ \
 * / /\/\ \| (_) | \ V / |  __/
 * \/    \/ \___/   \_/   \___|
 *                            
 */
#ifndef USE_GENERIC_COLLISION
// Collision Detection 
unsigned char isAllowedPosition(signed char X, signed char Y) {
    // return (abs(X) <= 5) && (abs(Y) <= 5);
    return 0;
}
#endif
signed int savRayCamPosX, savRayCamPosY;
void forward() {
    
    savRayCamPosX = rayCamPosX; savRayCamPosY = rayCamPosY;
    if (rayCamRotZ < -96) {
        rayCamPosX--;
    } else if (rayCamRotZ < -64) {
        rayCamPosX--; rayCamPosY--;
    }else if (rayCamRotZ < -32) {
        rayCamPosY--;
    }else if (rayCamRotZ < 0) {
        rayCamPosX++; rayCamPosY--;
    }else if (rayCamRotZ < 32) {
        rayCamPosX++;
    }else if (rayCamRotZ < 64) {
        rayCamPosX++; rayCamPosY++;
    } else if (rayCamRotZ < 96) {
        rayCamPosY++;
    } else if (rayCamRotZ < 127) {
        rayCamPosX--; rayCamPosY++;
    } else {
        rayCamPosX--;
    }
#ifdef USE_GENERIC_COLLISION
    if (isInWall(rayCamPosX, rayCamPosY)){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif

        rayCamPosX = savRayCamPosX; rayCamPosY = savRayCamPosY;
    }
}
void backward() {
    savRayCamPosX = rayCamPosX; savRayCamPosY = rayCamPosY;
    if (rayCamRotZ < -96) {
        rayCamPosX++;
    } else if (rayCamRotZ < -64) {
        rayCamPosX++; rayCamPosY++;
    } else if (rayCamRotZ < -32) {
        rayCamPosY++;
    } else if (rayCamRotZ < 0) {
        rayCamPosX--; rayCamPosY++;
    } else if (rayCamRotZ < 32) {
        rayCamPosX--;
    } else if (rayCamRotZ < 64) {
        rayCamPosX--; rayCamPosY--;
    } else if (rayCamRotZ < 96) {
        rayCamPosY--;
    } else if (rayCamRotZ < 127) {
        rayCamPosX++; rayCamPosY--;
    } else {
        rayCamPosX++;
    }
#ifdef USE_GENERIC_COLLISION
    if (isInWall(rayCamPosX, rayCamPosY)){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif

        rayCamPosX = savRayCamPosX; rayCamPosY = savRayCamPosY;
    }
}
void shiftLeft() {
    savRayCamPosX = rayCamPosX; savRayCamPosY = rayCamPosY;
    if (rayCamRotZ < -96) {
        rayCamPosY--;
    } else if (rayCamRotZ < -64) {
        rayCamPosX++; rayCamPosY--;
    } else if (rayCamRotZ < -32) {
        rayCamPosX++;
    } else if (rayCamRotZ < 0) {
        rayCamPosX++; rayCamPosY++;
    } else if (rayCamRotZ < 32) {
        rayCamPosY++;
    } else if (rayCamRotZ < 64) {
        rayCamPosX--; rayCamPosY++;
    } else if (rayCamRotZ < 96) {
        rayCamPosX--;
    } else if (rayCamRotZ < 127) {
        rayCamPosX--; rayCamPosY--;
    } else {
        rayCamPosY--;
    }
#ifdef USE_GENERIC_COLLISION
    if (isInWall(rayCamPosX, rayCamPosY)){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif
        rayCamPosX = savRayCamPosX; rayCamPosY = savRayCamPosY;
    }
}
void shiftRight() {
    savRayCamPosX = rayCamPosX; savRayCamPosY = rayCamPosY;
    if (rayCamRotZ < -96) {
        rayCamPosY++;
    } else if (rayCamRotZ < -64) {
        rayCamPosX--; rayCamPosY++;
    } else if (rayCamRotZ < -32) {
        rayCamPosX--;
    } else if (rayCamRotZ < 0) {
        rayCamPosX--; rayCamPosY--;
    } else if (rayCamRotZ < 32) {
        rayCamPosY--;
    } else if (rayCamRotZ < 64) {
        rayCamPosX++; rayCamPosY--;
    } else if (rayCamRotZ < 96) {
        rayCamPosX++;
    } else if (rayCamRotZ < 127) {
        rayCamPosX++; rayCamPosY++;
    } else {
        rayCamPosX++;
    }
#ifdef USE_GENERIC_COLLISION
    if (isInWall(rayCamPosX, rayCamPosY)){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif
        rayCamPosX = savRayCamPosX; rayCamPosY = savRayCamPosY;
    }
}
