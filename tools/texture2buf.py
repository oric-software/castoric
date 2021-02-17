
## Script to generate texture buffer from image file 
## Author : Jean-Baptiste PERIN
## Date : 2021

import os
from PIL import Image
import codegen
import argparse

def toSimpleRgb(val):
    return val//85

## [ref texture_file2buffer]
def image2TextureBuf (filepathname):

    base=os.path.basename(filepathname)

    namerad = os.path.splitext(base)[0]

    im = Image.open(filepathname)

    rgb_im = im.convert('RGB')

    imw, imh = im.width, im.height

    bufimgtranslat = []

    for ii in range (imw):
        for jj in range (imh):    
            ## [ref texel_codec]
            r, g, b = rgb_im.getpixel((ii, jj))
            texel_value = (r//85)*16 + (g//85)*4 + (b//85)
            bufimgtranslat.append(texel_value)

    cCode = codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimgtranslat)

    return cCode

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("imagefile", help="file path and name of the texture (png or bmp) ")
    args = parser.parse_args()
    print("// CAUTION !! GENERATED FILE. DO NOT MODIFY BY HAND")
    print("// texture buffer generated from file : " + args.imagefile)
    print("// by script : " + os.path.basename(__file__))
    print("// [ref texture_file2buffer]")
    print (image2TextureBuf (args.imagefile))
    # print (image2TextureBuf ('img/christmas.bmp'))

if __name__ == "__main__":
    # execute only if run as a script
    main()    
