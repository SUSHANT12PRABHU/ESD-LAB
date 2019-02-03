	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=SRC					
	LDR R1,=SRC+(len-1)*4			 
	
up	LDR R2,[R0]
	LDR R3,[R1]
	STR R2,[R1],#-4
	STR R3,[R0],#4
	CMP R0,R1
	BLT up
	
here B here

len equ 10
	AREA mydata,DATA,READWRITE
SRC DCD 0  
	END
	