import math
import random
import time
import struct

FIX2RAD = math.pi/128
FIX2DEG = 180/128

[glCamPosX, glCamPosY] = [-64,-64]
glCamRotZ = 45 #degres
[RaySegX1, RaySegY1] = [63,63]
[RaySegX2, RaySegY2] = [-63,63]
RayOppose = False
RayDivisor = 1
RayDistance = 0

RayTmpA = 0
RayTmpX=0
RayTmpB=0

RayDistPart1 = 0
RayDistPart2 = 0

tabmult_A = [
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71,
    72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87,
    88, 89, 90, 90, 91, 92, 93, 94,
    95, 96, 97, 98, 99, 100, 101, 102,
    103, 104, 105, 106, 107, 108, 109, 110,
    111, 112, 113, 114, 115, 116, 117, 118,
    119, 119, 120, 121, 122, 123, 124, 125
]
tabmult_B = [
    0, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 2, 2, 2, 2,
    2, 3, 3, 3, 3, 3, 4, 4,
    4, 4, 4, 5, 5, 5, 6, 6,
    6, 6, 7, 7, 7, 7, 8, 8,
    8, 9, 9, 9, 10, 10, 10, 11,
    11, 11, 12, 12, 13, 13, 13, 14,
    14, 15, 15, 15, 16, 16, 17, 17,
    18, 18, 18, 19, 19, 20, 20, 21,
    21, 22, 22, 23, 23, 24, 24, 25,
    25, 26, 26, 27, 27, 28, 29, 29,
    30, 30, 31, 31, 32, 33, 33, 34,
    34, 35, 36, 36, 37, 38, 38, 39,
    39, 40, 41, 41, 42, 43, 44, 44,
    45, 46, 46, 47, 48, 48, 49, 50,
    51, 51, 52, 53, 54, 54, 55, 56
]
tabmult_C = [
    0, 0, 2, 3, 4, 5, 5, 6,
    7, 8, 8, 9, 10, 11, 12, 13,
    14, 14, 15, 16, 17, 18, 19, 19,
    20, 21, 22, 23, 24, 24, 25, 26,
    27, 28, 29, 30, 30, 31, 32, 33,
    34, 35, 35, 36, 37, 38, 39, 40,
    40, 41, 42, 43, 44, 44, 45, 46,
    47, 48, 49, 49, 50, 51, 52, 53,
    54, 54, 55, 56, 57, 58, 59, 59,
    60, 61, 62, 63, 63, 64, 65, 66,
    67, 68, 68, 69, 70, 71, 72, 72,
    73, 74, 75, 76, 76, 77, 78, 79,
    80, 80, 81, 82, 83, 84, 85, 85,
    86, 87, 88, 89, 89, 90, 91, 92,
    93, 93, 94, 95, 96, 97, 97, 98,
    99, 100, 101, 101, 102, 103, 104, 105
]
tabmult_D = [
    0, 1, 1, 1, 2, 2, 3, 4,
    4, 5, 5, 6, 7, 7, 8, 8,
    9, 9, 10, 10, 11, 11, 12, 13,
    13, 14, 14, 15, 15, 16, 17, 17,
    18, 18, 19, 19, 20, 20, 21, 22,
    22, 23, 23, 24, 24, 25, 26, 26,
    27, 27, 28, 28, 29, 30, 30, 31,
    31, 32, 33, 33, 34, 34, 35, 35,
    36, 37, 37, 38, 38, 39, 40, 40,
    41, 41, 42, 43, 43, 44, 44, 45,
    46, 46, 47, 47, 48, 49, 49, 50,
    50, 51, 52, 52, 53, 53, 54, 55,
    55, 56, 56, 57, 58, 58, 59, 59,
    60, 61, 61, 62, 63, 63, 64, 64,
    65, 66, 66, 67, 68, 68, 69, 69,
    70, 71, 71, 72, 73, 73, 74, 74
]


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



tab_exp = [
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x0b, 0x0b, 
    0x0b, 0x0c, 0x0c, 0x0c, 0x0c, 0x0d, 0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x10, 
    0x10, 0x10, 0x11, 0x11, 0x11, 0x12, 0x12, 0x13, 0x13, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 0x16, 
    0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1c, 0x1d, 0x1d, 0x1e, 0x1f, 0x1f, 
    0x20, 0x21, 0x21, 0x22, 0x23, 0x24, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x29, 0x2a, 0x2b, 0x2c, 
    0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3b, 0x3c, 0x3d, 0x3f, 
    0x40, 0x41, 0x43, 0x44, 0x46, 0x47, 0x49, 0x4a, 0x4c, 0x4e, 0x4f, 0x51, 0x53, 0x55, 0x57, 0x59, 
    0x5b, 0x5c, 0x5f, 0x61, 0x63, 0x65, 0x67, 0x69, 0x6c, 0x6e, 0x70, 0x73, 0x75, 0x78, 0x7b, 0x7d, 
    0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x95, 0x98, 0x9c, 0x9f, 0xa2, 0xa6, 0xaa, 0xad, 0xb1, 
    0xb5, 0xb9, 0xbd, 0xc1, 0xc5, 0xca, 0xce, 0xd3, 0xd7, 0xdc, 0xe1, 0xe6, 0xeb, 0xf0, 0xf5, 0xfb
]

tab_exp_extended = [
    0, 6, 11, 17, 23, 29, 36, 42, 
    48, 55, 62, 69, 76, 83, 91, 98, 
    106, 114, 122, 130, 139, 147, 156, 165, 
    175, 184, 194, 203, 214, 224, 234, 245, 255] # FIXME: last value should be 256

tab_exp_extended2 = [
    11, 23, 34, 46, 59, 71, 84, 97, 
    110, 124, 138, 152, 167, 181, 197, 212, 
    228, 244]

tab_exp_extended3 = [
    17, 34, 51, 69, 87, 105, 124, 143, 163, 183, 204, 225, 246]

tab_divisor=[
        0, 254, 253, 251, 250, 248, 247, 245
        , 244, 242, 241, 240, 238, 237, 236, 235
        , 233, 232, 231, 230, 229, 229, 228, 227
        , 226, 226, 225, 225, 225, 224, 224, 224
        , 224, 224, 224, 224, 225, 225, 225, 226
        , 226, 227, 228, 229, 229, 230, 231, 232
        , 233, 235, 236, 237, 238, 240, 241, 242
        , 244, 245, 247, 248, 250, 251, 253, 254
        , 0, 2, 3, 5, 6, 8, 9, 11
        , 12, 14, 15, 16, 18, 19, 20, 21
        , 23, 24, 25, 26, 27, 27, 28, 29
        , 30, 30, 31, 31, 31, 32, 32, 32
        , 32, 32, 32, 32, 31, 31, 31, 30
        , 30, 29, 28, 27, 27, 26, 25, 24
        , 23, 21, 20, 19, 18, 16, 15, 14
        , 12, 11, 9, 8, 6, 5, 3, 2
        , 0, 254, 253, 251, 250, 248, 247, 245
        , 244, 242, 241, 240, 238, 237, 236, 235
        , 233, 232, 231, 230, 229, 229, 228, 227
        , 226, 226, 225, 225, 225, 224, 224, 224
        , 224, 224, 224, 224, 225, 225, 225, 226
        , 226, 227, 228, 229, 229, 230, 231, 232
        , 233, 235, 236, 237, 238, 240, 241, 242
        , 244, 245, 247, 248, 250, 251, 253, 254
        , 0, 2, 3, 5, 6, 8, 9, 11
        , 12, 14, 15, 16, 18, 19, 20, 21
        , 23, 24, 25, 26, 27, 27, 28, 29
        , 30, 30, 31, 31, 31, 32, 32, 32
        , 32, 32, 32, 32, 31, 31, 31, 30
        , 30, 29, 28, 27, 27, 26, 25, 24
        , 23, 21, 20, 19, 18, 16, 15, 14
        , 12, 11, 9, 8, 6, 5, 3, 2

]

tab_divisor_acc=[
   0, 255, 254, 254, 253, 252, 251, 251
   , 250, 249, 248, 247, 247, 246, 245, 244
   , 244, 243, 242, 242, 241, 240, 240, 239
   , 238, 238, 237, 236, 236, 235, 235, 234
   , 233, 233, 232, 232, 231, 231, 230, 230
   , 229, 229, 229, 228, 228, 227, 227, 227
   , 226, 226, 226, 226, 225, 225, 225, 225
   , 225, 224, 224, 224, 224, 224, 224, 224
   , 224, 224, 224, 224, 224, 224, 224, 224
   , 225, 225, 225, 225, 225, 226, 226, 226
   , 226, 227, 227, 227, 228, 228, 229, 229
   , 229, 230, 230, 231, 231, 232, 232, 233
   , 233, 234, 235, 235, 236, 236, 237, 238
   , 238, 239, 240, 240, 241, 242, 242, 243
   , 244, 244, 245, 246, 247, 247, 248, 249
   , 250, 251, 251, 252, 253, 254, 254, 255
   , 0, 1, 2, 2, 3, 4, 5, 5
   , 6, 7, 8, 9, 9, 10, 11, 12
   , 12, 13, 14, 14, 15, 16, 16, 17
   , 18, 18, 19, 20, 20, 21, 21, 22
   , 23, 23, 24, 24, 25, 25, 26, 26
   , 27, 27, 27, 28, 28, 29, 29, 29
   , 30, 30, 30, 30, 31, 31, 31, 31
   , 31, 32, 32, 32, 32, 32, 32, 32
   , 32, 32, 32, 32, 32, 32, 32, 32
   , 31, 31, 31, 31, 31, 30, 30, 30
   , 30, 29, 29, 29, 28, 28, 27, 27
   , 27, 26, 26, 25, 25, 24, 24, 23
   , 23, 22, 21, 21, 20, 20, 19, 18
   , 18, 17, 16, 16, 15, 14, 14, 13
   , 12, 12, 11, 10, 9, 9, 8, 7
   , 6, 5, 5, 4, 3, 2, 2, 1 
]




tab_sin = [
    0x00, 0x01, 0x02, 0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x08, 0x09, 0x09, 0x0a, 0x0b, 0x0c, 
    0x0c, 0x0d, 0x0e, 0x0e, 0x0f, 0x10, 0x10, 0x11, 0x12, 0x12, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 
    0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1d, 
    0x1e, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 
    0x1e, 0x1d, 0x1d, 0x1d, 0x1c, 0x1c, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x19, 0x19, 0x18, 0x18, 0x17, 
    0x17, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x12, 0x12, 0x11, 0x10, 0x10, 0x0f, 0x0e, 0x0e, 0x0d, 
    0x0c, 0x0c, 0x0b, 0x0a, 0x09, 0x09, 0x08, 0x07, 0x06, 0x05, 0x05, 0x04, 0x03, 0x02, 0x02, 0x01, 
    0x00, 0xff, 0xfe, 0xfe, 0xfd, 0xfc, 0xfb, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7, 0xf7, 0xf6, 0xf5, 0xf4, 
    0xf4, 0xf3, 0xf2, 0xf2, 0xf1, 0xf0, 0xf0, 0xef, 0xee, 0xee, 0xed, 0xec, 0xec, 0xeb, 0xeb, 0xea, 
    0xe9, 0xe9, 0xe8, 0xe8, 0xe7, 0xe7, 0xe6, 0xe6, 0xe5, 0xe5, 0xe5, 0xe4, 0xe4, 0xe3, 0xe3, 0xe3, 
    0xe2, 0xe2, 0xe2, 0xe2, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe2, 0xe2, 0xe2, 
    0xe2, 0xe3, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe5, 0xe6, 0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 
    0xe9, 0xea, 0xeb, 0xeb, 0xec, 0xec, 0xed, 0xee, 0xee, 0xef, 0xf0, 0xf0, 0xf1, 0xf2, 0xf2, 0xf3, 
    0xf4, 0xf4, 0xf5, 0xf6, 0xf7, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff
]

tab_cos = [
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 
    0x1e, 0x1d, 0x1d, 0x1d, 0x1c, 0x1c, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x19, 0x19, 0x18, 0x18, 0x17, 
    0x17, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x12, 0x12, 0x11, 0x10, 0x10, 0x0f, 0x0e, 0x0e, 0x0d, 
    0x0c, 0x0c, 0x0b, 0x0a, 0x09, 0x09, 0x08, 0x07, 0x06, 0x05, 0x05, 0x04, 0x03, 0x02, 0x02, 0x01, 
    0x00, 0xff, 0xfe, 0xfe, 0xfd, 0xfc, 0xfb, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7, 0xf7, 0xf6, 0xf5, 0xf4, 
    0xf4, 0xf3, 0xf2, 0xf2, 0xf1, 0xf0, 0xf0, 0xef, 0xee, 0xee, 0xed, 0xec, 0xec, 0xeb, 0xeb, 0xea, 
    0xe9, 0xe9, 0xe8, 0xe8, 0xe7, 0xe7, 0xe6, 0xe6, 0xe5, 0xe5, 0xe5, 0xe4, 0xe4, 0xe3, 0xe3, 0xe3, 
    0xe2, 0xe2, 0xe2, 0xe2, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe2, 0xe2, 0xe2, 
    0xe2, 0xe3, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe5, 0xe6, 0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 
    0xe9, 0xea, 0xeb, 0xeb, 0xec, 0xec, 0xed, 0xee, 0xee, 0xef, 0xf0, 0xf0, 0xf1, 0xf2, 0xf2, 0xf3, 
    0xf4, 0xf4, 0xf5, 0xf6, 0xf7, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff, 
    0x00, 0x01, 0x02, 0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x08, 0x09, 0x09, 0x0a, 0x0b, 0x0c, 
    0x0c, 0x0d, 0x0e, 0x0e, 0x0f, 0x10, 0x10, 0x11, 0x12, 0x12, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 
    0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1d, 
    0x1e, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
]

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



tabLog2Sin = [
        -64, -64, -62, -43, -30, -20, -11, -4, 2, 7, 12, 16, 20, 24, 27, 30
        , 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        , 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        , 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
        , 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        , 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        , 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        , 33, 30, 27, 24, 20, 16, 12, 7, 2, -4, -11, -20, -30, -43, -62, -64
        , -64, -64, -62, -43, -30, -20, -11, -4, 2, 7, 12, 16, 20, 24, 27, 30
        , 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        , 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        , 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
        , 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        , 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        , 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        , 33, 30, 27, 24, 20, 16, 12, 7, 2, -4, -11, -20, -30, -43, -62, -64
        ]

tabLog2Cos = [
        77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        , 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        , 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        , 33, 30, 27, 24, 20, 16, 12, 7, 2, -4, -11, -20, -30, -43, -62, -64
        , -64, -64, -62, -43, -30, -20, -11, -4, 2, 7, 12, 16, 20, 24, 27, 30
        , 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        , 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        , 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
        , 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        , 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        , 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        , 33, 30, 27, 24, 20, 16, 12, 7, 2, -4, -11, -20, -30, -43, -62, -64
        , -64, -64, -62, -43, -30, -20, -11, -4, 2, 7, 12, 16, 20, 24, 27, 30
        , 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        , 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        , 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
        ]

def log2sin(x):
    r = tabLog2Sin[struct.unpack('B',struct.pack("b", x))[0]]
    return r

def log2cos(x):
    r = tabLog2Cos[struct.unpack('B',struct.pack("b", x))[0]]
    return r


def sin(x):
    r = tab_sin[struct.unpack('B',struct.pack("b", x))[0]]
    return int.from_bytes(bytes([r]), byteorder='big', signed=True)

def cos(x):
    r = tab_cos[struct.unpack('B',struct.pack("b", x))[0]]
    return int.from_bytes(bytes([r]), byteorder='big', signed=True)

def oneoversin(x):
    r = tab_1oversin[struct.unpack('B',struct.pack("b", x))[0]]
    return int.from_bytes(bytes([r]), byteorder='big', signed=False)

def oneovercos(x):
    r = tab_1overcos[struct.unpack('B',struct.pack("b", x))[0]]
    return int.from_bytes(bytes([r]), byteorder='big', signed=False)


def log2(x):
    r = log2_tab[struct.unpack('B',struct.pack("b", x))[0]]
    return int.from_bytes(bytes([r]), byteorder='big', signed=False)

def longexp(x):
    
    if (x < 256):
        return tab_exp[x]
    elif (256 <= x < 289):
        return tab_exp_extended[x-256] + 256
    elif (289 <= x < 307):
        return tab_exp_extended2[x-289] + 512
    elif (307 <= x < 320):
        return tab_exp_extended3[x-307] + 756
    else:
        print ("overflow")
        return (2**16)-1

def atan2 (ty, tx):

    if abs(tx)>127 or abs(ty)>127:
        x=tx//2
        y=ty//2
    else:
        x=tx
        y=ty
    noct = 0
    if (x<0):
        ix = -x # struct.unpack('B',struct.pack("b", x))[0] ^ 0xFF
        noct |= 4
    else: ix = x
    if (y<0):
        iy = -y # struct.unpack('B',struct.pack("b", y))[0] ^ 0xFF
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
    # print (f"idx = {idx}, v= {v}, noct = {noct}, octant_adjust[noct]={octant_adjust[noct]}")

    v = int.from_bytes(bytes([v ^ octant_adjust [noct]]), byteorder='big', signed=True)

    return v


def norm (dx,dy):
    if (abs(dx)>=128 or abs(dy)>=128):
        ax, ay = abs(dx)//2, abs(dy)//2
        dividedBy2 = True
    else:
        ax, ay = abs(dx), abs(dy)
        dividedBy2 = False
    if ax >= ay:
        x, y = ax, ay
    else:
        x, y = ay, ax
    if y > x/2 :
        # N = (math.sqrt(5)-math.sqrt(2))*x + (2*math.sqrt(2) - math.sqrt(5))*y
        #N = tabmult_sqrt5_m_sqrt2 [x] + tabmult_2sqrt2_m_sqrt5[y]
        N = tabmult_C [x] + tabmult_D[y]
    else:
        # N = x+(math.sqrt(5)/2 - 1)*y
        #N = x + tabmult_sqrt5_m2 [y]
        N = tabmult_A [x] + tabmult_B[y]
    if dividedBy2:
        return 2*N
    else:
        return N



def fastComputeDistance (deltaX, deltaY, angle):
    
    if (deltaX != 0):
        # mur aligné avec (O, y)
        delta = abs(deltaX)
        p2 = oneovercos(angle)
    else:
        # mur aligné avec (O, x)
        delta = abs(deltaY) 
        p2 = oneoversin(angle)

    p1 = log2(delta)
    som = p1 + p2
    res = longexp(som)
    if som >= 320:
        print ("WARNING")
        print (f"p1 = {p1}, p2 = {p2}, som = {som}, res = {res}")
    
    return res

COEFF = 32/6


def fastComputeTextCol (glCamPosX, glCamPosY,
                         RaySegX1, RaySegY1,
                         RaySegX2, RaySegY2,
                         angle):
    [deltaX, deltaY] = [RaySegX1-glCamPosX, RaySegY1-glCamPosY]
    if (RaySegY2-RaySegY1 != 0):
        # mur aligné avec (O, y)
        delta = abs(deltaX)
        p2 = oneovercos(angle)
    elif (RaySegX2 - RaySegX1 != 0):
        # mur aligné avec (O, x)
        delta = abs(deltaY) 
        p2 = oneoversin(angle)
    else:
        print ("error")
        return 
    p1 = log2(delta)
    som = p1 + p2
    # print (som)
    res = longexp(som)
    if som >= 320:
        print ("WARNING")
        print (f"p1 = {p1}, p2 = {p2}, som = {som}, res = {res}")
    
    if (RaySegY2-RaySegY1 != 0):
        
        # print (v0)
        if (angle == 0):
            v0 = 0
            v1 = 0
            v2 = 0
        # elif (angle == ):
        elif angle>=1:
            v0 = log2sin(angle) # round(32*math.log2(math.sin(angle*FIX2RAD)*COEFF))
            v1 = som + v0
            v2 = longexp(v1) # (2**(v1/32)) # 
        elif angle<=-1:
            v0 = log2sin(angle) # round(32*math.log2(-math.sin(angle*FIX2RAD)*COEFF))
            v1 = som + v0
            v2 = -longexp(v1) # -(2**(v1/32)) # 
        else :
            print ("WHAT?")
        #v1 = som +
        #print (angle, v0, v1, v2)
        tc = round(abs(v2-deltaY*COEFF))
        return [res, tc]
        #return [res, abs(longexp(som+round(math.log2(abs(32*math.sin(angle*FIX2RAD)))))-deltaY)]
    elif (RaySegX2 - RaySegX1 != 0):
        if (angle == 0):
            v0 = 0
            v1 = 0
            v2 = 0
        # elif (angle == ):
        elif abs(angle)<64:
            v0 = log2cos(angle) 
            v1 = som + v0
            v2 = longexp(v1) # (2**(v1/32)) # 
        elif abs(angle)>=64:
            v0 = log2cos(angle) 
            v1 = som + v0
            v2 = -longexp(v1) # -(2**(v1/32)) # 
        else :
            print ("WHAT?")
        # tc = abs(res*math.cos(angle*FIX2RAD)-deltaX)
        tc = round(abs(v2-deltaX*COEFF))
        return [res, tc]
    


# [glCamPosX, glCamPosY] = [2, 1]
# [RaySegX1, RaySegY1] = [-4, 5]
# [RaySegX2, RaySegY2] = [-4, -3]
# glCamRotZ = -128
# rayAngleMin, rayAngleMax = 151, 207

# [glCamPosX, glCamPosY] = [2, 1]
# [RaySegX1, RaySegY1] = [12, 5]
# [RaySegX2, RaySegY2] = [12, -3]
# glCamRotZ = 0
# rayAngleMin, rayAngleMax = -20, 20

# [glCamPosX, glCamPosY] = [2, 1]
# [RaySegX1, RaySegY1] = [4, 8]
# [RaySegX2, RaySegY2] = [12,8]
# glCamRotZ = round(50/FIX2DEG)
# rayAngleMin, rayAngleMax = 35, 70

# [glCamPosX, glCamPosY] = [2, 1]
# [RaySegX1, RaySegY1] = [4, 8]
# [RaySegX2, RaySegY2] = [12,8]
# glCamRotZ = round(-50/FIX2DEG)
# rayAngleMin, rayAngleMax = -70, -32

# [glCamPosX, glCamPosY] = [2, 1]
# [RaySegX1, RaySegY1] = [-1, -5]
# [RaySegX2, RaySegY2] = [5,-5]
# glCamRotZ = round(-90/FIX2DEG)
# rayAngleMin, rayAngleMax = -114, -66

# [glCamPosX, glCamPosY] = [2, 1]
# [RaySegX1, RaySegY1] = [-1, 5]
# [RaySegX2, RaySegY2] = [5,5]
# glCamRotZ = round(90/FIX2DEG)
# rayAngleMin, rayAngleMax = 60, 120

[glCamPosX, glCamPosY] = [2, 1]
[RaySegX1, RaySegY1] = [-6,-3]
[RaySegX2, RaySegY2] = [-6,5]
glCamRotZ = round(-180/FIX2DEG)
rayAngleMin, rayAngleMax = 160, 200

for ii in range (rayAngleMin, rayAngleMax):
    angle = round(ii/FIX2DEG)
    if angle >= 0:
        sangle= int.from_bytes(bytes([angle]), byteorder='big', signed=True)
    else:
        sangle = angle
    # dist = fastComputeDistance (RaySegX1-glCamPosX, RaySegY1-glCamPosY, sangle)

    textcol = fastComputeTextCol (glCamPosX, glCamPosY,
                             RaySegX1, RaySegY1,
                             RaySegX2, RaySegY2,
                             sangle)
    print (ii, textcol)
