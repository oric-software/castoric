
## Author : Jean-Baptiste PERIN
## Date : 2021


## [ref config_generate]

import config

strConstants = f"""// Generated file. Do not modify by hand.
// To change values, edit config.py and regenerate with:
// python tools\generateConstants.py > proto\c\constants.h
#define NUMBER_OF_SLICE                 {config.NUMBER_OF_SLICE}

// [ref config_viewport]

#define VIEWPORT_HEIGHT                 {config.VIEWPORT_HEIGHT}
#define VIEWPORT_WIDTH                  {config.NUMBER_OF_SLICE}
#define VIEWPORT_START_COLUMN           {config.VIEWPORT_START_COLUMN}
#define VIEWPORT_START_LINE             {config.VIEWPORT_START_LINE}
#define TEXTURE_SIZE                    {config.TEXTURE_SIZE}
#define HALF_FOV_FIX_ANGLE              {config.HALF_FOV_FIX_ANGLE}
#define EMPTY_ALPHA                     0

// [ref scene_describe]
#define NB_MAX_WALL                     {config.NB_MAX_WALL}
#define NB_MAX_POINT                    {config.NB_MAX_POINT}

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
