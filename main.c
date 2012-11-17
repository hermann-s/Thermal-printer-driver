/**
 * main.c
 *
 * This programm is a driver for the EPL190H2C thermal printer.
 *
 */

/*--- includes ---*/
#include <avr/io.h>
#include "lib/uart.h"
#include <util/delay.h>


/*--- constants ---*/
// Teensy defaults to only 2 MHz, for compatibility with
// lower voltage power supplies. To run at 16 MHz, you MUST set the speed.
// This setting affects the CPU and ALL periperals, except USB.
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz 0x00 // see pjrc.com for frequency table

// Hardwareinterface to printer
#define LATCH   0//PC0
#define STROBE1 1//PC1
#define STROBE2 2//PC2
#define STROBE3 3//PC3
#define STROBE4 4//PC4
#define CLOCK   1//PB1
#define DATA_IN 2//PB2

#define READY           0
#define NO_PAPER        1
#define PRINTER_HEAD_UP 2
#define CUT_PAPER       3
#define PRINTING        4

#define F_CPU 16000000UL

/*--- prototyps ---*/
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void paper_step(uint8_t lines);


/*--- main ---*/
int main(void)
{
  // config 90USB1287
  CPU_PRESCALE(CPU_16MHz);
  //uart_init(9600);
  SPI_MasterInit();

  PORTC |= (1 << LATCH);
  PORTC |= (1 << STROBE1);
  PORTC |= (1 << STROBE2);
  PORTC |= (1 << STROBE3);
  PORTC |= (1 << STROBE4);

  /* variables */
  //char line = 0x00;
  //char printer_flag = 0;

  char test[72];
  for(int i=0; i < 72; i++) test[i]=0xff;

  while(1)
  {
    /* wait until is received */
    //if(1)//uart_available > 0)
    //{
      /* interrupt for usart, so caller knows state of printer */
      //printer_flag = PRINTING;

      //line = uart_getchar();
      //line = 0x01;
      //if(line == 0x00) /* status abfrage */
      //{
        //uart_putchar(printer_flag);
      //}
      //else if(line == 0x01) /* empfangen der daten */
      //{
        //while(uart_available > 0)
        //{
        //  line = uart_getchar();
          /* send line to printer */
        //  SPI_MasterTransmit(line);          
        //}
        for(int i=0; i < 72; i++) SPI_MasterTransmit(test[i]);
        
        PORTC &= ~(1 << LATCH);
        /* latch need a few nano sec. for write in latch register */
        PORTC |= (1 << LATCH);

        /* write first line */
        PORTC &= ~(1 << STROBE1);
        paper_step(1);
        PORTC |= (1 << STROBE1);

        PORTC &= ~(1 << STROBE2);
        paper_step(1);
        PORTC |= (1 << STROBE2);

        PORTC &= ~(1 << STROBE3);
        paper_step(1);
        PORTC |= (1 << STROBE3);

        PORTC &= ~(1 << STROBE4);
        paper_step(1);
        PORTC |= (1 << STROBE4);
      //}
      //else if(line == 0x02) /* motor vorschub */
      //{

      //}
      //else if(line == 0x03) /* cutter antreiben */
      //{

      //}
   // }
    
  }

  return 0;
}


/*===========================================================================*/
/*--- init spi interface ---*/
void SPI_MasterInit(void)
{
  /* Set MOSI and SCK output, all others input */
  DDRB = (1<<DDB2)|(1<<DDB1);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

/*--- send data over spi interface ---*/
void SPI_MasterTransmit(char cData)
{
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}


/*--- next line with steper ---*/
void paper_step(uint8_t lines)
{

}



