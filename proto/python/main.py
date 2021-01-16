import math

import angle
import trigo
import dda
import scene

# import display

FOV_IN_DEGREES          = 66
NUMBER_OF_SLICE         = 4

glCamPosX, glCamPosY    = 0, 0
glCamRotZ               = 0

RayLeftAlpha, RayRightAlpha = 0, 0

lPointsX                = []
lPointsY                = []
lWallsPt1               = []
lWallsPt2               = []

rayNbPoints, rayNbWalls = 0, 0

RayIdXPoint1, RayIdXPoint2 = 0,0
RayCurrentWall          = 0
RayNbSlice              = 0
InterpAngleLeft         = 0
InterpAngleRight        = 0
InterpIdxLeft           = 0
RayWallLog              = 0
RayAlpha, RaySliceIdx   = 0, 0
RayDistance             = 0

tab_denom               = None
lWallsCosBeta           = []
rayzbuffer              = []
raywall                 = []

lAngle                  = []
isVisible               = []
isFront                 = []

def initCamera():
    global glCamPosX, glCamPosY, glCamRotZ, RayLeftAlpha, RayRightAlpha
    glCamPosX               = 0
    glCamPosY               = 0
    glCamRotZ               = 64
    RayLeftAlpha            = round(glCamRotZ + angle.toFixAngle(math.radians(FOV_IN_DEGREES/2)))
    RayRightAlpha           = round(glCamRotZ - angle.toFixAngle(math.radians(FOV_IN_DEGREES/2)))
    

def initScene ():
    global rayNbPoints, rayNbWalls
    rayNbPoints = len(scene.tabPoints)
    rayNbWalls = len(scene.tabWalls)

    for jj in range (rayNbPoints):
        lPointsX.append(scene.tabPoints[jj][0])
        lPointsY.append(scene.tabPoints[jj][1])

    for jj in range (rayNbWalls):
        lWallsPt1.append(scene.tabWalls[jj][0])
        lWallsPt2.append(scene.tabWalls[jj][1])

    precalculateWallsAngle()

def precalculateWallsAngle():

    for idxWall in range(rayNbWalls):

        idxPt1 = lWallsPt1[idxWall]
        idxPt2 = lWallsPt2[idxWall]

        dX = lPointsX[idxPt2]-lPointsX[idxPt1]
        dY = lPointsY[idxPt2]-lPointsY[idxPt1]

        if (dX == 0):
            lWallsCosBeta.append(0)
        elif (dY == 0):
            if (dX > 0):
                lWallsCosBeta.append(32)
            else:
                lWallsCosBeta.append(-32)
        else:
            # Not aligned walls not handled
            pass

def rayInitCasting():
    global rayzbuffer, raywall
    rayzbuffer      = [255] * NUMBER_OF_SLICE
    raywall         = [255] * NUMBER_OF_SLICE

def IS_FRONT(idxPoint):
    return abs(lAngle[idxPoint])<64

def IS_VISIBLE(idxPoint):
    return abs(lAngle[idxPoint]) < angle.toFixAngle(math.radians(FOV_IN_DEGREES/2))

def rayProcessPoints():
    global RayIdXPoint1
    for RayIdXPoint1 in range (rayNbPoints):

        lAngle.append(trigo.atan2(lPointsY[RayIdXPoint1]-glCamPosY, lPointsX[RayIdXPoint1]-glCamPosX) - glCamRotZ)

        isVisible.append(1 if IS_VISIBLE(RayIdXPoint1) else 0)
        isFront.append(1 if IS_FRONT(RayIdXPoint1) else 0)

def preDraw():
    global tab_denom, RayWallLog
    if (lWallsCosBeta[RayCurrentWall] == 0):    # Wall is O,y aligned   
        RayWallLog = trigo.log2_tab[abs(lPointsX[RayIdXPoint1]-glCamPosX)]
        tab_denom = trigo.tab_1overcos
    else:                                    # Wall is O,x aligned
        RayWallLog = trigo.log2_tab[abs(lPointsY[RayIdXPoint1]-glCamPosY)]
        tab_denom = trigo.tab_1oversin

def toto():
    global RayAlpha, RaySliceIdx, RayNbSlice, tab_denom

    RayAlpha        = InterpAngleLeft
    RaySliceIdx     = InterpIdxLeft

    #if (RayNbSlice == 0): return

#ifdef DEBUG
    print (f"Wall {RayCurrentWall} from {RayIdXPoint1} to {RayIdXPoint2}, {RayNbSlice} slice from (c={RaySliceIdx} a={RayAlpha}) to (c={RaySliceIdx+RayNbSlice}, a={RayAlpha-RayNbSlice*2})");
#endif
    while(RayNbSlice != 0):
        RayDistance = RayWallLog + tab_denom[RayAlpha];
        # RayDistance = longexp(RayDistance);
#ifdef DEBUG
        print (f"RaySliceIdx = {RaySliceIdx} RayAlpha = {RayAlpha}, RayDistance={RayDistance}");
#endif
        if (rayzbuffer[RaySliceIdx] > RayDistance):
            rayzbuffer[RaySliceIdx] = RayDistance;
            raywall[RaySliceIdx] = RayCurrentWall;
        
        RaySliceIdx += 1;

        RayAlpha-=2 # FIXME SLICE_ANGULAR_INCREMENT
        RayNbSlice -= 1
        if (RayNbSlice == 0): break


def drawFullVisibleWall():
    global InterpAngleLeft, InterpAngleRight, RayNbSlice, InterpIdxLeft 
    preDraw()
    if (lAngle[RayIdXPoint1] > lAngle[RayIdXPoint2]):
        InterpIdxLeft = (NUMBER_OF_SLICE - lAngle[RayIdXPoint1]) >> 1
        InterpAngleLeft=lAngle[RayIdXPoint1]+ glCamRotZ
        InterpAngleRight=lAngle[RayIdXPoint2]+ glCamRotZ
        RayNbSlice = ((lAngle[RayIdXPoint1] - lAngle[RayIdXPoint2]) >> 1 )+1
    else:
        InterpIdxLeft = (NUMBER_OF_SLICE - lAngle[RayIdXPoint2]) >> 1
        InterpAngleLeft=lAngle[RayIdXPoint2]+ glCamRotZ
        InterpAngleRight=lAngle[RayIdXPoint1]+ glCamRotZ
        RayNbSlice = ((lAngle[RayIdXPoint2] - lAngle[RayIdXPoint1]) >> 1 )+1
    toto()

def drawRightCuttingWall1Visible():
    global InterpAngleLeft, InterpAngleRight, RayNbSlice, InterpIdxLeft 
    preDraw()
    InterpIdxLeft = (NUMBER_OF_SLICE - lAngle[RayIdXPoint1]) >> 1
    InterpAngleLeft=lAngle[RayIdXPoint1]+glCamRotZ
    InterpAngleRight=RayRightAlpha
    RayNbSlice = (((InterpAngleLeft - InterpAngleRight)&0xFF) >> 1)+1  
    toto()

def drawLeftCuttingWall1Visible():
    global InterpAngleLeft, InterpAngleRight, RayNbSlice, InterpIdxLeft 
    preDraw()
    InterpAngleLeft=RayLeftAlpha
    InterpAngleRight=lAngle[RayIdXPoint1]+ glCamRotZ
    InterpIdxLeft = 0
    RayNbSlice = (((InterpAngleLeft - InterpAngleRight)&0xFF) >> 1)+1
    toto()

def drawRightCuttingWall2Visible():
    global InterpAngleLeft, InterpAngleRight, RayNbSlice, InterpIdxLeft 
    preDraw()
    InterpAngleLeft=lAngle[RayIdXPoint2]+glCamRotZ
    InterpAngleRight=RayRightAlpha
    InterpIdxLeft = (NUMBER_OF_SLICE - lAngle[RayIdXPoint2]) >> 1
    RayNbSlice = (((InterpAngleLeft - InterpAngleRight)&0xFF) >> 1)+1
    toto()

def drawLeftCuttingWall2Visible():
    global InterpAngleLeft, InterpAngleRight, RayNbSlice, InterpIdxLeft 
    preDraw()
    InterpAngleLeft=RayLeftAlpha
    InterpAngleRight=lAngle[RayIdXPoint2]+ glCamRotZ
    InterpIdxLeft = 0
    RayNbSlice = (((InterpAngleLeft - InterpAngleRight)&0xFF) >> 1)+1
    toto()

def drawFullCrossingWall():
    global InterpAngleLeft, InterpAngleRight, RayNbSlice, InterpIdxLeft
    preDraw()
    InterpAngleLeft     =RayLeftAlpha
    InterpAngleRight    =RayRightAlpha
    RayNbSlice          = NUMBER_OF_SLICE
    InterpIdxLeft       = 0
    toto()

def rayProcessWalls():
    global RayCurrentWall, RayIdXPoint1, RayIdXPoint2
    for RayCurrentWall in range (rayNbWalls):

        RayIdXPoint1        = lWallsPt1[RayCurrentWall];
        RayIdXPoint2        = lWallsPt2[RayCurrentWall];

        if (isVisible[RayIdXPoint1]):
            if (isVisible[RayIdXPoint2]):
                drawFullVisibleWall()
            else:
                # Point 1 is visible and Point 2 is not in FOV
                if (lAngle[RayIdXPoint1] > 0):
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)):
                        drawLeftCuttingWall1Visible()
                    else:
                        if (abs(lAngle[RayIdXPoint1] - lAngle[RayIdXPoint2]) > 127):
                            drawLeftCuttingWall1Visible()
                        else:
                            drawRightCuttingWall1Visible();

                elif (lAngle[RayIdXPoint1] < 0):
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)):
                        drawRightCuttingWall1Visible();
                    else:
                        if (abs(lAngle[RayIdXPoint1] - lAngle[RayIdXPoint2]) > 127):
                            drawRightCuttingWall1Visible();
                        else:
                            drawLeftCuttingWall1Visible();

                else:
                    if (lAngle[RayIdXPoint2] < 0):
                        drawRightCuttingWall1Visible();
                    else:
                        drawLeftCuttingWall1Visible();

        else:
            if (isVisible[RayIdXPoint2]):
                # Point 2 is visible and Point 1 is not in FOV
                if (lAngle[RayIdXPoint2] > 0):
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)):
                        drawLeftCuttingWall2Visible()
                    else:
                        if (abs(lAngle[RayIdXPoint2] - lAngle[RayIdXPoint1]) > 127):
                            drawLeftCuttingWall2Visible()
                        else:
                            drawRightCuttingWall2Visible()
                elif (lAngle[RayIdXPoint2] < 0):
                    if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)):
                        drawRightCuttingWall2Visible()
                    else:
                        if (abs(lAngle[RayIdXPoint2] - lAngle[RayIdXPoint1]) > 127):
                            drawRightCuttingWall2Visible()
                        else:
                            drawLeftCuttingWall2Visible()
                else: # (lAngle[idxPt1] == 0
                    if (lAngle[RayIdXPoint1] < 0):
                        drawRightCuttingWall2Visible()
                    else:
                        drawLeftCuttingWall2Visible()

            else:
                if (   (isFront[RayIdXPoint1] 
                    or isFront[RayIdXPoint2] )
                    and ((lAngle[RayIdXPoint1] & 0x80) != (lAngle[RayIdXPoint2] & 0x80)) 
                    and (abs(lAngle[RayIdXPoint2]) < 127 - abs(lAngle[RayIdXPoint1])) 
                ):
                    drawFullCrossingWall()


    # Change output from logarithmic scale to linear scale 

    for RaySliceIdx in range (NUMBER_OF_SLICE):
        pass

# #ifdef USE_ANTIFISH
#         rayzbuffer[RaySliceIdx] -= unfish[RaySliceIdx];
# #endif
# #ifdef HIRES
#         TableVerticalPos[RaySliceIdx] =dist2hh(rayzbuffer[RaySliceIdx]);
#         rayzbuffer[RaySliceIdx] = longexp(rayzbuffer[RaySliceIdx]);        
# #else
#         TableVerticalPos[RaySliceIdx] = dist2lh(rayzbuffer[RaySliceIdx]);
#         rayzbuffer[RaySliceIdx] = longexp(rayzbuffer[RaySliceIdx]);
# #endif


def main ():
    print ("hello world")    
    initCamera()
    print (f"[{glCamPosX}, {glCamPosY}], ({RayLeftAlpha} {glCamRotZ} {RayRightAlpha})")
    initScene()
    print (f"nbPoints = {rayNbPoints}, nbWalls = {rayNbWalls}")
    rayInitCasting()
    rayProcessPoints()
    rayProcessWalls()

if __name__ == "__main__":
    main()
