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

// [ref camera_situation]

void player () {
    switch (key()) {
    case 8:  // left 
        rayCamRotZ              += ROT_ANGLE_STEP;
        RayLeftAlpha            = rayCamRotZ + HALF_FOV_FIX_ANGLE;
        refreshNeeded           = 1;
        break;
    case 9:  // right 
        rayCamRotZ              -= ROT_ANGLE_STEP; 
        RayLeftAlpha            = rayCamRotZ + HALF_FOV_FIX_ANGLE;
        refreshNeeded           = 1;
        break;
    case 10:  // down
        refreshNeeded           = 1;
        backward(); break;
    case 11:  // up
        refreshNeeded           = 1;
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
        refreshNeeded           = 1;
        shiftLeft(); break;
    case 88:  // X
        refreshNeeded           = 1;
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
#ifndef USE_C_GENERIC_COLLISION
// Collision Detection 
unsigned char isAllowedPosition(signed char vX, signed char vY) {
    signed char X, Y;
    X = vX + 12;
    Y = vY + 12;
	if (X%6 == 0) {
		if (Y%6 == 0) {
			// X and Y on 6 *6 grid
			return ((X == -6) && (Y == 6)) || ((X == 6) && ( Y == -6));
		} else {
			if (X == 0) {
				return 0;
			} else if (X == 6) {
				return (Y < 6) || (Y > 12);
			} else if (X == 12) {
				return (
					(Y < 6) || (Y > 18)
				);
			} else if (X == 18) {
				return ( (Y < 12) || (Y > 18) );
			} else if (X == 24) {
				return 0;
			} else    {
				return 1;
			}        
        }
    } else if (Y%6 == 0) {
		if (Y == 0) {
			return 0;
		} else if (Y == 6) {
			return (X < 6) || (X > 12);
		} else if (Y == 12) {
			return (X < 6) || (X > 18);
		} else if (Y == 18) {
			return (X < 12) || (X > 18);
		} else if (Y == 24) {
			return 0;
		} else{
			return 1;
		}
    }
    return 1;
}
#endif
void forward() {
    signed int X, Y;
    X = rayCamPosX; Y = rayCamPosY;
    if (-112 >= rayCamRotZ) {
        rayCamPosX--;
    } else if ((-112 < rayCamRotZ) && (-80 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY--;
    } else if ((-80 < rayCamRotZ) && (-48 >= rayCamRotZ)) {
        rayCamPosY--;
    } else if ((-48 < rayCamRotZ) && (-16 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY--;
    } else if ((-16 < rayCamRotZ) && (16 >= rayCamRotZ)) {
        rayCamPosX++;
    } else if ((16 < rayCamRotZ) && (48 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY++;
    } else if ((48 < rayCamRotZ) && (80 >= rayCamRotZ)) {
        rayCamPosY++;
    } else if ((80 < rayCamRotZ) && (112 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY++;
    } else {
        rayCamPosX--;
    }

#ifdef USE_C_GENERIC_COLLISION
    if (collideWall()){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif

        rayCamPosX = X; rayCamPosY = Y;
    }
}
void backward() {
    signed int X, Y;
    X = rayCamPosX; Y = rayCamPosY;
    if (-112 >= rayCamRotZ) {
        rayCamPosX++;
    } else if ((-112 < rayCamRotZ) && (-80 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY++;
    } else if ((-80 < rayCamRotZ) && (-48 >= rayCamRotZ)) {
        rayCamPosY++;
    } else if ((-48 < rayCamRotZ) && (-16 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY++;
    } else if ((-16 < rayCamRotZ) && (16 >= rayCamRotZ)) {
        rayCamPosX--;
    } else if ((16 < rayCamRotZ) && (48 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY--;
    } else if ((48 < rayCamRotZ) && (80 >= rayCamRotZ)) {
        rayCamPosY--;
    } else if ((80 < rayCamRotZ) && (112 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY--;
    } else {
        rayCamPosX++;
    }
#ifdef USE_C_GENERIC_COLLISION
    if (collideWall()){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif

        rayCamPosX = X; rayCamPosY = Y;
    }
}
void shiftLeft() {
    signed int X, Y;
    X = rayCamPosX; Y = rayCamPosY;
    if (-112 >= rayCamRotZ) {
        rayCamPosY--;
    } else if ((-112 < rayCamRotZ) && (-80 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY--;
    } else if ((-80 < rayCamRotZ) && (-48 >= rayCamRotZ)) {
        rayCamPosX--;
    } else if ((-48 < rayCamRotZ) && (-16 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY++;
    } else if ((-16 < rayCamRotZ) && (16 >= rayCamRotZ)) {
        rayCamPosY++;
    } else if ((16 < rayCamRotZ) && (48 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY++;
    } else if ((48 < rayCamRotZ) && (80 >= rayCamRotZ)) {
        rayCamPosX--;
    } else if ((80 < rayCamRotZ) && (112 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY--;
    } else {
        rayCamPosY--;
    }
#ifdef USE_C_GENERIC_COLLISION
    if (collideWall()){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif
        rayCamPosX = X; rayCamPosY = Y;
    }
}
void shiftRight() {
    signed int X, Y;
    X = rayCamPosX;
    Y = rayCamPosY;
    if (-112 >= rayCamRotZ) {
        rayCamPosY++;
    } else if ((-112 < rayCamRotZ) && (-80 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY++;
    } else if ((-80 < rayCamRotZ) && (-48 >= rayCamRotZ)) {
        rayCamPosX++;
    } else if ((-48 < rayCamRotZ) && (-16 >= rayCamRotZ)) {
        rayCamPosX--; rayCamPosY--;
    } else if ((-16 < rayCamRotZ) && (16 >= rayCamRotZ)) {
        rayCamPosY--;
    } else if ((16 < rayCamRotZ) && (48 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY--;
    } else if ((48 < rayCamRotZ) && (80 >= rayCamRotZ)) {
        rayCamPosX++;
    } else if ((80 < rayCamRotZ) && (112 >= rayCamRotZ)) {
        rayCamPosX++; rayCamPosY++;
    } else {
        rayCamPosX++;
    }
#ifdef USE_C_GENERIC_COLLISION
    if (collideWall()){
#else
    if (!isAllowedPosition(rayCamPosX, rayCamPosY)) {
#endif
        rayCamPosX = X; rayCamPosY = Y;
    }
}
