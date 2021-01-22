import math

def toFixAngle(angle_radian):
    return angle_radian*128/math.pi

def rayAngles (fov_angle_radian, number_of_slice):
    
    cameraPlaneLength       = 2*math.tan(fov_angle_radian/2)
    screenIncrementLength   = cameraPlaneLength/(number_of_slice-1)

    for ii in range (number_of_slice):
        k               = number_of_slice - 1 - 2*ii
        currentAngle    = math.atan (k*screenIncrementLength/2)
        yield round(currentAngle*128/math.pi)

def rayAngle2Col (ray_angle_radian, fov_angle_radian, number_of_slice):

    cameraPlaneLength       = 2*math.tan(fov_angle_radian/2)
    screenIncrementLength   = cameraPlaneLength/(number_of_slice-1)

    if (number_of_slice%2 == 0):
        return int (number_of_slice//2 - math.tan(ray_angle_radian)/screenIncrementLength)
    else:
        return int (number_of_slice//2 - (math.tan(ray_angle_radian)-screenIncrementLength/2)/screenIncrementLength)


def main ():
    
    FOV_IN_DEGREES          = 20

    NUMBER_OF_SLICE         = 5

    tabAngles               = list(rayAngles(math.radians(FOV_IN_DEGREES), NUMBER_OF_SLICE))

    print (tabAngles)
    tabCol                  = []
    for angle in range (tabAngles[0], tabAngles[-1]-1, -1):
        idxCol = rayAngle2Col (angle*math.pi/128, math.radians(FOV_IN_DEGREES), NUMBER_OF_SLICE)
        # print (angle, idxCol, tabAngles[idxCol])
        tabCol.append(idxCol)
    print (tabCol)
    
if __name__ == "__main__":
    main()
