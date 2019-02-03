	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=0
	MSR xPSR,R0
	
	LDR R1,=NUM1				
	LDR R2,=NUM2
	LDR R3,=RES	
	LDR R4,[R1]
	LDR R5,[R2]
	SUBS R6,R4,R5
	STR R6,[R3]
here B here
NUM1 DCD 0x4000300A
NUM2 DCD 0x20001007
	AREA mydata,DATA,READWRITE
RES DCD 0
	END
	