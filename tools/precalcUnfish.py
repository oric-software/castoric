# 
# Author : Jean-Baptiste PERIN
# Date : 2021 

import math
import config
import codegen

def unfish ():
    tab_unfish = []
    for angle in list(config.rayAngles()):
        a=angle/config.RAD_TO_FIX
        v= round(32*math.log2(1.0/math.cos(a)))
        tab_unfish.append(v)
    return tab_unfish

def main ():

    tabUnfish               = unfish ()
    stTabUnfish             = codegen.buffer2cCode("unfish", "unsigned char", tabUnfish)
    print (stTabUnfish)

if __name__ == "__main__":
    main()