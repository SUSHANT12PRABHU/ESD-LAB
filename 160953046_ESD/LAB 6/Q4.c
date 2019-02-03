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
	LPC_PINCON->PINSEL4 = 0;
	LPC_GPIO2->FIODIR = 0; 
	LED = 1<<3;
	while(1)
	{
		LPC_GPIO0->FIOPIN = LED;
		if(!(LPC_GPIO2->FIOPIN & (1<<12)))
		{	LED <<= 1;
		}
		for(j=0;j<35000;j++);
		if(LED == 0x00010000 ){
		LED = 0x00000010;
		}
	}
 }
