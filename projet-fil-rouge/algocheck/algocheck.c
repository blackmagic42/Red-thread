#include "algocheck.h"
#include <stdio.h>
#include <stdlib.h>

/*This module is use to check sequences generated by our algorithm*/

/*global variables*/
static uint8_t sequences[20],repeat;
static uint64_t occurence[256],counter;
static double sum,o,variance;

/*init the function which checks occurence of each value and the global mean*/
void init_check_value(void){
    for (int i=0;i<256;i++) occurence[i]=0;
    sum=0;
    o=0;
    counter=0;
}

/*select value to analyse it*/
void check_value(uint8_t value){
    occurence[value]++;
    sum+=value;
    counter++;
    
}

/*display analysis values*/
void end_check_value(void){
    o=(double)counter/256;
    for (int k=0;k<256;k++) variance+=(occurence[k]-o)*(occurence[k]-o);
    variance/=counter;
    printf("\nmoyenne statistique:%lf\n",sum/counter);
    printf("variance occurence=%lf\n",variance);
    printf("moyenne occurence:%lf\n",o);
}

/*display occurence of each value*/
void display_occurence(void){
    for (int k=0;k<256;k++){
        printf("tb[%3d]=%5lu   ",k,occurence[k]);
        if ((k+1)%8==0) putchar('\n');
    }
    putchar('\n');
}

/*save occurence of each value in a file*/
void save_occurence(char* restrict filename){
    FILE* f=fopen(filename,"w");
    if (f==NULL) return;
    for (int k=0;k<256;k++) fprintf(f,"%lu \n",occurence[k]);
    fclose(f);
}

/*init the function that check period: take 20 values*/
void init_check_period(uint8_t (*func)(void)){ //this function take as argument a function pointer
    repeat=0;
    for (int i=0;i<20;i++) sequences[i]=func();
}

/*function which checks the period: if a period is detected return 1 else 0.*/
uint64_t check_period(uint8_t value){
    if (sequences[repeat]==value){
        repeat++;
        if (repeat==20){
            repeat=0;
            return counter;
        }
    }else{
        repeat=0;
    }
    return 0;
}
