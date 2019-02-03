  AREA RESET,DATA,READONLY
  EXPORT __Vectors
__Vectors   
  DCD 0x10001000
  DCD Reset_Handler
  AREA mycode, CODE, READONLY
  ENTRY
  EXPORT Reset_Handler
Reset_Handler
  LDR R0, =SRC
  LDR R1, =DST
  LDR R2, [R0]
  STR R2, [R1]
  LDR R2, [R0,#4]
  STR R2, [R1,#4]
  LDR R2, [R0,#8]
  STR R2, [R1,#8]
  LDR R2, [R0,#12]
  STR R2, [R1,#12]
  LDR R2, [R0,#16]
  STR R2, [R1,#16]
HERE
  B HERE
SRC DCD 1,2,3,4,5
  AREA mydata, DATA, READWRITE
DST DCD 0
  END