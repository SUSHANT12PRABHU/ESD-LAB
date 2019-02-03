/***********************************************************************
 * LED Test
 * Developed by
 * Advanced Electronics Systems, Bengaluru.
 *----------------------------------------------------------------------
 * There are 8 GP leds on the board. This board serially toggles them.
 * Connect a 10 pin FRC cable from CNA to CNA1.
 * Port lines: P0.4 to P0.11
 ***********************************************************************/ 
 #include <LPC17xx.h>
 
 unsigned int i,j;
 unsigned long LED = 0x00000010;

 int main(void)
 {
	SystemInit();
	SystemCoreClockUpdate();

	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;

	while(1)
	{
		LED = 0x00000010;
		for(i=1;i<9;i++)	   //On the LED's serially
		{
			LPC_GPIO0->FIOSET = LED;
			for(j=0;j<50000;j++);
			LED <<= 1;	
		}

		LED = 0x00000010;

		for(i=1;i<9;i++)  	//Off the LED's serially
		{
			LPC_GPIO0->FIOCLR = LED;
			for(j=0;j<50000;j++);
			LED <<= 1;	
		}

	}
 }
