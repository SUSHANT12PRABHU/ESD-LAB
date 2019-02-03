	area RESET, DATA, readonly
	export __Vectors
		
__Vectors
	dcd 0x10001000
	dcd Reset_Handler
		
	area mycode, code, readonly
	ENTRY
	export Reset_Handler

Reset_Handler
	ldr r0, =0x06
	ldr r1, =0x0C
	ldr r2, =res
loop
	cmp r0, r1
	subgt r0, r1
	suble r1, r0
	teq r0, r1
	bne loop
	
	str r0, [r2]
	
halt
	b halt
	
	area mydata, DATA, readwrite
res dcd 0
	END