
;; Autogenerated file. Do not modify by hand.
;; Use script clearVertColBuf.py
;; [ref config_viewport] 
#include "config.h"
#ifndef  USE_C_VERTCOLBUF
_initBufVertCol

patch_sky_color:lda #$03	; Blue Sky
sta _bufVertColRight+0
sta _bufVertColLeft+0
sta _bufVertColRight+1
sta _bufVertColLeft+1
sta _bufVertColRight+2
sta _bufVertColLeft+2
sta _bufVertColRight+3
sta _bufVertColLeft+3
sta _bufVertColRight+4
sta _bufVertColLeft+4
sta _bufVertColRight+5
sta _bufVertColLeft+5
sta _bufVertColRight+6
sta _bufVertColLeft+6
sta _bufVertColRight+7
sta _bufVertColLeft+7
sta _bufVertColRight+8
sta _bufVertColLeft+8
sta _bufVertColRight+9
sta _bufVertColLeft+9
sta _bufVertColRight+10
sta _bufVertColLeft+10
sta _bufVertColRight+11
sta _bufVertColLeft+11
sta _bufVertColRight+12
sta _bufVertColLeft+12
sta _bufVertColRight+13
sta _bufVertColLeft+13
sta _bufVertColRight+14
sta _bufVertColLeft+14
sta _bufVertColRight+15
sta _bufVertColLeft+15
sta _bufVertColRight+16
sta _bufVertColLeft+16
sta _bufVertColRight+17
sta _bufVertColLeft+17
sta _bufVertColRight+18
sta _bufVertColLeft+18
sta _bufVertColRight+19
sta _bufVertColLeft+19
sta _bufVertColRight+20
sta _bufVertColLeft+20
sta _bufVertColRight+21
sta _bufVertColLeft+21
sta _bufVertColRight+22
sta _bufVertColLeft+22
sta _bufVertColRight+23
sta _bufVertColLeft+23
sta _bufVertColRight+24
sta _bufVertColLeft+24
sta _bufVertColRight+25
sta _bufVertColLeft+25
sta _bufVertColRight+26
sta _bufVertColLeft+26
sta _bufVertColRight+27
sta _bufVertColLeft+27
sta _bufVertColRight+28
sta _bufVertColLeft+28
sta _bufVertColRight+29
sta _bufVertColLeft+29
patch_ground_color:lda #$0C	; Green Grass Ground
sta _bufVertColRight+30
sta _bufVertColLeft+30
sta _bufVertColRight+31
sta _bufVertColLeft+31
sta _bufVertColRight+32
sta _bufVertColLeft+32
sta _bufVertColRight+33
sta _bufVertColLeft+33
sta _bufVertColRight+34
sta _bufVertColLeft+34
sta _bufVertColRight+35
sta _bufVertColLeft+35
sta _bufVertColRight+36
sta _bufVertColLeft+36
sta _bufVertColRight+37
sta _bufVertColLeft+37
sta _bufVertColRight+38
sta _bufVertColLeft+38
sta _bufVertColRight+39
sta _bufVertColLeft+39
sta _bufVertColRight+40
sta _bufVertColLeft+40
sta _bufVertColRight+41
sta _bufVertColLeft+41
sta _bufVertColRight+42
sta _bufVertColLeft+42
sta _bufVertColRight+43
sta _bufVertColLeft+43
sta _bufVertColRight+44
sta _bufVertColLeft+44
sta _bufVertColRight+45
sta _bufVertColLeft+45
sta _bufVertColRight+46
sta _bufVertColLeft+46
sta _bufVertColRight+47
sta _bufVertColLeft+47
sta _bufVertColRight+48
sta _bufVertColLeft+48
sta _bufVertColRight+49
sta _bufVertColLeft+49
sta _bufVertColRight+50
sta _bufVertColLeft+50
sta _bufVertColRight+51
sta _bufVertColLeft+51
sta _bufVertColRight+52
sta _bufVertColLeft+52
sta _bufVertColRight+53
sta _bufVertColLeft+53
sta _bufVertColRight+54
sta _bufVertColLeft+54
sta _bufVertColRight+55
sta _bufVertColLeft+55
sta _bufVertColRight+56
sta _bufVertColLeft+56
sta _bufVertColRight+57
sta _bufVertColLeft+57
sta _bufVertColRight+58
sta _bufVertColLeft+58
sta _bufVertColRight+59
sta _bufVertColLeft+59


initBufVertColDone    
	rts

#endif // USE_C_VERTCOLBUF


;; Autogenerated file. Do not modify by hand.
;; Use script copyVertColBuf.py
;; [ref config_viewport] 
#include "config.h"
#ifndef  USE_C_VERTCOLBUF
.zero
colorRight .dsb 1
colorLeft .dsb 1

.text
_drawBufVertCol
	lda _idxScreenCol: lsr: tax 
ldy #0 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+0)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+0)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+0)*3+2),x
ldy #1 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+1)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+1)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+1)*3+2),x
ldy #2 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+2)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+2)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+2)*3+2),x
ldy #3 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+3)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+3)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+3)*3+2),x
ldy #4 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+4)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+4)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+4)*3+2),x
ldy #5 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+5)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+5)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+5)*3+2),x
ldy #6 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+6)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+6)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+6)*3+2),x
ldy #7 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+7)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+7)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+7)*3+2),x
ldy #8 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+8)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+8)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+8)*3+2),x
ldy #9 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+9)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+9)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+9)*3+2),x
ldy #10 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+10)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+10)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+10)*3+2),x
ldy #11 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+11)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+11)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+11)*3+2),x
ldy #12 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+12)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+12)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+12)*3+2),x
ldy #13 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+13)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+13)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+13)*3+2),x
ldy #14 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+14)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+14)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+14)*3+2),x
ldy #15 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+15)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+15)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+15)*3+2),x
ldy #16 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+16)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+16)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+16)*3+2),x
ldy #17 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+17)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+17)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+17)*3+2),x
ldy #18 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+18)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+18)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+18)*3+2),x
ldy #19 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+19)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+19)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+19)*3+2),x
ldy #20 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+20)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+20)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+20)*3+2),x
ldy #21 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+21)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+21)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+21)*3+2),x
ldy #22 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+22)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+22)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+22)*3+2),x
ldy #23 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+23)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+23)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+23)*3+2),x
ldy #24 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+24)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+24)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+24)*3+2),x
ldy #25 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+25)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+25)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+25)*3+2),x
ldy #26 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+26)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+26)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+26)*3+2),x
ldy #27 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+27)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+27)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+27)*3+2),x
ldy #28 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+28)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+28)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+28)*3+2),x
ldy #29 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+29)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+29)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+29)*3+2),x
ldy #30 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+30)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+30)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+30)*3+2),x
ldy #31 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+31)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+31)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+31)*3+2),x
ldy #32 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+32)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+32)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+32)*3+2),x
ldy #33 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+33)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+33)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+33)*3+2),x
ldy #34 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+34)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+34)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+34)*3+2),x
ldy #35 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+35)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+35)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+35)*3+2),x
ldy #36 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+36)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+36)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+36)*3+2),x
ldy #37 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+37)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+37)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+37)*3+2),x
ldy #38 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+38)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+38)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+38)*3+2),x
ldy #39 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+39)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+39)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+39)*3+2),x
ldy #40 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+40)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+40)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+40)*3+2),x
ldy #41 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+41)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+41)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+41)*3+2),x
ldy #42 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+42)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+42)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+42)*3+2),x
ldy #43 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+43)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+43)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+43)*3+2),x
ldy #44 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+44)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+44)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+44)*3+2),x
ldy #45 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+45)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+45)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+45)*3+2),x
ldy #46 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+46)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+46)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+46)*3+2),x
ldy #47 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+47)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+47)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+47)*3+2),x
ldy #48 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+48)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+48)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+48)*3+2),x
ldy #49 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+49)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+49)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+49)*3+2),x
ldy #50 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+50)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+50)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+50)*3+2),x
ldy #51 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+51)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+51)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+51)*3+2),x
ldy #52 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+52)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+52)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+52)*3+2),x
ldy #53 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+53)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+53)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+53)*3+2),x
ldy #54 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+54)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+54)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+54)*3+2),x
ldy #55 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+55)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+55)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+55)*3+2),x
ldy #56 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+56)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+56)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+56)*3+2),x
ldy #57 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+57)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+57)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+57)*3+2),x
ldy #58 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+58)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+58)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+58)*3+2),x
ldy #59 ;; idxBufVertCol
lda _bufVertColLeft,y: sta colorLeft: lda _bufVertColRight,y: sta colorRight:
ldy colorLeft: lda _tabLeftRed, y: ldy colorRight: ora _tabRightRed, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+59)*3+0),x
ldy colorLeft: lda _tabLeftGreen, y: ldy colorRight: ora _tabRightGreen, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+59)*3+1),x
ldy colorLeft: lda _tabLeftBlue, y: ldy colorRight: ora _tabRightBlue, y:
sta HIRES_SCREEN_ADDRESS+NEXT_SCANLINE_INCREMENT*((VIEWPORT_START_LINE+59)*3+2),x


drawBufVertColDone    

	rts
#endif // USE_C_VERTCOLBUF


;; _drawBufVertCol_slow
;; 
;; ;; theAdr  = (unsigned char *)(baseAdr + (int)((multi120_high[VIEWPORT_START_LINE]<<8) | multi120_low[VIEWPORT_START_LINE])); 
;; ldy #VIEWPORT_START_LINE
;; lda _multi120_low,Y
;; clc
;; adc _baseAdr
;; sta _theAdr
;; lda _multi120_high,Y
;; adc _baseAdr+1
;; sta _theAdr+1
;; 
;; 
;; ;; for (idxBufVertCol = 0; idxBufVertCol < VIEWPORT_HEIGHT; ) 
;; lda #0
;; sta _idxBufVertCol
;; loop_over_line:
;; 
;;     ldy _idxBufVertCol
;;     lda _bufVertColLeft,y
;;     sta colorLeft
;;     lda _bufVertColRight,y
;;     sta colorRight
;;     
;;     ldy colorLeft 
;;     lda _tabLeftRed, y
;;     ldy colorRight
;;     ora _tabRightRed, y
;;     
;;     ldy #0
;;     sta (_theAdr),y 
;; 
;;     ldy colorLeft 
;;     lda _tabLeftGreen, y
;;     ldy colorRight
;;     ora _tabRightGreen, y
;; 
;;     ldy #40
;;     sta (_theAdr),y 
;; 
;;     ldy colorLeft 
;;     lda _tabLeftBlue, y
;;     ldy colorRight
;;     ora _tabRightBlue, y
;; 
;;     ldy #80
;;     sta (_theAdr),y 
;;     
;;     clc 
;;     lda _theAdr
;;     adc #120
;;     sta _theAdr
;;     .( : bcc skip: inc _theAdr+1: skip .)
;; 
;; 
;; ;;     idxBufVertCol++;
;; inc _idxBufVertCol
;; 
;; lda _idxBufVertCol
;; cmp #VIEWPORT_HEIGHT
;; beq end_loop_over_line
;; jmp loop_over_line
;; end_loop_over_line:
;; ;; 
;; 
;; drawBufVertColDone    
;; 
;; 	rts



