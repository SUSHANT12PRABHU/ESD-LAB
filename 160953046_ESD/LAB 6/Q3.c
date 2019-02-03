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
 
 unsigned int val=0,j,i=1;
 unsigned long LED = 0x00000010;

 int main(void)
 {
	SystemInit();
	SystemCoreClockUpdate();

	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	LPC_PINCON->PINSEL4 = 0x00000000;
	LPC_GPIO2->FIODIR = 0x00000000;
	while(1)
	{
		if(!(LPC_GPIO2->FIOPIN & (1<<12))){
			for(j=0;j<7000;j++);
			LPC_GPIO0->FIOPIN = val++;
		}
		else{
			for(j=0;j<7000;j++);
			LPC_GPIO0->FIOPIN = val--;
		}
	}
 }
