import math

def toFixAngle(angle_radian):
    return angle_radian*128/math.pi

def rayAngles (fov_angle_radian, number_of_slice):
    
    cameraPlaneLength       = 2*math.tan(fov_angle_radian/2)
    screenIncrementLength   = cameraPlaneLength/(number_of_slice-1)

    for ii in range (number_of_slice):
        k               = number_of_slice - 1 - 2*ii
        currentAngle    = math.atan (k*screenIncrementLength/2)
        yield currentAngle

def main ():
    
    FOV_IN_DEGREES          = 90
    NUMBER_OF_SLICE         = 4

    print (list(map(math.degrees,rayAngles(math.radians(FOV_IN_DEGREES), NUMBER_OF_SLICE))))
    
if __name__ == "__main__":
    main()
