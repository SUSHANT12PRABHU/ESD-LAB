	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=NUM1				
	LDR R1,=RES	
	LDR R10,=len

loop
	LDR R2,[R0],#4
	ADDS R3,R2
	ADC R4,#0
	SUB R10,#1
	TEQ R10,#0
	BNE loop
	
	STR R3,[R1],#4
	STR R4,[R1]
here B here
len equ 10
NUM1 DCD 0x11,0x22,0x33,0x44,0x55,0x1,0x2,0x3,0x4,0x5
	AREA mydata,DATA,READWRITE
RES DCD 0
	END
	