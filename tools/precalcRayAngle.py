# 
# Author : Jean-Baptiste PERIN
# Date : 2021 


import math
import codegen
import config

def toFixAngle(angle_radian):
    return angle_radian*128/math.pi



def unfish (tabAngles):
    tab_unfish = []
    for angle in tabAngles:
        #a= (ii-20)*2/RAD2FIX
        a=angle/config.RAD_TO_FIX
        v= round(32*math.log2(1.0/math.cos(a)))
        tab_unfish.append(v)
    return tab_unfish

def rayAngle2Col (ray_angle_radian):

    cameraPlaneLength       = 2*math.tan(math.radians(config.HFOV_IN_DEGREES/2))
    screenIncrementLength   = cameraPlaneLength/(config.NUMBER_OF_SLICE-1)

    if (config.NUMBER_OF_SLICE%2 == 0):
        return int (config.NUMBER_OF_SLICE//2 - math.tan(ray_angle_radian)/screenIncrementLength)
    else:
        return int (config.NUMBER_OF_SLICE//2 - (math.tan(ray_angle_radian)-screenIncrementLength/2)/screenIncrementLength)

def main ():
    
    tabAngles               = list(config.rayAngles())
    stRayAngles             = codegen.buffer2cCode("tabRayAngles", "signed char", tabAngles)
    print (stRayAngles)

    tabCol                  = []
    for angle in range (tabAngles[0], tabAngles[-1]-1, -1):
        idxCol = rayAngle2Col (angle*config.FIX_TO_RAD)
        tabCol.append (idxCol)
    stAngles2Col            = codegen.buffer2cCode("tabAngle2Col", "unsigned char", tabCol)
    print (stAngles2Col)
    
    # tabUnfish               = unfish (tabAngles)
    # stTabUnfish             = codegen.buffer2cCode("unfish", "unsigned int", tabUnfish)
    # print (stTabUnfish)

if __name__ == "__main__":
    main()
