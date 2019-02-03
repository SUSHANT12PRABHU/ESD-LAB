#include <LPC17xx.h>
#include <stdio.h>
unsigned long int i=0,j,flag=0;
unsigned char array[8]= {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 |= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	LPC_PINCON->PINSEL2 |= 0xFFFF3FFF;
	LPC_GPIO1->FIODIR |= 1<<23;
	LPC_PINCON->PINSEL2 |= 0;
	LPC_GPIO2->FIODIR |= 0<<10;
	
	LPC_GPIO1->FIOPIN |= 0<<23;
	while(1){
	/*if(!(LPC_GPIO2->FIOPIN & (1<<10))){
	 i--;
	}
	else{
	i++;
	}*/
	//LPC_GPIO0->FIOPIN=array[i%8]<<4;
	if(flag==0){
		LPC_GPIO0->FIOPIN=array[i]<<4;
		i++;
		if(i==8){
		flag=1;
		}
	}
	else{
		i--;
		if(i==-1){
		flag=0;
		}
		LPC_GPIO0->FIOPIN=array[i]<<4;
	}
	for(j=0;j<30000;j++);
	}

}