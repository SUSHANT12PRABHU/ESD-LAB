	AREA RESET,DATA,READONLY
	EXPORT __Vectors
		
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=num
	LDR R1,[R0]
	MOV R2,#8
	LDR R0,=res+7
back AND R3,R1,#0x0F
	BL HEX_ASCII
	STRB R3,[R0],#-1
	LSR R1,#4
	SUB R2,#1
	TEQ R2,#0
	BNE back
	  
halt
	B halt
num DCD 0x1234ABCD

HEX_ASCII
	CMP R3,#0x0A
	BLO down
	ADD R3,#0x07
down ADD R3,#0x30	
	BX LR
	
	AREA mydata,DATA,READWRITE
res DCD 0
	END