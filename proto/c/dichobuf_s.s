
#include "config.h"

#ifndef USE_C_DICHOBUF
.zero

_dichoInsertPos .dsb 1

_dichoInsertVal .dsb 1
_dichoInsertIdx .dsb 1

.text

_dichoInit:
.(
    lda #0
    sta _dichoNbVal
.)
    rts


_dichoASMInsert:
.(

;;    if (0==(insertPos = dichoNbVal)) return insertPos;
;;
;;    do {
;;        insertPos-=1;
;;    } while ((insertPos != 0) && (tabDichoVals[insertPos] > val));
;;    if (tabDichoVals[insertPos] <= val) insertPos+=1;
;;    return insertPos;


    lda _dichoNbVal
    sta _dichoInsertPos
    beq insertPositionFound

dichoSearchLoop
        dec _dichoInsertPos

    beq dichoSearchEndLoop
    ldy _dichoInsertPos
    lda _tabDichoVals,y
    cmp _dichoInsertVal
    bcc dichoSearchEndLoop
    beq dichoSearchEndLoop
    jmp dichoSearchLoop

dichoSearchEndLoop   
    ldy _dichoInsertPos
    lda _dichoInsertVal
    cmp _tabDichoVals,y
    bcc insertPositionFound
        inc _dichoInsertPos
        
insertPositionFound

;;    idx = dichoNbVal;
;;    while (idx != pos) {
;;        tabDichoVals[idx] = tabDichoVals[idx-1];
;;        tabDichoIdxs[idx] = tabDichoIdxs[idx-1];
;;        idx     -= 1;
;;    }
;;    tabDichoVals[idx] = val;
;;    tabDichoIdxs[idx] = index;
;;    dichoNbVal +=1;
    ldy _dichoNbVal
    cpy _dichoInsertPos
    beq dichoInsertEndLoop
dichoInsertLoop
        dey
        lda _tabDichoVals, y
        ldx _tabDichoIdxs, y
        iny
        sta _tabDichoVals, y
        txa
        sta _tabDichoIdxs, y
        dey
    cpy _dichoInsertPos
    bne dichoInsertLoop
dichoInsertEndLoop

    lda _dichoInsertVal
    sta _tabDichoVals, y
    lda _dichoInsertIdx
    sta _tabDichoIdxs, y
    inc _dichoNbVal

dichoInsertDone
.)
    rts

#endif //USE_C_DICHOBUF    