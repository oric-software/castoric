
import dda

VIEWPORT_LEFT_COLUMN        = 2
VIEWPORT_RIGHT_COLUMN       = 78
SCREEN_WIDTH                = 80
SCREEN_HEIGHT               = 64
# centered on screen
# SCREEN_WIDTH, SCREEN_HEIGHT column 
def displaySprite(column, height):
    start_column    = max (VIEWPORT_LEFT_COLUMN, column - height//2)
    #end_column      = min (VIEWPORT_RIGHT_COLUMN, column + height//2)
    nb_column       = height//2
    scrColIdx          = column - height//2
    scrLinIdx          = SCREEN_HEIGHT // 2 - height // 2
    for ii in dda.parcours(32, height):
        for jj in dda.parcours(32, height):
            
            print (scrLinIdx, scrColIdx, ii, jj)
            scrColIdx   += 1
        scrLinIdx      += 1
        scrColIdx      = column - height//2

def main ():
    print ("start")
    displaySprite(20, 12)

if __name__ == "__main__":
    # execute only if run as a script
    main()    



