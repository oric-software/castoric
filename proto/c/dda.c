
// Digital Differential Analyzer Algorithm
// Incremental error algorithm

unsigned char   ddaNbVal;
unsigned char   ddaNbStep;
unsigned char   ddaStartValue;

unsigned char   ddaCurrentValue;
unsigned char   ddaEndValue;

signed char     ddaCurrentError;
void            (*ddaStepFunction)(); 

void ddaStep0(){
    PROFILE_ENTER(ROUTINE_DDASTEP0);
    ddaCurrentValue         += 1;
    PROFILE_LEAVE(ROUTINE_DDASTEP0);    
}

void ddaStep1(){
    PROFILE_ENTER(ROUTINE_DDASTEP1);
    while ((ddaCurrentError<<1) >= ddaNbStep) {
        ddaCurrentError         -= ddaNbStep;
        ddaCurrentValue         += 1;
    }
    ddaCurrentError     += ddaNbVal;
    PROFILE_LEAVE(ROUTINE_DDASTEP1);    
}
void ddaStep2(){
    PROFILE_ENTER(ROUTINE_DDASTEP2);
    ddaCurrentError         -= ddaNbVal;
    if ((ddaCurrentError<<1) < ddaNbStep) {
        ddaCurrentError     += ddaNbStep;
        ddaCurrentValue     += 1;
    }
    PROFILE_LEAVE(ROUTINE_DDASTEP2);
}

void ddaInit(){
    PROFILE_ENTER(ROUTINE_DDAINIT);
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
    PROFILE_LEAVE(ROUTINE_DDAINIT);
}

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