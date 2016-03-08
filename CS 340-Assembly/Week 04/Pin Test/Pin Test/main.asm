;Adam Novoa
;7/7/2015
;CS 340

TITLE	Pin Test Program

INCLUDE Irvine32.inc

.data
	infileName	byte	"PIN.txt",0
	infile		dword	0
	buffer		byte	2000 dup(0)
	outfileName	byte	"Result.dat",0
	outfile		dword	0
	ranges		dword	5,9,2,5,4,8,1,4,3,6		;order lower bound,higher bound

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
	add		esi,-2
	
.data
	pinS	byte	5 dup(?)
			byte	" Is a valid PIN"
			byte	0Dh,0Ah,00h
	PinF	byte	5 dup(?)
			byte	" Is an invalid pin at location "
	index	byte	?
			byte	0Dh,0Ah,00h
.code
LMain:
	add		esi,2
	lea		edi,ranges
	call	testCode
	mov		edi,esi
	cmp		eax,1
	je		fail
	lea		esi,pinS
	jmp		goon
fail:
	lea		esi,index
	add		cl,'0'
	mov		[esi],cl
	lea		esi,pinF
goon:
	mov		edx,[edi]
	mov		[esi],edx
	mov		dl,4[edi]
	mov		4[esi],dl
	mov		edx,esi
	mov		eax,outfile
	call	print
	mov		esi,edi
	add		esi,5
	mov		dl,[esi]
	cmp		dl,0Dh
	je		LMain
exit
main ENDP

;esi points to string of pins

testCode PROC
	push	esi
	mov		ecx,0
L1:
	add		ecx,1
	mov		eax,0
	mov		ebx,0
	mov		al,[esi]
	inc		esi
	add		eax,-'0'
	push	eax
	mov		ebx,[edi]
	push	ebx
	add		edi,4
	mov		ebx,[edi]
	push	ebx
	add		edi,4
	call	testPin
	cmp		eax,1
	je		fail
	cmp		ecx,5
	jl		L1
	pop		esi
	mov		ecx,0
	ret
fail:
	pop	esi
	ret
testCode ENDP

;Stack Order
;ebp
;ret addr
;upper bound
;lower bound
;pin value

testPin PROC
	push	ebp
	mov		ebp,esp
	mov		eax,16[ebp]
	mov		ebx,12[ebp]
	cmp		eax,ebx
	jl		fail
	mov		ebx,8[ebp]
	cmp		eax,ebx
	jg		fail
	mov		eax,0
	pop		ebp
	ret		12
fail:
	mov		eax,1
	pop		ebp
	ret		12
testPin ENDP

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