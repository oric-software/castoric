
extern unsigned char collideX   ;
extern unsigned char collideY   ;
extern unsigned char isColliding;



#ifdef USE_C_GENERIC_COLLISION

void collideWall() {
    
    isColliding         = 0;
    RayCurrentWall = rayNbWalls;
    do {
        RayCurrentWall --;
        RayIdXPoint1        = lWallsPt1[RayCurrentWall];
        RayIdXPoint2        = lWallsPt2[RayCurrentWall];

        if (lWallsCosBeta[RayCurrentWall] == 0){    // Wall is O,y aligned   
            if (rayCamPosX == lPointsX[RayIdXPoint1]) {
                if (
                    ((rayCamPosY >= lPointsY[RayIdXPoint1]) && (rayCamPosY <= lPointsY[RayIdXPoint2]))
                    || ((rayCamPosY >= lPointsY[RayIdXPoint2]) && (rayCamPosY <= lPointsY[RayIdXPoint1]))
                ) {
                    isColliding         = 1;
                    return;
                }
            }
        } else {                                    // Wall is O,x aligned
            if (rayCamPosY == lPointsY[RayIdXPoint1]) {
                if (
                    ((rayCamPosX >= lPointsX[RayIdXPoint1]) && (rayCamPosX <= lPointsX[RayIdXPoint2]))
                    || ((rayCamPosX >= lPointsX[RayIdXPoint2]) && (rayCamPosX <= lPointsX[RayIdXPoint1]))
                ) {
                    isColliding         = 1;
                    return;
                }
            }
        }
    } while (RayCurrentWall != 0);
}
#endif // USE_C_GENERIC_COLLISION


unsigned char isInWall(signed char X, signed char Y) {
    unsigned char res;

    collideX        = X;
    collideY        = Y;
    collideWall();

    return isColliding;
}
