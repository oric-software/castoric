import math

WALL_HEIGHT             = 6
CAMERA_PLANE_HEIGHT     = 8

HFOV_IN_DEGREES         = 92 # 112
VIEWPORT_WIDTH          = 48 # 74 # 80 # 48 # 48 # Max : 80
VIEWPORT_HEIGHT         = 32 # 60 # 64 # 32 # 32 # Max : 64
VIEWPORT_START_COLUMN   = 16 #  2 #  0 # 32 #  2 # Min : 0
VIEWPORT_START_LINE     = 16 #  2 #  0 # 32 #  0 # Min : 0

NB_MAX_WALL             = 60
NB_MAX_POINT            = 64

NUMBER_OF_SLICE         = VIEWPORT_WIDTH

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