;; Assembly routines for collision detection
;; Author : Jean-Baptiste PERIN
;; Date : 2021
;; 

_collideX        .dsb 1
_collideY        .dsb 1
_isColliding     .dsb 1

#ifndef  USE_C_GENERIC_COLLISION
_collideWall:
.(



;;    isColliding         = 0;
;;    RayCurrentWall = rayNbWalls;
    lda     #0
    sta     _isColliding
    lda     _rayNbWalls
    sta     _RayCurrentWall
    dec     _RayCurrentWall

;;    do {
collideWallLoop:

;;        RayCurrentWall --;
;;        RayIdXPoint1        = lWallsPt1[RayCurrentWall];
;;        RayIdXPoint2        = lWallsPt2[RayCurrentWall];

        ldy         _RayCurrentWall
        lda         _lWallsPt1,Y
        sta         _RayIdXPoint1
        lda         _lWallsPt2,Y
        sta         _RayIdXPoint2

;;        if (lWallsCosBeta[RayCurrentWall] == 0){    // Wall is O,y aligned   
        ldy         _RayCurrentWall
        lda         _lWallsCosBeta, Y
        beq         WallIsOyAligned
        jmp         WallIsOxAligned
WallIsOyAligned
;;            if (collideX == lPointsX[RayIdXPoint1]) {
            ldy         _RayIdXPoint1
            lda         _lPointsX, y
            cmp         _collideX
            bne         EndIfCollideX         
;;                if (
;;                    ((collideY >= lPointsY[RayIdXPoint1]) && (collideY <= lPointsY[RayIdXPoint2]))
;;                    || ((collideY >= lPointsY[RayIdXPoint2]) && (collideY <= lPointsY[RayIdXPoint1]))
;;                ) {
;;    if (collideY == P1Y) {
;;        return 1
;;    } else if (CollideY > P1Y) {
;;        if (colideY <= P2Y) {
;;            return 1
;;        }
;;    } else {
;;        if (colideY >= P2Y) {
;;            return 1
;;        }
;;    }
                lda         _collideY
                ldy         _RayIdXPoint1
                cmp         _lPointsY, y
                beq         YCollidingWall
                bpl         collideYGreaterThanP1Y
                jmp         collideYLowerThanP1Y

collideYGreaterThanP1Y
                ldy         _RayIdXPoint2
                cmp         _lPointsY, y
                beq         YCollidingWall
                bmi         YCollidingWall
                jmp         EndIfYinWall

collideYLowerThanP1Y                
                ldy         _RayIdXPoint2
                cmp         _lPointsY, y
                bpl         YCollidingWall
                jmp         EndIfYinWall

YCollidingWall
;;                    isColliding         = 1;
                    lda             #1
                    sta             _isColliding
;;                    return;
                    ;; jmp             collideWallDone
                    rts
EndIfYinWall
;;                }
EndIfCollideX
;;            }
        jmp         EndIfWallIsOyAligned
;;        } else {                                    // Wall is O,x aligned
WallIsOxAligned
;;            if (_collideY == lPointsY[RayIdXPoint1]) {
            ldy         _RayIdXPoint1
            lda         _lPointsY, y
            cmp         _collideY
            bne         EndIfCollideY         
;;                if (
;;                    ((collideX >= lPointsX[RayIdXPoint1]) && (collideX <= lPointsX[RayIdXPoint2]))
;;                    || ((collideX >= lPointsX[RayIdXPoint2]) && (collideX <= lPointsX[RayIdXPoint1]))
;;                ) {
;;    if (collideX == P1X) {
;;        return 1
;;    } else if (CollideX > P1X) {
;;        if (colideX <= P2X) {
;;            return 1
;;        }
;;    } else {
;;        if (colideX >= P2X) {
;;            return 1
;;        }
;;    }
                lda         _collideX
                ldy         _RayIdXPoint1
                cmp         _lPointsX, y
                beq         XCollidingWall
                bpl         collideXGreaterThanP1X
                jmp         collideXLowerThanP1X

collideXGreaterThanP1X
                ldy         _RayIdXPoint2
                cmp         _lPointsX, y
                beq         XCollidingWall
                bmi         XCollidingWall
                jmp         EndIfXinWall

collideXLowerThanP1X              
                ldy         _RayIdXPoint2
                cmp         _lPointsX, y
                bpl         XCollidingWall
                jmp         EndIfXinWall

XCollidingWall
;;                    isColliding         = 1;
                    lda             #1
                    sta             _isColliding
;;                    return;
                    ;; jmp             collideWallDone
                    rts
EndIfXinWall
;;                }
EndIfCollideY
;;            }
;;        }

EndIfWallIsOyAligned
;;    } while (RayCurrentWall != 0);
    dec     _RayCurrentWall
    bmi     collideWallEndLoop
    jmp     collideWallLoop

collideWallEndLoop:
collideWallDone:
.)
    rts
#endif  USE_C_GENERIC_COLLISION

