// already includes types.h
#include "systick.c"
#include "gpio.c"


void start(void);
void systick_handler(void);
void idle(void);

void start(void) {

    rcc_init();
    // rcc
    // iniate led
    struct gpio *gp;
    gp = GPIOC_BASE;
    led_init(gp, PC13, GPIOC_ENABLE);
    systick_init();

    // initate systick timer, to be used for context switching
    

    // 3 led flash means  start has finished
    blink(3);

    
    //
    idle();

}

// idle, wait for  scheduler
void idle(void){
    while(1){
    
    }
}

// sys tick timer handler
// the goal is to context switch, but it s far-fetched  now, we are very far away.
void systick_handler(void){
        
    // blink clock src
    int src;
    src = get_clock_src();
    blink(1);
    blink(2);

    //blink(src);
    return;
}

// serial usart
