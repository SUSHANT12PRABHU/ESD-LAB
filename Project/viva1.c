#include<LPC17xx.h>
#include<stdio.h>
unsigned long temp1, temp2;
 unsigned char col,row,flag,n_flag=0;
 unsigned long int i=0,j,var1,temp,temp3,k=0;
	
	int op1, expr, op2, tens,unit, temp4; 
 
 void scan(void)
 {
 	unsigned long temp3;

	temp3 = LPC_GPIO1->FIOPIN;	
	temp3 &= 0x07800000;
	if(temp3 != 0x00000000)
	{
		LPC_GPIO0->FIOSET=0x01;
				flag = 1;
			if (temp3 ==0x00800000)
				col=0;
			else if (temp3==0x01000000)
				col=1;
			else if (temp3==0x02000000)
				col=2;
			else if (temp3==0x04000000)
				col=3;
   
	}//1st if(temp3 != 0x00000000)
 }//end scan
int main(void)
 {
 	SystemInit();
	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR |= 0x000000F0;//LED P0.4 TO P0.7
	LPC_GPIO2->FIODIR |= 0x00003C00; //made output P2.10 to P2.13 (rows)
	LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26 (cols)
	 LPC_GPIO1->FIOCLR=0xF87FFFFF;
	 
	 while(1)
	{
		for(row=0;row<4;row++)
			{
				if(row == 0)
				temp = 0x00000400;
				else if(row == 1)
				continue;
				else if(row == 2)
				temp = 0x00001000;
				else if(row == 3)
				continue;
			
				LPC_GPIO2->FIOPIN = temp;
				flag = 0;
				while(flag==0){
				scan();
				}
				if(flag == 1)
				{	
					flag=0;
					LPC_GPIO1->FIOCLR=0xF87FFFFF;
					while(flag==0){
					scan();
					}
					if(col==0)
						LPC_GPIO0->FIOSET=0x01<<4;
					else if(col==1)
						LPC_GPIO0->FIOSET=0x02<<4;
					else if(col==2)
						LPC_GPIO0->FIOSET=0x04<<4;
					else
						LPC_GPIO0->FIOSET=0x08<<4;
					
				}
			}
		}
 }
 
 