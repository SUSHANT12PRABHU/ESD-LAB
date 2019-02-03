#include <LPC17xx.h>
#include<stdio.h>

#define FIRST_SEG 0XF87FFFFF;
#define SECOND_SEG 0xF8FFFFFF;
#define THIRD_SEG 0xF97FFFFF;
#define FOURTH_SEG 0XF9FFFFFF;
#define DISABLE_ALL 0xFA7FFFFF;

unsigned int dig1=0x00, dig2=0x00, dig3=0x00, dig4=0x00;
unsigned int count = 0x00, dig_count=0x00, temp1=0x00;
unsigned char array_dec[10] = {0x6F,0x7F,0x07,0x7D,0x6D,0x66,0x4F,0x5B,0x06,0x3F};
unsigned char tmr0_flg = 0x00, one_sec_flg = 0x00;
unsigned long int temp2 = 0x00000000, i=0;
unsigned int temp3=0x00;
void Delay(void);
void Display(void);

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0XFF0000FF;
	LPC_PINCON->PINSEL3 &= 0XFFC03FFF;
	
	LPC_GPIO0->FIODIR |= 0X00000FF0;
	LPC_GPIO1->FIODIR |= 0X07800000;
	
	while(1)
	{
			Delay();
			dig_count +=1;
			if(dig_count == 0x05)
			{
				dig_count = 0x00;
				//one_sec_flg = 0xFF;
			}
			if(one_sec_flg == 0xFF)
			{
				one_sec_flg = 0x00;
				dig1 +=1;
					if(dig1 == 0x0A)
					{
						dig1 = 0;
						dig2 += 1;
							if(dig2 == 0X0A)
							{
								dig2=0;
								 dig3+=1;
									if(dig3 == 0x0A)
									{
										dig3=0;
										dig4+=1;
										if(dig4 == 0x0A)
										{
											dig4=0;
										}
									}
							}
					}
			}
			Display();
	}
}
void Display(void)
{
	if(dig_count == 0x01)
	{
		temp1=dig1;
		LPC_GPIO1->FIOPIN = FIRST_SEG;
	}
	else	if(dig_count == 0x02)
	{
		temp1=dig2;
		LPC_GPIO1->FIOPIN = SECOND_SEG;
	}
	else	if(dig_count == 0x03)
	{
		temp1=dig3;
		LPC_GPIO1->FIOPIN = THIRD_SEG;
	}
	else	if(dig_count == 0x04)
	{
		temp1=dig4;
		LPC_GPIO1->FIOPIN = FOURTH_SEG;
	}
	temp1 &= 0x0F;
	temp2 = array_dec[temp1];
	temp2 = temp2<<4;
	LPC_GPIO0->FIOPIN = temp2;
	for(i=0;i<500;i++);
	LPC_GPIO0->FIOCLR = 0X00000FF0;
	LPC_GPIO1->FIOPIN = DISABLE_ALL;
}
void Delay(void)
{
	unsigned int i;
	for(i=0;i<500;i++);
	if(count==100)
	{
		one_sec_flg = 0XFF;
		count = 0x00;
	}
	else count += 1;
}
