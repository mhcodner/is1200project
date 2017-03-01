.macro movi reg, val
	lui \reg, %hi(\val)
	ori \reg, \reg, %lo(\val)
.endm

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.macro STUB num
	.align 4
	.section .vector_new_\num,"ax",@progbits
	.global __vector_\num
	__vector_\num:
		movi $k0, _isr_primary_install
		lw $k0, \num * 4($k0)
		jr $k0
.endm

.align 4
.global __use_isr_install
__use_isr_install:
STUB 0


.section .text
.align 4
.global _isr_primary_install
_isr_primary_install:
.word _isr_stub





# Interrupts are handled here
.align 4
.set noreorder
.global _isr_stub
_isr_stub:
	eret
	nop


# Exceptions are handled here (trap, syscall, etc)
.section .gen_handler,"ax",@progbits
.set noreorder
.ent _gen_exception
_gen_exception:
	mfc0 $k0, $14, 0
	addi $k0, $k0, 4
	mtc0 $k0, $14, 0
	eret
	nop

.end _gen_exception


.global delay
delay:
  PUSH $ra
  li $t1, 1000        # load 1000 ms to register t1 (t1 is like ms)
  li $t2, 0           # int i = 0
  li $t3, 13000000     # constant from code

  while:
    ble $t1, 0, finish  # branch less or equal for 0 and t1
    nop                 # no operation
    sub $t1, $t1, 1     # ms = ms - 1

    for:
      beq $t2, $t3, while #  i < constant;
      nop
      addi $t2, $t2, 1    # i = i + 1
      j for               # go back to start of loop
      nop

finish:
  POP $ra
  jr $ra
  nop