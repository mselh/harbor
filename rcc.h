#include "types.h"

/* Important: The processor comes out of reset using HSI for System Clock(an internal 8 Mhz RC clock)
    RM0008 Rev 21 8.2.6*
 * */

#define RCC_BASE (struct rcc *) 0x40021000

/* The reset and clock control module */
struct rcc {
    volatile unsigned long rc;  /* 0 - clock control */
    volatile unsigned long cfg; /* 4 - clock config */
    volatile unsigned long cir; /* 8 - clock interrupt */
    volatile unsigned long apb2;    /* c - peripheral reset */
    volatile unsigned long apb1;    /* 10 - peripheral reset */
    volatile unsigned long ape3;    /* 14 - peripheral enable */
    volatile unsigned long ape2;    /* 18 - peripheral enable */
    volatile unsigned long ape1;    /* 1c - peripheral enable */
    volatile unsigned long bdcr;    /* 20 - xx */
    volatile unsigned long csr; /* 24 - xx */
};

/* This gives a blink rate of about 2.7 Hz */
/* i.e. the delay time is about 0.2 seconds (200 ms) */
#define FAST    200

// clock pclk2, 72MHz is the max
#define PCLK2	72000000

// to get 72 MHz, we need PLL scaling as 9x
#define PLLMUL9X (7 << 18) 

void rcc_init(void);
void delay(int);
int get_clock_src(void);

/* THE END */
