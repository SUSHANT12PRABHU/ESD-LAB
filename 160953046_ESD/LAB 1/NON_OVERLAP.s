	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=arr					;=arr
	LDR R1,=arr+len*4			;=arr+(len)*4
	MOV R5,#10
up	LDR R2,[R0],#4	
	STR R2,[R1],#4
	SUB R5,#1
	TEQ R5,#0
	BNE up
here B here
	AREA mydata,DATA,READWRITE
arr DCD 0 
len equ 10
	END
	