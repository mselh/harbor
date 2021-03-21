#include "types.h"
#include "rcc.h"


void rcc_init(void){
    struct rcc* c;
    c = RCC_BASE;

    // turn on HSE
    //c->rc = c->rc | HSE_ON;
    // wait for  8 cycles, or, as done here, wait flag to raise
    //while(((c->rc >> 17) & 1) == 0x0){
    //}
    //there is no bit level access only > bytes

    // first configure pll, first one, unnumbered one
    // 21-18 of c->cfg, pll multiplier 9x
    c->cfg = PLL_HSE | PLLMUL9X | SYS_HSI | APB1_DIV2;;
    // set pll clock source to external, cuz it is more accurate

    int tmp1=60;
    while(tmp1--){
    }
    
    // enable pll, by turnin on 24th bit
    c->rc = HSI_ON | HSE_ON | PLL_ENABLE | HSE_TRIM;

    // wait for pll to be ready 
    // bit 25 pll ready
    while(!( c->rc & PLL_LOCK ) ) {
    }
    int tmp;
    tmp=60;
    while(tmp--){
    }
    * FLASH_ACR = FLASH_PREFETCH | FLASH_WAIT2;
    
    c->cfg = PLL_HSE | PLLMUL9X | SYS_PLL | APB1_DIV2;
    tmp=60;
    while(tmp--){
    }


}

void delay(int seconds) {
    volatile int count = seconds * 500 * FAST;
    while(count>0){
        count--; 
    }
}

// outputs SWS[1:0]: System clock switch status
int get_clock_src(void){

    struct rcc* c;
    c = RCC_BASE;

    // we need 3 and 2th bits
    // shift two times, then mask with 3
    u32 reg = c->cfg;
    u32 val = reg >> 2;
    val = val & 3; 
    
    return (int) val;
}
