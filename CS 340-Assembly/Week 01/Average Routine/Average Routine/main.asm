;Adam Novoa
;CS 340
;6/9/2015

TITLE Average Routine

INCLUDE Irvine32.inc

.data
ary		dword	100,-50,125,94,35,-192,82,634,193,999
		dword	-524,1,-5,300,15,81,414,143,132,52,-62,38
		dword	56,42,-81,55,43,121,215,0						
count	dword	?
sum		dword	?
.code
main PROC
	
	lea esi,ary
	mov eax,0
	mov ecx,0

L1:	add eax,[esi]
	add ecx,1
	add esi,4
	mov ebx,[esi]
	cmp ebx,0
	jne L1
	mov sum,eax
	mov count,ecx
.data
	label1 byte "Sum of values = "
	sumChar byte 8 DUP(20h)
			byte 0Ah,0Dh,00h
.code
	lea esi,sumChar
	mov ecx,8
	call blankout
	mov eax,sum
	add esi,-1
	call hexToChar
	lea esi,label1
	call print

.data
	label2 byte "Average of values = "
	avgChar byte 8 DUP(20h)
			byte 0Ah,0Dh,00h
.code	
	lea esi,avgChar
	mov ecx,8
	call blankout
	mov eax,sum
	mov edx,0
	IDIV count
	add esi,-1
	call hexToChar
	lea esi,label2
	call print

.data
	label3 byte "Remainder of average = "
	modChar byte 8 DUP(20h)
			byte 0Ah,0Dh,00h
.code	
	lea esi,avgChar
	mov ecx,8
	call blankout
	mov eax,sum
	mov edx,0
	IDIV count
	mov eax,edx
	add esi,-1
	call hexToChar
	lea esi,label2
	call print
exit
main ENDP

blankout PROC
L2:	mov al,' '
	mov [esi],al
	add ecx,-1
	add esi,1
	cmp ecx,0
	jne L2
	ret
blankout ENDP

print Proc
L3:	mov al,[esi]
	call WriteChar
	add esi,1
	mov bl,[esi]
	cmp bl,0
	jne L3
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


END main