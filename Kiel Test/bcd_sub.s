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
	LDR R0,=bcd2
	LDR R2,[R0]
	LDR R0,=res
	SUB R1,R2
	STR R1,[R0],#4
	MOV R11,0x0F
	MOV R9,#8
	
up1	MOV R3,R1
	AND R3,R11
	CMP R3,0x0A
	BHS goto
	SUB R9,#1
	TEQ R9,#0
	BNE up1
	B exit1
goto SUB R1,#0x06
exit1 STR R1,[R0]
halt
	B halt
bcd DCD 0x105
bcd2 DCD 0x77
	AREA mydata,DATA,READWRITE
res DCD 0
	END