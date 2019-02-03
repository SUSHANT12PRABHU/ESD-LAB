	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	ldr r0, =0x0A
	ldr r1, =0x05
	ldr r10, =DES
LOOP
	ADDS R2,R0
	ADC R3,#0
	SUB R1,#1
	TEQ R1,#0
	BNE LOOP
	
	STR r2, [r10], #4
	STR r3, [r10]
	
halt
	b halt
	
	area mydata, DATA, readwrite
DES DCD 0
	END