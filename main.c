/**
 * main.c
 *
 * This programm is a driver for the EPL190H2C thermal printer.
 *
 */

/*--- includes ---*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


/*--- constants ---*/
// Teensy defaults to only 2 MHz, for compatibility with
// lower voltage power supplies. To run at 16 MHz, you MUST set the speed.
// This setting affects the CPU and ALL periperals, except USB.
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz 0x00 // see pjrc.com for frequency table


/*--- main ---*/
int main(void)
{
  CPU_PRESCALE(CPU_16MHz);
  LED_CONFIG;

  while (1)
  {
    
  }

  return 0;
}
