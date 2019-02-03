	area RESET, DATA, readonly
	export __Vectors
		
__Vectors
	dcd 0x10001000
	dcd Reset_Handler
		
	area mycode, code, readonly
	ENTRY
	export Reset_Handler

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
num dcd 0x02, 0x04, 0xA, 0x6, 0x8
	area mydata, DATA, readwrite
res dcd 0
	END