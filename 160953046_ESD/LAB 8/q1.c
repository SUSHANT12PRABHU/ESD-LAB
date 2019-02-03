//CNB TO SWITCH S2
//CNAD TO CND
//P0.23-PO.28 for LCD
#include<LPC17xx.h>
#include<stdlib.h>
#include<stdio.h>

#define rs_ctrl  0x08000000  //P0.27
#define en_ctrl  0x10000000  //P0.28
#define dt_ctrl  0x07800000  //P0.23 to P0.26 data lines
void lcd_init(void);
void display(void);
void wr_cn(void);
void wr_dn(void);
void clear_ports(void);
void delay(unsigned int);


void lcd_com(void);
void lcd_data(void);
void char_puts(char ch);//not used
void lcd_puts(unsigned char *);


void clr_disp(void);
int col, row;
unsigned long int temp1=0,temp2=0,wait,o=0;

void scan(void);

int main()
{
	unsigned char Msg3[]= {"RANDOM NUMBER:"};
  unsigned char Msg4;
	SystemInit();
	SystemCoreClockUpdate();
	lcd_init();
	
	temp1=(0x80);
  lcd_com();
  delay(800);
	lcd_puts(&Msg3[0]);
	
  while(1){
	if(!(LPC_GPIO2->FIOPIN & 1<<12)){
		o=rand();
	  o=o%7;
	if(o==0)
	 	o=1;
	Msg4=o+0X30;
	
	temp1=(0xC0);
  lcd_com();
  delay(800);
	lcd_puts(&Msg4);
	}
}
}



void lcd_puts(unsigned char *buf1)
{
		unsigned int i=0;
		LPC_GPIO0->FIOMASK = 0xE07FFFFF;		
		while(buf1[i]!='\0')
    {
        temp1 = buf1[i];
     	lcd_data();
		i++;
        if(i==16)
		{
           	temp1 = 0xc0;
			lcd_com();
		}
	 for(wait=0;wait<100000;wait++);
}
}
void lcd_init()
{
	LPC_PINCON->PINSEL1 &=0xFC003FFF;        //P0.23 - P0.28 io lines
 	LPC_GPIO0->FIOMASK = 0xE07FFFFF;         //mask all except P0.23 - P0.28 
	
	
	
	LPC_PINCON->PINSEL4 &=0x0; //P2.12
	LPC_GPIO0->FIODIR |= dt_ctrl;
	LPC_GPIO0->FIODIR |= rs_ctrl;
	LPC_GPIO0->FIODIR |= en_ctrl;
	clear_ports();
delay(3200);

temp2=(0x30<<19);
wr_cn();
delay(3000);

temp2=(0x30<<19);
wr_cn();
delay(3000);

temp2=(0x30<<19);
wr_cn();
delay(3000);

temp2=(0x20<<19);
wr_cn();
delay(1000);

temp1=(0x28);
lcd_com();
delay(3000);

temp1=(0x0c);
lcd_com();
delay(800);

temp1=(0x06);
lcd_com();
delay(800);

temp1=(0x01);
lcd_com();
delay(1000);

temp1=(0x80);
lcd_com();
delay(800);
return;
}
 
void lcd_com()
{
	LPC_GPIO0->FIOMASK = 0xE07FFFFF;
	temp2=temp1&0Xf0;
	temp2=temp2<<19;
	wr_cn();
   	temp2=temp1&0x0f;
	temp2=temp2<<23;
	wr_cn();
	delay(1000);
	return;
}
void lcd_data()
{
	LPC_GPIO0->FIOMASK = 0xE07FFFFF;
	temp2=temp1&0Xf0;
	temp2=temp2<<19;
	wr_dn();
	temp2=temp1&0x0f;
	temp2=temp2<<23;
	wr_dn();
	delay(1000);
	return;
}

void wr_cn()
{
	LPC_GPIO0->FIOMASK = 0xE07FFFFF;
	clear_ports();
	LPC_GPIO0->FIOPIN=temp2;
	LPC_GPIO0->FIOCLR=rs_ctrl;
	LPC_GPIO0->FIOSET=en_ctrl;
	delay(25);
	LPC_GPIO0->FIOCLR=en_ctrl;
	return;
}


void wr_dn()
{
	LPC_GPIO0->FIOMASK = 0xE07FFFFF;
	clear_ports();
	LPC_GPIO0->FIOPIN=temp2;
	LPC_GPIO0->FIOSET=rs_ctrl;
	LPC_GPIO0->FIOSET=en_ctrl;
	delay(25);
	LPC_GPIO0->FIOCLR=en_ctrl;
	return;
}

void clear_ports(void)

{
		 LPC_GPIO0->FIOMASK = 0xE07FFFFF;	
     LPC_GPIO0->FIOCLR = dt_ctrl;
     LPC_GPIO0->FIOCLR = rs_ctrl;
     LPC_GPIO0->FIOCLR = en_ctrl; 
		 return;
}

void clr_disp(void)

{
		 LPC_GPIO0->FIOMASK = 0xE07FFFFF;	
     temp1 = 0x01;
     lcd_com();
     delay(300);
     return;

}

void delay(unsigned int f)

{
		
   unsigned int r;

   for(r=0;r<f;r++);

   return;

}


