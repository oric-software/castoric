
// Digital Differential Analyzer Algorithm
// Incremental error algorithm

unsigned char   iea1NbVal;
unsigned char   iea1NbStep;
unsigned char   iea1StartValue;

unsigned char   iea1CurrentValue;
unsigned char   iea1EndValue;

signed char     iea1CurrentError;
void            (*iea1StepFunction)(); 

void iea1Step0(){
    iea1CurrentValue         += 1;
}

void iea1Step1(){

    while ((iea1CurrentError<<1) >= iea1NbStep) {
        iea1CurrentError         -= iea1NbStep;
        iea1CurrentValue         += 1;
    }
    iea1CurrentError     += iea1NbVal;
 
}
void iea1Step2(){
    iea1CurrentError         -= iea1NbVal;
    if ((iea1CurrentError<<1) < iea1NbStep) {
        iea1CurrentError     += iea1NbStep;
        iea1CurrentValue     += 1;
    }
}

void iea1Init(){
    iea1CurrentValue         = iea1StartValue;
    iea1EndValue             = iea1StartValue + iea1NbVal;

    if          (iea1NbVal > iea1NbStep) {
        iea1CurrentError     = iea1NbVal;
        iea1StepFunction     = &iea1Step1;
    } else if   (iea1NbVal < iea1NbStep) {
        iea1CurrentError     = iea1NbStep;
        iea1StepFunction     = &iea1Step2;
    } else {
        iea1CurrentError     = iea1EndValue;
        iea1StepFunction     = &iea1Step0;
    }
}

unsigned char   iea2NbVal;
unsigned char   iea2NbStep;
unsigned char   iea2StartValue;

unsigned char   iea2CurrentValue;
unsigned char   iea2EndValue;

signed char     iea2CurrentError;
void            (*iea2StepFunction)(); 

void iea2Step0(){
    iea2CurrentValue         += 1;
}

void iea2Step1(){

    while ((iea2CurrentError<<1) >= iea2NbStep) {
        iea2CurrentError         -= iea2NbStep;
        iea2CurrentValue         += 1;
    }
    iea2CurrentError     += iea2NbVal;
 
}
void iea2Step2(){
    iea2CurrentError         -= iea2NbVal;
    if ((iea2CurrentError<<1) < iea2NbStep) {
        iea2CurrentError     += iea2NbStep;
        iea2CurrentValue     += 1;
    }
}

void iea2Init(){
    iea2CurrentValue         = iea2StartValue;
    iea2EndValue             = iea2StartValue + iea2NbVal;

    if          (iea2NbVal > iea2NbStep) {
        iea2CurrentError     = iea2NbVal;
        iea2StepFunction     = &iea2Step1;
    } else if   (iea2NbVal < iea2NbStep) {
        iea2CurrentError     = iea2NbStep;
        iea2StepFunction     = &iea2Step2;
    } else {
        iea2CurrentError     = iea2EndValue;
        iea2StepFunction     = &iea2Step0;
    }
}

