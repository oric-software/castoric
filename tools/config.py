import math

WALL_HEIGHT             = 6
CAMERA_PLANE_HEIGHT     = 8
HFOV_IN_DEGREES         = 112
VIEWPORT_HEIGHT         = 64
VIEWPORT_START_COLUMN   = 2
VIEWPORT_WIDTH          = 78
NUMBER_OF_SLICE         = 78

TEXTURE_SIZE            = 32
RAD_TO_FIX              = 128/math.pi
FIX_TO_RAD              = math.pi/128

VFOV_IN_DEGREES         = HFOV_IN_DEGREES * VIEWPORT_HEIGHT / VIEWPORT_WIDTH
FOCAL                   = CAMERA_PLANE_HEIGHT * math.cos(math.radians(VFOV_IN_DEGREES/2)) / math.sin(math.radians(VFOV_IN_DEGREES/2))


def rayAngles ():
    
    cameraPlaneLength       = 2*math.tan(math.radians(HFOV_IN_DEGREES/2))
    screenIncrementLength   = cameraPlaneLength/(NUMBER_OF_SLICE-1)

    for ii in range (NUMBER_OF_SLICE):
        k               = NUMBER_OF_SLICE - 1 - 2*ii
        currentAngle    = math.atan (k*screenIncrementLength/2)
        yield round(currentAngle*128/math.pi)

HALF_FOV_FIX_ANGLE      = list(rayAngles ())[0]



def main ():

    print (list(rayAngles ()))

if __name__ == "__main__":
    main()