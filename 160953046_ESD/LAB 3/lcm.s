	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=num1
	LDR R1,[R0]
	LDR R0,=num2
	LDR R2,[R0]
	MUL R3,R1,R2
up
 	CMP R1,R2 
	BEQ exit
	
	SUBHI R1,R2
	SUBLO R2,R1
	B up
	
exit
	LDR R0,=res
	STR R1,[R0]
upm
	CMP R3,R2
	BLO down
	SUB R3,R2
	ADD R8,#1
	B upm
down 
	LDR R0,=res
	STR R8,[R0]
halt
	B halt
num1 DCD 0x00000006
num2 DCD 0x00000003
	AREA mydata,DATA,READWRITE
lcm DCD 0
res DCD 0
	END