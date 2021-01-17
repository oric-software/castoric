import codegen

tabRightRed     = []
tabLeftRed      = []
tabRightGreen   = []
tabLeftGreen    = []
tabRightBlue    = []
tabLeftBlue     = []

encodeLColor = [ 0, 2, 5, 7 ]
encodeHColor = [ (0<<3)|0x40, (2<<3)|0x40, (5<<3)|0x40, (7<<3)|0x40]


def main ():
    for ii in range (64):
        r, g, b = (ii>>4)& 0x03, (ii>>2)& 0x03, (ii)& 0x03
        print (ii, r, g, b)
        tabRightRed.append(encodeLColor[r])  
        tabLeftRed.append(encodeHColor[r])   
        tabRightGreen.append(encodeLColor[g])
        tabLeftGreen.append(encodeHColor[g]) 
        tabRightBlue.append(encodeLColor[b]) 
        tabLeftBlue.append(encodeHColor[b])  

    print (codegen.buffer2cCode("tabRightRed", "unsigned char", tabRightRed))
    print (codegen.buffer2cCode("tabLeftRed", "unsigned char", tabLeftRed))
    print (codegen.buffer2cCode("tabRightGreen", "unsigned char", tabRightGreen))
    print (codegen.buffer2cCode("tabLeftGreen", "unsigned char", tabLeftGreen))
    print (codegen.buffer2cCode("tabRightBlue", "unsigned char", tabRightBlue))
    print (codegen.buffer2cCode("tabLeftBlue", "unsigned char", tabLeftBlue))


if __name__ == "__main__":
    # execute only if run as a script
    main()    
