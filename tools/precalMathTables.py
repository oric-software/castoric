
# Author : Jean-Baptiste PERIN
# Date : 2021 
import math
import codegen

WALL_HEIGHT     = 6
SCREEN_HEIGHT   = 200
RAD_TO_FIX      = 128/math.pi

def genUnlogd2hh():
    tab_d2hh = []
    ideal = [round((SCREEN_HEIGHT - RAD_TO_FIX*4*math.atan2(WALL_HEIGHT, 2**(ii/32)))/2) for ii in range (0, 256)]
    for ii in range (0,256):
        v = min(SCREEN_HEIGHT/2,max(0,ideal[ii]))
        tab_d2hh.append(round(v))
    return tab_d2hh

def main():
    unlogd2hh = genUnlogd2hh()
    print (codegen.buffer2cCode("unlogd2hh", "unsigned char", unlogd2hh))

if __name__ == "__main__":
    main()
