	area RESET, DATA, readonly
	export __Vectors
		
__Vectors
	dcd 0x10001000
	dcd Reset_Handler
		
	area mycode, code, readonly
	ENTRY
	export Reset_Handler

Reset_Handler
	ldrb r0, =0x56
	ldrb r1, =0x12
	ldrb r10, =0x0
	orn r1, r10, r1
	
	area mydata, data, readwrite
res dcb 