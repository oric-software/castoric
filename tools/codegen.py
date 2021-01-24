

def buffer2cCode(theName, theType, theBuffer):
    theCode = ""
    first = True
    for ii in range(len(theBuffer)):
        if first:
            theCode += f"{theType} {theName}[] = {{\n\t"
            first = False
        else:
            theCode += ", "
        theCode += f"{theBuffer[ii]}"
        if ((ii+1) %16 == 0) and (ii != 0):
            theCode += "\n\t"
    theCode += "};\n"
    return theCode

def buffer2pyCode(theName, theBuffer):
    theCode = ""
    first = True
    for ii in range(len(theBuffer)):
        if first:
            theCode += f"{theName} = [\n\t"
            first = False
        else:
            theCode += ", "
        theCode += f"{theBuffer[ii]}"
        if ((ii+1) %16 == 0) and (ii != 0):
            theCode += "\n\t"
    theCode += "]\n"
    return theCode

def dda(nbVal, nbStep, startValue = 0):
    ii=startValue
    yield ii    
    if nbVal>nbStep:
 
        err = nbVal
        while (ii < nbVal+ startValue):
            err     -= nbStep
            ii      += 1
            if (2*err < nbStep):
                err     += nbVal
                yield ii # if (ii <= nbVal+ startValue): 
                
    elif nbVal<nbStep:
        
        err = nbStep
        while (ii < nbVal+ startValue):
            err -= nbVal
            if (2*err < nbStep):
                err     += nbStep
                ii      += 1
            yield ii
    else:
        while (ii <= (nbVal + startValue)):
            ii      += 1
            yield ii

def main ():
    stWall = buffer2cCode("idxWall", "unsigned char", [0 for ii in range(40)])
    stHeight = buffer2cCode("tabHeight", "unsigned char", [40-ii for ii in dda(28,40)])
    stTexCol = buffer2cCode("tabTexCol", "unsigned char", [ii for ii in range(40)])
    stMulti40 = buffer2cCode("multi40", "unsigned int", [40*ii for ii in range(200)])
    stMulti120 = buffer2cCode("multi120", "unsigned int", [120*ii for ii in range(40)])
    stMulti27 = buffer2cCode("multi27", "unsigned int", [27*ii for ii in range(40)])
    stMulti32 = buffer2cCode("multi32", "unsigned int", [32*ii for ii in range(32)])
    print (stWall)
    print (stHeight)
    print (stTexCol)
    print (stMulti40)
    print (stMulti120)
    print (stMulti27)
    print (stMulti32)
if __name__ == "__main__":
    # execute only if run as a script
    main()    
