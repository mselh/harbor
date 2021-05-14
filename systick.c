#include "types.h"

#define SYSTICK_BASE ((struct systick_timer *) 0xE000E010)

void systick_init(void); 
struct systick_timer {
	u32 csr;      /* SYSTICK control and status register,       Address offset: 0x00 */
	u32 rvr;      /* SYSTICK reload value register,             Address offset: 0x04 */
	u32 cvr;      /* SYSTICK current value register,            Address offset: 0x08 */
	u32 calib;    /* SYSTICK calibration value register,        Address offset: 0x0C */
}; 


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
    st->rvr = 0xCFFFFFFA;
    // set curr value to 0
    //st->cvr = 0x003FFFFA;
    st->cvr = 0;
}
