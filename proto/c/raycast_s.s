;; Assembly routines for raycasting
;; Author : Jean-Baptiste PERIN
;; Date : 2021
;; 
#include "constants.h"
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