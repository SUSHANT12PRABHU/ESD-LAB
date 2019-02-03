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
	MOV R2,#8
	MOV R4,#0
	
back LDRB R1,[R0],#1
	BL ASCII_HEX
	LSL R4,#4
	ORR R4,R1
	SUB R2,#1
	TEQ R2,#0
	BNE back
	LDR R0,=res
	STR R4,[R0]	
	  
halt
	B halt
;num DCB "1234ABCD" ;
num dcb 0x31,0x32,0x33,0x34,0x41,0x42,0x43,0x44

ASCII_HEX
	CMP R1,#0x41
	BLO down
	SUB R1,#0x07
down SUB R1,#0x30	
	BX LR
	
	AREA mydata,DATA,READWRITE
res DCD 0
	END