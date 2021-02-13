# 
# Author : Jean-Baptiste PERIN
# Date : 2021 

import codegen
import config

def main():
    unlogd2hh = [round (config.WALL_HEIGHT * config.FOCAL / 2**(ii/32)) for ii in range (0,256) ]
    print (codegen.buffer2cCode("unlogd2hh", "unsigned char", unlogd2hh))

if __name__ == "__main__":
    main()
