
# Digital Differential Analyzer Algorithm
# Incremental error algorithm

def parcours(nbVal, nbStep, startValue = 0):
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
    for v in parcours(5, 12):
        print (v)

if __name__ == "__main__":
    # execute only if run as a script
    main()
