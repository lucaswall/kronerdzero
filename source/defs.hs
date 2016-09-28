

.equ SCREEN_X, 640
.equ SCREEN_Y, 480
.equ SCREEN_BPP, 8
.equ PIXEL_SIZE, 1

.equ PERIPHERAL_BASE, 0x3F000000 // Peripheral Base Address
.equ MAIL_BASE, 0xB880 // Mailbox Base Address
.equ MAIL_WRITE, 0x20 // Mailbox Write Register
.equ MAIL_TAGS, 0x8 // Mailbox Channel 8: Tags (ARM to VC)
