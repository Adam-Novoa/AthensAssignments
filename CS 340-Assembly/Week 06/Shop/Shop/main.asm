;Adam Novoa
;CS 340
;7/14/2015

TITLE Shop List

INCLUDE Irvine32.inc

.data

	finish	byte	"Thank you for your purchase please come again.",0Dh,0Ah
			byte	"You total is $",00h
	newline	byte	0Ah,00h,00h
	zero	byte	"    0.00",00h

	menu	byte	"Welcome to the ‘Finger Shopping’ Store.",0Dh,0Ah
			byte	"Please make your selections.",0Dh,0Ah
			byte	"                               Sub Total",0Dh,0Ah
			byte	"__     Paper 8x11      12.19     0.00",0Dh,0Ah
			byte	"__     Pk Pencil        1.59     0.00",0Dh,0Ah
			byte	"__     Address Book     3.50     0.00",0Dh,0Ah
			byte	"__     Pk Pens          2.59     0.00",0Dh,0Ah
			byte	"__     Stapler         12.00     0.00",0Dh,0Ah
			byte	"__     3 Ring Binder    4.75     0.00",0Dh,0Ah
			byte	"__     Staples          2.25     0.00",0Dh,0Ah
			byte	"__     Paper Clips      1.50     0.00",0Dh,0Ah
			byte	"__     Gum Labels      14.40     0.00",0Dh,0Ah
			byte	"__     Tissues          2.79     0.00",0Dh,0Ah
			byte	"__     Postits          3.20     0.00",0Dh,0Ah
			byte	"__     Markers          9.95     0.00",0Dh,0Ah
			byte	"__     Erasers          0.16     0.00",0Dh,0Ah
			byte	"__     Scissors         2.75     0.00",0Dh,0Ah
			byte	"__     ALL DONE (Exit)",0Dh,0Ah
			byte	"          Your Bill              0.00",0Dh,0Ah,00h
	
	minX	byte	3
	maxX	byte	17
	curX	byte	0
	prices	dword	1219,159,350,259,1200,475,225,150,1440,279,320,995,16,275
	count	dword	14 dup(0)
	total	dword	0
	flag	byte	0
	temp	byte	10 dup(0),0

	


.code
main PROC
	lea		esi,menu
	call	print
	mov		dl,1
LM:

	lea		esi,count
	lea		edi,prices
	mov		eax,0
	mov		al,curX
	mov		ebx,4
	IMUL	ebx
	add		esi,eax
	add		edi,eax

	mov		dl,1
	mov		dh,minX
	add		dh,curX
	call	Gotoxy
	mov		eax,0
	call	ReadChar
	cmp		al,0
	je		move
	cmp		al,30h
	jl		LM		;key less than '0'
	cmp		al,39h
	jg		LM		;key greater than '9'

	mov		dl,curX
	mov		cl,maxX
	sub		cl,minX
	cmp		dl,cl
	je		fin

	mov		ah,0
	add		al,-30h
	push	eax
	mov		ebx,[esi]
	mov		eax,[edi]
	mov		edx,0
	IMUL	ebx
	sub		total,eax
	pop		eax
	cmp		flag,0
	jne		L1

	mov		ebx,eax
	mov		[esi],ebx
	mov		edx,0
	mov		eax,[edi]
	IMUL	ebx
	add		total,eax
	call	refresh
	mov		flag,1
	jmp		LM
L1:
	push	eax
	mov		eax,[esi]
	cmp		eax,10
	jl		L2
	mov		edx,0
	mov		ebx,10
	IDIV	ebx
	mov		eax,edx
L2:
	mov		ebx,10
	IMUL	ebx
	mov		edx,eax
	pop		eax
	add		edx,eax
	mov		eax,edx
	mov		[esi],eax
	mov		ebx,eax
	mov		edx,0
	mov		eax,[edi]
	IMUL	ebx
	add		total,eax
	call	refresh
	mov		flag,1
	jmp		LM


move:
	cmp		ah,48h
	jne		nxt
	cmp		curX,0
	je		LM
	sub		curX,1
	mov		flag,0
nxt:
	cmp		ah,50h
	jne		LM
	cmp		curX,14
	je		LM
	add		curX,1
	mov		flag,0
	jmp		LM

fin:
	mov		dh,19
	mov		dl,0
	call	Gotoxy
	lea		esi,finish
	call	print
	
	lea		esi,temp
	mov		ecx,10
	call	zeroout
	mov		eax,0
	mov		eax,total
	mov		ebx,100
	mov		edx,0
	IDIV	ebx
	push	edx
	call	ItoA
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	mov		cl,'.'
	mov		[esi],cl
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	pop		eax
	call	ItoA
	call	print
	lea		esi,newline
	call	print
	
exit
main ENDP

zeroout PROC
	push	eax
L2:	mov		al,00h
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
	pop		eax
	ret
zeroout ENDP

ItoA PROC
	push ebx
	push edx
	mov	ecx,0

L4:	mov edx,0
	mov ebx,10
	IDIV ebx
	add dl,'0'
	mov [esi],dl
	add esi,-1
	inc	ecx
	cmp eax,0
	jne L4

	inc	esi
	pop	edx
	pop	ebx
	ret
ItoA ENDP

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

print Proc
L3:	mov al,[esi]
	call WriteChar
	add esi,1
	mov bl,[esi]
	cmp bl,0
	jne L3
	ret
print ENDP


;eax = subtotal
;ebx = count

refresh PROC

	push	esi

	push	eax	
	mov		eax,ebx
	lea		esi,temp
	mov		ecx,10
	call	zeroout
	call	ItoA
	mov		dl,0
	mov		dh,minX
	add		dh,curX
	call	Gotoxy
	mov		eax,ebx

	cmp		eax,9
	jg		L1
	dec		esi
	mov		cl,'_'
	mov		[esi],cl
L1:
	call	print
	pop		eax
	mov		edx,0
	mov		ebx,100
	IDIV	ebx
	push	edx
	mov		ecx,0
	
	lea		esi,temp
	mov		ecx,10
	call	zeroout
	call	ItoA

	mov		dh,minX
	add		dh,curX
	mov		dl,29
	
	call	Gotoxy
	mov		dl,33
	mov		edi,esi
	lea		esi,zero
	call	print
	inc		dl	
	sub		dl,cl
	call	Gotoxy
	mov		esi,edi
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	mov		cl,'.'
	mov		[esi],cl
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	pop		eax
	call	ItoA
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	mov		eax,0
	mov		eax,total
	mov		ebx,100
	mov		edx,0
	IDIV	ebx
	push	edx
	call	ItoA
	mov		dh,18
	mov		dl,29	
	call	Gotoxy	
	mov		edi,esi
	lea		esi,zero
	call	print
	mov		dl,34
	sub		dl,cl
	call	Gotoxy
	mov		esi,edi
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	mov		cl,'.'
	mov		[esi],cl
	call	print

	lea		esi,temp
	mov		ecx,10
	call	zeroout
	pop		eax
	call	ItoA
	call	print
	pop		esi
	ret
refresh ENDP


END main