	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=hex
	LDR R1,[R0]
	MOV R5,#0
	MOV R7,#32
back BL div
	CMP R1,#0
	BNE back
	LSR R5,R7
	LDR R1,=bcd
	STR R5,[R1]
	
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
	
	AREA mydata,DATA,READWRITE
hex DCD 0
bcd DCD 0
	END