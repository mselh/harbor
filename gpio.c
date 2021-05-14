#include "types.h"
#include "rcc.h"

#define GPIOA_ENABLE    0x04
#define GPIOB_ENABLE    0x08
#define GPIOC_ENABLE    0x10

#define UART1_ENABLE	0x4000

#define OUTPUT_50M	3
#define ALT_PUSH_PULL		8



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

#define PC13    13


void led_init( struct gpio* , int, ulong); 
void led_on(struct gpio*, int );
void led_off(struct gpio* , int );


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

// blink n times with a delay
// requires led_init() to be called earlier
void blink(int n){

    struct gpio* gp;
    gp = GPIOC_BASE;
    while (n--) {
       led_on(gp, PC13);
       delay(35);
       led_off(gp, PC13);
       delay(10);
    }
}

void
gpio_mode ( struct gpio *gp, int bit, int mode )
{
	int reg;
	int conf;
	int shift;

	reg = 0;
	if ( bit >= 8 ) {
	    reg = 1;
	    bit -= 8;
	}
	shift = bit * 4;

	conf = gp->cr[reg] & ~(0xf<<shift);
	gp->cr[reg] = conf | (mode << shift);
}

void
gpio_uart1 ( void )
{
	gpio_mode ( GPIOA_BASE, 9, OUTPUT_50M | ALT_PUSH_PULL );
	// gpio_mode ( GPIOA_BASE, 10, INPUT_FLOAT );
}
