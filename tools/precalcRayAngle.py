import math
import codegen

def toFixAngle(angle_radian):
    return angle_radian*128/math.pi

def rayAngles (fov_angle_radian, number_of_slice):
    
    cameraPlaneLength       = 2*math.tan(fov_angle_radian/2)
    screenIncrementLength   = cameraPlaneLength/(number_of_slice-1)

    for ii in range (number_of_slice):
        k               = number_of_slice - 1 - 2*ii
        currentAngle    = math.atan (k*screenIncrementLength/2)
        yield round(currentAngle*128/math.pi)

RAD2FIX = 128/math.pi

def unfish (tabAngles):
    tab_unfish = []
    for angle in tabAngles:
        #a= (ii-20)*2/RAD2FIX
        a=angle/RAD2FIX
        v= round(32*math.log2(1.0/math.cos(a)))
        tab_unfish.append(v)
    return tab_unfish

def rayAngle2Col (ray_angle_radian, fov_angle_radian, number_of_slice):

    cameraPlaneLength       = 2*math.tan(fov_angle_radian/2)
    screenIncrementLength   = cameraPlaneLength/(number_of_slice-1)

    if (number_of_slice%2 == 0):
        return int (number_of_slice//2 - math.tan(ray_angle_radian)/screenIncrementLength)
    else:
        return int (number_of_slice//2 - (math.tan(ray_angle_radian)-screenIncrementLength/2)/screenIncrementLength)

def main ():
    
    FOV_IN_DEGREES          = 112
    NUMBER_OF_SLICE         = 40
    tabAngles               = list(rayAngles(math.radians(FOV_IN_DEGREES), NUMBER_OF_SLICE))
    stRayAngles             = codegen.buffer2cCode("tabRayAngles", "signed char", tabAngles)
    print (stRayAngles)
    tabCol                  = []
    for angle in range (tabAngles[0], tabAngles[-1]-1, -1):
        idxCol = rayAngle2Col (angle*math.pi/128, math.radians(FOV_IN_DEGREES), NUMBER_OF_SLICE)
        #print (angle, idxCol , tabAngles [idxCol] )
        tabCol.append (idxCol)
    stAngles2Col            = codegen.buffer2cCode("tabAngle2Col", "unsigned char", tabCol)
    print (stAngles2Col)
    
    tabUnfish               = unfish (tabAngles)
    stTabUnfish             = codegen.buffer2cCode("unfish", "unsigned int", tabUnfish)
    print (stTabUnfish)

if __name__ == "__main__":
    main()
