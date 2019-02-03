#include<LPC17xx.h>
#include<stdlib.h>

#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000

void lcd_init();
void wr_cn();
void clr_disp();
void delay_lcd(unsigned int);
void lcd_com();
void wr_dn();
void lcd_data();
void clear_ports();
void lcd_puts(unsigned char *);

extern unsigned long temp1, temp2;
unsigned long temp1 = 0, temp2 = 0;
char digits[7] = {'0', '0', '0', '0','0','0','\0'};
unsigned int dig_count=0,choice=0;

int change_mins()
{
	digits[5]+=1;
	if (digits[5]==(10+'0'))
	{
		digits[5]=0+'0';
		digits[4]=digits[4]+1;
	}
	if (digits[4]==(6+'0'))
		{digits[4]=0+'0';
			return 1;
		}
	return 0;
}
void change()
{
	digits[1]+=1;
	if (digits[1]==(10+'0'))
	{
		digits[1]=0+'0';
		digits[0]=digits[0]+1;
	}
	if (digits[0]==(6+'0'))
		{digits[0]=0+'0';
			//return 1;
		}
	//return 0;
}
int change_hours()
{
	digits[3]+=1;
	if (digits[3]==(10+'0'))
		{digits[3]=0+'0';
			digits[2]+=1;
		}
	if (digits[2]==(6+'0'))
	{
		digits[2]=0+'0';
		digits[3]=0+'0';
		return 1;
	}
	return 0;
}

int main(void) {
	SystemInit();
	SystemCoreClockUpdate();
    
    lcd_init();
    
    temp1 = 0x80;
    lcd_com();
    delay_lcd(800);
	
		 LPC_TIM0->TCR=0X02;
	LPC_TIM0->CTCR=0X00;
	LPC_TIM0->MR0=999;
	LPC_TIM0->MCR=0X02;
	LPC_TIM0->EMR=0X20;
	LPC_TIM0->PR=2999;
	LPC_TIM0->TCR=0X01;
	while(1)
	{
		dig_count+=1;
		if (dig_count==5)
		{
			dig_count=0;
		}
		if(LPC_TIM0->EMR&0x01){
			
				 LPC_TIM0->TCR=0X02;
	LPC_TIM0->CTCR=0X00;
	LPC_TIM0->MR0=999;
	LPC_TIM0->MCR=0X02;
	LPC_TIM0->EMR=0X20;
	LPC_TIM0->PR=2999;
	LPC_TIM0->TCR=0X01;
			choice=change_mins();
		
		if (choice==1)
		{
			choice=change_hours();
			if(choice==1)
				change();
		}
		clr_disp();
	lcd_puts(&digits[0]);
}
		

	}
}

void lcd_init() {
    LPC_PINCON->PINSEL3 &= 0xfc003fff;
    LPC_GPIO0->FIODIR |= DT_CTRL;
    LPC_GPIO0->FIODIR |= RS_CTRL;
    LPC_GPIO0->FIODIR |= EN_CTRL;
    
    clear_ports();
    delay_lcd(3200);
    
    temp2 = (0x30<<19);
    wr_cn();
    delay_lcd(30000);
    
    temp2 = (0x30<<19);
    wr_cn();
    delay_lcd(30000);    
    
    temp2 = (0x30<<19);
    wr_cn();
    delay_lcd(30000);

    temp2 = (0x20<<19);
    wr_cn();
    delay_lcd(30000);    
    
    temp1 = 0x28;
    lcd_com();
    delay_lcd(30000);
    
    temp1 = 0x0c;
    lcd_com();
    delay_lcd(800);
    
    temp1 = 0x06;
    lcd_com();
    delay_lcd(800);

    temp1 = 0x01;
    lcd_com();
    delay_lcd(10000);

    temp1 = 0x80;
    lcd_com();
    delay_lcd(800);
    
    return;
}

void lcd_com() {
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_cn();
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 23;
    wr_cn();
    delay_lcd(1000);
    
    return;
}

void wr_cn() {
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;
    LPC_GPIO0->FIOCLR = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    
    return;
}

void lcd_data() {
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_dn();
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 23;
    wr_dn();
    delay_lcd(1000);
    
    return;
}

void wr_dn() {
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;
    LPC_GPIO0->FIOSET = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    
    return;
}

void delay_lcd(unsigned int r1) {
    unsigned int r;
    for(r=0; r<r1; r++);
}

void clr_disp() {
    temp1 = 0x01;
    lcd_com();
    delay_lcd(10000);
    
    return;
}

void clear_ports() {
    LPC_GPIO0->FIOCLR = DT_CTRL;
    LPC_GPIO0->FIOCLR = RS_CTRL;
    LPC_GPIO0->FIOCLR = EN_CTRL;
    
    return;
}

void lcd_puts(unsigned char *buf1) {
    unsigned int i = 0;
	while(buf1[i]!='\0')
	{
        temp1 = buf1[i];
        lcd_data();
		i++;
		if(i==2 || i==4)
		{
			temp1=':';
			lcd_data();
		}
    }
}
    
