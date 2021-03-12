#include "types.h" 
#include "rcc.h"

void start(void);
void led_init( struct gpio* , int ); 
void led_on(struct gpio*, int );
void led_off(struct gpio* , int );
void delay(int);

void start(void) {

    // iniate led
    struct gpio *gp;
    gp = GPIOC_BASE;

    led_init(gp, PC13);
    // loop blink
    

    int cnt = 15;
    while (cnt-- ) {
        led_on(gp, PC13);
        delay(2);
        led_off(gp, PC13);
        delay(2);
    }

}


void led_init( struct gpio* gp, int bit ) {
    int conf;
    int shift;
    struct rcc *rp = RCC_BASE;

    /* Turn on GPIO C */
    rp->ape2 |= GPIOC_ENABLE;

    gp = GPIOC_BASE;

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
