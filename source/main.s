
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

  bl _framebuffer_init

  fb_ptr .req r4
  line_len .req r5
  pos_y .req r6
  pos_x .req r7
  fill_color .req r8
  line_pos .req r9
  wait_var .req r9

  bl _framebuffer_getptr // ret r0 = frame buffer pointer
  mov fb_ptr, r0
  mov line_len, #2048

MainLoop:

  mov pos_y, #600

go:
 
  mov pos_x, #0
  ldr fill_color, =0xf800
draw:
  mul line_pos, line_len, pos_y
  add line_pos, pos_x
  strh fill_color, [fb_ptr, line_pos]
  add pos_x, #2
  cmp pos_x, #2048
  bne draw

  movw wait_var, #0xffff
w:
  subs wait_var, #1
  bne w

  sub pos_y, #1
  cmp pos_y, #100
  bne go

  bl _framebuffer_clear

  b MainLoop

  .unreq fb_ptr
  .unreq line_len
  .unreq pos_y
  .unreq pos_x
  .unreq fill_color
  .unreq line_pos
  .unreq wait_var

Loop:
  b Loop

CoreLoop: // Infinite Loop For Core 1..3
  b CoreLoop

.ltorg


