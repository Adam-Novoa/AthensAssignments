;Adam Novoa
;CS 340
;7/12/2015

TITLE Largest Common Factor

INCLUDE Irvine32.inc

.data
	num1	dword	?
	num2	dword	?
	read	byte	"Input two numbers to find GCF",0Dh,0Ah
			byte	"or a negative number to quit",0Dh,0Ah,00h

.code
main PROC

LR:
	lea		esi,read
	call	print
	call	ReadInt
	mov		num1,eax
	cmp		eax,0
	jl		fin
	push	eax
	call	ReadInt
	mov		num2,eax
	cmp		eax,0
	jl		fin
	push	eax
	call	GCF

.data
	ans		byte	"The GCF of"
	number1	byte	5 dup(?)
			byte	" and"
	number2 byte	5 dup(?)
			byte	" is"
	result	byte	5 dup(?),0Dh,0Ah,0Dh,0Ah,00h
.code
	lea		esi,result
	mov		ecx,5
	call	blankout
	call	ItoA

	lea		esi,number1
	mov		ecx,5
	call	blankout
	mov		eax,num1
	call	ItoA

	lea		esi,number2
	mov		ecx,5
	call	blankout
	mov		eax,num2
	call	ItoA
	lea		esi,ans
	call	print
	jmp		LR
fin:
exit
main ENDP

blankout PROC
	push	eax
L2:	mov		al,' '
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
	add		esi,-1
	pop		eax
	ret
blankout ENDP

ItoA PROC

L4:	mov edx,0
	mov ebx,10
	IDIV ebx
	add dl,'0'
	mov [esi],dl
	add esi,-1
	cmp eax,0
	jne L4
	ret
ItoA ENDP

print Proc
L3:	mov al,[esi]
	call WriteChar
	add esi,1
	mov bl,[esi]
	cmp bl,0
	jne L3
	ret
print ENDP

GCF	Proc
	push	ebp
	mov		ebp,esp
	mov		eax,8[ebp]	;n
	mov		ebx,12[ebp]	;m
	cmp		ebx,0
	je		base;GCF found

	mov		edx,0
	IDIV	ebx
	push	edx
	push	ebx
	call	GCF
	pop		ebp
	ret 8
base:
	mov		eax,8[ebp]
	pop		ebp
	ret 8
GCF ENDP

END main