;Adam Novoa
;CS 340
;6/16/2015

TITLE Triangle

INCLUDE Irvine32.inc

.data
	infileName	byte	"triangle.txt",0
	infile		dword	0
	buffer		byte	2000 dup(0)
	numbers		dword	200 dup(0)
	triangle	dword	3 dup(?)
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
	
	lea		edi,numbers
	call	processArray

doAgain:	
	lea		esi,numbers
	add		esi,count	;move esi to next set of numbers
	add		count,12

L1:
	mov		eax,[esi]	
	cmp		eax,0
	je		fin
	lea		edi,triangle
	mov		ecx,3

L2:	mov		eax,[esi]
	mov		[edi],eax
	add		edi,4
	add		esi,4
	loop	L2
	lea		edi,triangle
	
	call	order
	mov		[edi],eax
	mov		4[edi],ebx
	mov		8[edi],edx

.data
	num1	byte	10 dup(?)
	num2	byte	10 dup(?)
	num3	byte	10 dup(?),00h
.code

	lea		esi,num1
	mov		ecx,10
	call	blankout
	add		esi,-1
	mov		eax,[edi]
	call	hexToChar

	lea		esi,num2
	mov		ecx,10
	call	blankout
	add		esi,-1
	mov		eax,4[edi]
	call	hexToChar

	lea		esi,num3
	mov		ecx,10
	call	blankout
	add		esi,-1
	mov		eax,8[edi]
	call	hexToChar

	mov		eax,[edi]
	mov		ebx,4[edi]
	mov		edx,8[edi]

	call	isRightTri
	cmp		eax,1
	je		isRight
	jne		notR

isRight:
.data
	answer	byte	" is a right triangle."
			byte	0Dh,0Ah,00h
.code
	lea		edx,num1
	mov		eax,outfile
	call	print
	lea		edx,answer
	mov		eax,outfile
	call	print

	jmp	doAgain

notR:
	mov		eax,[edi]
	mov		ebx,4[edi]
	mov		edx,8[edi]
	call	isTri
	cmp		eax,0
	je		notTri

.data
	answer2	byte	" is a triangle. "
			byte	0Dh,0Ah,00h
.code
	lea		edx,num1
	mov		eax,outfile
	call	print
	lea		edx,answer2
	mov		eax,outfile
	call	print

	jmp	doAgain
notTri:
.data
	answer3	byte	" is not a triangle. "
			byte	0Dh,0Ah,00h
.code
	lea		edx,num1
	mov		eax,outfile
	call	print
	lea		edx,answer3
	mov		eax,outfile
	call	print

	jmp	doAgain
fin:
exit
main ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;esi start of data to be read       ;
;edi start of location to store data;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
processArray PROC
L1:	call	AtoI
	mov		[edi],eax
	add		edi,4
clear:
	inc		esi
	mov		bl,[esi]
	cmp		bl,0	;end of file
	je		L2
	cmp		bl,'0'	;NaN
	jl		clear
	cmp		bl,'9'	;NaN
	jg		clear
	jmp		L1

L2:
	ret
processArray ENDP


blankout PROC
L2:	mov		al,' '
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
	ret
blankout ENDP

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;result                             ;
;eax contains highest number        ;
;ebx contains lowest or equal number;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
highest PROC
	cmp eax,ebx
	jg	done
	mov ecx,eax
	mov eax,ebx
	mov ebx,ecx
done:
	ret
highest ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;edi points to first of three numbers;
;Result								 ;
;eax has highest number				 ;
;ebx has middle number				 ;
;edx has lowest number				 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
order PROC
.data
	temp dword ?
	top dword ?
.code
	mov		eax,[edi]
	add		edi,4
	mov		ebx,[edi]
	call	highest
	mov		temp,ebx
	add		edi,4
	mov		ebx,[edi]
	call	highest
	mov		top,eax
	mov		eax,temp
	call	highest
	mov		edx,ebx
	mov		ebx,eax
	mov		eax,top
	add		edi,-8
	ret
order ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;eax has highest number			   ;
;ebx has middle number			   ;
;edx has lowest number			   ;
;result							   ;
;eax has 1 for true or 0 for false ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
isRightTri PROC
	imul	eax,eax
	imul	ebx,ebx
	imul	edx,edx
	add		ebx,edx
	cmp		eax,ebx
	jne		neq
	mov		eax,1
	ret
neq:
	mov		eax,0
	ret
isRightTri ENDP

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

hexToChar PROC

L4:	mov edx,0
	mov ebx,10
	IDIV ebx
	add dl,'0'
	mov [esi],dl
	add esi,-1
	cmp eax,0
	jne L4
	ret
hexToChar ENDP

isTri Proc
	add	ebx,edx
	cmp	eax,ebx
	jg	nTri
	mov	eax,1
	ret
nTri:
	mov	eax,0
	ret
isTri ENDP

END main