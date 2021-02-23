
import config

# [ref config_viewport] 

ficcontent_header = f"""
;; Autogenerated file. Do not modify by hand.
;; Use script clearViewport.py
;; [ref config_viewport] 
#include "config.h"
#ifndef  USE_C_VIEWPORT
_clearViewport
.(
	lda #$40	; pixel eteint
	ldx #VIEWPORT_WIDTH/2	
loop_x
"""	


ficcontent_trailer = f"""
	dex
    beq clearViewportDone
	jmp loop_x
clearViewportDone    
	rts
.)
#endif // USE_C_VIEWPORT
"""

def main ():
    
	content = ficcontent_header
	for ii in range (config.VIEWPORT_HEIGHT * 3):
		content += f"sta HIRES_SCREEN_ADDRESS + VIEWPORT_START_COLUMN/2 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + {ii}),x\n"
	content += ficcontent_trailer
	print (content)

if __name__ == "__main__":
    main()

