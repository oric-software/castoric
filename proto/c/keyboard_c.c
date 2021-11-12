

#define KEY_Q       0x41
#define KEY_C       0x43
#define KEY_D       0x44
#define KEY_E       0x45
#define KEY_O       0x4F
#define KEY_A       0x51
#define KEY_S       0x53
#define KEY_W       0x5A
#define KEY_Z       0x57
#define KEY_X       0x58

#define KEY_Y       0x59
#define KEY_H       0x48
#define KEY_T       0x54
#define KEY_U       0x55
#define KEY_G       0x47
#define KEY_J       0x4A
#define KEY_L       0x4C

#define KEY_UP      0x01
#define KEY_DOWN    0x03
#define KEY_LEFT    0x02
#define KEY_RIGHT   0x04

#define KEY_ESCAPE  0x1B

char keyForward         = KEY_UP;
char keyBackward        = KEY_DOWN;
char keyTurnLeft        = KEY_LEFT;
char keyTurnRight       = KEY_RIGHT;
char keyStraffeLeft     = KEY_X;
char keyStraffeRight    = KEY_C;
char keyQuit            = KEY_ESCAPE;

unsigned char keybconfig        = 0; // 0 : ArrowKeys + XC,  1: AZEQSD , 2 : TYUGHJ
unsigned char soundenabled      = 0; // 0 : No Sound, 1 = Sound Enabled

void setKeyboardConfig(){
    if (keybconfig == 0) {
        keyForward         = KEY_UP;
        keyBackward        = KEY_DOWN;
        keyTurnLeft        = KEY_LEFT;
        keyTurnRight       = KEY_RIGHT;
        keyStraffeLeft     = KEY_X;
        keyStraffeRight    = KEY_C;
        keyQuit            = KEY_ESCAPE;
    } else if (keybconfig == 1) {
        keyForward         = KEY_Z;
        keyBackward        = KEY_S;
        keyTurnLeft        = KEY_A;
        keyTurnRight       = KEY_E;
        keyStraffeLeft     = KEY_Q;
        keyStraffeRight    = KEY_D;
        keyQuit            = KEY_ESCAPE;
    } else if (keybconfig == 2) {
        keyForward         = KEY_Y;
        keyBackward        = KEY_H;
        keyTurnLeft        = KEY_T;
        keyTurnRight       = KEY_U;
        keyStraffeLeft     = KEY_G;
        keyStraffeRight    = KEY_J;
        keyQuit            = KEY_ESCAPE;
    }
}

