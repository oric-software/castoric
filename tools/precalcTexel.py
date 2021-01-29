import codegen

tabRightRed     = []
tabLeftRed      = []
tabRightGreen   = []
tabLeftGreen    = []
tabRightBlue    = []
tabLeftBlue     = []

encodeLColor = [ 0, 2, 5, 7 ]
encodeHColor = [ (0<<3)|0x40, (2<<3)|0x40, (5<<3)|0x40, (7<<3)|0x40]

encodeCyanLColor = [ 0, 2, 2, 5 ]
encodeCyanHColor = [ (0<<3)|0x40, (0<<3)|0x40, (2<<3)|0x40, (5<<3)|0x40]
encodeMagentaLColor = [ 0, 2, 5, 7 ]
encodeMagentaHColor = [ (0<<3)|0x40, (2<<3)|0x40, (5<<3)|0x40, (7<<3)|0x40]
encodeYellowLColor = [ 0, 5, 5, 7 ]
encodeYellowHColor = [ (0<<3)|0x40, (2<<3)|0x40, (5<<3)|0x40, (7<<3)|0x40]


def main ():
    for ii in range (64):
        r, g, b = (ii>>4)& 0x03, (ii>>2)& 0x03, (ii)& 0x03
        print (ii, r, g, b)
        tabRightRed.append(encodeCyanLColor[r])  
        tabLeftRed.append(encodeCyanHColor[r])   
        tabRightGreen.append(encodeMagentaLColor[g])
        tabLeftGreen.append(encodeMagentaHColor[g]) 
        tabRightBlue.append(encodeYellowLColor[b]) 
        tabLeftBlue.append(encodeYellowHColor[b])  

    print (codegen.buffer2cCode("tabRightRed", "unsigned char", tabRightRed))
    print (codegen.buffer2cCode("tabLeftRed", "unsigned char", tabLeftRed))
    print (codegen.buffer2cCode("tabRightGreen", "unsigned char", tabRightGreen))
    print (codegen.buffer2cCode("tabLeftGreen", "unsigned char", tabLeftGreen))
    print (codegen.buffer2cCode("tabRightBlue", "unsigned char", tabRightBlue))
    print (codegen.buffer2cCode("tabLeftBlue", "unsigned char", tabLeftBlue))


if __name__ == "__main__":
    # execute only if run as a script
    main()    
