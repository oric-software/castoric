#define ROT_ANGLE_STEP 16
/*    ___  _                           
 *   / _ \| |  __ _  _   _   ___  _ __ 
 *  / /_)/| | / _` || | | | / _ \| '__|
 * / ___/ | || (_| || |_| ||  __/| |   
 * \/     |_| \__,_| \__, | \___||_|   
 *                   |___/             
 */
void forward();
void shiftLeft();
void backward();
void shiftRight();

void player () {
    switch (get()) {
    case 8:  // left 
        glCamRotZ += ROT_ANGLE_STEP;
        RayLeftAlpha            = glCamRotZ + tabRayAngles[0];
        break;
    case 9:  // right 
        glCamRotZ -= ROT_ANGLE_STEP; 
        RayLeftAlpha            = glCamRotZ + tabRayAngles[0];
        break;
    case 10:  // down
        backward(); break;
    case 11:  // up
        forward(); break;
    // case 80:  // P        HEP !! DONT TOUCH THAT !!!
    //     glCamPosZ += 1; break;
    // case 59:  // ;       FORGET ABOUT IT !!
    //     glCamPosZ -= 1; break;
    case 81:  // Q
        running = 0; break;
    // case 65:  // A
    //     glCamRotX -= 2; break;
    case 90:  // Z
        shiftLeft(); break;
    case 88:  // X
        shiftRight(); break;
    default:
        break;
    }
}
/*                          
 *   /\/\    ___  __   __  ___ 
 *  /    \  / _ \ \ \ / / / _ \
 * / /\/\ \| (_) | \ V / |  __/
 * \/    \/ \___/   \_/   \___|
 *                            
 */
// Collision Detection 
unsigned char isAllowedPosition(signed char X, signed char Y) {

    return 1;

}
void forward() {
    signed int X, Y;
    X = glCamPosX; Y = glCamPosY;
    if (-112 >= glCamRotZ) {
        glCamPosX--;
    } else if ((-112 < glCamRotZ) && (-80 >= glCamRotZ)) {
        glCamPosX--; glCamPosY--;
    } else if ((-80 < glCamRotZ) && (-48 >= glCamRotZ)) {
        glCamPosY--;
    } else if ((-48 < glCamRotZ) && (-16 >= glCamRotZ)) {
        glCamPosX++; glCamPosY--;
    } else if ((-16 < glCamRotZ) && (16 >= glCamRotZ)) {
        glCamPosX++;
    } else if ((16 < glCamRotZ) && (48 >= glCamRotZ)) {
        glCamPosX++; glCamPosY++;
    } else if ((48 < glCamRotZ) && (80 >= glCamRotZ)) {
        glCamPosY++;
    } else if ((80 < glCamRotZ) && (112 >= glCamRotZ)) {
        glCamPosX--; glCamPosY++;
    } else {
        glCamPosX--;
    }
    if (!isAllowedPosition(glCamPosX, glCamPosY)) {
        glCamPosX = X; glCamPosY = Y;
    }
}
void backward() {
    signed int X, Y;
    X = glCamPosX; Y = glCamPosY;
    if (-112 >= glCamRotZ) {
        glCamPosX++;
    } else if ((-112 < glCamRotZ) && (-80 >= glCamRotZ)) {
        glCamPosX++; glCamPosY++;
    } else if ((-80 < glCamRotZ) && (-48 >= glCamRotZ)) {
        glCamPosY++;
    } else if ((-48 < glCamRotZ) && (-16 >= glCamRotZ)) {
        glCamPosX--; glCamPosY++;
    } else if ((-16 < glCamRotZ) && (16 >= glCamRotZ)) {
        glCamPosX--;
    } else if ((16 < glCamRotZ) && (48 >= glCamRotZ)) {
        glCamPosX--; glCamPosY--;
    } else if ((48 < glCamRotZ) && (80 >= glCamRotZ)) {
        glCamPosY--;
    } else if ((80 < glCamRotZ) && (112 >= glCamRotZ)) {
        glCamPosX++; glCamPosY--;
    } else {
        glCamPosX++;
    }
    if (!isAllowedPosition(glCamPosX, glCamPosY)) {
        glCamPosX = X; glCamPosY = Y;
    }
}
void shiftLeft() {
    signed int X, Y;
    X = glCamPosX; Y = glCamPosY;
    if (-112 >= glCamRotZ) {
        glCamPosY--;
    } else if ((-112 < glCamRotZ) && (-80 >= glCamRotZ)) {
        glCamPosX++; glCamPosY--;
    } else if ((-80 < glCamRotZ) && (-48 >= glCamRotZ)) {
        glCamPosX--;
    } else if ((-48 < glCamRotZ) && (-16 >= glCamRotZ)) {
        glCamPosX++; glCamPosY++;
    } else if ((-16 < glCamRotZ) && (16 >= glCamRotZ)) {
        glCamPosY++;
    } else if ((16 < glCamRotZ) && (48 >= glCamRotZ)) {
        glCamPosX--; glCamPosY++;
    } else if ((48 < glCamRotZ) && (80 >= glCamRotZ)) {
        glCamPosX--;
    } else if ((80 < glCamRotZ) && (112 >= glCamRotZ)) {
        glCamPosX--; glCamPosY--;
    } else {
        glCamPosY--;
    }
    if (!isAllowedPosition(glCamPosX, glCamPosY)) {
        glCamPosX = X; glCamPosY = Y;
    }
}
void shiftRight() {
    signed int X, Y;
    X = glCamPosX;
    Y = glCamPosY;
    if (-112 >= glCamRotZ) {
        glCamPosY++;
    } else if ((-112 < glCamRotZ) && (-80 >= glCamRotZ)) {
        glCamPosX--; glCamPosY++;
    } else if ((-80 < glCamRotZ) && (-48 >= glCamRotZ)) {
        glCamPosX++;
    } else if ((-48 < glCamRotZ) && (-16 >= glCamRotZ)) {
        glCamPosX--; glCamPosY--;
    } else if ((-16 < glCamRotZ) && (16 >= glCamRotZ)) {
        glCamPosY--;
    } else if ((16 < glCamRotZ) && (48 >= glCamRotZ)) {
        glCamPosX++; glCamPosY--;
    } else if ((48 < glCamRotZ) && (80 >= glCamRotZ)) {
        glCamPosX++;
    } else if ((80 < glCamRotZ) && (112 >= glCamRotZ)) {
        glCamPosX++; glCamPosY++;
    } else {
        glCamPosX++;
    }
    if (!isAllowedPosition(glCamPosX, glCamPosY)) {
        glCamPosX = X; glCamPosY = Y;
    }
}
