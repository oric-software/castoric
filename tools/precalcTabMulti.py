# 
# Author : Jean-Baptiste PERIN
# Date : 2021 


import codegen
import config


def main ():
    
    coeff = config.TEXTURE_SIZE / config.WALL_HEIGHT

    stMulti120_high = codegen.buffer2cCode("multi120_high", "unsigned char", [((120*ii)&0xFF00)>>8 for ii in range(64)])
    stMulti120_low = codegen.buffer2cCode("multi120_low", "unsigned char", [(120*ii)&0x00FF for ii in range(64)])
    stMulti32_low = codegen.buffer2cCode("multi32_high", "unsigned char", [((32*ii)&0xFF00)>>8 for ii in range(32)])
    stMulti32_high = codegen.buffer2cCode("multi32_low", "unsigned char", [(32*ii)&0x00FF for ii in range(32)])
    stMultiCoeff = codegen.buffer2cCode("multiCoeff", "unsigned char", [round(coeff*ii) for ii in range(45)])

    print (stMulti120_low)
    print (stMulti120_high)
    print (stMulti32_low)
    print (stMulti32_high)
    print (stMultiCoeff)

if __name__ == "__main__":
    # execute only if run as a script
    main()    

