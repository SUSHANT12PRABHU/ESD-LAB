#include <LPC17xx.h>
#define	FIRST_SEG	0xF87FFFFF
void scan(void);
 
unsigned char col,row,flag;
unsigned long int i,var1,temp,temp3,temp2;
unsigned char SEVEN_CODE[4][4] = {{0x3F,0x06,0x5B,0x4F},{0x66,0x6D,0x7D,0x07},{0x7F,0x6F,0x77,0x7c},{0x58,0x5e,0x79,0x71}};

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	 
	LPC_PINCON->PINSEL0 &= 0x7F0000FF;	 //P0.4 to P0.11 GPIO data lines
	LPC_PINCON->PINSEL1 &= 0xFFFFFFF8;
	LPC_GPIO0->FIODIR |= 0x00078FF0;		//P0.4 to P0.11 output
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF; 	//P1.23 to P1.26 MADE GPIO
	LPC_PINCON->PINSEL4 &= 0xF00FFFFF; 	//P2.10 t P2.13 made GPIO
	LPC_GPIO2->FIODIRL |= 0x3C00; 		//made output P2.10 to P2.13 (rows)
	LPC_GPIO1->FIODIRH &= 0xF87F; 		//made input P1.23 to P1.26 (cols)

	while(1)
		for(row=0;row<4;row++){
			if(row == 0)
			temp = 0x00000400;
			else if(row == 1)
			temp = 0x00000800;
			else if(row == 2)
			temp = 0x00001000;
			else if(row == 3)
			temp = 0x00002000;
		
			LPC_GPIO2->FIOPIN = temp;
			flag = 0;
			scan();
			if(flag == 1)
			{
				temp2 = SEVEN_CODE[row][col]; 
				LPC_GPIO0->FIOMASK=FIRST_SEG>>4;
				LPC_GPIO0->FIOPIN = FIRST_SEG>>4;  
				temp2 = temp2 << 4;
				LPC_GPIO0->FIOMASK=0xFFFFF00F;
				LPC_GPIO0->FIOPIN = temp2;		// Taking Data Lines for 7-Seg
				break;
			}
		}		
}

void scan(void)
{
 	unsigned long temp3;
	temp3 = LPC_GPIO1->FIOPIN;	
	temp3 &= 0x07800000;
	if(temp3 != 0x00000000)
	{
		flag = 1;
		if (temp3 ==0x00800000)
			col=0;
		else if (temp3==0x01000000)
			col=1;
		else if (temp3==0x02000000)
			col=2;
		else if (temp3==0x04000000)
			col=3;
	}
}