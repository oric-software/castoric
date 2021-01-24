
import struct 
import math
import codegen



FIX2RAD = math.pi/128

def genLogTrigoTables(coeff):
    tabLog2Sin = []
    tabLog2Cos = []
    for angle in range (256):
        v= int.from_bytes(bytes([angle]), byteorder='big', signed=True)
        if (v == 0):
            lsinv = -64
        else:
            lsinv = min(77,max(-64, round(32*math.log2(abs(math.sin(v*FIX2RAD))*coeff))))

        if (v == 64):
            lcosv = -64
        else:
            lcosv = min(77,max(-64, round(32*math.log2(abs(math.cos(v*FIX2RAD))*coeff))))
        tabLog2Sin.append(lsinv)
        tabLog2Cos.append(lcosv)
        print (angle, v, lsinv, lcosv)
    return [tabLog2Sin, tabLog2Cos]

def main():
    [tls, tlc] = genLogTrigoTables(32/6)
    print (codegen.buffer2pyCode("tabLog2Sin", tls))
    print (codegen.buffer2pyCode("tabLog2Cos", tlc))

if __name__ == "__main__":
    main()
