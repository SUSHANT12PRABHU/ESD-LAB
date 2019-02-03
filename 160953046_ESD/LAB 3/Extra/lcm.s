	area RESET, DATA, readonly
	export __Vectors
		
__Vectors
	dcd 0x10001000
	dcd Reset_Handler
		
	area mycode, code, readonly
	ENTRY
	export Reset_Handler

Reset_Handler
	ldr r0, =0x01
	ldr r1, =0x06
	ldr r2, =0x05
	
loop
	