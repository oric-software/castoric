# 
# Author : Jean-Baptiste PERIN
# Date : 2021 


import codegen
import config


def main ():
    
    coeff = config.TEXTURE_SIZE / config.WALL_HEIGHT

    stMulti120 = codegen.buffer2cCode("multi120", "unsigned int", [120*ii for ii in range(64)])
    stMulti32 = codegen.buffer2cCode("multi32", "unsigned int", [32*ii for ii in range(32)])
    stMultiCoeff = codegen.buffer2cCode("multiCoeff", "unsigned char", [round(coeff*ii) for ii in range(45)])

    print (stMulti120)
    print (stMulti32)
    print (stMultiCoeff)
if __name__ == "__main__":
    # execute only if run as a script
    main()    

