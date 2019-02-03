#include<stdio.h>
#include<LPC17xx.h>

void EINT3_IRQHandler(void);
void keyscan(void);
unsigned int i,j,k,temp,row,col,flag,temp3;
void sevenseg(int, int);

int main(void)
{   
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL1=0;
	LPC_PINCON->PINSEL2=0;
	LPC_GPIO2->FIODIR=0;//set p2.0-p2.2 to input COLS
	LPC_GPIO1->FIODIR=0x07;// set p1.0-p1.2 to output ROWS
	LPC_GPIO0->FIODIR=0x00000800; //P0.11 output
	LPC_GPIOINT->IO2IntEnR=0X07;// generate interrupt on rising edge
	NVIC_EnableIRQ(EINT3_IRQn);// enable interrupt gloabally
  while(1)
	{
		
	for(row=0;row<3;row++)
	{
		if(row==0)
			 temp=1<<0;//set row 0 value to 1
		else if(row==1)
			temp=1<<1;//set row 1 value to 1
		else if (row==2)
			temp=1<<2;//set row 2 value to 1
		
	  LPC_GPIO1->FIOPIN=temp;
		//for(k=0;k<2000;k++);
		//LPC_GPIO2->FIOPIN=1;

	}
}
}

void EINT3_IRQHandler(void)
{
	keyscan();
	sevenseg(row,col);
  for(i=0;i<500;i++);
  LPC_GPIOINT->IO2IntClr=0x07;	
	
}

void keyscan(void)
{
	temp3=LPC_GPIO2->FIOPIN;
	temp3&=0x07;
	if(temp3!=0)
	{
		if(temp3==1<<0)
			col=0;
		else if (temp3==1<<1)
			col=1;
		else if (temp3==1<<2)
			col=2;
	}
}
void sevenseg(int row,int col)
{
	unsigned int arr[3][3]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f};
  unsigned int temp4=arr[row][col];
  /*LPC_GPIO1->FIOPIN|=(1<<23);
  LPC_GPIO0->FIOPIN=(temp4<<4);
	*/
	LPC_GPIO0->FIOSET = 1<<11;
	for(k=0;k<1000;k++);
	LPC_GPIO0->FIOCLR = 1<<11;
	//LPC_GPIO0->FIOPIN |= (temp4<<11);
}