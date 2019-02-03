	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R13,=0x10001000
	LDR R0,=num
	LDR R1,[R0]
	MOV R2,#0
	BL facto
	LDR R0,=res
	STR R2,[R0]
halt
	B halt
num DCD 0x06
facto
	CMP R1,#1
	BEQ exit
	PUSH {R1}
	PUSH {LR}
	SUB R1,#1
	BL facto
	POP{LR}
	POP{R1}
	MUL R2,R1,R2
	B down
exit MOV R2,#1
down BX LR
	
	AREA mydata,DATA,READWRITE
res DCD 0
	END
	
	