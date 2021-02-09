#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "box64bits.h"

void PrintByteBinaryRepresentation(FILE* stream,uint8_t value){ //for nist test
    for (int i=7;i>=0;i--) fputc('0'+((value>>i)&1),stream);
}


int main(){
    uint8_t value;
    uint64_t i;

    FILE* f=fopen("grayscale.txt","w");

    init_random(12);
    
    for (i=1;i<=90000;i++){ //generate grayscale array
        value=random_uint8();

        fprintf(f,"%hhu ",value);
        if (i%300==0) fprintf(f,"\n");      
        
    }
    fclose(f);
    
    init_random(13);

    f=fopen("rgb256.txt","w"); //generate rgb array

    for (int i=1;i<=270000;i++){
        value=random_uint8();
        fprintf(f,"%3hhu ",value);
        if (i%900==0) fprintf(f,"\n");
    }
    fclose(f);
    
    return 0;
}