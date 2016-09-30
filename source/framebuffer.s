
.include "defs.hs"

.section .text

.globl framebuffer_init
framebuffer_init:

  ldr r0, =FB_STRUCT
  add r0, #MAIL_TAGS

  ldr r1, =PERIPHERAL_BASE + MAIL_BASE + MAIL_WRITE + MAIL_TAGS

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

  ldr r0, =SCREEN_BUFFER

  mov pc, lr


.globl framebuffer_clear
framebuffer_clear:

  buffer_ptr .req r0
  fb_size .req r1
  clear_color1 .req r2
  clear_color2 .req r3

  ldr r0, =FB_SIZE
  ldr fb_size, [r0]
  ldr buffer_ptr, =SCREEN_BUFFER
  mov clear_color1, #0
  mov clear_color2, #0

ClearLoop:
  strd clear_color1, clear_color2, [buffer_ptr]
  add buffer_ptr, #8
  subs fb_size, #8
  bne ClearLoop

  .unreq buffer_ptr
  .unreq fb_size
  .unreq clear_color1
  .unreq clear_color2

  mov pc, lr


.globl framebuffer_commit
framebuffer_commit:

  fb_ptr .req r0
  fb_size .req r1
  buffer_ptr .req r2

  push {r4, r5}
  ldr r3, =FB_POINTER
  ldr fb_ptr, [r3]
  ldr r3, =FB_SIZE
  ldr fb_size, [r3]
  ldr buffer_ptr, =SCREEN_BUFFER

CopyLoop:
  ldrd r4, r5, [buffer_ptr]
  strd r4, r5, [fb_ptr]
  add fb_ptr, #8
  add buffer_ptr, #8
  subs fb_size, #8
  bne CopyLoop

  .unreq fb_ptr
  .unreq fb_size
  .unreq buffer_ptr

  pop {r4, r5}
  mov pc, lr

.globl framebuffer_setpal
framebuffer_setpal:

  // r0 start index
  // r1 color count
  // r2 color table addr

  ldr r3, =FB_PAL
  lsl r0, #2
  add r3, r0

pal_loop:
  cmp r1, #0
  beq pal_end
  ldr r0, [r2]
  str r0, [r3]
  add r2, #4
  add r3, #4
  sub r1, #1
  b pal_loop

pal_end:

  mov pc, lr


.ltorg


.section .data

.align 16
SCREEN_BUFFER:
.fill SCREEN_X * SCREEN_Y * PIXEL_SIZE


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
  .int 0 // Value Buffer
  .int 0 // Value Buffer

  .int 0x0004800B // Set_Palette ; Tag Identifier
  .int 0x00000408 // Value Buffer Size In Bytes
  .int 0x00000408 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int 0 // Value Buffer (Offset: First Palette Index To Set (0-255))
  .int 256 // Value Buffer (Length: Number Of Palette Entries To Set (1-256))
FB_PAL:
  .int 0x00000000
  .int 0xffffffff
  .fill 4 * 254

  .int 0x00040001 // Allocate_Buffer ; Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
  .int 0x00000008 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
FB_POINTER:
  .int 0 // Value Buffer
FB_SIZE:
  .int 0 // Value Buffer

.int 0x00000000 // 0x0 (End Tag)
FB_STRUCT_END:

