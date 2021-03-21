# 
# Author : Jean-Baptiste PERIN
# Date : 2021 

import config
import codegen

def iea(nbVal, nbStep, startValue = 0):
    ii=startValue
    yield ii    
    if nbVal>nbStep:
 
        err = nbVal
        while (ii < nbVal+ startValue):
            err     -= nbStep
            ii      += 1
            if (2*err < nbStep):
                err     += nbVal
                if (ii != nbVal): yield ii # if (ii <= nbVal+ startValue): 
                
    elif nbVal<nbStep:
        
        err = nbStep
        while (ii < nbVal+ startValue):
            err -= nbVal
            if (2*err < nbStep):
                err     += nbStep
                ii      += 1
            if (ii != nbVal): yield ii
    else:
        while (ii < (nbVal + startValue)):
            ii      += 1
            if (ii != nbVal): yield ii


def main ():


    tabIdxRdTexture = []
    for u in range (1,config.VIEWPORT_HEIGHT):
        for v in iea(config.TEXTURE_SIZE, u):
            tabIdxRdTexture.append(v)
    strTabIdxRdTexture = codegen.buffer2cCode("tabIdxRdTexture", "unsigned char", tabIdxRdTexture)
    print (strTabIdxRdTexture)

if __name__ == "__main__":
    # execute only if run as a script
    main()

