;Adam Novoa
;CS 340
;6/30/2015

TITLE RandNbrDicePgm


INCLUDE Irvine32.inc


.data
	outfileName	byte	"Result.dat",0
	outfile		dword	0
	i	dword	1
	d	dword	4000000h
	y	dword	100001
	dice	byte	598 dup(1),2,2
	count	dword	0,0,0,0,0,0
	runSize	dword	0,0,0,0,0,0
	runCount dword	0,0,0,0,0,0
	doubles dword	0,0,0,0,0,0

.code
main PROC
	lea		edx,outfileName
	call	CreateOutputFile
	mov		outfile,eax



	mov		ecx,600
	lea		esi,dice
Lrand:
	call	rand
	mov		[esi],al
	inc		esi
	loop	Lrand

	mov		ecx,600
	lea		esi,dice
	lea		edi,count
	call	countDice

.data
	counter	dword	6
	lab		byte	"The number of dice that were ",30h,"'s"
	answer	byte	10 dup(?)
			byte	0Dh,0Ah,00h

.code
LP1:
	lea		esi,lab
	mov		dl,1
	add		29[esi],dl
	lea		esi,answer
	mov		ecx,10
	call	blankout
	mov		eax,[edi]
	call	ItoA
	lea		edx,lab
	mov		eax,outfile
	call	print
	add		edi,4
	mov		ecx,counter
	sub		counter,1
	loop	LP1




	lea		esi,dice
	lea		edi,runSize
	mov		ecx,600
	call	longestRun
	lea		edi,runSize

.data
	lab2	byte	"The largest run of ",30h,"'s was"
	answer2	byte	10 dup(?)
			byte	0Dh,0Ah,00h
.code
	lea		esi,lab2
	mov		dl,30h
	mov		19[esi],dl
	mov		counter,6

LP2:
	lea		esi,lab2
	mov		dl,1
	add		19[esi],dl
	lea		esi,answer2
	mov		ecx,10
	call	blankout
	mov		eax,[edi]
	call	ItoA
	lea		edx,lab2
	mov		eax,outfile
	call	print
	add		edi,4
	mov		ecx,counter
	sub		counter,1
	loop	LP2

	lea		esi,dice
	lea		edi,runCount
	mov		ecx,600
	call	countRuns
	lea		edi,runCount

.data
	lab3	byte	"The number runs of ",30h,"'s was"
	answer3	byte	10 dup(?)
			byte	0Dh,0Ah,00h
.code
	lea		esi,lab3
	mov		dl,30h
	mov		19[esi],dl
	mov		counter,6

LP3:
	lea		esi,lab3
	mov		dl,1
	add		19[esi],dl
	lea		esi,answer3
	mov		ecx,10
	call	blankout
	mov		eax,[edi]
	call	ItoA
	lea		edx,lab3
	mov		eax,outfile
	call	print
	add		edi,4
	mov		ecx,counter
	sub		counter,1
	loop	LP3


	lea		esi,dice
	lea		edi,doubles
	mov		ecx,600
	call	countDoubles
	lea		edi,doubles

.data
	lab4	byte	"The number of double ",30h,"'s was"
	answer4	byte	10 dup(?)
			byte	0Dh,0Ah,00h
.code
	lea		esi,lab4
	mov		dl,30h
	mov		21[esi],dl
	mov		counter,6

LP4:
	lea		esi,lab4
	mov		dl,1
	add		21[esi],dl
	lea		esi,answer4
	mov		ecx,10
	call	blankout
	mov		eax,[edi]
	call	ItoA
	lea		edx,lab4
	mov		eax,outfile
	call	print
	add		edi,4
	mov		ecx,counter
	sub		counter,1
	loop	LP4












	
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

rand PROC
	mov		eax,y
	mov		ebx,15625
	mov		edx,0
	IMUL	eax,ebx
	add		eax,22221
	mov		ebx,d
	mov		edx,0
	IDIV	ebx
	mov		y,edx
	mov		eax,edx
	mov		ebx,6
	IMUL	eax,ebx
	mov		ebx,d
	mov		edx,0
	IDIV	ebx
	add		eax,1
	ret
rand ENDP

countDice PROC
	mov		ebx,1
	mov		eax,0
	mov		al,[esi]
L:
	cmp		eax,1
	je		L1
	cmp		eax,2
	je		L2
	cmp		eax,3
	je		L3
	cmp		eax,4
	je		L4
	cmp		eax,5
	je		L5
	cmp		eax,6
	je		L6

	jmp	fin
L1:	add		[edi],ebx
	jmp	fin
L2:	add		4[edi],ebx
	jmp	fin
L3:	add		8[edi],ebx
	jmp	fin
L4:	add		12[edi],ebx
	jmp	fin
L5:	add		16[edi],ebx
	jmp	fin
L6:	add		20[edi],ebx
	jmp		fin
	
fin:
	inc		esi
	mov		al,[esi]
	loop	L
	ret
countDice ENDP

longestRun PROC

	mov		eax,7
	push	eax
	push	esi
	push	ecx
	mov		ebx,0
	mov		edx,0
	add		edi,-4
	mov		dl,0
LM:
	add		edi,4
	mov		esi,4[esp]
	mov		ecx,[esp]
	add		edx,1
	mov		eax,-1
	add		8[esp],eax
	mov		eax,0
	mov		ebx,0
	cmp		8[esp],eax
	je		fin
L1:
	
	cmp		ecx,0
	je		LM
	add		ecx,-1
	mov		al,[esi]
	inc		esi
	cmp		dl,al
	jne		L2
	add		ebx,1
	cmp		ebx,[edi]
	jle		L1
	mov		[edi],ebx
	jmp		L1
L2:
	mov		ebx,0
	jmp		L1
fin:
	pop		ecx
	pop		esi
	pop		eax

	ret
longestRun ENDP

countRuns Proc
	
	mov		eax,7
	push	eax
	push	esi
	push	ecx
	mov		ebx,0
	mov		edx,0
	add		edi,-4
	mov		dl,0
LM:
	add		edi,4
	mov		esi,4[esp]
	mov		ecx,[esp]
	add		edx,1
	mov		eax,-1
	add		8[esp],eax
	mov		eax,0
	mov		ebx,0
	cmp		8[esp],eax
	je		fin
L1:
	add		ecx,-1
	cmp		ecx,-1
	jl		LM
	je		L2
	mov		al,[esi]
	inc		esi
	cmp		dl,al
	jne		L2
	add		ebx,1
	jmp		L1
L2:
	cmp		ebx,1
	jle		L3
	mov		ebx,1
	add		[edi],ebx
L3:
	mov		ebx,0
	jmp		L1
fin:
	pop		ecx
	pop		esi
	pop		eax
	ret
countRuns ENDP

countDoubles PROC
	
	mov		eax,7
	push	eax
	push	esi
	push	ecx
	mov		ebx,0
	mov		edx,0
	add		edi,-4
	mov		dl,0
LM:
	add		edi,4
	mov		esi,4[esp]
	mov		ecx,[esp]
	add		edx,1
	mov		eax,-1
	add		8[esp],eax
	mov		eax,0
	mov		ebx,0
	cmp		8[esp],eax
	je		fin
L1:
	add		ecx,-1
	cmp		ecx,-1
	je		LM
	mov		al,[esi]
	inc		esi
	cmp		dl,al
	jne		L2

	inc		ebx
	cmp		ebx,1
	je		L1
	mov		eax,1
	add		[edi],eax
	jmp		L1
	jmp		L1
L2:
	mov		ebx,0
	jmp		L1
fin:
	pop		ecx
	pop		esi
	pop		eax
	ret
countDoubles ENDP

END main