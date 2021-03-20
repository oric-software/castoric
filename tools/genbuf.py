

## Script to generate texture buffer from image file 
## Author : Jean-Baptiste PERIN
## Date : 2021

import os
from PIL import Image
import codegen


def toSimpleRgb(val):
    return val//64

## [ref texture_file2buffer]
def image2TextureBuf (filepathname):

    base=os.path.basename(filepathname)

    namerad = os.path.splitext(base)[0]

    im = Image.open(filepathname)

    imw, imh = im.width, im.height
    print ("%d %d"%(im.width, im.height))

    if ((im.width != 32) or (im.height != 32)) : im.thumbnail((32,32))
    
    rgb_im = im.convert('RGB')

    imw, imh = im.width, im.height

    bufimgtranslat = []

    for ii in range (imw):
        for jj in range (imh):    
            ## [ref texel_codec]
            r, g, b = rgb_im.getpixel((ii, jj))
            texel_value = toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b)
            bufimgtranslat.append(texel_value)

    cCode = codegen.buffer2cCode("texture_"+namerad.lower(), "unsigned char", bufimgtranslat)

    return cCode

PATH = "..\\img\\textures"
DEST_PATH = "..\\proto\\c\\textures"
def main():
    list_file = [fic for fic in os.listdir(PATH) if (fic.endswith(".png") or fic.endswith(".jpg") or fic.endswith(".bmp"))]
    for fil in list_file:
        print (PATH+'\\'+fil)
        theCode = image2TextureBuf (PATH+'\\'+fil)
        filepathname = DEST_PATH+'\\'+"texture_"+os.path.splitext(fil)[0].lower()+".h"
        print (filepathname)
        with open (filepathname, "w") as f:
            f.write ("#ifndef TEXTURE_%s_H\n"%(os.path.splitext(fil)[0].upper()))
            f.write ("#define TEXTURE_%s_H\n"%(os.path.splitext(fil)[0].upper()))
            f.write (theCode)
            f.write ("\n#endif\n")
##    parser = argparse.ArgumentParser()
##    parser.add_argument("imagefile", help="file path and name of the texture (png or bmp) ")
##    args = parser.parse_args()
##    print("// CAUTION !! GENERATED FILE. DO NOT MODIFY BY HAND")
##    print("// texture buffer generated from file : " + args.imagefile)
##    print("// by script : " + os.path.basename(__file__))
##    print("// [ref texture_file2buffer]")
##    print (image2TextureBuf (args.imagefile))
    # print (image2TextureBuf ('img/christmas.bmp'))

if __name__ == "__main__":
    # execute only if run as a script
    main()    
