	area RESET, DATA, readonly
	export __Vectors
		
__Vectors
	dcd 0x10001000
	dcd Reset_Handler
		
	area mycode, code, readonly
	ENTRY
	export Reset_Handler

Reset_Handler
	ldr r0, =0x0A
	ldr r1, =0x05
	ldr r10, =DES
	
loop
	adds r2, r0
	adc r3, #0
	sub r1, #1
	teq r1, #0
	bne loop
	
	str r2, [r10], #4
	str r3, [r10]
	
halt
	b halt
	
	area mydata, DATA, readwrite
DES DCD 0
	END