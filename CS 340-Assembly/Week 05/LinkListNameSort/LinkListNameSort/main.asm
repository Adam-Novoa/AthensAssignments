;Adam Novoa
;7/7/2015
;CS 340

TITLE	Link List Name Sort

INCLUDE Irvine32.inc

.data
	infileName	byte	"NamesAndGrades.txt",0
	infile		dword	0
	buffer		byte	2000 dup(0)
	outfileName	byte	"Result.dat",0
	outfile		dword	0
	maxGrade	dword	0
	head		dword	0
	LinkList	byte	2000 dup(?);20 bytes name/ 4 bytes grade/ 4 bytes prev addr/ 4 bytes next addr


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

	call	AtoI
	mov		maxGrade,eax
	add		esi,1
	mov		edi,esi
	lea		esi,LinkList

LR:	
	push	head
	call	insert
	pop		head
	mov		al,[edi]
	cmp		al,0Ah
	je		LR

	mov		edi,head
LP:
.data
	lab		byte 20 dup(?)
	grade	byte 4 dup(?)
			byte 0Dh,0Ah,00h
.code
	mov		eax,20[edi]
	mov		edx,0
	mov		ebx,100
	IMUL	ebx

	mov		ebx,maxGrade
	IDIV	ebx
	lea		esi,grade
	mov		ecx,4
	call	blankout
	call	ItoA

	mov 	ecx,20
	lea		esi,lab
LText:
	mov		al,[edi]
	mov		[esi],al
	add		edi,1
	add		esi,1
	loop	LText

	lea		edx,lab
	mov		eax,outfile
	call	print
	mov		eax,8[edi]
	mov		edi,eax
	cmp		eax,0
	jne		LP

.data
	nl	byte	0Dh,0Ah,00h
.code
	lea		edx,nl
	mov		eax,outfile
	call	print

	mov		edi,head
	lea		esi,lab
	push	edi
	push	esi
	lea		esi,grade
	push	esi
	call	recurPrint

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

;Stack Order
;ebp
;ret addr
;@head

insert PROC
	push	ebp
	mov		ebp,esp
	mov		ecx,20
	push	esi
	call	blankout
	pop		esi
	push	esi
L1:
	mov		dl,[edi]
	inc		edi
	cmp		dl,' '
	je		nxt
	mov		[esi],dl
	inc		esi
	jmp		L1
skip:
	inc		edi
nxt:
	mov		dl,[edi]
	cmp		dl,' '
	je		skip
	mov		esi,edi
	call	AtoI
	mov		edi,esi
	add		edi,1
	pop		esi
	mov		20[esi],eax
	mov		eax,0
	mov		24[esi],eax
	mov		28[esi],eax

	push	edi	;done with this entry
	mov		edx,8[ebp]
	cmp		edx,0
	jne		nxt2
	
	;inserts first item in list
	
	mov		8[ebp],esi
	jmp		fin

	;edi = old data
	;esi = new data

nxt2:	;data already in list
	mov		edi,edx
	mov		eax,20[edi]
	mov		ebx,20[esi]
	cmp		ebx,eax
	jg		insB4		;insert in middle of list
	mov		eax,28[edi]
	cmp		eax,0
	je		last		;insert into end of list
	mov		edx,28[edi]
	mov		edi,edx
	jmp		nxt2

insB4:	;FRONT
	;new entry goes before this entry
	mov		eax,24[edi]
	cmp		eax,0
	jne		nxt3
	;Entry is new head
	mov		8[ebp],esi
	mov		24[edi],esi
	mov		28[esi],edi
	;head->new-><-old
	jmp		fin

nxt3:	;MIDDLE
	mov		24[esi],eax
	mov		24[edi],esi
	mov		28[esi],edi
	;old  <-new-><-old
	mov		edi,eax
	mov		ebx,esi
	mov		28[edi],ebx
	;old-><-new-><-old
	jmp		fin

last:	;END
	mov		eax,esi
	mov		ebx,edi
	mov		28[edi],eax
	mov		24[esi],ebx
	;old-><-new->nul

fin:
	add		esi,32
	pop		edi ;reset to read next entry
	pop		ebp
	ret
insert ENDP

;grade
;label
;nxt addres

recurPrint PROC
	push	ebp
	mov		ebp,esp
	mov		edi,16[ebp]
	mov		eax,28[edi]
	cmp		eax,0
	je		nxt
	push	eax
	mov		eax,12[ebp]
	push	eax
	mov		eax,8[ebp]
	push	eax
	call	recurPrint
	mov		edi,16[ebp]
nxt:
	mov		eax,20[edi]
	mov		edx,0
	mov		ebx,100
	IMUL	ebx

	mov		ebx,maxGrade
	IDIV	ebx
	mov		esi,8[ebp]
	mov		ecx,4
	call	blankout
	call	ItoA

	mov 	ecx,20
	mov		esi,12[ebp]
LText:
	mov		al,[edi]
	mov		[esi],al
	add		edi,1
	add		esi,1
	loop	LText

	mov		edx,12[ebp]
	mov		eax,outfile
	call	print
	pop		ebp
	ret	12



recurPrint ENDP

END main