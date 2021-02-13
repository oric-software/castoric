import os
from PIL import Image
import codegen

def toSimpleRgb(val):
    return val//85

def image2AlphaTextureBuf (filepathname):
    base=os.path.basename(filepathname)
    namerad = os.path.splitext(base)[0]
    im = Image.open(filepathname, 'r')
    imw, imh = im.width, im.height
    rgb_im = im.convert('RGBA')
    # if (imw != 32) or (imh != 32): 
    #     print ("Texture must be 32*32 pixels")
    #     return None

    # if (im.mode == 'RGBA'):
    #     print ("Texture must contain alpha channel")
    #     return None

    #red, green, blue, alpha = im.split()

    bufimgtranslat          = []
    alpha                   = []
    for ii in range (imw):
        for jj in range (imh):    
            r, g, b, a = rgb_im.getpixel((ii, jj))
            # print (r, g, b, a)
            bufimgtranslat.append(toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))
            if (r+g+b == 0):
                alpha.append(1)
            else:
                alpha.append(0)

    cCode = codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimgtranslat)
    cCode += codegen.buffer2cCode("alpha_"+namerad, "unsigned char", alpha)
    return cCode

def image2TextureBuf (filepathname):
    base=os.path.basename(filepathname)
    namerad = os.path.splitext(base)[0]
    im = Image.open(filepathname)
    rgb_im = im.convert('RGB')
    imw, imh = im.width, im.height

    # bufimg = []
    bufimgtranslat = []

    # for jj in range (imh):
    #     for ii in range (imw):    
    #         r, g, b = rgb_im.getpixel((ii, jj))
    #         bufimg.append(toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))

    for ii in range (imw):
        for jj in range (imh):    
            r, g, b = rgb_im.getpixel((ii, jj))
            bufimgtranslat.append(toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))

    # cCode += codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimg)
    cCode = codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimgtranslat)

    return cCode

def main():
    print (image2TextureBuf ('img/bluestone.png'))
    print (image2TextureBuf ('img/christmas.bmp'))
    print (image2TextureBuf ('img/colorstone.png'))
    print (image2TextureBuf ('img/eagle.png'))
    print (image2TextureBuf ('img/greystone.png'))
    print (image2TextureBuf ('img/logo.png'))
    print (image2TextureBuf ('img/mossy.png'))
    print (image2TextureBuf ('img/pillar.png'))
    print (image2TextureBuf ('img/purplestone.png'))
    print (image2TextureBuf ('img/redbrick.png'))
    print (image2TextureBuf ('img/wood.png'))
    print (image2TextureBuf ('img/wood.bmp'))
if __name__ == "__main__":
    # execute only if run as a script
    main()    
