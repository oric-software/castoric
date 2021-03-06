
import struct

# [255] + [round(32*math.log2(abs(1/math.sin(angle*math.pi/128)))) for angle in range (1,128)] + [round(32*math.log2(abs(1/math.sin(angle*math.pi/128)))) for angle in range (-127,0)]

tab_1oversin =[
    255, 171, 139, 120, 107, 97, 89, 82, 
    75, 70, 65, 61, 57, 54, 50, 47, 
    44, 42, 39, 37, 35, 33, 31, 29, 
    27, 25, 24, 22, 21, 20, 18, 17, 
    16, 15, 14, 13, 12, 11, 10, 9, 
    9, 8, 7, 6, 6, 5, 5, 4, 
    4, 3, 3, 2, 2, 2, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 2, 2, 2, 3, 3, 
    4, 4, 5, 5, 6, 6, 7, 8, 
    9, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 20, 21, 22, 24, 25, 
    27, 29, 31, 33, 35, 37, 39, 42, 
    44, 47, 50, 54, 57, 61, 65, 70, 
    75, 82, 89, 97, 107, 120, 139, 171, 
    171, 139, 120, 107, 97, 89, 82, 75, 
    70, 65, 61, 57, 54, 50, 47, 44, 
    42, 39, 37, 35, 33, 31, 29, 27, 
    25, 24, 22, 21, 20, 18, 17, 16, 
    15, 14, 13, 12, 11, 10, 9, 9, 
    8, 7, 6, 6, 5, 5, 4, 4, 
    3, 3, 2, 2, 2, 1, 1, 1, 
    1, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 1, 
    1, 1, 2, 2, 2, 3, 3, 4, 
    4, 5, 5, 6, 6, 7, 8, 9, 
    9, 10, 11, 12, 13, 14, 15, 16, 
    17, 18, 20, 21, 22, 24, 25, 27, 
    29, 31, 33, 35, 37, 39, 42, 44, 
    47, 50, 54, 57, 61, 65, 70, 75, 
    82, 89, 97, 107, 120, 139, 171
]

# [min(255,round(32*math.log2(abs(1/math.cos(angle*math.pi/128))))) for angle in range (0,128)] + [min(255,round(32*math.log2(abs(1/math.cos(angle*math.pi/128))))) for angle in range (-127,0)]
tab_1overcos=[
    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 2, 2, 2, 3, 3, 
    4, 4, 5, 5, 6, 6, 7, 8, 
    9, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 20, 21, 22, 24, 25, 
    27, 29, 31, 33, 35, 37, 39, 42, 
    44, 47, 50, 54, 57, 61, 65, 70, 
    75, 82, 89, 97, 107, 120, 139, 171, 
    255, 171, 139, 120, 107, 97, 89, 82, 
    75, 70, 65, 61, 57, 54, 50, 47, 
    44, 42, 39, 37, 35, 33, 31, 29, 
    27, 25, 24, 22, 21, 20, 18, 17, 
    16, 15, 14, 13, 12, 11, 10, 9, 
    9, 8, 7, 6, 6, 5, 5, 4, 
    4, 3, 3, 2, 2, 2, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 2, 2, 2, 3, 3, 
    4, 4, 5, 5, 6, 6, 7, 8, 
    9, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 20, 21, 22, 24, 25, 
    27, 29, 31, 33, 35, 37, 39, 42, 
    44, 47, 50, 54, 57, 61, 65, 70, 
    75, 82, 89, 97, 107, 120, 139, 171, 
    255, 171, 139, 120, 107, 97, 89, 82, 
    75, 70, 65, 61, 57, 54, 50, 47, 
    44, 42, 39, 37, 35, 33, 31, 29, 
    27, 25, 24, 22, 21, 20, 18, 17, 
    16, 15, 14, 13, 12, 11, 10, 9, 
    9, 8, 7, 6, 6, 5, 5, 4, 
    4, 3, 3, 2, 2, 2, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0
]





## atan(2^(x/32))*128/pi

atan_tab = [
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x01,0x01,0x01,0x01,0x01,0x02,0x02,0x02,
            0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
            0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
            0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
            0x03,0x03,0x03,0x03,0x03,0x04,0x04,0x04,
            0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
            0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
            0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
            0x07,0x07,0x07,0x07,0x07,0x07,0x08,0x08,
            0x08,0x08,0x08,0x08,0x09,0x09,0x09,0x09,
            0x09,0x0a,0x0a,0x0a,0x0a,0x0b,0x0b,0x0b,
            0x0b,0x0c,0x0c,0x0c,0x0c,0x0d,0x0d,0x0d,
            0x0d,0x0e,0x0e,0x0e,0x0e,0x0f,0x0f,0x0f,
            0x10,0x10,0x10,0x11,0x11,0x11,0x12,0x12,
            0x12,0x13,0x13,0x13,0x14,0x14,0x15,0x15,
            0x15,0x16,0x16,0x17,0x17,0x17,0x18,0x18,
            0x19,0x19,0x19,0x1a,0x1a,0x1b,0x1b,0x1c,
            0x1c,0x1c,0x1d,0x1d,0x1e,0x1e,0x1f,0x1f
]

        ## log2(x)*32 

log2_tab = [
        0x00,0x00,0x20,0x32,0x40,0x4a,0x52,0x59,
        0x60,0x65,0x6a,0x6e,0x72,0x76,0x79,0x7d,
        0x80,0x82,0x85,0x87,0x8a,0x8c,0x8e,0x90,
        0x92,0x94,0x96,0x98,0x99,0x9b,0x9d,0x9e,
        0xa0,0xa1,0xa2,0xa4,0xa5,0xa6,0xa7,0xa9,
        0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,
        0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,
        0xb9,0xba,0xbb,0xbc,0xbd,0xbd,0xbe,0xbf,
        0xc0,0xc0,0xc1,0xc2,0xc2,0xc3,0xc4,0xc4,
        0xc5,0xc6,0xc6,0xc7,0xc7,0xc8,0xc9,0xc9,
        0xca,0xca,0xcb,0xcc,0xcc,0xcd,0xcd,0xce,
        0xce,0xcf,0xcf,0xd0,0xd0,0xd1,0xd1,0xd2,
        0xd2,0xd3,0xd3,0xd4,0xd4,0xd5,0xd5,0xd5,
        0xd6,0xd6,0xd7,0xd7,0xd8,0xd8,0xd9,0xd9,
        0xd9,0xda,0xda,0xdb,0xdb,0xdb,0xdc,0xdc,
        0xdd,0xdd,0xdd,0xde,0xde,0xde,0xdf,0xdf,
        0xdf,0xe0,0xe0,0xe1,0xe1,0xe1,0xe2,0xe2,
        0xe2,0xe3,0xe3,0xe3,0xe4,0xe4,0xe4,0xe5,
        0xe5,0xe5,0xe6,0xe6,0xe6,0xe7,0xe7,0xe7,
        0xe7,0xe8,0xe8,0xe8,0xe9,0xe9,0xe9,0xea,
        0xea,0xea,0xea,0xeb,0xeb,0xeb,0xec,0xec,
        0xec,0xec,0xed,0xed,0xed,0xed,0xee,0xee,
        0xee,0xee,0xef,0xef,0xef,0xef,0xf0,0xf0,
        0xf0,0xf1,0xf1,0xf1,0xf1,0xf1,0xf2,0xf2,
        0xf2,0xf2,0xf3,0xf3,0xf3,0xf3,0xf4,0xf4,
        0xf4,0xf4,0xf5,0xf5,0xf5,0xf5,0xf5,0xf6,
        0xf6,0xf6,0xf6,0xf7,0xf7,0xf7,0xf7,0xf7,
        0xf8,0xf8,0xf8,0xf8,0xf9,0xf9,0xf9,0xf9,
        0xf9,0xfa,0xfa,0xfa,0xfa,0xfa,0xfb,0xfb,
        0xfb,0xfb,0xfb,0xfc,0xfc,0xfc,0xfc,0xfc,
        0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfe,0xfe,
        0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff
]

octant_adjust = [
        0b00111111, #        ;; x+,y+,|x|>|y|
        0b00000000, #        ;; x+,y+,|x|<|y|
        0b11000000, #        ;; x+,y-,|x|>|y|
        0b11111111, #        ;; x+,y-,|x|<|y|
        0b01000000, #        ;; x-,y+,|x|>|y|
        0b01111111, #        ;; x-,y+,|x|<|y|
        0b10111111, #        ;; x-,y-,|x|>|y|
        0b10000000, #        ;; x-,y-,|x|<|y|
]


def atan2 (ty, tx):

    if abs(tx)>127 or abs(ty)>127:
        x=tx//2
        y=ty//2
    else:
        x=tx
        y=ty
    noct = 0
    if (x<0):
        ix = struct.unpack('B',struct.pack("b", x))[0] ^ 0xFF
        noct |= 4
    else: ix = x
    if (y<0):
        iy = struct.unpack('B',struct.pack("b", y))[0] ^ 0xFF
        noct |= 2
    else: iy = y
    # print (ix, iy)
    # print (log2_tab[ix], log2_tab [iy], log2_tab[ix] - log2_tab [iy])
    res_div = log2_tab[ix] - log2_tab [iy]
    # print(res_div)
    if log2_tab[ix] >= log2_tab [iy]:
        idx = res_div ^ 0xFF #struct.unpack('B',struct.pack("b", res_div))[0] ^ 0xFF
        noct |= 1
    #
    #if (res_div > 0): idx = res_div ^ 0xFF
    else : idx = res_div # struct.unpack('B',struct.pack("b", res_div))[0]

    v= atan_tab[idx]
    #v = v ^ octant_adjust [noct]
    v = int.from_bytes(bytes([v ^ octant_adjust [noct]]), byteorder='big', signed=True)

    return v
