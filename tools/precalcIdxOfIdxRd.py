# 
# Author : Jean-Baptiste PERIN
# Date : 2021 

import codegen
import config

def main():
    strTabIdxRd              = "_adrTabIdxRd_low\n"
    for ii in range (64):
        strTabIdxRd          += f"\t.byt <(_tabIdxRdTexture + (({ii} + 1) * {ii})/2)\n"
    strTabIdxRd              += "_adrTabIdxRd_high\n"
    for ii in range (64):
        strTabIdxRd          += f"\t.byt >(_tabIdxRdTexture + (({ii} + 1) * {ii})/2)\n"
    print (strTabIdxRd)
if __name__ == "__main__":
    main()