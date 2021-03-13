// #include "types.h" 
#include "rcc.h"

void start(void);

void start(void) {

    // iniate led
    struct gpio *gp;
    gp = GPIOC_BASE;
    led_init(gp, PC13, GPIOC_ENABLE);
    
    // loop blink

    int cnt = 15;
    while (cnt-- ) {
        led_on(gp, PC13);
        delay(2);
        led_off(gp, PC13);
        delay(2);
    }

}

