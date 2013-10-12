	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:
Leh_func_begin1:
	pushq	%rbp
Ltmp0:
	movq	%rsp, %rbp
Ltmp1:
	subq	$48, %rsp
Ltmp2:
	movl	%edi, %eax
	movl	%eax, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movabsq	$8, %rax
	movq	%rax, %rdi
	callq	__Znwm
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	callq	__ZN7DerivedC1Ev
	movq	-32(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	-40(%rbp), %rcx
	movq	%rcx, %rdi
	callq	*%rax
	movl	$0, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
Leh_func_end1:

	.section	__TEXT,__StaticInit,regular,pure_instructions
	.align	4, 0x90
__GLOBAL__I_main:
Leh_func_begin2:
	pushq	%rbp
Ltmp3:
	movq	%rsp, %rbp
Ltmp4:
	movl	$1, %eax
	movl	$65535, %ecx
	movl	%eax, %edi
	movl	%ecx, %esi
	callq	__Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	ret
Leh_func_end2:

	.section	__TEXT,__textcoal_nt,coalesced,pure_instructions
	.globl	__ZN4BaseC2Ev
.weak_definition __ZN4BaseC2Ev
	.align	1, 0x90
__ZN4BaseC2Ev:
Leh_func_begin3:
	pushq	%rbp
Ltmp5:
	movq	%rsp, %rbp
Ltmp6:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	__ZTV4Base@GOTPCREL(%rip), %rcx
	leaq	(%rcx), %rcx
	movabsq	$16, %rdx
	addq	%rdx, %rcx
	movq	%rcx, (%rax)
	popq	%rbp
	ret
Leh_func_end3:

	.globl	__ZN4Base5printEv
.weak_definition __ZN4Base5printEv
	.align	1, 0x90
__ZN4Base5printEv:
Leh_func_begin4:
	pushq	%rbp
Ltmp7:
	movq	%rsp, %rbp
Ltmp8:
	subq	$16, %rsp
Ltmp9:
	movq	%rdi, -8(%rbp)
	movq	__ZSt4cout@GOTPCREL(%rip), %rax
	leaq	(%rax), %rax
	leaq	L_.str1(%rip), %rcx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end4:

	.globl	__ZN7DerivedC1Ev
.weak_definition __ZN7DerivedC1Ev
	.align	1, 0x90
__ZN7DerivedC1Ev:
Leh_func_begin5:
	pushq	%rbp
Ltmp10:
	movq	%rsp, %rbp
Ltmp11:
	subq	$16, %rsp
Ltmp12:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	callq	__ZN4BaseC2Ev
	movq	-8(%rbp), %rax
	movq	__ZTV7Derived@GOTPCREL(%rip), %rcx
	leaq	(%rcx), %rcx
	movabsq	$16, %rdx
	addq	%rdx, %rcx
	movq	%rcx, (%rax)
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end5:

	.globl	__ZN7Derived5printEv
.weak_definition __ZN7Derived5printEv
	.align	1, 0x90
__ZN7Derived5printEv:
Leh_func_begin6:
	pushq	%rbp
Ltmp13:
	movq	%rsp, %rbp
Ltmp14:
	subq	$16, %rsp
Ltmp15:
	movq	%rdi, -8(%rbp)
	movq	__ZSt4cout@GOTPCREL(%rip), %rax
	leaq	(%rax), %rax
	leaq	L_.str(%rip), %rcx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end6:

	.section	__TEXT,__StaticInit,regular,pure_instructions
	.align	4, 0x90
__Z41__static_initialization_and_destruction_0ii:
Leh_func_begin7:
	pushq	%rbp
Ltmp16:
	movq	%rsp, %rbp
Ltmp17:
	subq	$16, %rsp
Ltmp18:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$1, %eax
	jne	LBB7_3
	movl	-8(%rbp), %eax
	cmpl	$65535, %eax
	jne	LBB7_3
	leaq	__ZStL8__ioinit(%rip), %rax
	movq	%rax, %rdi
	callq	__ZNSt8ios_base4InitC1Ev
	leaq	___tcf_0(%rip), %rax
	movabsq	$0, %rcx
	movq	___dso_handle@GOTPCREL(%rip), %rdx
	leaq	(%rdx), %rdx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	___cxa_atexit
LBB7_3:
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end7:

	.section	__TEXT,__text,regular,pure_instructions
	.align	4, 0x90
___tcf_0:
Leh_func_begin8:
	pushq	%rbp
Ltmp19:
	movq	%rsp, %rbp
Ltmp20:
	subq	$16, %rsp
Ltmp21:
	movq	%rdi, -8(%rbp)
	leaq	__ZStL8__ioinit(%rip), %rax
	movq	%rax, %rdi
	callq	__ZNSt8ios_base4InitD1Ev
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end8:

	.section	__DATA,__datacoal_nt,coalesced
	.globl	__ZTV4Base
.weak_definition __ZTV4Base
	.align	4
__ZTV4Base:
	.quad	0
	.quad	__ZTI4Base
	.quad	__ZN4Base5printEv

	.globl	__ZTI4Base
.weak_definition __ZTI4Base
	.align	4
__ZTI4Base:
	.quad	__ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	__ZTS4Base

	.section	__TEXT,__const_coal,coalesced,pure_instructions
	.globl	__ZTS4Base
.weak_definition __ZTS4Base
__ZTS4Base:
	.asciz	 "4Base"

	.section	__DATA,__datacoal_nt,coalesced
	.globl	__ZTV7Derived
.weak_definition __ZTV7Derived
	.align	4
__ZTV7Derived:
	.quad	0
	.quad	__ZTI7Derived
	.quad	__ZN7Derived5printEv

	.globl	__ZTI7Derived
.weak_definition __ZTI7Derived
	.align	4
__ZTI7Derived:
	.quad	__ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	__ZTS7Derived
	.quad	__ZTI4Base

	.section	__TEXT,__const_coal,coalesced,pure_instructions
	.globl	__ZTS7Derived
.weak_definition __ZTS7Derived
__ZTS7Derived:
	.asciz	 "7Derived"

	.section	__TEXT,__cstring,cstring_literals
L_.str:
	.asciz	 "Derived"

L_.str1:
	.asciz	 "Base"

.zerofill __DATA,__bss,__ZStL8__ioinit,1,3
	.section	__DATA,__mod_init_func,mod_init_funcs
	.align	3
	.quad	__GLOBAL__I_main
	.section	__TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame0:
Lsection_eh_frame:
Leh_frame_common:
Lset0 = Leh_frame_common_end-Leh_frame_common_begin
	.long	Lset0
Leh_frame_common_begin:
	.long	0
	.byte	1
	.asciz	 "zR"
	.byte	1
	.byte	120
	.byte	16
	.byte	1
	.byte	16
	.byte	12
	.byte	7
	.byte	8
	.byte	144
	.byte	1
	.align	3
Leh_frame_common_end:
	.globl	_main.eh
_main.eh:
Lset1 = Leh_frame_end1-Leh_frame_begin1
	.long	Lset1
Leh_frame_begin1:
Lset2 = Leh_frame_begin1-Leh_frame_common
	.long	Lset2
Ltmp22:
	.quad	Leh_func_begin1-Ltmp22
Lset3 = Leh_func_end1-Leh_func_begin1
	.quad	Lset3
	.byte	0
	.byte	4
Lset4 = Ltmp0-Leh_func_begin1
	.long	Lset4
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset5 = Ltmp1-Ltmp0
	.long	Lset5
	.byte	13
	.byte	6
	.align	3
Leh_frame_end1:

__GLOBAL__I_main.eh:
Lset6 = Leh_frame_end2-Leh_frame_begin2
	.long	Lset6
Leh_frame_begin2:
Lset7 = Leh_frame_begin2-Leh_frame_common
	.long	Lset7
Ltmp23:
	.quad	Leh_func_begin2-Ltmp23
Lset8 = Leh_func_end2-Leh_func_begin2
	.quad	Lset8
	.byte	0
	.byte	4
Lset9 = Ltmp3-Leh_func_begin2
	.long	Lset9
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset10 = Ltmp4-Ltmp3
	.long	Lset10
	.byte	13
	.byte	6
	.align	3
Leh_frame_end2:

	.globl	__ZN4BaseC2Ev.eh
.weak_definition __ZN4BaseC2Ev.eh
__ZN4BaseC2Ev.eh:
Lset11 = Leh_frame_end3-Leh_frame_begin3
	.long	Lset11
Leh_frame_begin3:
Lset12 = Leh_frame_begin3-Leh_frame_common
	.long	Lset12
Ltmp24:
	.quad	Leh_func_begin3-Ltmp24
Lset13 = Leh_func_end3-Leh_func_begin3
	.quad	Lset13
	.byte	0
	.byte	4
Lset14 = Ltmp5-Leh_func_begin3
	.long	Lset14
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset15 = Ltmp6-Ltmp5
	.long	Lset15
	.byte	13
	.byte	6
	.align	3
Leh_frame_end3:

	.globl	__ZN4Base5printEv.eh
.weak_definition __ZN4Base5printEv.eh
__ZN4Base5printEv.eh:
Lset16 = Leh_frame_end4-Leh_frame_begin4
	.long	Lset16
Leh_frame_begin4:
Lset17 = Leh_frame_begin4-Leh_frame_common
	.long	Lset17
Ltmp25:
	.quad	Leh_func_begin4-Ltmp25
Lset18 = Leh_func_end4-Leh_func_begin4
	.quad	Lset18
	.byte	0
	.byte	4
Lset19 = Ltmp7-Leh_func_begin4
	.long	Lset19
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset20 = Ltmp8-Ltmp7
	.long	Lset20
	.byte	13
	.byte	6
	.align	3
Leh_frame_end4:

	.globl	__ZN7DerivedC1Ev.eh
.weak_definition __ZN7DerivedC1Ev.eh
__ZN7DerivedC1Ev.eh:
Lset21 = Leh_frame_end5-Leh_frame_begin5
	.long	Lset21
Leh_frame_begin5:
Lset22 = Leh_frame_begin5-Leh_frame_common
	.long	Lset22
Ltmp26:
	.quad	Leh_func_begin5-Ltmp26
Lset23 = Leh_func_end5-Leh_func_begin5
	.quad	Lset23
	.byte	0
	.byte	4
Lset24 = Ltmp10-Leh_func_begin5
	.long	Lset24
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset25 = Ltmp11-Ltmp10
	.long	Lset25
	.byte	13
	.byte	6
	.align	3
Leh_frame_end5:

	.globl	__ZN7Derived5printEv.eh
.weak_definition __ZN7Derived5printEv.eh
__ZN7Derived5printEv.eh:
Lset26 = Leh_frame_end6-Leh_frame_begin6
	.long	Lset26
Leh_frame_begin6:
Lset27 = Leh_frame_begin6-Leh_frame_common
	.long	Lset27
Ltmp27:
	.quad	Leh_func_begin6-Ltmp27
Lset28 = Leh_func_end6-Leh_func_begin6
	.quad	Lset28
	.byte	0
	.byte	4
Lset29 = Ltmp13-Leh_func_begin6
	.long	Lset29
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset30 = Ltmp14-Ltmp13
	.long	Lset30
	.byte	13
	.byte	6
	.align	3
Leh_frame_end6:

__Z41__static_initialization_and_destruction_0ii.eh:
Lset31 = Leh_frame_end7-Leh_frame_begin7
	.long	Lset31
Leh_frame_begin7:
Lset32 = Leh_frame_begin7-Leh_frame_common
	.long	Lset32
Ltmp28:
	.quad	Leh_func_begin7-Ltmp28
Lset33 = Leh_func_end7-Leh_func_begin7
	.quad	Lset33
	.byte	0
	.byte	4
Lset34 = Ltmp16-Leh_func_begin7
	.long	Lset34
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset35 = Ltmp17-Ltmp16
	.long	Lset35
	.byte	13
	.byte	6
	.align	3
Leh_frame_end7:

___tcf_0.eh:
Lset36 = Leh_frame_end8-Leh_frame_begin8
	.long	Lset36
Leh_frame_begin8:
Lset37 = Leh_frame_begin8-Leh_frame_common
	.long	Lset37
Ltmp29:
	.quad	Leh_func_begin8-Ltmp29
Lset38 = Leh_func_end8-Leh_func_begin8
	.quad	Lset38
	.byte	0
	.byte	4
Lset39 = Ltmp19-Leh_func_begin8
	.long	Lset39
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset40 = Ltmp20-Ltmp19
	.long	Lset40
	.byte	13
	.byte	6
	.align	3
Leh_frame_end8:


.subsections_via_symbols
