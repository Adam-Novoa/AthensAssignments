;Adam Novoa
;CS 340
;7/5/2015

TITLE Profit Table


INCLUDE Irvine32.inc

.data
	outfileName	byte	"Result.dat",0
	outfile			dword	0
	bestPrice		dword	0
	bestProfit		dword	0
	ticketPrice		dword	275
	patrons			dword	130
	patronCost		dword	88
	header			byte	"Ticket Price     Patrons     Profit "
					byte	0Dh,0Ah,00h

.code
main PROC
	lea		edx,outfileName
	call	CreateOutputFile
	mov		outfile,eax

	lea		edx,header
	mov		eax,outfile
	call	print

LMain:
	mov		eax,ticketPrice
	mov		ebx,patrons
	mov		edx,patronCost
	push	eax
	push	ebx
	push	edx
	call	calcPrice

.data
	price		byte	12 dup(?)
	numPatron	byte	12 dup(?)
	profit		byte	11 dup(?),' '
				byte	0Dh,0Ah,00h
.code

	mov		ebx,bestProfit
	cmp		eax,ebx
	jle		goon2
	mov		bestProfit,eax
	mov		ebx,ticketPrice
	mov		bestPrice,ebx

goon2:
	lea		esi,profit
	mov		ecx,11
	call	blankout
	cmp		eax,0

	jge		L1
	neg		eax
	mov		ecx,1
L1:
	mov		ebx,100
	mov		edx,0
	IDIV	ebx
	mov		ebx,eax
	mov		eax,edx
	call	ItoA
	mov		dl,'.'
	mov		[esi],dl
	add		esi,-1
	mov		eax,ebx
	call	ItoA
	cmp		ecx,1

	jne		goon
	mov		dl,'-'
	mov		[esi],dl
	add		esi,-1
goon:
	mov		eax,ticketPrice
	lea		esi,price
	mov		ecx,12
	call	blankout
	mov		ebx,100
	mov		edx,0
	IDIV	ebx
	mov		ebx,eax
	mov		eax,edx
	call	ItoA
	mov		dl,'.'
	mov		[esi],dl
	add		esi,-1
	mov		eax,ebx
	call	ItoA

	mov		eax,patrons
	lea		esi,numPatron
	mov		ecx,12
	call	blankout
	call	ItoA

	lea		edx,price
	mov		eax,outfile
	call	print

	mov		eax,patrons
	add		eax,15
	mov		patrons,eax
	mov		eax,patronCost
	add		eax,3
	mov		patronCost,eax
	mov		eax,ticketPrice
	sub		eax,5
	mov		ticketPrice,eax
	cmp		eax,145
	jne		LMain

.data
	lab		byte	"Best ticket price is"
	answer	byte	10 dup(?)
			byte	0Dh,0Ah,00h
.code
	lea		esi,answer
	mov		eax,bestPrice
	mov		ecx,10
	call	blankout
	mov		ebx,100
	mov		edx,0
	IDIV	ebx
	mov		ebx,eax
	mov		eax,edx
	call	ItoA
	mov		dl,'.'
	mov		[esi],dl
	add		esi,-1
	mov		eax,ebx
	call	ItoA
	lea		edx,lab
	mov		eax,outfile
	call	print


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
	push ebx
	push edx
L4:	mov edx,0
	mov ebx,10
	IDIV ebx
	add dl,'0'
	mov [esi],dl
	add esi,-1
	cmp eax,0
	jne L4
	pop edx
	pop ebx
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


;order on stack
;Cost per patron
;number of patrons
;ticket Price
;result in eax

calcPrice PROC
	push	ebp
	mov		ebp,esp
	push	ebx
	mov		eax,16[ebp]
	mov		ebx,8[ebp]
	sub		eax,ebx
	mov		ebx,12[ebp]
	IMUL	ebx
	pop		ebx
	pop	ebp
	ret	12
calcPrice ENDP



END main