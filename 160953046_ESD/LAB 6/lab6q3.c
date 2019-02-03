#include<LPC17xx.h>

unsigned long LED=0x00000010;
unsigned int i,j;
unsigned int x;
int main(void){
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_PINCON->PINSEL4 &=0xFCFFFFFF;
	LPC_GPIO0->FIODIR |=0x00000FF0;
	LPC_GPIO2->FIODIR |=0x00000000;
	
	while(1){
	
		x=LPC_GPIO2->FIOPIN &0x00001000;
	
		if(x==0x00001000){
			LPC_GPIO2->FIOPIN=LED;
			for(j=0;j<1000;j++);
			LED=LED<<1;
		}
		
		if(LED==0x00001000){
				LED=0x00000010;
		}
}				
				
}
	