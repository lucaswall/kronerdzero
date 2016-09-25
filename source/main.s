
.section .init
.globl _start
_start:

mrc p15,0,r0,c0,c0,5 // R0 = Multiprocessor Affinity Register (MPIDR)
ands r0,#3 // R0 = CPU ID (Bits 0..1)
bne CoreLoop // IF (CPU ID != 0) Branch To Infinite Loop (Core ID 1..3)

b Entry

.section .text

Entry:

mov sp,#0x8000

FB_Init:

  //imm32 r0,FB_STRUCT + MAIL_TAGS
  ldr r0, =FB_STRUCT
  add r0, #8

//PERIPHERAL_BASE                = $3F000000 ; Peripheral Base Address
//MAIL_BASE   = $B880 ; Mailbox Base Address
//MAIL_WRITE  =   $20 ; Mailbox Write Register
//MAIL_TAGS    = $8 ; Mailbox Channel 8: Tags (ARM to VC)
  //imm32 r1,PERIPHERAL_BASE + MAIL_BASE + MAIL_WRITE + MAIL_TAGS
  ldr r1, =0x3F00B8A8

  str r0,[r1] // Mail Box Write

  ldr r1, =FB_POINTER // R0 = Frame Buffer Pointer
  ldr r0, [r1]
  cmp r0, #0 // Compare Frame Buffer Pointer To Zero
  beq FB_Init // IF Zero Re-Initialize Frame Buffer

  and r0, #0x3FFFFFFF // Convert Mail Box Frame Buffer Pointer From BUS Address To Physical Address ($CXXXXXXX -> $3XXXXXXX)
  str r0, [r1] // Store Frame Buffer Pointer Physical Address


  mov r3, #2048

MainLoop:

  mov r4, #600

go:
 
  mov r2, #0
  ldr r1, =0xf800f800
draw:
  mul r6, r3, r4
  add r6, r2
  str r1, [r0, r6]
  add r2, #4
  cmp r2, #2048
  bne draw

  movw r5, #0xffff
w:
  sub r5, #1
  cmp r5, #0
  bne w

  mov r2, #0
  ldr r1, =0x00000000
clear:
  mul r6, r3, r4
  add r6, r2
  str r1, [r0, r6]
  add r2, #4
  cmp r2, #2048
  bne clear

  sub r4, #1
  cmp r4, #100
  bne go

  b MainLoop


Loop:
  b Loop

CoreLoop: // Infinite Loop For Core 1..3
  b CoreLoop

.ltorg

.align 16
FB_STRUCT: // Mailbox Property Interface Buffer Structure
  .int FB_STRUCT_END - FB_STRUCT // Buffer Size In Bytes (Including The Header Values, The End Tag And Padding)
  .int 0x00000000 // Buffer Request/Response Code
	       // Request Codes: 0x00000000 Process Request Response Codes: $80000000 Request Successful, $80000001 Partial Response
// Sequence Of Concatenated Tags
  .int 0x00048003 // Set_Physical_Display // Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int 1024 // SCREEN_X ; Value Buffer
  .int 768 // SCREEN_Y ; Value Buffer

  .int 0x00048004 // Set_Virtual_Buffer // Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int 1024 // SCREEN_X ; Value Buffer
  .int 768 // SCREEN_Y ; Value Buffer

  .int 0x00048005 // Set_Depth ; Tag Identifier
  .int 0x00000004 // Value Buffer Size In Bytes
  .int 0x00000004 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int 16 // BITS_PER_PIXEL ; Value Buffer

  .int 0x00048009 // Set_Virtual_Offset ; Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
FB_OFFSET_X:
  .int 0 // Value Buffer
FB_OFFSET_Y:
  .int 0 // Value Buffer

  .int 0x0004800B // Set_Palette ; Tag Identifier
  .int 0x00000010 // Value Buffer Size In Bytes
  .int 0x00000010 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int 0 // Value Buffer (Offset: First Palette Index To Set (0-255))
  .int 2 // Value Buffer (Length: Number Of Palette Entries To Set (1-256))
FB_PAL:
  .int 0x00000000,0xFFFFFFFF // RGBA Palette Values (Offset To Offset+Length-1)

  .int 0x00040001 // Allocate_Buffer ; Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
FB_POINTER:
  .int 0 // Value Buffer
  .int 0 // Value Buffer

.int 0x00000000 // 0x0 (End Tag)
FB_STRUCT_END:


