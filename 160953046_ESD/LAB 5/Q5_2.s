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
	MOV R2,#9
up2	MOV R3,R2
	MOV R1,R0
	LDR R4,[R0]
up1	LDR R5,[R1,#4]!
	CMP R4,R5
	BLS skip
	STR R4,[R1]
	STR R5,[R0]
	LDR R4,[R0]
skip SUB R3,#1
	 TEQ R3,#0
	 BNE up1
	 ADD R0,#4
	 SUB R2,#1
	 TEQ R2,#0
	 BNE up2
halt B halt
	
	AREA mydata,DATA,READWRITE
res DCD 0
arr DCD 0x1C,0x1D,0x1E,0x1F,0x16,0x15,0x14,0x13,0x12,0x11
	END
	
	