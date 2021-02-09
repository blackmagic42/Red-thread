#include "box64bits.h"
#include <stdio.h>
/*bytes generator -> minimum period:65 011 464 */

/*this 64 bit unsigned int has 32 1 and 32 0 in its binary representation*/
static uint64_t number=0xFFFFFFFF; //default value

/*swap two byte inside a 64 bits unsigned int */
static void swap_bytes(void* n,uint8_t byte_1,uint8_t byte_2){
    uint8_t* ptr=n; //          0 1 | 1 0 | 1 1 | 0 0
    ptr[byte_1]^=ptr[byte_2]; //1 1 | 1 0 | 0 1 | 0 0
    ptr[byte_2]^=ptr[byte_1]; //1 0 | 1 1 | 0 1 | 0 0
    ptr[byte_1]^=ptr[byte_2]; //1 0 | 0 1 | 1 1 | 0 0
}

/*take n bits on the right side of the number and move them on the left side of it*/
static void move_right(uint64_t* var,uint8_t n){ 
    uint64_t a=(*var)&((1<<n)-1);
    (*var)>>=n;
    (*var)|=(a<<(64-n));
}

/*init number with the seed given in argument*/
void init_random(uint32_t seed){
    number=(1103515245*seed+12345)&0xFFFFFFFF;
    number|=(~number)<<32;
}

/*generate one random byte*/
uint8_t random_uint8(void){
    move_right(&number,25);

    if (number&0x1) swap_bytes(&number,0,4); //swap bytes
    if (number&0x2) swap_bytes(&number,1,5);
    if (number&0x8) swap_bytes(&number,2,6);
    if (number&0x40) swap_bytes(&number,3,7);
     
    return (number>>42)&0xFF; //return a 8 bits sequence of the number
}