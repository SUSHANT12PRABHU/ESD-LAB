#include<LPC17xx.h>
#include<stdio.h>
#define	FIRST_SEG	0xF87FFFFF
 #define	SECOND_SEG	0xF8FFFFFF
 #define	THIRD_SEG	0xF97FFFFF
 #define	FOURTH_SEG	0xF9FFFFFF
 #define	DISABLE_ALL 0xFA7FFFFF
 void Display(void);
void delay(void);
void scan(void);
unsigned int dig1=0x00,dig2=0x00,dig3=0x00,dig4=0x00,count=0x00, up=0, dn=0, f=0;
 unsigned int twenty_count = 0x00,dig_count=0x00,temp1=0x00;
 unsigned char tmr0_flg = 0x00,one_sec_flg = 0x00;
 unsigned long int temp2 = 0x00000000,i=0;
 unsigned int temp3=0x00;
unsigned long int i,var1,row,flag,col,temp;
unsigned char SEVEN_CODE[4][4]={{0x3F,0x06,0x5B,0x4F},{0x66,0x6D,0x7D,0x07},{0x7F,0x6F, 0x77,0x7C},{0x39, 0x5E, 0x79, 0x71}};

int main(void){
SystemInit();
SystemCoreClockUpdate();
LPC_PINCON->PINSEL0 |= 0x0FFFFFFF;
LPC_PINCON->PINSEL1 |= 0xFFFFFFC0;
	
LPC_PINCON->PINSEL0 |= 0x00003FC0;
LPC_GPIO0->FIODIR |=0x007F8000;
LPC_GPIO0->FIODIR |=0x00003C00;
	
LPC_PINCON->PINSEL3 &= 0xFFC03FFF;
LPC_GPIO1->FIODIR |= 0x07800000;	

while(1){

for(row=0;row<4;row++){

			if(row==0){
			temp=0x00000400;
			}
			else if(row==1){
				
			temp=0x00000800;}
			else if(row ==2){
				
			temp=0x00001000;}
			else if(row ==3){
			temp=0x00002000;}
			LPC_GPIO2->FIOPIN=temp;
			flag=0;
			scan();
			if(flag==1){
				temp2=SEVEN_CODE[row][col];
			  LPC_GPIO0->FIOMASK=0xFFF87FFF;
				LPC_GPIO0->FIOPIN = FIRST_SEG ;
				temp2 = temp2<<4;
				LPC_GPIO0->FIOMASK=0xFFFFF00F;
				LPC_GPIO0->FIOPIN = temp2 ;
				for(i=0;i<1000;i++);
				LPC_GPIO0->FIOCLR = 0x00000FF0;
				break;
				}		
}
}
}
	void scan(void){
    unsigned long temp3;

		temp3= LPC_GPIO1->FIOPIN;
		temp3 &=0x07800000;

			if(temp3!=0x00000000){
			flag =1;
			if(temp3==0x00800000)
			col=0;

			else if(temp3==0x01000000)
			col=1;

			else if(temp3==0x02000000)
			col=2;

			else if(temp3==0x04000000)
			col=3;

			}
		}
		void delay(void)
{
	unsigned int i;
	for(i=0;i<100;i++);
	if(count==100)
		{
		one_sec_flg=0xFF;
		count=0x00;
		}
		else
			count+=1;
}
