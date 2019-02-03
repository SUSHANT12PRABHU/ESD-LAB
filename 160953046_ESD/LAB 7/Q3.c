#include <LPC17xx.h>
#include <stdio.h>
 #define	FIRST_SEG	0xF87FFFFF
 #define	SECOND_SEG	0xF8FFFFFF
 #define	THIRD_SEG	0xF97FFFFF
 #define	FOURTH_SEG	0xF9FFFFFF
 #define	DISABLE_ALL 0xFA7FFFFF

 unsigned int dig1=0x00,dig2=0x00,dig3=0x00,dig4=0x00,count=0x00, up=0, dn=0, f=0;
 unsigned int twenty_count = 0x00,dig_count=0x00,temp1=0x00;
 unsigned char array_dec[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F, 0x77,0x7C, 0x39, 0x5E, 0x79, 0x71};
 unsigned char tmr0_flg = 0x00,one_sec_flg = 0x00;
 unsigned long int temp2 = 0x00000000,i=0;
 unsigned int temp3=0x00;

void Display(void);
void delay(void);
	 
int main(void)
{    
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;	 //P0.4 to P0.11 GPIO data lines
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF;	 //P1.23 to P1.26 GPIO enable lines

	LPC_GPIO0->FIODIR |= 0x00000FF0;	//P0.4 to P0.11 output
	LPC_GPIO1->FIODIR |= 0x07800000;	//P1.23 to P1.26 output
	 
	while(1)
	{
		delay();
	    if((LPC_GPIO2->FIOPIN &(1<<0)))
		{
			f=1;
			up=0x10;
			dn=0;
		}	
		else 
		{
			up = 0xffffffff;
			f=-1;
			dn=0x0F;
		}
			dig_count +=1;  
			if(dig_count == 0x05)
			
				dig_count = 0x00;
				
			

			if(one_sec_flg == 0xFF)
			{
	 			one_sec_flg = 0x00;
				dig1 +=f;//units place counter
	              
				if(dig1 == up)
				{ 
					dig1 = dn;
					dig2 +=f;

					if(dig2 == up)
					{
						dig2 = dn;
						dig3+=f;

						if(dig3 == up)
						{
							dig3 = dn;
							dig4 += f;
	                             
							if(dig4 == up)
							{
								dig4 = dn;
							} //end of dig4
						
						} //end of dig3
					
					} //end of dig2

				}  //end of dig1

			}   //end of one_sec if

 		Display();	
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
void Display(void)      //To Display on 7-segments
 {

        
	if(dig_count == 0x01)		// For Segment U8
	{
		temp1 = dig1; 
		LPC_GPIO1->FIOPIN = FIRST_SEG;    

	}

	else if(dig_count == 0x02)	// For Segment U9
	{
		temp1 = dig2;             
		LPC_GPIO1->FIOPIN = SECOND_SEG;    
   
	}

	else if(dig_count == 0x03)	// For Segment U10
	{
		temp1 = dig3;           
		LPC_GPIO1->FIOPIN = THIRD_SEG;    
	}
	else if(dig_count == 0x04)	// For Segment U11
	{ 
		temp1 = dig4;   
		LPC_GPIO1->FIOPIN = FOURTH_SEG;    

	}
	temp1 &= 0x0F;
	temp2 = array_dec[temp1];	// Decoding to 7-segment
	temp2<<=4;
	LPC_GPIO0->FIOPIN = temp2;		// Taking Data Lines for 7-Seg
	for(i=0;i<500;i++);
	LPC_GPIO0->FIOCLR = 0x00000FF0;
}
	
