#include <stdio.h>
#include <LPC17xx.h>

#define FIRST_SEG 0xF87FFFFF
#define SECOND_SEG 0xF8FFFFFF
#define THIRD_SEG 0xF97FFFFF
#define FOURTH_SEG 0xF9FFFFFF
#define DISABLE_ALL 0xFA7FFFFF

unsigned long seg_list[4] = {FIRST_SEG, SECOND_SEG, THIRD_SEG, FOURTH_SEG};
unsigned char seg_disp[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned int val_arr[4] = {0}, twenty_count = 0x00;
unsigned char one_sec_flg = 0x00;

void delay();
void display();

int main(){
	int i, n, n1;
	SystemInit();
	SystemCoreClockUpdate();
	
	//For display
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	
	//FOr segment selection
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF;
	LPC_GPIO1->FIODIRH |= 0x0780;
	while(1){
		delay();
		if(one_sec_flg == 0xFF)
		{
			one_sec_flg = 0x00;
			i++;
			if(i==9999)	i = 0;
			n1 = i;
			for(n=0; n<4; n++){
				val_arr[n] = n1%10;
				n1 /= 10;
			}
		}
		display();
	}
	return 0;
}

void delay(void)
 {
	 unsigned int i;
	 for (i=0;i<1000;i++);
		if(twenty_count == 3000){     //multiplied by 500x2msec for 1 Sec 
			one_sec_flg = 0xFF;
			twenty_count = 0x00;			 
		}
		else twenty_count += 1;
 }
void display(){
	int n;
	long i;
	for(n=0; n<4; n++){
		LPC_GPIO1->FIOPIN = seg_list[n];
		LPC_GPIO0->FIOPIN = seg_disp[val_arr[n]]<<4;
		for(i=0; i<500; i++);
		LPC_GPIO0->FIOCLRL = 0x0FF0;
	}
} 