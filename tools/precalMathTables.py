
# Author : Jean-Baptiste PERIN
# Date : 2021 
import math
import codegen

WALL_HEIGHT             = 6
VIEWPORT_HEIGHT         = 200
VIEWPORT_WIDTH          = 320

RAD_TO_FIX              = 128/math.pi
HFOV_IN_DEGREES         = 112
NUMBER_OF_SLICE         = 80

H=6
VFOV_IN_DEGREES         = HFOV_IN_DEGREES * VIEWPORT_HEIGHT / VIEWPORT_WIDTH
FOCAL                   = H * math.cos(math.radians(VFOV_IN_DEGREES/2)) / math.sin(math.radians(VFOV_IN_DEGREES/2))
print (VFOV_IN_DEGREES, FOCAL)

def genUnlogd2hh():
    tab_d2hh = []
    for ii in range (0,256):
        v = WALL_HEIGHT * FOCAL / 2**(ii/32)# (VIEWPORT_HEIGHT - FOCAL*WALL_HEIGHT/(2**(ii/32))) / 2
        tab_d2hh.append(round (v))
    return tab_d2hh

def genOldUnlogd2hh():
    tab_d2hh = []
    # ideal = [round((SCREEN_HEIGHT - RAD_TO_FIX*4*math.atan2(WALL_HEIGHT, 2**(ii/32)))/2) for ii in range (0, 256)]
    # for ii in range (0,256):
    #     v = min(SCREEN_HEIGHT/2,max(0,ideal[ii]))
    #     tab_d2hh.append(round(v))
    ideal = [round((VIEWPORT_HEIGHT - RAD_TO_FIX*4*math.atan2(WALL_HEIGHT, 2**(ii/32)))/2) for ii in range (0, 256)]
    for ii in range (0,256):
        v = min(VIEWPORT_HEIGHT/2,max(0,ideal[ii]))
        tab_d2hh.append(round((100-v)/4))
    return tab_d2hh

def main():
    unlogd2hh = genUnlogd2hh()
    print (codegen.buffer2cCode("unlogd2hh", "unsigned char", unlogd2hh))
    # print (codegen.buffer2cCode("oldunlogd2hh", "unsigned char", genOldUnlogd2hh()))

if __name__ == "__main__":
    main()
