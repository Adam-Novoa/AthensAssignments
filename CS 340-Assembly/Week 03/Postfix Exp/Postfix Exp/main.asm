;Adam Novoa
;CS 340
;6/30/2015

TITLE	Postfix exp eval

INCLUDE Irvine32.inc

.data
	infileName	byte	"postfix exp.txt",0
	infile		dword	0
	buffer		byte	2000 dup(0)
	outfileName	byte	"Result.dat",0
	outfile		dword	0

	equation	byte	100 dup(?)
				byte	0Dh,0Ah,00h
.code
main PROC
	lea		edx,outfileName
	call	CreateOutputFile
	mov		outfile,eax	
	lea		edx,infileName
	call	OpenInputFile
	mov		infile,eax
	lea		edx,buffer
	mov		ecx,2000
	call	ReadFromFile
	lea		esi,buffer
	add		esi,-1

Lmain:
	inc		esi
	mov		edi,esi
	lea		esi,equation
	mov		ecx,100
	call	Blankout
	mov		esi,edi
	lea		edi,equation
	mov		ecx,0
	mov		ebx,0
LRead:
	mov		bl,[esi]
	cmp		bl,00h
	je		fin
	mov		[edi],bl
	inc		ecx
	inc		edi
	inc		esi
	cmp		bl,0Dh
	jne		LRead
	
	sub		esi,ecx
	mov		edi,esi
	mov		eax,outfile
	lea		edx,equation
	call	print
	mov		esi,edi
	
L1:	
	call	AtoI
	push	eax
	jmp		nxt
clear:
	inc		esi
nxt:
	mov		bl,[esi]
	cmp		bl,2Bh
	je		plus

	cmp		bl,2Ah
	je		multiply

	cmp		bl,2Dh
	je		minus

	cmp		bl,2Fh
	je		divide

	cmp		bl,00h	;end of data
	je		fin
	cmp		bl,0Dh	;end of line
	je		L2
	cmp		bl,'0'	;NaN
	jl		clear
	cmp		bl,'9'	;NaN
	jg		clear
	jmp		L1

	plus:
	pop		ebx
	pop		eax
	add		eax,ebx
	push	eax
	jmp		clear

	multiply:
	pop		ebx
	pop		eax
	IMUL	ebx
	push	eax
	jmp		clear

	minus:
	pop		ebx
	pop		eax
	sub		eax,ebx
	push	eax
	jmp		clear

	divide:
	pop		ebx
	pop		eax
	mov		edx,0
	IDIV	ebx
	push	eax
	jmp		clear	

L2:
.data
	answer	byte	10 dup(?)
			byte	0Dh,0Ah,00h
.code
	push	esi
	mov		ebx,eax
	lea		esi,answer
	mov		ecx,10
	call	blankout	
	add		esi,-1
	mov		eax,ebx
	call	ItoA
	mov		eax,outfile
	lea		edx,answer
	call	print
	pop		esi
	jmp		Lmain
fin:
exit
main ENDP

blankout PROC
L2:	mov		al,' '
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
	add		esi,-1
	ret
blankout ENDP

zeroout PROC
L2:	mov		al,0
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
	ret
zeroout ENDP

AtoI PROC
	mov		eax,0
	mov		ebx,10
L1:	mov		ecx,0
	mov		cl,[esi]
	cmp		cl,'0'
	JL		L2
	cmp		cl,'9'
	JG		L2
	sub		cl,'0'
	IMUL	ebx
	add		eax,ecx
	inc		esi
	jmp		L1

L2:
	ret
AtoI ENDP

ItoA PROC
	mov	ecx,0
	cmp	eax,0
	jge	L4
	mov	ebx,-1
	IMUL ebx
	mov	ecx,1

L4:	mov edx,0
	mov ebx,10
	IDIV ebx
	add dl,'0'
	mov [esi],dl
	add esi,-1
	cmp eax,0
	jne L4

	cmp	ecx,1
	jne	fin
	mov	bl,2Dh
	mov	[esi],bl
	add	esi,-1
fin:
	ret
ItoA ENDP

print PROC
.data
	file	dword	?
.code
	mov		file,eax
	push	esi
	mov		esi,edx;
again:	
	mov		edx,esi
	mov		eax,file
	mov		ebx,0
	mov		ecx,1
	mov		bl,[esi]
	inc		esi
	cmp		bl,0
	je		goon
	call	WriteToFile
	inc		edx
	jmp		again
goon:
	pop		esi
	ret
print ENDP



END main