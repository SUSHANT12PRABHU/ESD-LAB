/***********************************************************************
 * DEVELOPED BY SUSHANT [GROUP 4] ©
 * DISTANCE IR SENSOR
 *----------------------------------------------------------------------
 * [CNAD CNA FOR LCD]
 * P1.4-P1.9 FOR LCD DISPLAY (CNA)
 * Connect a 10 pin FRC cable from CNA to CNAD FOR LCD
 * P0.23 AD0.0 TO IR SENSOR RIGHTMOST TOP PIN OF PIN CND
 ***********************************************************************/

#include<LPC17xx.h>
#define Ref_Vtg 3.300             //REFERENCE VOLTAGE 0.4V - 3V
#define Full_Scale 0xfff
/*
#define RS_CTRL 0x00100000       //P0.20
#define EN_CTRL 0x00200000			 //P0.21
#define DT_CTRL 0x000F0000			//P0.16-P0.19
*/

#define RS_CTRL 1<<8						//P1.8
#define EN_CTRL 1<<9						//P1.9
#define DT_CTRL 0xf<<4					//P1.4-P1.7

#define To_Cm_Slope 0.5								//CONVERSION FACTOR
#define To_Cm 30             		//CONVERSION FACTOR

void lcd_init(void);
void wr_cn(void);
void clrscr(void);
void delay(unsigned int);
void lcd_com(void);
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char *);
unsigned long int temp1=0, temp2=0;

int main(void){
	
	unsigned long adc_temp;
	unsigned int i;
	float in_vtg;
	unsigned char vtg[7],dval[7];
	//unsigned char Msg3[11] = {"ANALOG IP:"};
	unsigned char Msg3[10] = {"DISTANCE:"};
	unsigned char Msg4[12] = {"ADC OUTPUT:"};

	SystemInit();
	SystemCoreClockUpdate();

	LPC_SC->PCONP |= (1<<15);            							//PCONP 
	lcd_init();
	LPC_PINCON->PINSEL1 |= 1<<14;
	LPC_SC->PCONP |= (1<<12);    								       //PCONP
	SystemCoreClockUpdate();

	temp1 = 0x80;
	lcd_com();
	delay(800);
	lcd_puts(&Msg3[0]);

	temp1 = 0xc0;
	lcd_com();
	delay(800);
	lcd_puts(&Msg4[0]);
	
	while(1){

		LPC_ADC->ADCR = (1<<0)|(1<<21)|(1<<24); //START AD0.0 POWER ON
		
		while((adc_temp = LPC_ADC->ADGDR) == 0x80000000); //POLL DONE BIT
		adc_temp = LPC_ADC->ADGDR;
		adc_temp >>= 4;
		adc_temp &= 0x00000FFF;
		
		/*
		adc_temp = (LPC_ADC->ADGDR >> 4) & 0xfff;
		adc_temp1 = adc_temp*To_Cm_Slope + (1-To_Cm_Slope)*adc_temp;
		in_vtg = ((float)adc_temp1 * Ref_Vtg) / Full_Scale;
		distance = 27/in_vtg;
		sprintf(vtg, "%2.1f", distance);
		*/
		
		in_vtg = (((float)adc_temp * (float)Ref_Vtg)) / ((float)Full_Scale); //CHANGE VALUE DEPENDING ON REFERENCE
		in_vtg = ((float)To_Cm /(float)in_vtg);															//CONVERTING TO CM 
		
		sprintf(vtg,"%3.2fcm",in_vtg);
		sprintf(dval,"%x",adc_temp);
		
		for(i=0;i<2000;i++);
		
		temp1 = 0x89;
		lcd_com();
		delay(800);
		lcd_puts(&vtg[0]);
		
		temp1 = 0xcb;
		lcd_com();
		delay(800);
		lcd_puts(&dval[0]);
		
		for(i=0;i<200000;i++);
		
		for(i=0;i<7;i++)
			vtg[i]=dval[i]=0x00;
		adc_temp=0;
		in_vtg=0;
	}
}
void lcd_init(){

	LPC_PINCON->PINSEL0 |= 0xFFF000FF; //P1.8 - P1.19
	LPC_GPIO0->FIODIR |= DT_CTRL;
	LPC_GPIO0->FIODIR |= RS_CTRL;
	LPC_GPIO0->FIODIR |= EN_CTRL;
	clear_ports();
	delay(3200);
	
	temp2 = (0x30<<0);
	wr_cn();
	delay(30000);
	
	temp2 = (0x30<<0);
	wr_cn();
	delay(30000);
	
	temp2 = (0x30<<0);
	wr_cn();
	delay(30000);
	temp2 = (0x20<<0);
	wr_cn();
	delay(30000);
	
	temp1 = 0x28;
	lcd_com();
	delay(30000);
	
	temp1 = 0x0c;
	lcd_com();
	delay(30000);
	
	temp1 = 0x06;
	lcd_com();
	delay(30000);
	
	temp1 = 0x01;
	lcd_com();
	delay(30000);
	
	temp1 = 0x80;
	lcd_com();
	delay(30000);
	return;
}

void lcd_com(void){

	temp2 = temp1 & 0xf0;
	temp2 = temp2 << 0;
	wr_cn();
	temp2 = temp1 & 0x0f;
	temp2 = temp1 << 4;
	wr_cn();
	delay(1000);
	return;
}

void wr_cn(){

	clear_ports();
	LPC_GPIO0->FIOPIN = temp2;
	LPC_GPIO0->FIOCLR = RS_CTRL;
	LPC_GPIO0->FIOSET = EN_CTRL;
	delay(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	return;
}

void lcd_data(void){
	
	temp2 = temp1 & 0xf0;
	temp2 = temp2 << 0;
	wr_dn();
	temp2 = temp1 & 0x0f;
	temp2 = temp1 << 4;
	wr_dn();
	delay(1000);
	return;
}

void wr_dn(){

	clear_ports();
	LPC_GPIO0->FIOPIN = temp2;
	LPC_GPIO0->FIOSET = RS_CTRL;
	LPC_GPIO0->FIOSET = EN_CTRL;
	delay(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	return;
}

void delay(unsigned int r1){
	unsigned int r;
	for(r=0;r<r1;r++);
	return;
}

void clrscr(void){

	temp1 = 0x01;
	lcd_com();
	delay(10000);
	return;
}

void clear_ports(){

	LPC_GPIO0->FIOCLR = DT_CTRL;
	LPC_GPIO0->FIOCLR = RS_CTRL;
	LPC_GPIO0->FIOCLR = EN_CTRL;
	return;
}

void lcd_puts(unsigned char *buf1){

	unsigned int i=0;
	while(buf1[i]!='\0'){
		temp1 = buf1[i];
		lcd_data();
		i++;
		if(i==16){
			temp1 = 0xc0;
			lcd_com();
		}
	}
	return;
}

/***********************************************************************
 * DEVELOPED BY SUSHANT [GROUP 4]
 * DISTANCE IR SENSOR
 * CREATED ON 31/03/18 ©
 ***********************************************************************/
