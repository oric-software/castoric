;; Assembly routines for raycasting
;; Author : Jean-Baptiste PERIN
;; Date : 2021
;; 
#include "config.h"
#define ANGLE_MAX $C0
.zero 

; static unsigned char* tab_denom;
_tab_denom:             .dsb 2

.text

#ifndef USE_C_ZBUFFWALLS
_zbuffWalls:
.(
    lda     _rayNbWalls
    sta     _RayCurrentWall
    dec     _RayCurrentWall
wallsloop:



;;         RayIdXPoint1        = lWallsPt1[RayCurrentWall];
;;         RayIdXPoint2        = lWallsPt2[RayCurrentWall];
;; 
        ldy         _RayCurrentWall
        lda         _lWallsPt1,Y
        sta         _RayIdXPoint1
        lda         _lWallsPt2,Y
        sta         _RayIdXPoint2

;;         if (isVisible[RayIdXPoint1]) {
        ldy         _RayIdXPoint1
        lda         _isVisible,Y

        bne         Point1Visible_00
        jmp         Point1NotVisible_00
Point1Visible_00
;;             if (isVisible[RayIdXPoint2]) {
            ldy         _RayIdXPoint2
            lda         _isVisible,Y
            beq         Point2NotVisible_00

;;                 drawFullVisibleWall();
                jsr     _drawFullVisibleWall
jmp EndIfPoint2Visible_00                
;;             } else {
Point2NotVisible_00
;;                 // Point 1 is visible and Point 2 is not in FOV
;;                 if (lAngle[RayIdXPoint1] > 0){
                ldy         _RayIdXPoint1
                lda         _lAngle,Y
                beq         Angle1Null_00
                bpl         Angle1Positiv
Angle1Null_00
jmp  Angle1NegativeOrNull_00              
Angle1Positiv
;;                     if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                    ldy         _RayIdXPoint1
                    lda         _lAngle,Y
                    ldy         _RayIdXPoint2
                    eor         _lAngle,Y
                    and         #$80
                    bne         AngleDifferentSign_00
;;                         drawLeftCuttingWall1Visible();
                        jsr         _drawLeftCuttingWall1Visible
jmp EndIfAngleSameSign_00
;;                     } else {
AngleDifferentSign_00

                        ldy _RayIdXPoint2
                        lda _lAngle,Y
                        sta reg7
                        ldy _RayIdXPoint1
                        lda _lAngle,Y
                        sec
                        sbc reg7
                        bvc VeryWideAngle_01
                        jsr _drawLeftCuttingWall1Visible
                        jmp endAngleSpecific_01
VeryWideAngle_01
                        jsr _drawRightCuttingWall1Visible
endAngleSpecific_01



;;                     }
EndIfAngleSameSign_00
    jmp EndIfAngle1_00
;; 
Angle1NegativeOrNull_00
;;                 } else if (lAngle[RayIdXPoint1] < 0) {
                ldy         _RayIdXPoint1
                lda         _lAngle,Y
                bpl         Angle1PositivOrNull_01
;;                     if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                    ldy         _RayIdXPoint1
                    lda         _lAngle,Y
                    ldy         _RayIdXPoint2
                    eor         _lAngle,Y
                    and         #$80
                    bne         AngleDifferentSign_01

;;                         drawRightCuttingWall1Visible();
                        jsr         _drawRightCuttingWall1Visible
jmp EndIfAngleSameSign_01
;;                     } else {
AngleDifferentSign_01
                        ldy _RayIdXPoint2
                        lda _lAngle,Y
                        sta reg7
                        ldy _RayIdXPoint1
                        lda _lAngle,Y
                        sec
                        sbc reg7
                        bvc VeryWideAngle_02
                        jsr _drawRightCuttingWall1Visible
                        jmp endAngleSpecific_02
VeryWideAngle_02
                        jsr _drawLeftCuttingWall1Visible
endAngleSpecific_02



;;                     }
EndIfAngleSameSign_01
jmp EndIfAngle1_00
;; 
Angle1PositivOrNull_01
;;                 } else { // (lAngle[idxPt1] < 0)

                        ldy _RayIdXPoint2
                        lda _lAngle,Y
                        bpl PositivPoint2Angle
                            jsr _drawRightCuttingWall1Visible
                        jmp endPositivPoint2Angle
PositivPoint2Angle
                            jsr _drawLeftCuttingWall1Visible
endPositivPoint2Angle


EndIfAngle1_00

;;                 }
EndIfPoint2Visible_00 
;;             }
jmp EndIfPoint1Visible_00
;;         } else {
Point1NotVisible_00
;;             if (isVisible[RayIdXPoint2]) {
            ldy         _RayIdXPoint2
            lda         _isVisible,Y
            bne         Point2Visible_01
            jmp         Point2NotVisible_01
;; 
Point2Visible_01
;;                 // Point 2 is visible and Point 1 is not in FOV
;;                 if (lAngle[RayIdXPoint2] > 0){
                ldy         _RayIdXPoint2
                lda         _lAngle,Y
                beq         Angle2Null_00
                bpl         Angle2Positiv_01
Angle2Null_00
                jmp         Angle2NegativeOrNull_01
Angle2Positiv_01                
;;                     if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                    ldy         _RayIdXPoint1
                    lda         _lAngle,Y
                    ldy         _RayIdXPoint2
                    eor         _lAngle,Y
                    and         #$80
                    bne         AngleDifferentSign_02
;;                         drawLeftCuttingWall2Visible();
                        jsr         _drawLeftCuttingWall2Visible
                        jmp         EndIfAngleSameSign_02
;;                     } else {
AngleDifferentSign_02    

                        ldy _RayIdXPoint1
                        lda _lAngle,Y
                        sta reg7
                        ldy _RayIdXPoint2
                        lda _lAngle,Y
                        sec
                        sbc reg7
                        bvc VeryWideAngle_03
                        jsr _drawLeftCuttingWall2Visible
                        jmp endAngleSpecific_03
VeryWideAngle_03
                        jsr _drawRightCuttingWall2Visible
endAngleSpecific_03



EndIfAngleSameSign_02
;;                     }
jmp         EndIfAngle2Positiv_01
Angle2NegativeOrNull_01
;;                 } else if (lAngle[RayIdXPoint2] < 0) {
                        ldy         _RayIdXPoint2
                        lda         _lAngle, y
                        bmi         Angle2Negativ_02
                        jmp         Angle2Null_01
Angle2Negativ_02                        
;;                     if ((lAngle[RayIdXPoint1] & 0x80) == (lAngle[RayIdXPoint2] & 0x80)) {
                            ldy         _RayIdXPoint1
                            lda         _lAngle,Y
                            ldy         _RayIdXPoint2
                            eor         _lAngle,Y
                            and         #$80
                            bne         AngleDifferentSign_03

;;                         drawRightCuttingWall2Visible();
                                jsr         _drawRightCuttingWall2Visible
                                jmp         EndIfAngleSameSign_03
;;                     } else {
AngleDifferentSign_03

                            ldy _RayIdXPoint1
                            lda _lAngle,Y
                            sta reg7
                            ldy _RayIdXPoint2
                            lda _lAngle,Y
                            sec
                            sbc reg7
                            bvc VeryWideAngle_04
                            jsr _drawRightCuttingWall2Visible
                            jmp endAngleSpecific_04
VeryWideAngle_04
                            jsr _drawLeftCuttingWall2Visible
endAngleSpecific_04

EndIfAngleSameSign_03

;;                     }
        jmp             EndIfAngle2_03
;;                 } else { // (lAngle[idxPt2] == 0
Angle2Null_01

                        ldy _RayIdXPoint1
                        lda _lAngle,Y
                        bpl PositivPoint2Angle_02
                            jsr _drawRightCuttingWall2Visible
                        jmp endPositivPoint2Angle_02
PositivPoint2Angle_02
                            jsr _drawLeftCuttingWall2Visible
endPositivPoint2Angle_02

EndIfAngle2_03
;;                 }
EndIfAngle2Positiv_01
jmp EndIfPoint2Visible_01
;;             } else {
Point2NotVisible_01
;;                 if (   (isFront[RayIdXPoint1] 
;;                     || isFront[RayIdXPoint2] )
;;                     && ((lAngle[RayIdXPoint1] & 0x80) != (lAngle[RayIdXPoint2] & 0x80)) 
;;                     && (abs(lAngle[RayIdXPoint2]) < 127 - abs(lAngle[RayIdXPoint1])) 
;;                 ) {
                    ldy         _RayIdXPoint1
                    lda         _isFront, Y
                    ldy         _RayIdXPoint2
                    ora         _isFront, Y
                    beq         EndIfFullCrossingWall

                    ldy         _RayIdXPoint1
                    lda         _lAngle,Y
                    ldy         _RayIdXPoint2
                    eor         _lAngle,Y
                    and         #$80
                    beq         EndIfFullCrossingWall

                    ldy _RayIdXPoint1   ;; FIXME  // not sure about this way to code the condition.
                    lda _lAngle,Y
                    sta reg7
                    ldy _RayIdXPoint2
                    lda _lAngle,Y
                    sec
                    sbc reg7
                    bvs EndIfFullCrossingWall
;;                     drawFullCrossingWall();
                        jsr         _drawFullCrossingWall
EndIfFullCrossingWall
;;                 }
EndIfPoint2Visible_01
;;             }

EndIfPoint1Visible_00
;;         }

    dec     _RayCurrentWall
    bmi     wallsendloop
    jmp     wallsloop

wallsendloop

.)
    rts

#endif // USE_C_ZBUFFWALLS

#ifndef USE_C_DISTOFFSETSLICES
_distOffsetSlices:
.(

;;     RaySliceIdx = NUMBER_OF_SLICE;
;;     do {
;;          
;;         RaySliceIdx--;


    lda         #NUMBER_OF_SLICE-1
    sta         _RaySliceIdx

loopOnSlices

;;        RayCurrentWall                  = raywall[RaySliceIdx];
;;        tabTexCol [RaySliceIdx]         = 0;
        ldy         _RaySliceIdx
        lda         #0
        sta         _tabTexCol, Y
        lda         _raywall, Y
        sta         _RayCurrentWall

;;        if (RayCurrentWall != 255) {
        eor         #$FF
        bne         AWallOnThisSlice
        jmp         NoWallOnThisSlice
AWallOnThisSlice
;;            raylogdist[RaySliceIdx] = rayzbuffer[RaySliceIdx];
;;            if (unfish[RaySliceIdx] < rayzbuffer[RaySliceIdx])
;;                rayzbuffer[RaySliceIdx] -= unfish[RaySliceIdx];
            ldy         _RaySliceIdx
            lda         _rayzbuffer,Y
            tax
            tya
            asl
            tay
            txa
            sta         _raylogdist,Y
            iny
            lda         #0
            sta        _raylogdist,Y


            ldy         _RaySliceIdx            
            lda         _rayzbuffer,Y
            sec       
            sbc         _unfish,Y
            beq         WallTooClosed
            bmi         WallTooClosed
            sta         _rayzbuffer,Y

WallTooClosed
        
;;            TableVerticalPos[RaySliceIdx] =dist2hh(rayzbuffer[RaySliceIdx]);
        ldy         _RaySliceIdx        
        lda         _rayzbuffer,Y
        tay
        lda         _unlogd2hh, Y
        ldy         _RaySliceIdx
        sta         _TableVerticalPos, Y

;;             rayCurrentAngle       = rayCamRotZ + tabRayAngles[RaySliceIdx];
        ldy         _RaySliceIdx
        lda         _tabRayAngles, Y
        clc
        adc         _rayCamRotZ
        sta         _rayCurrentAngle

;;              if (lWallsCosBeta[RayCurrentWall] == 0)
        ldy         _RayCurrentWall
        lda         _lWallsCosBeta, Y
        beq         WallIsOyAligned
        jmp         WallIsOxAligned
WallIsOyAligned
;;                  if (rayCurrentAngle == 0){
;;                      rayTmp2 = 0;
;;                  } else {
;;                      rayTmp1 = raylogdist[RaySliceIdx] + tabLog2Sin[(unsigned char)rayCurrentAngle];
;;                      if (rayTmp1<0) rayTmp1=0;
;;                      rayTmp2 = longexp(rayTmp1);
;;                      if (rayCurrentAngle <= 0) rayTmp2 = -rayTmp2;
;;                  }

                lda _rayCurrentAngle
                bne rayAngleNotNull_405
                    sta _rayTmp2
                    sta _rayTmp2+1
                jmp endIfAngleNull_405
rayAngleNotNull_405:
                tay
                lda _tabLog2Sin, Y
                tax
                lda _RaySliceIdx
                asl
                tay
                lda _raylogdist,Y
                sta _rayTmp1
                iny
                lda _raylogdist,Y
                sta _rayTmp1+1
                txa
                    bpl notneg_405
                    dec _rayTmp1+1
notneg_405
                    clc
                    adc _rayTmp1
                    sta _rayTmp1
                    lda #0
                    adc _rayTmp1+1
                    sta _rayTmp1+1
                beq skipnullifneg_405
                bpl skipnullifneg_405
                    lda #0
                    sta _rayTmp1
                    sta _rayTmp1+1
skipnullifneg_405:
                ldy _rayTmp1;"   
                lda _tab_exp, y
                sta _rayTmp2
                lda #0
                sta _rayTmp2+1
                lda _rayCurrentAngle
                bpl skipinvert_405
                lda #0 : sec : sbc _rayTmp2 : sta _rayTmp2 : lda #0 : sbc _rayTmp2+1 : sta _rayTmp2+1 
skipinvert_405
endIfAngleNull_405

;;                  rayDeltaY      = lPointsY[lWallsPt1[RayCurrentWall]]-rayCamPosY;
;;                  if (rayDeltaY < 0) {
;;                      rayTmp2      +=  multiCoeff[-rayDeltaY];
;;                  } else {
;;                      rayTmp2      -=  multiCoeff[rayDeltaY];
;;                  }

.(
                ldy _RayCurrentWall
                lda _lWallsPt1, Y
                tay
                lda _lPointsY, Y
                sec
                sbc _rayCamPosY
                sta _rayDeltaY
                bpl DeltaYPositivOrNull
                    eor #$FF:sec: adc#0
                    tay
                    lda _rayTmp2
                    clc
                    adc _multiCoeff,Y
                    sta _rayTmp2
                    lda _rayTmp2+1
                    adc #0
                    sta _rayTmp2+1
                jmp EndifDeltaYNegativ
DeltaYPositivOrNull
                    tay
                    lda _rayTmp2
                    sec
                    sbc _multiCoeff,Y
                    sta _rayTmp2
                    lda _rayTmp2+1
                    sbc #0
                    sta _rayTmp2+1
EndifDeltaYNegativ
.)

        jmp         EndIfWallIsOyAligned
;;              } else {                       // Wall is O,x aligned 
WallIsOxAligned

;;                  if (tabRayAngles[RaySliceIdx] == 0){
;;                      rayTmp2 = 0;
;;                  } else {
;;                      rayTmp1 = raylogdist[RaySliceIdx] + tabLog2Cos[(unsigned char)rayCurrentAngle]; // v0; //tabLog2Cos[rayCurrentAngle];
;;                      if (rayTmp1<0) rayTmp1=0;
;;                      rayTmp2 = longexp(rayTmp1);
;;                      if (abs (rayCurrentAngle) >= 64) {
;;                          rayTmp2 = -rayTmp2; // -(2**(v1/32)) # 
;;                      }
;;                  }
                ;; ldy _RaySliceIdx
                ;; lda _tabRayAngles,Y          
                lda _rayCurrentAngle
                bne AngleNotNull_411
                    sta _rayTmp2
                    sta _rayTmp2+1
                jmp EndifAngleNull_411
AngleNotNull_411
                    ldy _rayCurrentAngle
                    lda _tabLog2Cos, Y
                    tax
                    lda _RaySliceIdx
                    asl
                    tay
                    lda _raylogdist,Y
                    sta _rayTmp1
                    iny
                    lda _raylogdist,Y
                    sta _rayTmp1+1
                    txa
                        bpl notneg_411
                        dec _rayTmp1+1
notneg_411
                    clc
                    adc _rayTmp1
                    sta _rayTmp1
                    lda #0
                    adc _rayTmp1+1
                    sta _rayTmp1+1
                    ;;beq skipnullifneg_411
                    bpl skipnullifneg_411
                        lda #0
                        sta _rayTmp1
                        sta _rayTmp1+1
skipnullifneg_411:
                    ldy _rayTmp1
                    lda _tab_exp, y
                    sta _rayTmp2
                    lda #0
                    sta _rayTmp2+1
                    lda _rayCurrentAngle
                    bpl skipinvert_411
                        eor #$FF
                        sec
                        adc #0
skipinvert_411
                    cmp #64
                    bcc skipInvertTmp2_411
                lda #0 : sec : sbc _rayTmp2 : sta _rayTmp2 : lda #0 : sbc _rayTmp2+1 : sta _rayTmp2+1 
skipInvertTmp2_411
EndifAngleNull_411

;;                  rayDeltaX      = lPointsX[lWallsPt1[RayCurrentWall]]-rayCamPosX;
;;                  if (rayDeltaX < 0){
;;                      rayTmp2      += multiCoeff[-rayDeltaX];
;;                  } else {
;;                      rayTmp2      -= multiCoeff[rayDeltaX];
;;                  }


                ldy _RayCurrentWall
                lda _lWallsPt1, Y
                tay
                lda _lPointsX, Y
                sec
                sbc _rayCamPosX
                sta _rayDeltaX
                bpl DeltaXPositivOrNull
                    eor #$FF:sec: adc#0
                    tay
                    lda _rayTmp2
                    clc
                    adc _multiCoeff,Y
                    sta _rayTmp2
                    lda _rayTmp2+1
                    adc #0
                    sta _rayTmp2+1
                jmp EndifDeltaXNegativ
DeltaXPositivOrNull
                    tay
                    lda _rayTmp2
                    sec
                    sbc _multiCoeff,Y
                    sta _rayTmp2
                    lda _rayTmp2+1
                    sbc #0
                    sta _rayTmp2+1
EndifDeltaXNegativ



EndIfWallIsOyAligned

            ;; if (rayTmp2 < 0) rayTmp2 = -rayTmp2;
            lda         _rayTmp2+1
            bpl         skipInvertRayTmp2_354
                lda #0 : sec : sbc _rayTmp2 : sta _rayTmp2 : lda #0 : sbc _rayTmp2+1 : sta _rayTmp2+1 :

skipInvertRayTmp2_354            
            ;; tabTexCol [RaySliceIdx]        = rayTmp2;
            ldy         _RaySliceIdx
            lda         _rayTmp2
            sta         _tabTexCol, Y

NoWallOnThisSlice

    dec         _RaySliceIdx
    bmi         endLoopOnSlices
    jmp         loopOnSlices
endLoopOnSlices

.)
    rts

#endif // USE_C_DISTOFFSETSLICES


#ifndef USE_C_RAYCAST

_rayInitCasting:
.(
    ldy #NUMBER_OF_SLICE
    lda #$FF
.(: loop:
    sta _rayzbuffer, Y
    sta _raywall, Y
    dey
    bpl loop: .):

.)
    rts
#endif

#ifndef USE_C_PREDRAW
; void preDraw()
_preDraw:
.(
    ldy _RayCurrentWall
    lda _lWallsCosBeta,Y
    bne OxAlignedWall

    ldy _RayIdXPoint1
    lda _lPointsX,Y
    sec
    sbc _rayCamPosX
    bpl PositivOyDeltaWithWall
    eor #$FF
    clc
    adc #1
    PositivOyDeltaWithWall
    tay
    lda _log2_tab,Y
    sta _RayWallLog

    lda #<(_tab_1overcos)
    sta _tab_denom
    lda #>(_tab_1overcos)
    sta _tab_denom+1


    jmp predrawDone
OxAlignedWall:
    ldy _RayIdXPoint1
    lda _lPointsY,Y
    sec
    sbc _rayCamPosY
    bpl PositivOxDeltaWithWall
    eor #$FF
    clc
    adc #1
PositivOxDeltaWithWall
    tay
    lda _log2_tab,Y
    sta _RayWallLog

    lda #<(_tab_1oversin)
    sta _tab_denom
    lda #>(_tab_1oversin)
    sta _tab_denom+1

predrawDone:
    rts
.)
#endif // USE_C_PREDRAW

#ifndef USE_C_TOTO
;; void toto() {
_toto:
.(
    ;; RayAlpha        = InterpAngleLeft;
    ;; RaySliceIdx     = InterpIdxLeft;
    ;; if (RayNbSlice == 0) return;

    lda _InterpAngleLeft
    sta _RayAlpha
    lda _InterpIdxLeft
    sta _RaySliceIdx
    lda _RayNbSlice
    bne RayNbSliceNotNull
    jmp toto_done
RayNbSliceNotNull:

RayLoop:
    ;; while(1){
        ;; // RayDistance = longexp(RayDistance);
        ;; RayDistance = RayWallLog + (unsigned int)tab_denom[(unsigned char)RayAlpha];
        ldy _RayAlpha;
        lda (_tab_denom),Y;
        clc
        adc _RayWallLog;
        sta _RayDistance;
        lda _RayDistance+1;
        adc #0;
        sta _RayDistance+1;


        ;; if (rayzbuffer[RaySliceIdx] > RayDistance){
        ;;      rayzbuffer[RaySliceIdx] = RayDistance;
        ;;      raywall[RaySliceIdx] = RayCurrentWall;
        ;; }

        ldy _RaySliceIdx
        lda _rayzbuffer,Y
        clc
        sbc _RayDistance
        bcc raycloserwall
            lda _RayDistance
            sta _rayzbuffer,Y
            lda _RayCurrentWall
            sta _raywall,Y
raycloserwall:

        ;; if ((--RayNbSlice) == 0) break;
        dec _RayNbSlice
        beq  toto_done

        ;; RaySliceIdx += 1;
        inc _RaySliceIdx

        ;; RayAlpha = rayCamRotZ + tabRayAngles[RaySliceIdx];
        ldy _RaySliceIdx
        lda _tabRayAngles,Y
        clc
        adc _rayCamRotZ
        sta _RayAlpha

    jmp RayLoop
    ;; }
toto_done:
    rts
.)
#endif ;; USE_C_TOTO


#ifndef USE_C_RAYCAST

.zero

octant .dsb 1          ;

_tx .dsb 1
_ty .dsb 1
_res .dsb 1

.text

;https:;;codebase64.org/doku.php?id=base:8bit_atan2_8-bit_angle
_atan2_8:
.(

    lda _ty
    bne YNotNull
    lda _tx
    bpl YNullXPositiv
    lda #$80 ;; -128
    sta _res
    jmp _atan2_8_done
YNullXPositiv
    lda #0
    sta _res
    jmp _atan2_8_done
YNotNull:
    lda _tx
    bne XNotNull
    lda _ty
    bpl XNullYPositiv
    lda #$C0 ;; -64
    sta _res
    jmp _atan2_8_done
XNullYPositiv
    lda #64
    sta _res
    jmp _atan2_8_done
XNotNull:
    clc
    bpl Xpositiv
    eor #$ff
    adc #1
    sec
Xpositiv:
    tax
    rol octant

    lda _ty
    clc
    bpl Ypositiv
    eor #$ff
    adc #1
    sec
Ypositiv:
    tay
    rol octant

    sec
    lda _log2_tab,x
    sbc _log2_tab,y
    bcc *+4
    eor #$ff
    tax

    lda octant
    rol
    and #$07
    tay

    lda _atan_tab, x
    eor _octant_adjust,y
    sta _res
_atan2_8_done    
.)
    rts


#endif // USE_C_RAYCAST

#ifndef USE_C_RAYCAST
; static void drawFullCrossingWall(){
_drawFullCrossingWall:
.(
    ;; preDraw();
    jsr _preDraw

    ; InterpAngleLeft     =RayLeftAlpha;
    lda _RayLeftAlpha
    sta _InterpAngleLeft

    ; RayNbSlice          = NB_SLICES;
    lda #NUMBER_OF_SLICE 
    sta _RayNbSlice

    ; InterpIdxLeft       = 0;
    lda #0
    sta _InterpIdxLeft

    ;; toto();

    jsr _toto
    rts
.)


_drawLeftCuttingWall1Visible
.(

    jsr         _preDraw

    lda         _RayLeftAlpha
    sta         _InterpAngleLeft

    lda         #0
    sta         _InterpIdxLeft

    ldy         _RayIdXPoint1
    lda         _lAngle, Y
    eor         #$FF
    sec     
    adc         #HALF_FOV_FIX_ANGLE
    tay     
    lda         _tabAngle2Col, Y
    sta         _RayNbSlice

    jsr         _toto
.)
    rts

_drawLeftCuttingWall2Visible
.(
    jsr         _preDraw
    lda         _RayLeftAlpha
    sta         _InterpAngleLeft
    lda         #0
    sta         _InterpIdxLeft
    ldy         _RayIdXPoint2
    lda         _lAngle, Y
    eor         #$FF
    sec     
    adc         #HALF_FOV_FIX_ANGLE
    tay     
    lda         _tabAngle2Col, Y
    sta         _RayNbSlice
    jsr         _toto
.)
    rts

_drawRightCuttingWall1Visible
.(
    jsr _preDraw
    ldy _RayIdXPoint1
    lda _lAngle, Y
    tay  ;;save lAngle[RayIdXPoint1] in Y
    clc
    adc _rayCamRotZ
    sta _InterpAngleLeft
    tya  ;;retrieve lAngle[RayIdXPoint1] from Y
    eor #$FF
    sec
    adc #HALF_FOV_FIX_ANGLE
    tay
    lda _tabAngle2Col, Y
    sta _InterpIdxLeft
    eor #$FF
    sec
    adc #NUMBER_OF_SLICE
    sta _RayNbSlice
    jsr _toto
.)
    rts

_drawRightCuttingWall2Visible
.(
    jsr _preDraw
    ldy _RayIdXPoint2
    lda _lAngle, Y
    tay ;; save lAngle[RayIdXPoint2] in Y
    clc
    adc _rayCamRotZ
    sta _InterpAngleLeft
    tya ;; retrieve lAngle[RayIdXPoint2] from Y
    eor #$FF
    sec
    adc #HALF_FOV_FIX_ANGLE
    tay
    lda _tabAngle2Col, Y
    sta _InterpIdxLeft
    eor #$FF
    sec
    adc #NUMBER_OF_SLICE
    sta _RayNbSlice

    jsr _toto

.)
    rts

_drawFullVisibleWall
.(
    ; preDraw();
    jsr _preDraw

    ; if (lAngle[RayIdXPoint1] > lAngle[RayIdXPoint2]){
    ldy _RayIdXPoint2
    lda _lAngle,Y
    ldy _RayIdXPoint1
    sec
    sbc  _lAngle,Y
    bpl Point1OnTheRight

        ldy _RayIdXPoint1
        lda _lAngle, Y
        tax ;; save lAngle[(RayIdXPoint1)]] in X

        clc
        adc _rayCamRotZ
        sta _InterpAngleLeft

        txa ;; retrieve lAngle[(RayIdXPoint1)]] from X
        eor #$FF
        sec
        adc #HALF_FOV_FIX_ANGLE
        tay
        lda _tabAngle2Col, Y
        sta _InterpIdxLeft
        tax ;; save InterpIdxLeft in X

        ldy _RayIdXPoint2
        lda _lAngle, Y
        eor #$FF
        sec
        adc #HALF_FOV_FIX_ANGLE
        tay
        lda _tabAngle2Col, Y
        sta _RayNbSlice

        txa ;; retrieve InterpIdxLeft from X
        eor #$FF
        sec
        adc _RayNbSlice
        sta _RayNbSlice

    jmp ReadyForToto
    ; } else {
Point1OnTheRight:

        ldy _RayIdXPoint2
        lda _lAngle, Y
        tax ;; save lAngle[(RayIdXPoint2)]] in X

        clc
        adc _rayCamRotZ
        sta _InterpAngleLeft

        txa ;; retrieve lAngle[(RayIdXPoint2)]] from X
        eor #$FF
        sec
        adc #HALF_FOV_FIX_ANGLE
        tay
        lda _tabAngle2Col, Y
        sta _InterpIdxLeft
        tax ;; save InterpIdxLeft in X

        ldy _RayIdXPoint1
        lda _lAngle, Y
        eor #$FF
        sec
        adc #HALF_FOV_FIX_ANGLE
        tay
        lda _tabAngle2Col, Y
        sta _RayNbSlice

        txa ;; retrieve InterpIdxLeft from X
        eor #$FF
        sec
        adc _RayNbSlice
        sta _RayNbSlice

ReadyForToto:
    ; toto();
    jsr _toto
.)    
    rts
#endif ;; USE_C_RAYCAST



#ifndef USE_C_PROCESS_POINT
; #define IS_FRONT(i)     (((lAngle[(i)] & ANGLE_MAX) == 0) || ((lAngle[(i)] & ANGLE_MAX) == ANGLE_MAX))
; void rayProcessPoints() {
; 
;     RayIdXPoint1 = rayNbPoints;
; 
;     do {
;         RayIdXPoint1                -= 1;
;         lAngle[RayIdXPoint1]        =  ATAN2(lPointsY[RayIdXPoint1]-rayCamPosY, lPointsX[RayIdXPoint1]-rayCamPosX) - rayCamRotZ;
; 
;         isVisible[RayIdXPoint1]     = (abs(lAngle[RayIdXPoint1])<HALF_FOV_FIX_ANGLE)?1:0;
;         isFront[RayIdXPoint1]       = IS_FRONT(RayIdXPoint1)?1:0;
;     } while ( RayIdXPoint1 != 0 );
; }
_rayProcessPoints
.(
    ldy         _rayNbPoints
loop_00

    dey            
    sty         _RayIdXPoint1

    lda         #0
    sta         _isVisible, Y
    sta         _isFront, Y



    lda         _lPointsY, Y
    sec
    sbc         _rayCamPosY
    sta         _ty

    lda         _lPointsX, Y
    sec
    sbc         _rayCamPosX
    sta         _tx

    jsr         _atan2_8
    ldy         _RayIdXPoint1 ;; FIXME: Restore Y

    lda         _res
    sec
    sbc         _rayCamRotZ
    sta         _lAngle, Y

                                ; IS_FRONT
    and         #ANGLE_MAX
    beq         maskZero
    cmp         #ANGLE_MAX
    bne         skipFront             

maskZero
    lda         #1
    sta         _isFront, Y 
skipFront


    lda         _lAngle, Y
.(
    bpl         angleIsPositiv :  clc: eor #$FF : adc #1: angleIsPositiv:.)

    cmp         #HALF_FOV_FIX_ANGLE
    bcs         angleGreaterFOVov2
    lda         #1
    sta         _isVisible, Y
        
angleGreaterFOVov2

    tya
    bne         loop_00
    
.)
    rts
#endif ;; USE_C_PROCESS_POINT