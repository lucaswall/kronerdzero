
.include "defs.hs"

.section .text

.globl temperature_get
temperature_get:

  ldr r0, =REQ_CODE
  mov r1, #0
  str r1, [r0]
  ldr r0, =VALUE_LEN
  mov r1, #8
  str r1, [r0]
  ldr r0, =MAIL_STRUCT
  add r0, #8
  ldr r1, =PERIPHERAL_BASE + MAIL_BASE + MAIL_WRITE + MAIL_TAGS
  str r0, [r1] // Mail Box Write
  ldr r1, =TEMP_VALUE
  ldr r0, [r1]

  mov pc, lr


.section .data


.align 16
MAIL_STRUCT: // Mailbox Property Interface Buffer Structure
  .int MAIL_STRUCT_END - MAIL_STRUCT // Buffer Size In Bytes (Including The Header Values, The End Tag And Padding)
REQ_CODE:
  .int 0x00000000 // Buffer Request/Response Code

  .int 0x00030006 // Get temperature ; Tag Identifier
  .int 0x00000008 // Value Buffer Size In Bytes
VALUE_LEN:
  .int 0x00000004 // 1 bit (MSB) Request/Response Indicator (0=Request, 1=Response), 31 bits (LSB) Value Length In Bytes
  .int 0 // Value Buffer
TEMP_VALUE:
  .int 0 // Value Buffer

.int 0x00000000 // 0x0 (End Tag)
MAIL_STRUCT_END:
