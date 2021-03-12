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

#define GPIOA_ENABLE    0x04
#define GPIOB_ENABLE    0x08
#define GPIOC_ENABLE    0x10

#define RCC_BASE    (struct rcc *) 0x40021000

/* One of the 3 gpios */
struct gpio {
    volatile unsigned long cr[2];
    volatile unsigned long idr;
    volatile unsigned long odr;
    volatile unsigned long bsrr;
    volatile unsigned long brr;
    volatile unsigned long lock;
};

#define GPIOA_BASE  (struct gpio *) 0x40010800
#define GPIOB_BASE  (struct gpio *) 0x40010C00
#define GPIOC_BASE  (struct gpio *) 0x40011000

#define MODE_OUT_2  0x02    /* Output, 2 Mhz */

#define CONF_GP_UD  0x0 /* Pull up/down */
#define CONF_GP_OD  0x4 /* Open drain */

/* This gives a blink rate of about 2.7 Hz */
/* i.e. the delay time is about 0.2 seconds (200 ms) */
#define FAST    200
#define PC13    13

/* THE END */
