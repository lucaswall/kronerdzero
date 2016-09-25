

.equ SCREEN_X, 1024
.equ SCREEN_Y, 768
.equ SCREEN_BPP, 16


.section .text

.globl framebuffer_init
framebuffer_init:

  //imm32 r0,FB_STRUCT + MAIL_TAGS
  ldr r0, =FB_STRUCT
  add r0, #8

//PERIPHERAL_BASE                = $3F000000 ; Peripheral Base Address
//MAIL_BASE   = $B880 ; Mailbox Base Address
//MAIL_WRITE  =   $20 ; Mailbox Write Register
//MAIL_TAGS    = $8 ; Mailbox Channel 8: Tags (ARM to VC)
  //imm32 r1,PERIPHERAL_BASE + MAIL_BASE + MAIL_WRITE + MAIL_TAGS
  ldr r1, =0x3F00B8A8

  str r0, [r1] // Mail Box Write

  ldr r1, =FB_POINTER // R0 = Frame Buffer Pointer
  ldr r0, [r1]
  cmp r0, #0 // Compare Frame Buffer Pointer To Zero
  beq framebuffer_init // IF Zero Re-Initialize Frame Buffer

  and r0, #0x3FFFFFFF // Convert Mail Box Frame Buffer Pointer From BUS Address To Physical Address ($CXXXXXXX -> $3XXXXXXX)
  str r0, [r1] // Store Frame Buffer Pointer Physical Address

  mov pc, lr


.globl framebuffer_getptr
framebuffer_getptr:

  ldr r1, =FB_POINTER
  ldr r0, [r1]

  mov pc, lr


.globl framebuffer_clear
framebuffer_clear:

  fb_ptr .req r0
  fb_size .req r1
  clear_color .req r2

  ldr r3, =FB_POINTER
  ldr fb_ptr, [r3]
  ldr r3, =FB_SIZE
  ldr fb_size, [r3]
  mov clear_color, #0

ClearLoop:
  str clear_color, [fb_ptr]
  add fb_ptr, #4
  subs fb_size, #4
  bne ClearLoop

  .unreq fb_ptr
  .unreq fb_size
  .unreq clear_color

  mov pc, lr


.ltorg


.section .data

.align 16
FB_STRUCT: // Mailbox Property Interface Buffer Structure
  .int FB_STRUCT_END - FB_STRUCT // Buffer Size In Bytes (Including The Header Values, The End Tag And Padding)
  .int 0x00000000 // Buffer Request/Response Code
         // Request Codes: 0x00000000 Process Request Response Codes: $80000000 Request Successful, $80000001 Partial Response
// Sequence Of Concatenated Tags
  .int 0x00048003 // Set_Physical_Display // Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int SCREEN_X // Value Buffer
  .int SCREEN_Y // Value Buffer

  .int 0x00048004 // Set_Virtual_Buffer // Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int SCREEN_X // Value Buffer
  .int SCREEN_Y // Value Buffer

  .int 0x00048005 // Set_Depth ; Tag Identifier
  .int 0x00000004 // Value Buffer Size In Bytes
  .int 0x00000004 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int SCREEN_BPP // Value Buffer

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
FB_SIZE:
  .int 0 // Value Buffer

.int 0x00000000 // 0x0 (End Tag)
FB_STRUCT_END:
