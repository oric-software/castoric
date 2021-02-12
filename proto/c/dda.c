
// Digital Differential Analyzer Algorithm
// Incremental error algorithm

#ifdef USE_C_DDA 
unsigned char   ddaNbVal;
unsigned char   ddaNbStep;
unsigned char   ddaStartValue;

unsigned char   ddaCurrentValue;
unsigned char   ddaEndValue;

signed char     ddaCurrentError;
void            (*ddaStepFunction)(); 

void ddaStep0(){

    ddaCurrentValue         += 1;
 
}

void ddaStep1(){

    while ((ddaCurrentError<<1) >= ddaNbStep) {
        ddaCurrentError         -= ddaNbStep;
        ddaCurrentValue         += 1;
    }
    ddaCurrentError     += ddaNbVal;
  
}
void ddaStep2(){

    ddaCurrentError         -= ddaNbVal;
    if ((ddaCurrentError<<1) < ddaNbStep) {
        ddaCurrentError     += ddaNbStep;
        ddaCurrentValue     += 1;
    }

}

void ddaInit(){

    ddaCurrentValue         = ddaStartValue;
    ddaEndValue             = ddaStartValue + ddaNbVal;

    if          (ddaNbVal > ddaNbStep) {
        ddaCurrentError     = ddaNbVal;
        ddaStepFunction     = &ddaStep1;
    } else if   (ddaNbVal < ddaNbStep) {
        ddaCurrentError     = ddaNbStep;
        ddaStepFunction     = &ddaStep2;
    } else {
        ddaCurrentError     = ddaEndValue;
        ddaStepFunction     = &ddaStep0;
    }

}

#else
extern unsigned char   ddaNbVal;
extern unsigned char   ddaNbStep;
extern unsigned char   ddaStartValue;

extern unsigned char   ddaCurrentValue;
extern unsigned char   ddaEndValue;

extern signed char     ddaCurrentError;
extern void            (*ddaStepFunction)(); 
#endif // USE_C_DDA 



// void main (){

//     printf ("hello\n");

//     ddaStartValue       = 0;
//     ddaNbStep           = 5;
//     ddaNbVal            = 12;

//     ddaInit();
//     printf ("%d\n", ddaCurrentValue);
//     while (ddaCurrentValue < ddaEndValue) {
//         (*ddaStepFunction)(); 
//         printf ("%d\n", ddaCurrentValue);
//     }
// }