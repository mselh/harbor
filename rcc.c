#include "types.h"
#include "rcc.h"

void led_init( struct gpio* gp, int bit, ulong gp_enable ) {
    int conf;
    int shift;
    struct rcc *rp = RCC_BASE;

    // Turn on GPIO port within clock 
    rp->ape2 |= gp_enable;


    shift = (bit - 8) * 4;
    conf = gp->cr[1] & ~(0xf<<shift);
    conf |= (MODE_OUT_2|CONF_GP_OD) << shift;
    gp->cr[1] = conf;

}


// bssr <16 => BRy, resets to 0
void led_off(struct gpio* gp, int bit) {
    gp->bsrr = 1 << bit;
}

// bssr > 16 => BSy ports, sets to 1
void led_on(struct gpio* gp, int bit) {
    gp->bsrr = 1<<(bit+16);
}

void delay(int seconds) {
    volatile int count = seconds * 500 * FAST;
    while(count>0){
        count--; 
    }
}
