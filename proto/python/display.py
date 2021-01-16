from tkinter import *
from PIL import Image

master = Tk()

canvas_width = 240
canvas_height = 200
w = Canvas(master, 
           width=canvas_width,
           height=canvas_height)
w.pack()

y = int(canvas_height / 2)
w.create_line(0, y, canvas_width, y, fill="#476042")

im = Image.open('Image.bmp')
rgb_im = im.convert('RGB')
imw, imh = im.width, im.height

[ratioW, ratioH] = map(round, [canvas_width/imw, canvas_height/imh])

def rgb_color(rgb):
    return '#%02x%02x%02x' % rgb
 
print(rgb_color((200, 100, 25)))
print (imw, imh, ratioW, ratioH)
for jj in range (imh):
    for ii in range (imw):    
        r, g, b = rgb_im.getpixel((ii, jj))
        #print(r, g, b)
        w.create_rectangle(
            ii*ratioW, jj*ratioH,
            (ii+1)*ratioW, (jj+1)*ratioH,
            fill=rgb_color((r, g, b)), width=0)
mainloop()
