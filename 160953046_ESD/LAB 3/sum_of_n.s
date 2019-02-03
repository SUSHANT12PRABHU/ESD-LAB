	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	ldr r0, =n
	ldr r1, =num
	ldr r9, =res
	ldr r8, =0x1
	
loop
	ldr r10, [r1], #4
	
	mla r2, r2, r8, r10
	sub r0, #1
	teq r0, #0
	bne loop
	
	str r2, [r9]
	
halt
	b halt
	
n equ 5
num dcd 0x02, 0x04, 0x02, 0x06, 0x01

	AREA mydata,DATA,READWRITE
res dcd 0
	END