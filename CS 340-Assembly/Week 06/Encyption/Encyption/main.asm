INCLUDE Irvine32.inc

.data
	infileName	byte	"Encyption.txt",0
	infile		dword	0
	buffer		byte	2000 dup(0)
	outfileName	byte	"Result.dat",0
	outfile		dword	0
	key			byte	25 dup(0)

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
	lea		edi,buffer
	
LM:

.data
	line	byte	200 dup(0)
.code
	mov		ecx,200
	lea		esi,line
	call	zeroout
	lea		esi,line
	dec		edi
fill:
	inc		edi
	mov		al,[edi]
	mov		[esi],al
	inc		esi
	cmp		al,0Dh
	jne		fill

	lea		edx,line
	mov		eax,outfile
	call	print

	inc		edi
	mov		ecx,25
	lea		esi,key
	call	zeroout
	
	inc		edi
getKey:
	mov		al,[edi]
	mov		[esi],al
	inc		esi
	inc		edi
	mov		al,[edi]
	cmp		al,0Dh
	jne		getKey

	push	edi
	lea		esi,key

.data
	newline	byte	0Dh,0Ah,00h
.code
	lea		edx,newline
	mov		eax,outfile
	call	print

	lea		esi,line
	lea		edi,key
	call	encypt

	lea		edx,line
	mov		eax,outfile
	call	print

	lea		edx,newline
	mov		eax,outfile
	call	print

	lea		esi,line
	lea		edi,key
	call	encypt

	lea		edx,line
	mov		eax,outfile
	call	print

	lea		edx,newline
	mov		eax,outfile
	call	print

	pop		edi
	add		edi,2
	mov		al,[edi]
	cmp		al,00h
	je		fin

	lea		edx,newline
	mov		eax,outfile
	call	print

	jmp		LM
fin:
exit
main ENDP

zeroout PROC
	push	esi
	push	eax
L2:	mov		al,00h
	mov 	[esi],al
	add		ecx,-1
	add		esi,1
	cmp		ecx,0
	jne		L2
	pop		eax
	pop		esi
	ret
zeroout ENDP

;esi data
;edi key
encypt PROC
	push	esi
	push	edi
	push	ebp
	mov		ebp,esp
reset:
	mov		edi,4[ebp]
L1:	
	mov		al,[esi]
	cmp		al,0
	je		fin
	mov		dl,[edi]
	cmp		dl,0
	je		reset
	xor		al,dl
	mov		[esi],al
	inc		esi
	inc		edi
	jmp		L1
fin:
	pop		ebp
	pop		edi
	pop		esi
	ret
encypt ENDP

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