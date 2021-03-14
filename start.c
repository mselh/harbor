// #include "types.h" 
#include "rcc.h"

#define SYSTICK_BASE ((struct systick_timer *) 0xE000E010)

void start(void);
void systick_handler(void);
void idle(void);

// move to systick.h
void systick_init(void); 
struct systick_timer {
	u32 csr;      /* SYSTICK control and status register,       Address offset: 0x00 */
	u32 rvr;      /* SYSTICK reload value register,             Address offset: 0x04 */
	u32 cvr;      /* SYSTICK current value register,            Address offset: 0x08 */
	u32 calib;    /* SYSTICK calibration value register,        Address offset: 0x0C */
}; 

void start(void) {

    // iniate led
    struct gpio *gp;
    gp = GPIOC_BASE;
    led_init(gp, PC13, GPIOC_ENABLE);
    systick_init();

    // initate systick timer, to be used for context switching
    

    // 3 led flash means  start has finished
    int cnt = 2;
    while (cnt--) {
       led_on(gp, PC13);
       delay(2);
       led_off(gp, PC13);
       delay(2);
    }

    idle();

}

void idle(void){
    for(;;){
    
    }
}

// sys tick timer handler
// maybe moved to a function of its own
// the goal is to context switch, but it s far fetched  now, we are very far away.
void systick_handler(void){
        
    struct gpio *gp;
    gp = GPIOC_BASE;

    // blink
    led_on(gp, PC13);
    delay(2);
    led_off(gp, PC13);
    delay(1);
}

// configures systick
void systick_init(void) {
    // get systick timer
    struct systick_timer *st;
    st = SYSTICK_BASE;

    // enable auto interrupt at 0
    st->csr |= (1 << 1);
    // enable systick counter
    st->csr |= (1 << 0);

    // specify start value
    st->rvr = 0x003FFFFA;
    // set curr value to 0
    //st->cvr = 0x003FFFFA;
    st->cvr = 0;
}

