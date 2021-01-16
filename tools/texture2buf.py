
from PIL import Image
import codegen

im = Image.open('..\img\img_32x32.bmp')
rgb_im = im.convert('RGB')
imw, imh = im.width, im.height

def toSimpleRgb(val):
    return val//85

bufimg = []
bufimgtranslat = []

for jj in range (imh):
    for ii in range (imw):    
        r, g, b = rgb_im.getpixel((ii, jj))
        bufimg.append(toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))
        #print (r, g, b, toSimpleRgb(r), toSimpleRgb(g), toSimpleRgb(b), toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))

for ii in range (imw):
    for jj in range (imh):    
        r, g, b = rgb_im.getpixel((ii, jj))
        bufimgtranslat.append(toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))
        #print (r, g, b, toSimpleRgb(r), toSimpleRgb(g), toSimpleRgb(b), toSimpleRgb(r)*16 + toSimpleRgb(g)*4 + toSimpleRgb(b))


# print(buf_blue)

cCode = f"#define TEXTURE_WIDTH {imw}\n#define TEXTURE_HEIGHT {imh}\n"


cCode += codegen.buffer2cCode("bufimg", "unsigned char", bufimg)
print (cCode)

cCode += codegen.buffer2cCode("bufimgtrans", "unsigned char", bufimgtranslat)
print (cCode)
