#ifndef ALGOCHECK_H
#define ALGOCHECK_H
#include <stdint.h>

/*We have used these functions to check if our algorithm were efficient*/

/*init the function which checks occurence of each value and the global mean*/
extern void init_check_value(void);

/*select value to analyse it*/
extern void check_value(uint8_t value);

/*display analysis values*/
extern void end_check_value(void);

/*display occurence of each value*/
extern void display_occurence(void);

/*save occurence of each value in a file*/
extern void save_occurence(char* restrict filename);

/*init the function that check period: take 20 values*/
extern void init_check_period(uint8_t (*func)(void)); //function pointer

/*function which checks the period: if a period is detected return 1 else 0.*/
extern uint64_t check_period(uint8_t value);

#endif
