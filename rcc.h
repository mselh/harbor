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
// setter of pll input clock source to external crystall
#define PLL_HSE		0x10000
// enabler bits for pll as sysclock
#define PLL_LOCK 0x02000000

// hse on at init
#define HSI_ON		1
#define HSE_ON		0x10000
#define PLL_ENABLE	0x01000000

#define SYS_HSI 0x00
#define SYS_PLL 0x02

#define HSE_TRIM	0x80

#define APB1_DIV2	(4<<8)


#define FLASH_ACR	((volatile unsigned long *) 0x40022000)

#define FLASH_PREFETCH	0x0010	/* enable prefetch buffer */
#define FLASH_HCYCLE	0x0008	/* enable half cycle access */

#define FLASH_WAIT0	0x0000	/* for sysclk <= 24 Mhz */
#define FLASH_WAIT1	0x0001	/* for 24 < sysclk <= 48 Mhz */
#define FLASH_WAIT2	0x0002	/* for 48 < sysclk <= 72 Mhz */
void rcc_init(void);
void delay(int);
int get_clock_src(void);

/* THE END */
