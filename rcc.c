#include "types.h"
#include "rcc.h"


void rcc_init(void){

    struct rcc* c;
    c = RCC_BASE;



}

void delay(int seconds) {
    volatile int count = seconds * 500 * FAST;
    while(count>0){
        count--; 
    }
}

// outputs SWS[1:0]: System clock switch status
int get_clock_src(void){

    struct rcc* c;
    c = RCC_BASE;

    // we need 3 and 2th bits
    // shift two times, then mask with 3
    u32 reg = c->cfg;
    u32 val = reg >> 2;
    val = val & 3; 
    
    return (int) val;
}
