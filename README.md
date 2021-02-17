# Ray Casting System for Oric Computers

- [Camera](#camera)

- [Configuration](#config)

- [Viewport](#viewport)

- [Raycast](#raycast)

- [Scene](#scene)

- [Texel](#texel)

- [Texture](#texture)


--- 
## Camera <a name="camera"></a>

[[camera_situation]](https://github.com/oric-software/castoric/search?q=camera_situation)

--- 
## Configuration <a name="config"></a>

[[config_generate]](https://github.com/oric-software/castoric/search?q=config_generate)



--- 
## Viewport <a name="viewport"></a>

[[config_viewport]](https://github.com/oric-software/castoric/search?q=config_viewport)

--- 
## Raycasting <a name="raycast"></a>

[[lookup_generate]](https://github.com/oric-software/castoric/search?q=lookup_generate)



--- 
## Scene <a name="scene"></a>

### Scene description

[[scene_describe]](https://github.com/oric-software/castoric/search?q=scene_describe)

A scene is basically a list of walls that make a place we want to render on screen. And describing the scene consists in giving:
- coordinates of walls'extremities named `points`
- link between this points that make wall
- texture to be applied on wall

These informations are stored in tables:
- `lPointsX` and `lPointsY` which respectively contains X and Y coordinates of points 
- `lWallsPt1` and `lWallsPt2` which contains index of extremities point as entry in tables `lPointsX` and `lPointsY`
- `wallTexture[]` which contains pointers to buffer containing texture assigned to wall.

Thus, given a wall number `wallId`, it is possible to retrieve all information for this wall with the following code:

```C

// Retrieve point index
unsigned char P1, P2;
P1 = lWallsPt1[wallId] // pointId of extremity 1 of wall wallId
P2 = lWallsPt2[wallId] // pointId of extremity 2 of wall wallId

// Retrieve X and Y coordinates of each extremity
signed char P1X, P1Y, P2X, P2Y;
P1X = lPointsX[pointId] // X coordinates of extremity 1
P1Y = lPointsY[pointId] // Y coordinates of extremity 1
P2X = lPointsX[pointId] // X coordinates of extremity 2
P2Y = lPointsY[pointId] // Y coordinates of extremity 2

// Retrieve the buffer of the texture to be applied on this wall
unsigned char *ptr_texture;
ptr_texture = wallTexture [wallId];
```` 

### Scene loading

[[scene_load]](https://github.com/oric-software/castoric/search?q=scene_load)

To ease the description of scene content, a function named `initScene (signed char sceneData[])`is provided in file [proto/c/scene.c](proto/c/scene.c).
This function loads the tables `lWallsPt1`, `lWallsPt2`, `lPointsX` and `lPointsY` with data coming from a simpler description format shown below:

```C
signed char scene_00[] = {

    /* nbPoints = */ 4, /* nbWall = */ 4
	, -6, -6	 	// P0
	, -6,  6		// P1
	,  6,  6		// P2
	,  6, -6		// P3
	, 0, 1   // W0
	, 1, 2   // W1
	, 2, 3   // W2
	, 3, 0   // W2

};
```
In this format:
- the first byte is the number `NP` of point,
- the second bytes is the number `NW` of wall,
- the `NP`*2 next bytes are X,Y coordinates of points,

- the `NW`*2 next bytes are indexes of the two points extremities of wall.


**CAUTION:** If you plan to animate scene'elements you have to manipulate values in tables `lWallsPt1`, `lWallsPt2`, `lPointsX` and `lPointsY`. do not try to animate things in scene data `scene_00` for this table is only used at init stap to preload scene geometry in raycasting input buffers.

--- 
## Texel <a name="texel"></a>

[[texel_codec]](https://github.com/oric-software/castoric/search?q=texel_codec)

Texels are groups of 3*3 pixels on screen. 3 scanlines for RGB components by 3 pixels.

Colors are obtained by combining Red Green Blue components within a texel across scanline on screen.

Since Oric graphic screen works with 6 bits per bytes in memory screen, two texels share the same memory cell. We call them left / right texel.

A texel can be obtained from a pixel in texture by;
- extracting RGB components of this pixel,
- encoding each 3 components on a 2 bits value ,
- arranging thoses groups of two bits in the 6 least significant bits of a byte.

As shown in the following python code extracted from the script that convert texture image file to C buffer definition : [tools/texture2buf.py](tools/texture2buf.py).

```python 
    ## Open image file and get RGB 
    im = Image.open(filepathname)
    rgb_im = im.convert('RGB')

    ## compute texel value of pixel at position (ii, jj) in image
    r, g, b = rgb_im.getpixel((ii, jj))
    texel_value = (r//85)*16 + (g//85)*4 + (b//85)
```

A typical way to draw the previously computed `texel_value` at position (`line`, `column`) on screen is to use a code similar to the following one:

```C
// tables to convert rgb components into pixel 
unsigned char encodeRightColor = [ 0, 2, 5, 7 ]
// Left side texel include attribute that turn on drawing
unsigned char encodeLeftColor = [ (0<<3)|0x40, (2<<3)|0x40, (5<<3)|0x40, (7<<3)|0x40]

    // retrieve the color components from the color value
    r = (texel_value>>4)& 0x03;
    g = (texel_value>>2)& 0x03;
    b = (texel_value)& 0x03;

    // compute the address where to write the texel
    adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + (line*3)*NEXT_SCANLINE_INCREMENT + (column>>1));

    // if texel is left or right
    if ((column&0x01) == 0){
        *adr |= encodeLeftColor[r];
        adr += NEXT_SCANLINE_INCREMENT;
        *adr |= encodeLeftColor[g];
        adr += NEXT_SCANLINE_INCREMENT;
        *adr |= encodeLeftColor[b];
    } else {
        *adr |= encodeRightColor[r];
        adr += NEXT_SCANLINE_INCREMENT;
        *adr |= encodeRightColor[g];
        adr += NEXT_SCANLINE_INCREMENT;
        *adr |= encodeRightColor[b];
    }
```

--- 

## Textures <a name="texture"></a>

[[texture_file2buffer]](https://github.com/oric-software/castoric/search?q=texture_file2buffer)

|||
|--|--|
| Textures are 32*32 pixels PNG or BMP files stored in [img](img) directory. For example this image made by rax ![img/christmas.bmp](img/christmas.bmp) that you can see a zoomed version beside | <img src="img/christmas.bmp" alt="drawing" width="400"/>|

These textures files are first converted into buffer with the script [texture2buf.py](tools/texture2buf.py) called in [build.bat](build.bat).



```shell
python tools\texture2buf.py img\christmas.bmp > proto\c\texture_christmas.h
```

This command generates a file `texture_christmas.h` defining a buffer corresponding to a C version of the image.

```c
unsigned char texture_christmas[] = {
	60, 60, 60, 60, 60, 51, 0, 12, 12, 12, 12, 12, 51, ... , 60, 60
};
```

This file is then included in scene description file [scene.c](proto/c/scene.c)

```c
#include "texture_christmas.h"
```

In order for the texture to be assigned to the wall in scene.
```C
unsigned char *wallTexture[] = {
	texture_christmas		// W0
	, texture_XXXX		    // W1
};
```
