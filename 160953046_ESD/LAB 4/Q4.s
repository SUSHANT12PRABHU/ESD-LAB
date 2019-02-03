	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=bcd
	LDR R1,[R0]
	MOV R7,#32
	MOV R8,0xF0000000
	
	MOV R10,#0x0A
up	MOV R3,R1
	AND R3,R8
	MOV R10,R7
	SUB R10,#1
	LSR R3,R10
	LSR R8,#4
	MLA R5,R5,R10,R3
	SUB R7,#4
	TEQ R7,#0
	BNE up
	
	LDR R0,=hex
	STR R5,[R0]
	
halt
	b halt
	
bcd DCD 0x19
	AREA mydata,DATA,READWRITE
hex DCD 0
	END
	
	