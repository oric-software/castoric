# 
# Author : Jean-Baptiste PERIN
# Date : 2021 

import struct 
import math
import codegen
import config


def genLogTrigoTables(coeff):
    tabLog2Sin = []
    tabLog2Cos = []
    for angle in range (256):
        v= int.from_bytes(bytes([angle]), byteorder='big', signed=True)
        if (v == 0):
            lsinv = -64
        else:
            lsinv = min(77,max(-64, round(32*math.log2(abs(math.sin(v*config.FIX_TO_RAD))*coeff))))

        if (v == 64):
            lcosv = -64
        else:
            lcosv = min(77,max(-64, round(32*math.log2(abs(math.cos(v*config.FIX_TO_RAD))*coeff))))
        tabLog2Sin.append(lsinv)
        tabLog2Cos.append(lcosv)
        # print (angle, v, lsinv, lcosv)
    return [tabLog2Sin, tabLog2Cos]

def log1oversin():
    return [255] + [round(32*math.log2(abs(1/math.sin(angle*math.pi/128)))) for angle in range (1,128)] + [min(255,round(32*math.log2(abs(1/math.sin(angle*math.pi/128))))) for angle in range (-128,0)]

def log1overcos():
    return [min(255,round(32*math.log2(abs(1/math.cos(angle*math.pi/128))))) for angle in range (0,128)] + [min(255,round(32*math.log2(abs(1/math.cos(angle*math.pi/128))))) for angle in range (-128,0)]


def main():
    [tls, tlc] = genLogTrigoTables(32/6)
    # print (codegen.buffer2pyCode("tabLog2Sin", tls))
    # print (codegen.buffer2pyCode("tabLog2Cos", tlc))

    print (codegen.buffer2cCode("tabLog2Sin", "signed char", tls))
    print (codegen.buffer2cCode("tabLog2Cos", "signed char", tlc))
    print (codegen.buffer2cCode("tab_1oversin", "unsigned char", log1oversin()))
    print (codegen.buffer2cCode("tab_1overcos", "unsigned char", log1overcos()))

if __name__ == "__main__":
    main()
