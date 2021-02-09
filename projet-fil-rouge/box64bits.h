#ifndef BOX64BITS_H
#define BOX64BITS_H
#include <stdint.h>

/*init random generation with the seed given in argument*/
extern void init_random(uint32_t seed);

/*generate one random byte*/
extern uint8_t random_uint8(void);

#endif