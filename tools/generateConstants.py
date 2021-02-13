

import config

strConstants = f"""// Generated file. Do not modify by hand.
// To change values, edit config.py and regenerate with:
// python tools\generateConstants.py > proto\c\constants.h
#define NUMBER_OF_SLICE                 {config.NUMBER_OF_SLICE}

#define VIEWPORT_HEIGHT                 {config.VIEWPORT_HEIGHT}

#define TEXTURE_SIZE                    {config.TEXTURE_SIZE}

#define VIEWPORT_UP_LINE                0
#define VIEWPORT_DOWN_LINE              64
#define VIEWPORT_LEFT_COLUMN            2
#define VIEWPORT_RIGHT_COLUMN           78
#define EMPTY_ALPHA                     0


//((unsigned int)0xA000)
#define HIRES_SCREEN_ADDRESS            40960

#define NEXT_SCANLINE_INCREMENT         40
#define TEXT_SCREEN_HEIGHT              26
#define NB_LESS_LINES_4_COLOR           2
"""


def main ():
    print (strConstants)

if __name__ == "__main__":
    # execute only if run as a script
    main()    
