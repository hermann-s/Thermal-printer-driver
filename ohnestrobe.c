


#define DDR_PRINT DDRB
#define PORT_PRINT PORTB
#define CLOCK_PRINT 1
#define DATA_PRINT 2
#define LATCH_PRINT 3

int i, j;
char buf[73];


for(i = 0; i < 72; i++)
{
	for(j = 0; j < 8; j++)
	{
		PORT_PRINT &= ~(1<<CLOCK_PRINT);
		
		if(buf[i+1] & (1<<j))
			PORT_PRINT |= (1<<DATA_PRINT);
		else
			PORT_PRINT &= ~(1<<DATA_PRINT);

		PORT_PRINT |= (1<<CLOCK_PRINT);
		_delay_ms(1);	/* TODO: Raus */
	}
	
}
PORT_PRINT &= ~(1<<LATCH_PRINT);
_delay_ms(1);	/* TODO: Raus! */
PORT_PRINT |= (1<<LATCH_PRINT);

/* Hier die Strobes auf Low und dann wieder auf High */
