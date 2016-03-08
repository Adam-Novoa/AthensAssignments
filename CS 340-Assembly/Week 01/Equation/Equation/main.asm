;Adam Novoa
;5/30/2015
;CS 340
;Equation

TITLE Equation

INCLUDE Irvine32.inc

.data
	Avar	dword 35
	Bvar	dword 17
	Cvar	dword 86	;C is a reserved word
	Dvar	dword 52
	Zvar	dword ?		;Answer
	temp	dword ?
.code
main PROC
	
	mov eax,Avar
	add eax,Bvar
	add eax,eax
	mov ebx,Cvar
	sub ebx,Dvar
	mov ecx,3
	mov temp,ebx
	mov ebx,0
L1:
	add ebx,temp
	sub ecx,1
	cmp ecx,0
	jnz L1

	sub eax,ebx
	mov temp,7
	mov ebx,0
	mov ecx,4
.data
	product dword 7
.code
L2:
	mov temp,ecx
	mov ecx,7
	mov ebx,0
	L3:
		sub ecx,1
		add ebx,product
		cmp ecx,0
		jnz L3
	mov product,ebx
	mov ecx,temp
	sub ecx,1
	cmp ecx,0
	jnz L2

	add eax,ebx
	mov Zvar,eax
	call DumpRegs
exit
main ENDP
END main

;result of DumpRegs
;
;  EAX=000041A9  EBX=000041A7  ECX=00000000  EDX=003F1005
;  ESI=00000000  EDI=00000000  EBP=0038FCC4  ESP=0038FCBC
;  EIP=003F355B  EFL=00000206  CF=0  SF=0  ZF=0  OF=0  AF=0  PF=1
;
;Press any key to continue . . .