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
	LDR R1,=num2
	LDR R3,[R0]
	LDR R4,[R1]
	LDR R2,=gcd
up
 	CMP R3,R4 
	BEQ exit
	
	SUBHI R3,R4
	SUBLO R4,R3
	B up
	
exit STR R3,[R2]
	
halt
	B halt
	AREA mydata,DATA,READWRITE
gcd DCD 0
num1 DCD 0
num2 DCD 0
	END