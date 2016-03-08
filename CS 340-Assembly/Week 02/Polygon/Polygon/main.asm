;Adam Novoa
;CS 340
;6/30/2015

TITLE	Polygon Pgm

INCLUDE Irvine32.inc

.data
	infileName	byte	"Points.txt",0
	infile		dword	0
	buffer		byte	2000 dup(0)
	points		dword	200 dup(0)
	count		dword	0
	outfileName	byte	"Result.dat",0
	outfile		dword	0

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
	
	lea		edi,points	
L1:	
	call	AtoI
	add		count,1
	mov		[edi],eax
	add		edi,4
	jmp		nxt
clear:
	inc		esi
nxt:
	mov		bl,[esi]
	cmp		bl,00h
	je		fin
	cmp		bl,0Dh	;end of line
	je		L2
	cmp		bl,'0'	;NaN
	jl		clear
	cmp		bl,'9'	;NaN
	jg		clear
	jmp		L1
L2:
	mov		ecx,count
	lea		edi,points
	call	findA

.data
	pos		dword	?
	ans		dword	0
	lab		byte	"Area of polygon is"
	answer	byte	10 dup(?)
	e		byte	0Ah,0Dh,0Ah,00h
.code
	mov		pos,esi
	mov		ans,eax
	lea		esi,answer
	mov		ecx,10
	call	blankout	
	add		esi,-1
	mov		eax,ans
	call	ItoA

	mov		eax,outfile
	lea		edx,lab
	call	print
	mov		esi,pos
	lea		edi,points
	jmp		clear

fin:
exit
main ENDP

findA Proc
	mov		edx,0
L1:
	mov		eax,8[edi]
	mov		ebx,4[edi]
	imul	eax,ebx
	add		edx,eax
	mov		eax,[edi]
	mov		ebx,12[edi]
	imul	eax,ebx
	sub		edx,eax
	add		edi,8
	add		ecx,-2
	cmp		ecx,4
	jne		L1
	mov		eax,edx
	mov		edx,0
	mov		ebx,2
	IDIV	ebx
	ret
findA ENDP


blankout PROC
L2:	mov		al,' '
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
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

print PROC
.data
	file	dword	?
.code
	mov		file,eax
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
	ret
print ENDP



END main