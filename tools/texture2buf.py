import os
from PIL import Image
import codegen

def toSimpleColorComponentVal(val):
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
            bufimgtranslat.append(toSimpleColorComponentVal(r)*16 + toSimpleColorComponentVal(g)*4 + toSimpleColorComponentVal(b))
            if (r+g+b == 0):
                alpha.append(1)
            else:
                alpha.append(0)

    cCode = codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimgtranslat)
    cCode += codegen.buffer2cCode("alpha_"+namerad, "unsigned char", alpha)
    return cCode



def image2TextureRGBBuf (filepathname):
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
    #         bufimg.append(toSimpleColorComponentVal(r)*16 + toSimpleColorComponentVal(g)*4 + toSimpleColorComponentVal(b))

    for ii in range (imw):
        for jj in range (imh):    
            r, g, b = rgb_im.getpixel((ii, jj))
            bufimgtranslat.append(toSimpleColorComponentVal(r)*16 + toSimpleColorComponentVal(g)*4 + toSimpleColorComponentVal(b))

    # cCode = f"#define TEXTURE_WIDTH {imw}\n#define TEXTURE_HEIGHT {imh}\n"
    # cCode += codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimg)
    cCode = codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimgtranslat)

    return cCode


def image2TextureCMYBuf (filepathname):
    base=os.path.basename(filepathname)
    namerad = os.path.splitext(base)[0]
    im = Image.open(filepathname)
    cmy_im = im.convert('CMYK')
    imw, imh = im.width, im.height

    bufimgtranslat = []

    for ii in range (imw):
        for jj in range (imh):    
            c, m, y, k = cmy_im.getpixel((ii, jj))
            #print (cmy_im.getpixel((ii, jj)))
            bufimgtranslat.append(toSimpleColorComponentVal(c)*16 + toSimpleColorComponentVal(m)*4 + toSimpleColorComponentVal(y))

    cCode = codegen.buffer2cCode("texture_"+namerad, "unsigned char", bufimgtranslat)

    return cCode


def main():
    # print (f"#define TEXTURE_WIDTH 32\n#define TEXTURE_HEIGHT 32\n")
    # print (image2TextureRGBBuf ('img/bluestone.png'))
    # print (image2TextureRGBBuf ('img/christmas.bmp'))
    # print (image2TextureRGBBuf ('img/colorstone.png'))
    # print (image2TextureRGBBuf ('img/eagle.png'))
    # print (image2TextureRGBBuf ('img/greystone.png'))
    # print (image2TextureRGBBuf ('img/logo.png'))
    # print (image2TextureRGBBuf ('img/mossy.png'))
    # print (image2TextureRGBBuf ('img/pillar.png'))
    # print (image2TextureRGBBuf ('img/purplestone.png'))
    # print (image2TextureRGBBuf ('img/redbrick.png'))
    # print (image2TextureRGBBuf ('img/wood.png'))
    # print (image2TextureRGBBuf ('img/wood.bmp'))
    # print (image2TextureCMYBuf ('img/barrel.png'))
    print (image2TextureCMYBuf ('img/wood.bmp'))

if __name__ == "__main__":
    # execute only if run as a script
    main()    
