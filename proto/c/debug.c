

void detailPoints(){
    unsigned char idxPoint;

    for (idxPoint = 0; idxPoint < rayNbPoints; idxPoint ++) {
        printf ("point %d [%d %d], a= %d\n", idxPoint, lPointsX[idxPoint], lPointsY[idxPoint], lAngle[idxPoint]);
    }
}
void textZBuffer () {
    unsigned char ii, jj;
    for (jj=0; jj< 10; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], rayzbuffer[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], rayzbuffer[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], rayzbuffer[(jj)+20] , TableVerticalPos[jj+20]);
    }
    for (jj=30; jj< 40; jj++)  {
        printf ("%d|%d|%d|%d\n", (jj), raywall[(jj)], rayzbuffer[(jj)], TableVerticalPos[jj]);
     }
}
void textCol () {
    unsigned char ii, jj;
    for (jj=0; jj< 10; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
    }
    get();
    for (jj=30; jj< 40; jj++)  {
        printf ("%d|%d|%d|%d \t %d|%d|%d|%d \t%d|%d|%d|%d\n", (jj), raywall[(jj)], tabTexCol[(jj)], TableVerticalPos[jj], (jj)+10, raywall[(jj)+10], tabTexCol[(jj)+10], TableVerticalPos[jj+10], (jj)+20, raywall[(jj)+20], tabTexCol[(jj)+20] , TableVerticalPos[jj+20]);
     }
     get();
}

