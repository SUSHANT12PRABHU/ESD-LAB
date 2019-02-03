	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=arr
	LDR R1,=num
	LDR R1,[R1]
	MOV R2,#10
	MOV R4,#1
	
up	LDR R10,[R0],#4
	CMP R1,R10
	BEQ exit
	ADD R4,#1
	SUB R2,#1
	TEQ R2,#0
	BNE up
	
	LDR R0,=res
	CMP R4,#1
	BHI end1
	MOV R4,#0
end1
	STR R4,[R0]
	
halt
	b halt
	
arr DCD 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A
	AREA mydata,DATA,READWRITE
res DCD 0
	END
	
	