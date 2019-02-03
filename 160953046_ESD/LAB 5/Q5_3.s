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
	MOV R4,#0
	MOV R12,#1
	
up	LDR R10,[R0],#4
	ADD R4,#1
	CMP R1,R10
	BEQ exit
	SUB R2,#1
	TEQ R2,#0
	BNE up
	ADD R4,#1
	
exit LDR R0,=res
	LDR R1,=res+4
	CMP R4,#1
	BHS end1
	SUB R12,#1
	MOV R4,#0
end1
	CMP R4,#0x0A
	BLS end2
	SUB R12,#1	;found or not
	MOV R4,#0xFF	;index if not found
end2
	STR R4,[R0]
	STR R12,[R1]
	
halt
	b halt
	
arr DCD 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A
num DCD 0x23
	AREA mydata,DATA,READWRITE
res DCD 0
	END
	
	