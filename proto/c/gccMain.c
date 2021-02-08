
#include <stdio.h>

#include "profile.h"

#include "colorimg.c"
#include "dda.c"
#include "tabTexelColor.c"
#include "raycast.c"
#include "scene.c"


// #define PROFILE_ENTER(x)
// #define PROFILE_LEAVE(x)

void initCamera(){
    glCamPosX               = 3; // 0; // -62; // 39;  //
    glCamPosY               = 3; // 0; //- 62; // -25; //
    glCamRotZ               = 32; // 32; // 64; //
    RayLeftAlpha            = glCamRotZ + tabRayAngles[0];
    // RayRightAlpha           = glCamRotZ - tabRayAngles[0];
}

void rayInitCasting(){
    unsigned char ii;
    for (ii=0; ii< NB_SLICES; ii++) {
        rayzbuffer[ii]      = 255;
        raywall[ii]         = 255;
    }
}


void textCol () {
    unsigned char ii, jj;
    for (jj=0; jj< 10; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
    }

    for (jj=30; jj< 40; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
     }
}

void precalculateWallsAngle() {
    unsigned char idxWall, idxPt1, idxPt2;
    signed char dX, dY, angle;

    for (idxWall = 0; idxWall < rayNbWalls; idxWall ++) { 

        idxPt1 = lWallsPt1[idxWall];
        idxPt2 = lWallsPt2[idxWall];

        dX = lPointsX[idxPt2]-lPointsX[idxPt1];
        dY = lPointsY[idxPt2]-lPointsY[idxPt1];

        if (dX == 0) {
            lWallsCosBeta[idxWall] = 0;
        } else if (dY == 0) {
            if (dX > 0) {
                lWallsCosBeta[idxWall] = 32;
            } else {
                lWallsCosBeta[idxWall] = -32;
            }
        } else {
            /* 
             *  Not aligned walls not handled
             */
        }
    }
}

void initScene (signed char sceneData[]){
	unsigned int ii;
	unsigned char jj;

	ii=0;
	rayNbPoints = (unsigned char)sceneData[ii++];
	rayNbWalls = (unsigned char)sceneData[ii++];
	for (jj=0; jj < rayNbPoints; jj++){
		lPointsX[jj]= sceneData[ii++] ; lPointsY[jj] = sceneData[ii++];  // points 0
	}
	for (jj=0; jj < rayNbWalls; jj++){
		lWallsPt1[jj]= (unsigned char)(sceneData[ii++]) ; lWallsPt2[jj] = (unsigned char)(sceneData[ii++]);// points 0
	}
    precalculateWallsAngle();
}

#include "iea2d.c"
#define max(x,y)          (((x)<(y))?(y):(x))
#define min(x,y)          (((x)<(y))?(x):(y))
#define VIEWPORT_LEFT_COLUMN            2
#define VIEWPORT_RIGHT_COLUMN           78

#define VIEWPORT_UP_LINE                0
#define VIEWPORT_DOWN_LINE              64

#define SCREEN_WIDTH                    80
#define SCREEN_HEIGHT                   64

void displaySprite(unsigned char column, unsigned char height){

    signed char scrColIdx, scrLinIdx;

    // unsigned char start_column, end_column, nb_column;
    // start_column    = max(VIEWPORT_LEFT_COLUMN, column-height/2);
    // end_column      = min(VIEWPORT_RIGHT_COLUMN, column + height/2);
    // nb_column       = height/2;

    scrColIdx          = column - height/2;
    scrLinIdx          = SCREEN_HEIGHT/ 2 - height/2;

    iea1StartValue       = 0;
    iea1NbVal            = TEXTURE_HEIGHT;
    iea1NbStep           = height;
    iea1Init();

    do {
        iea2StartValue       = 0;
        iea2NbVal            = TEXTURE_HEIGHT;
        iea2NbStep           = height;
        iea2Init();
        do {
            printf ("%d %d, %d %d\n", scrLinIdx, scrColIdx, iea1CurrentValue, iea2CurrentValue);
            (*iea2StepFunction)();
            scrColIdx   += 1;
        } while (iea2CurrentValue <= iea2EndValue);
        (*iea1StepFunction)();
        scrLinIdx      += 1;
        scrColIdx      = column - height/2;
    } while (iea1CurrentValue <= iea1EndValue);
}

//precalTexPixelOffset[N] =  Nth value of Incremental Error Algo (nbStep = Height on screen , nbVal = TEXTURE_DIMENSION)
unsigned char precalTexPixelOffset[80];
void precalcTexPixelRunthrough(unsigned char height){

    unsigned char       idxTexPixel;    // run through precalTexPixelOffset
    idxTexPixel           = 0;

    iea2StartValue       = 0;
    iea2NbVal            = TEXTURE_HEIGHT-1;
    iea2NbStep           = height;
    iea2Init();
    do {
        precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
        (*iea2StepFunction)();
    } while (iea2CurrentValue < iea2EndValue);
    precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;


}
unsigned char *ptrTexture;
unsigned int multi32[] = {
	0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480
	, 512, 544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 960, 992
	};
#define EMPTY_ALPHA 0
unsigned char          texcolumn, texline;
unsigned int            offTexture;
unsigned char           renCurrentColor;
unsigned char *theAdr;

void displaySprite02(unsigned char column, unsigned char height){

    signed char         viewportColIdx, viewportLinIdx;

    unsigned char       idxLinTexture, idxColTexture;
    unsigned char       nbColumn, nbLine;
    unsigned char       wallheight;
    int ii;
    int adrScreenCol        = 0;
    int adrScreenWrt        = 0;

    ptrTexture = texture_pillar;

    precalcTexPixelRunthrough(height);
    // for (idxTexPixel = 0; idxTexPixel <= iea2NbStep; idxTexPixel ++) {
    //     printf ("%d\n", precalTexPixelOffset [idxTexPixel]);
    // }

    viewportColIdx           = column - height/2;
    viewportLinIdx           = SCREEN_HEIGHT/ 2 - height/2;
    idxLinTexture       = 0;
    idxColTexture       = 0;
    adrScreenCol        = 0;
    adrScreenWrt        = 0;
    nbColumn            = height; // number of column on Screen of the Sprite
    nbLine              = height; // number of line on Screen of the Sprite

    // Rejoindre la bordure gauche
    while ((viewportColIdx < VIEWPORT_LEFT_COLUMN) && (nbColumn != 0)) {
        nbColumn            --;
        viewportColIdx      ++;
        idxColTexture       ++;
        printf ("skipped column %d (nbColumn = %d)\n", viewportColIdx, nbColumn);
    }
    if (nbColumn == 0) return ;

    // Parcours colonne
    do {
        printf ("--== drawing column %d (nbColumn = %d) ==-- \n", viewportColIdx, nbColumn);
        // Si Profondeur [colonne] < DistanceObject
        // On determine ici la colonne du sprite est visible en comparant la hauteur à l'ecran du sprite à celle du 
        // Cela évite d'utiliser la 
        // si l'objet du sprite est plus grand ou plus petit que le mur affiche sur cette colonne
        //          if (rayzbuffer[RaySliceIdx] < DistanceObject) {
        //          if (raylogdist[RaySliceIdx] < 32*log2(DistanceObject) ){
        wallheight = 32 - (100-TableVerticalPos[viewportColIdx])/4;
        if (height > wallheight) {
            // Rejoindre la bordure haute de l'ecran
            idxLinTexture           = 0;
            viewportLinIdx          = SCREEN_HEIGHT/ 2 - height/2;
            nbLine                  = height;
            while ((viewportLinIdx--) < VIEWPORT_UP_LINE) {
                printf ("skipped lin %d \n", viewportLinIdx, nbColumn);
                idxLinTexture ++;
            }
            // go right to next column if 
            // if () continue;
            // Parcour ligne
            do {
                // Si couleur [ligneTGexture][colonneTexture] != EMPTY
                texcolumn           = precalTexPixelOffset [idxColTexture];
                offTexture          = multi32[texcolumn];
                texline             = precalTexPixelOffset [idxLinTexture];
                renCurrentColor     = ptrTexture[offTexture + texline];
                if (renCurrentColor != EMPTY_ALPHA) {
                    // afficher texel [couleur] a ligneViewport, colonneViewpport
                    printf ("display color %d (= texture [%d, %d]) at position(%d, %d)\n", renCurrentColor, texline, texcolumn, viewportLinIdx, viewportColIdx);
                }
                idxLinTexture       ++;
            // Jusqu'à indice ligne > 64 
            } while (((++viewportLinIdx) < VIEWPORT_DOWN_LINE) && ((--nbLine) != 0));
        }
        idxColTexture       ++;
    } while (((++viewportColIdx) < VIEWPORT_RIGHT_COLUMN ) && ((--nbColumn) > 0));
    // Jusqu'à idxColonne = VIEWPORT_RIGHT_COLUMN ou  nbColumn = 0


}

void main(){

    printf ("DEBUT\n");
    initCamera();
    initScene (scene_00);

    rayInitCasting();
    rayProcessPoints();
    rayProcessWalls();

    // textCol ();

    displaySprite02(3, 20);

    printf ("FIN\n");
}
