/**
 * main.c
 *
 * This programm is a driver for the EPL190H2C thermal printer.
 *
 */

/*--- includes ---*/
#include <avr/io.h>
#include <util/delay.h>

/*--- constants ---*/
// Teensy defaults to only 2 MHz, for compatibility with
// lower voltage power supplies. To run at 16 MHz, you MUST set the speed.
// This setting affects the CPU and ALL periperals, except USB.
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz 0x00 // see pjrc.com for frequency table

// Hardwareinterface to printer
#define LATCH   0
#define STROBE1 1
#define STROBE2 2
#define STROBE3 3
#define STROBE4 4
#define CLOCK   1
#define DATA_IN 2


#define DDR_PRINT DDRB
#define PORT_PRINT PORTB
#define CLOCK_PRINT 1
#define DATA_PRINT 2


/*--- prototyps ---*/
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void paper_step(uint8_t lines);
void printStrobe1(void);
void printStrobe2(void);
void printStrobe3(void);
void printStrobe4(void);


/*--- main ---*/
int main(void)
{
  // config 90USB1287
  CPU_PRESCALE(CPU_16MHz);

  DDRC |= (1 << LATCH) | (1 << STROBE1) | (1 << STROBE2) | (1 << STROBE3) | (1 << STROBE4);
  PORTC |= (1 << LATCH);
  PORTC |= (1 << STROBE1);
  PORTC |= (1 << STROBE2);
  PORTC |= (1 << STROBE3);
  PORTC |= (1 << STROBE4);
  
  DDR_PRINT |= (1 << CLOCK_PRINT) | (1 << DATA_PRINT);
  /*int i, j;
  char buf[73];

  for(i = 0; i < 72; i++)
  {
    for(j = 0; j < 8; j++)
    {
      PORT_PRINT &= ~(1<<CLOCK_PRINT);
  
      if(1)
        PORT_PRINT |= (1<<DATA_PRINT);
      else
        PORT_PRINT &= ~(1<<DATA_PRINT);
 
      _delay_ms(1); 
      PORT_PRINT |= (1<<CLOCK_PRINT);
      _delay_ms(1);
    }
  }*/

  while(1)
  {
    /*PORTC &= ~(1 << LATCH);
    _delay_ms(1);
    PORTC |= (1 << LATCH);

    _delay_ms(1);*/


  }

  return 0;
}


/*===========================================================================*/
/*--- init spi interface ---*/
void SPI_MasterInit(void)
{
  PRR0 &= ~(1<<2);
  /* Set MOSI and SCK output, all others input */
  DDRB = (1<<DDB2)|(1<<DDB1);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
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


void printStrobe1(void)
{
  PORTC &= ~(1 << STROBE1);
  _delay_ms(10);
  PORTC |= (1 << STROBE1);
}

void printStrobe2(void)
{
  PORTC &= ~(1 << STROBE2);
  _delay_ms(10);
  PORTC |= (1 << STROBE2);
}

void printStrobe3(void)
{
  PORTC &= ~(1 << STROBE3);
  _delay_ms(10);
  PORTC |= (1 << STROBE3);
}

void printStrobe4(void)
{
  PORTC &= ~(1 << STROBE4);
  _delay_ms(10);
  PORTC |= (1 << STROBE4);
}


