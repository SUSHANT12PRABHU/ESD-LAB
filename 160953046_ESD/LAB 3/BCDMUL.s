	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=bcd1
	LDR R1,=bcd2
	LDR R2,[R0]
	LDR R3,[R1]
	
	MOV R10,#0x0A
	MOV R4,R2
	AND R2,#0x0F
	LSR R4,#4
	MLA R5,R4,R10,R2
	
	MOV R4,R3
	AND R3,#0x0F
	LSR R4,#4
	MLA R6,R4,R10,R3
loop
	ADDS R8,R5
	ADC R7,#0
	SUB R6,#1
	TEQ R6,#0
	BNE loop
	LDR R11,=DES
	STR R8, [R11], #4
	STR R7, [R11],#4
	

	MOV R1,R8
	MOV R5,#0
	MOV R7,#32
back BL div
	CMP R1,#0
	BNE back
	LSR R5,R7
	STR R5,[R11]
	
halt
	b halt
	
div MOV R3,#0
up	CMP R1,#10
	BLO exit
	SUB R1,#0x0A
	ADD R3,#1
	B up
exit 
	ORR R5,R1
	MOV R1,R3
	ROR R5,#4
	SUB R7,#4
	BX LR 

bcd1 DCD 0x10
bcd2 DCD 0x10
	AREA mydata,DATA,READWRITE
DES DCD 0
	END