 	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC1
	LDR R1, =SRC2
	LDR R2, =DST1
	LDR R3, =DST2
	LDR R4, [R0]
	LDR R5, [R1]
	STR R4, [R2]
	STR R5, [R3]
here
	B here
SRC1 DCD 0x675321
SRC2 DCD 0x123456
	AREA mydata, DATA, READWRITE
DST1 DCD 0
DST2 DCD 5
	END