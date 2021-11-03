

#define DICHO_NB_MAX_VAL 8

unsigned char dichoNbVal = 0;

unsigned char tabDichoVals [DICHO_NB_MAX_VAL];
unsigned char tabDichoIdxs [DICHO_NB_MAX_VAL];


#ifndef USE_C_DICHOBUF
extern unsigned char dichoInsertVal;
extern unsigned char dichoInsertIdx;
#endif


#ifdef USE_C_DICHOBUF

void dichoInit(){
    dichoNbVal = 0;
}

unsigned char dichoSearchPos(unsigned char val) {
    unsigned char insertPos;

    if (0==(insertPos = dichoNbVal)) return insertPos;

    do {
        insertPos-=1;
    } while ((insertPos != 0) && (tabDichoVals[insertPos] > val));
    if (tabDichoVals[insertPos] <= val) insertPos+=1;
    return insertPos;
}

void dichoInsertAtPos(unsigned char pos, unsigned char index, unsigned char val){
    unsigned char idx;
    idx = dichoNbVal;
    while (idx != pos) {
        tabDichoVals[idx] = tabDichoVals[idx-1];
        tabDichoIdxs[idx] = tabDichoIdxs[idx-1];
        idx     -= 1;
    }
    tabDichoVals[idx] = val;
    tabDichoIdxs[idx] = index;
    dichoNbVal +=1;
}
#endif // USE_C_DICHOBUF

void dichoInsert (unsigned char index, unsigned char val){
    
#ifdef USE_C_DICHOBUF

    unsigned char insPos;

    // recherche de la postion d'insertion
    insPos = dichoSearchPos(val);

    // insertion
    dichoInsertAtPos(insPos, index, val);
#else
    dichoInsertVal = val;
    dichoInsertIdx = index;
    dichoASMInsert();

#endif //  USE_C_DICHOBUF
}

// void displayTable(){
//     int ii;
//     for (ii= 0; ii < dichoNbVal; ii++) {
//         printf("%d\t", tabDichoIdxs[ii]);
//     }
//     printf ("\n");
//     for (ii= 0; ii < dichoNbVal; ii++) {
//         printf("%d\t", tabDichoVals[ii]);
//     }
//     printf ("\n");
// }
// void main () {

//     dichoInsert (1, 10);
//     dichoInsert (2, 15);
//     dichoInsert (3, 5);
//     dichoInsert (4, 12);
//     dichoInsert (5, 17);

//     displayTable();
// }


