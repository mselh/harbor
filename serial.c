#include "types.h"
#include "gpio.c"

// implemented for usart1

#define UART1_BASE	(struct uart *) 0x40013800
#define	ST_TXE		0x0080		/* Transmitter empty */

// uart register from manual
struct uart {
	volatile unsigned long status;	/* 00 */
	volatile unsigned long data;	/* 04 */
	volatile unsigned long baud;	/* 08 */
	volatile unsigned long cr1;	/* 0c */
	volatile unsigned long cr2;	/* 10 */
	volatile unsigned long cr3;	/* 14 */
	volatile unsigned long gtp;	/* 18 - guard time and prescaler */
};

// innitializes uart 1, serial 1
void serial_init(void);
static void  uart_init(struct uart*, int);

void serial_init(void) {
    // we will  work with uart 1, which happends to be in gpio_A
    // toggle it
    
    struct rcc *rp = RCC_BASE;
    rp->ape2 |= GPIOA_ENABLE;
    rp->ape2 |= UART1_ENABLE;

    gpio_uart1();
    uart_init(UART1_BASE, 115200);
    
}

static void
uart_init( struct uart *up, int baud )
{
	/* 1 start bit, even parity */
	up->cr1 = 0x340c;
	up->cr2 = 0;
	up->cr3 = 0;
	up->gtp = 0;

	up->baud = PCLK2 / baud;
}

void
serial_putc ( int c )
{
	struct uart *up = UART1_BASE;

	while ( ! (up->status & ST_TXE) )
	    ;
	up->data = c;
}

