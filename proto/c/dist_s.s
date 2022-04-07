#include "config.h"

#ifndef USE_C_COMPUTELOGDIST
;; void computeLogDistance (){
_computeLogDistance
.(
;;     signed char     deltaX(tmp5), deltaY(tmp5+1);
;;     unsigned char   log2Delta(tmp6);
;;     unsigned int    log2dist(tmp6+1);
;; 
;;     deltaX          = objPosX[engCurrentObjectIdx]-rayCamPosX;
    ldy _engCurrentObjectIdx
    lda _objPosX, y
    sec
    sbc _rayCamPosX
    sta tmp5
;;     deltaY          = objPosY[engCurrentObjectIdx]-rayCamPosY;
    lda _objPosY, y
    sec
    sbc _rayCamPosY
    sta tmp5+1
;; 
;;     if ((deltaX == 0) && (deltaY == 0)){
    lda tmp5
    ora tmp5+1
    bne  endif_01
;;         objLogDistance[engCurrentObjectIdx] = 0;
;;         objAngle[engCurrentObjectIdx] = 0;
        lda #0
        sta _objLogDistance,y
        sta _objAngle,y
        jmp computeLogDistanceDone
;;         return ;
endif_01
;;     }
;;     
;;     objAlpha[engCurrentObjectIdx]  = ATAN2(deltaY, deltaX);
    lda tmp5+1: sta _ty
    lda tmp5: sta _tx
    jsr         _atan2_8
    lda _res : 
    ldy _engCurrentObjectIdx
    sta _objAlpha, y

;;     objAngle[engCurrentObjectIdx]           = objAlpha[engCurrentObjectIdx]-rayCamRotZ;
    sec: sbc _rayCamRotZ: sta _objAngle,Y
;; 
;;     if (abs(deltaX) > abs(deltaY)) {
    lda tmp5
    .(:bpl already_positiv:eor #$FF: sec: adc #1: sta tmp5 :already_positiv:.)
    lda tmp5+1
    .(:bpl already_positiv:eor #$FF: sec: adc #1: sta tmp5+1 :already_positiv:.)
    cmp tmp5
    bcs else_02
;;         log2Delta = log2_tab[(unsigned char)(abs(deltaX))];
            ldy tmp5
            lda _log2_tab, Y
            sta tmp6
;;         objLogDistance[engCurrentObjectIdx] = log2Delta + (unsigned int)tab_1overcos[(unsigned char)objAlpha[engCurrentObjectIdx]];
            ldy _engCurrentObjectIdx
            lda _objAlpha,Y
            tay
            lda _tab_1overcos, Y
            clc 
            adc tmp6
            ldy _engCurrentObjectIdx
            sta _objLogDistance,Y
        jmp endif_02
;;     } else {
else_02
;;         log2Delta = log2_tab[(unsigned char)(abs(deltaY))];
            ldy tmp5+1
            lda _log2_tab, Y
            sta tmp6
;;         objLogDistance[engCurrentObjectIdx] = log2Delta + (unsigned int)tab_1oversin[(unsigned char)objAlpha[engCurrentObjectIdx]];
            ldy _engCurrentObjectIdx
            lda _objAlpha,Y
            tay
            lda _tab_1oversin, Y
            clc 
            adc tmp6
            ldy _engCurrentObjectIdx
            sta _objLogDistance,Y

endif_02
;;     }

computeLogDistanceDone
;; }
.)
    rts
#endif ;; USE_C_COMPUTELOGDIST