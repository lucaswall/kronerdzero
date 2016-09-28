

.equ SCREEN_X, 640
.equ SCREEN_Y, 480
.equ SCREEN_BPP, 8
.equ PIXEL_SIZE, 1

.equ PERIPHERAL_BASE, 0x3F000000 // Peripheral Base Address
.equ MAIL_BASE, 0xB880 // Mailbox Base Address
.equ MAIL_WRITE, 0x20 // Mailbox Write Register
.equ MAIL_TAGS, 0x8 // Mailbox Channel 8: Tags (ARM to VC)

.equ HW_RNG_BASE, (PERIPHERAL_BASE + 0x104000)
.equ HW_RNG_CTRL, (HW_RNG_BASE + 0x00)
.equ HW_RNG_CTRL_EN, 0x1
.equ HW_RNG_STATUS, (HW_RNG_BASE + 0x04)
.equ HW_RNG_DATA, (HW_RNG_BASE + 0x08)
.equ HW_RNG_WARMUP_COUNT, 0x40000

