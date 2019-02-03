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
	MOV R4,#0
	MOV R9,#2
up	
	MOV R2,#8
back LDRB R1,[R0],#1
	LSL R4,#8
	ORR R4,R1
	SUB R2,#2
	TEQ R2,#0
	BNE back
	CMP R9,#1
	BEQ let
	LDR R5,=res+4
	STR R4,[R5]
let	SUB R9,#1
	TEQ R9,#0
	BNE up
	LDR R5,=res
	STR R4,[R5]	
halt
	B halt
num dcb 0x31,0x32,0x33,0x34,0x41,0x42,0x44,0x45
	AREA mydata,DATA,READWRITE
res DCD 0
	END