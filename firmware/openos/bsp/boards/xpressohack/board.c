/**
\brief LPC17XX-specific definition of the "board" bsp module.

\author Xavi Vilajosana <xvilajosana@eecs.berkeley.edu>, February 2012.
*/

#include "LPC17xx.h"
#include "board.h"
#include "leds.h"
#include "uart.h"
#include "spi.h"
#include "radio.h"
#include "bsp_timers.h"
#include "clkpwr.h"

//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

void board_init() {

   LPC_PINCON->PINSEL4     &= ~0x3<<16;          // set pinsel to GPIO pag 110 port 2.8
   LPC_PINCON->PINSEL4     &= ~0x3<<8;          // P2.4
   LPC_PINCON->PINSEL4     &= ~0x3<<10;         // P2.5

   LPC_GPIO2->FIODIR        |=  1<<8;            // P2.8 as SLP_TR -- set as output
   LPC_GPIO2->FIODIR        |=  1<<4;            // P2.4 as Radio RST --set as output
   LPC_GPIO2->FIODIR        &= ~1<<5;            // P2.5 as RADIO ISR --set as input


   LPC_GPIO2->FIOCLR        |=  1<<8;           //clear slrptr
   LPC_GPIOINT->IO2IntClr  |=  1<<5;            // P2.5 clear interrupt.
   LPC_GPIOINT->IO2IntEnR  |=  1<<5;            // P2.5 enable as interrupt when low to high


   // initialize bsp modules
   leds_init();
   debugpins_init();
   timers_init();
   spi_init();
   //uart_init();
   radio_init();
   //radiotimer_init();
}

void board_sleep() {
   CLKPWR_Sleep();
}

//=========================== private =========================================
