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


#undef USE_C_PREDRAW
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
#endif // USE_ASM_PREDRAW

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

    lda _tx
    clc
    bpl Xpositiv
    eor #$ff
    sec
Xpositiv:
    tax
    rol octant

    lda _ty
    clc
    bpl Ypositiv
    eor #$ff
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