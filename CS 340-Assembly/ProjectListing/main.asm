;Jonathan Crowell
;PainfulProgram
;Make me cry

INCLUDE Irvine32.inc


;.386
;.model flat,stdcall
;.stack 4096
;Exitprocess proto,dwExitCode:dword

			      
.data
BUFFER_SIZE = 2000	

inFile	dword	?						
inBuffer	byte	BUFFER_SIZE dup (?)			

myFile	byte "Listing.txt",0		

bytesRead	dword	?					

				
NULL equ	00h				
LF	 equ	0ah	
CR	 equ	0dh	

				
paper	dword	0		
pencil	dword	0
addBook	dword	0
pens	dword	0	
stapler	dword	0
binder	dword	0	
staples	dword	0	
clip	dword	0	
labels	dword	0
tissues	dword	0	
postits	dword	0	
markers	dword	0
erasers	dword	0	
scissors dword	0	
dollars	dword	0	
cents	dword	0	


finished	byte "Thank you for shopping at Pie-In-The-Sky!", CR, LF
byte "Please have a wonderful day and come back soon!", CR, LF
byte "The total amount due is: $"
strTotal	byte	8 dup (?), CR, LF, NULL


.code
main proc

	mov	esi, offset inBuffer
	mov	ecx, BUFFER_SIZE			
	call	cleanBuffer

	mov	edx, offset myFile
	call	OpenInputFile		
	mov	inFile, eax
	call	readMe				

	mov	esi, offset inBuffer	
	call	WriteLine			

	mov	edx, 0					
	mov	dh, 8					
	mov	dl, 1					
	call	Gotoxy						

	call	keyCheck						

	mov	edx, 0						
	mov	dh, 25					
	mov	dl, 0						
	call	Gotoxy			

	mov	esi, offset finished	
	call	WriteLine				
														
														
	call ReadChar		
	exit

main endp

keyCheck proc
 	next:	
		mov	eax, 0			
 		call ReadChar			
 		cmp	al, 0			
 		je	updown			
 		mov	ah, 0			
 		cmp	al, '0'			
 		jl	next				
 		cmp	al, '9'			
 		jg	next				
 				
		call	WriteChar			

		Push edx
 		call	calculate		

		cmp al, 'X'
		je finish

				
 		call	printTotal		
		Pop edx

		call Gotoxy				
 		jmp	next

 	updown:	
		cmp	ah, 48h			
 		je	up				
 		cmp	ah, 50h			
 		je	down				

						
 	up:		
		cmp	dh, 8			
 		je	next			
 		add	dh, -1			
 		call	Gotoxy			
 		jmp	next				

 	down:	
		cmp	dh, 22			
 		je	next				
 		add	dh, 1			
 		call	Gotoxy			
 		jmp	next				

 	finish:	
		Pop edx 			
 		ret
 			
keyCheck endp

 calculate proc	;USES	edx
 		mov	ebx, 0			
 		add	al, -30h			
 		cmp	dh, 8			
 	je	paperRow			
 		cmp	dh, 9			
 	je	pencilRow			
 		cmp	dh, 10			
 	je	addBookRow			
 		cmp	dh, 11			
 	je	pensRow			
 		cmp	dh, 12			 
 	je	staplerRow			
 		cmp	dh, 13			
 	je	binderRow			
 		cmp	dh, 14			
 	je	staplesRow			
 		cmp	dh, 15			
 	je	clipRow			
		cmp	dh, 16			
	je	labelsRow			
		cmp	dh, 17			
	je	tissuesRow			
		cmp	dh, 18			
	je	postitsRow			
		cmp	dh, 19			
	je	markersRow			
		cmp	dh, 20			
	je	erasersRow			
		cmp	dh, 21			
	je	scissorsRow			
		cmp	dh, 22			
	je	killRow			

	paperRow:	
		mov	edx, 0			
		mov	ebx, 1219			
		mul	ebx				
		mov	paper, eax		
		mov	dh, 8			
		mov	dl, 31			
		call printAmount
		jmp	finish
							
	pencilRow:
		mov	edx, 0			
		mov	ebx, 159			
		mul	ebx				
		mov	pencil, eax		
		mov	dh, 9			
		mov	dl, 31			
		call printAmount
		jmp	finish


	addBookRow:	
		mov	edx, 0			
		mov	ebx, 350			
		mul	ebx				
		mov	addBook, eax		
		mov	dh, 10			
		mov	dl, 31			
		call printAmount
		jmp	finish

	pensRow:	
		mov	edx, 0			
		mov	ebx, 259			
		mul	ebx				
		mov	pens, eax			
		mov	dh, 11			
		mov	dl, 31			
		call printAmount
		jmp	finish

	staplerRow:
		mov	edx, 0			
		mov	ebx, 1200			
		mul	ebx				
		mov	stapler, eax		
		mov	dh, 12			
		mov	dl, 31			
		call printAmount
		jmp	finish

	binderRow:
		mov	edx, 0			
		mov	ebx, 475			
		mul	ebx				
		mov	binder, eax		
		mov	dh, 13			
		mov	dl, 31			
		call printAmount
		jmp	finish

	staplesRow:	
		mov	edx, 0			
		mov	ebx, 225			
		mul	ebx				
		mov	staples, eax		
		mov	dh, 14			
		mov	dl, 31			
		call printAmount
		jmp	finish

	clipRow:
		mov	edx, 0			
		mov	ebx, 150			
		mul	ebx				
		mov	clip, eax			
		mov	dh, 15			
		mov	dl, 31			
		call printAmount
		jmp	finish

	labelsRow:	
		mov	edx, 0			
		mov	ebx, 1440			
		mul	ebx				
		mov	labels, eax		
		mov	dh, 16			
		mov	dl, 31			
		call printAmount
		jmp	finish

	tissuesRow:
		mov	edx, 0			
		mov	ebx, 279			
		mul	ebx				
		mov	tissues, eax		
		mov	dh, 17			
		mov	dl, 31			
		call printAmount
		jmp	finish

	postitsRow:
		mov	edx, 0			
		mov	ebx, 320			
		mul	ebx				
		mov	postits, eax		
		mov	dh, 18			
		mov	dl, 31			
		call printAmount				
		jmp	finish

	markersRow:
		mov	edx, 0			
		mov	ebx, 995			
		mul	ebx				
		mov	markers, eax		
		mov	dh, 19			
		mov	dl, 31			
		call printAmount				
		jmp	finish

	erasersRow:	
		mov	edx, 0			
		mov	ebx, 16			
		mul	ebx				
		mov	erasers, eax		
		mov	dh, 20			
		mov	dl, 31			
		call printAmount
		jmp	finish

	scissorsRow:
		mov	edx, 0			
		mov	ebx, 275			
		mul	ebx				
		mov	scissors, eax		
		mov	dh, 21			
		mov	dl, 31			
		call printAmount
		jmp finish

	killRow: 
 		mov	dh, 22			
 		call	Gotoxy			
 		mov	al, 'X'			
 		call WriteChar 

	finish:
		ret
calculate endp

printTotal proc
	mov	eax, 0			
	mov	esi, offset paper	
	mov	ecx, 14			
	next:
		mov	ebx, [esi]		
		add	eax, ebx			
		add	esi, 4			
		dec	ecx				
		cmp	ecx, 0			
		jne	next				

		mov	dh, 23			
		mov	dl, 31			
				
		call printAmount

	ret
printTotal endp
	
moneyStringSetup proc
	mov	esi, offset strTotal	
	mov	ecx, 8				
	call blankOut				
	mov	eax, cents			
	call i2a				
	dec	esi					
	mov	ebx, 0				
	mov	bl, '.'				
	mov	[esi], bl				
	mov	eax, dollars			
	call	i2a				
	ret
moneyStringSetup endp

printAmount proc
	Push edx

	mov	ebx, 100			
	mov	edx, 0			
	div	ebx				
	mov	dollars, eax		
	mov	cents, edx		
	call	moneyStringSetup			

	Pop edx

	call	Gotoxy			
	mov	esi, offset strTotal
	call	WriteLine			

	mov	dh, 8			
	mov	dl, 1	
	call Gotoxy
	ret
printAmount endp

cleanBuffer proc
	next:
		mov	bl, NULL			
		mov	[esi], bl			
		inc	esi				
		dec	ecx				
		cmp	ecx, 0			
		jne	next				
	ret					
cleanBuffer endp

readMe proc 
	mov	eax, inFile			
	mov	edx, offset inBuffer	
	mov	ecx, BUFFER_SIZE		
	call	ReadFromFile			
	mov	bytesRead, eax			
	ret					
readMe endp

incBuffer proc							
	next:	
		mov	al, [esi]				
		cmp	al, NULL				
		je	finish				
		mov	[edi], al				
		inc	esi					
		inc	edi					
		jmp	next
	finish:
		ret
incBuffer endp

a2i proc
	mov	eax, 0			
	next:
		mov	edx, 0			
		mov	dl, [esi] 		
		cmp	dl, NULL			
		je	finish		
		add	dl, -30h			
		imul	eax, 10			
		add	eax, edx		
		inc	esi
		jmp	next 			
	finish:
		ret				
a2i endp

i2a proc
	next:
		mov	edx, 0				
		mov	ebx, 10				
		div	ebx					
		add	dl, '0'				
		dec	esi					
		mov	[esi], dl				
		cmp	eax, 0				
		jne	next
	ret
i2a endp

blankOut proc
	next:
		mov	bl, ' '			
 		mov	[esi], bl			
 		inc	esi				
 		dec	ecx				
 		cmp	ecx, 0			
 		jne	next				
 	ret				
blankOut endp



WriteLine proc
 	next:
		mov	al,[esi]			
 		cmp	al, NULL			
 		je	DONE				
 		call WriteChar			
 		inc	esi				
 		jmp	next				
 	DONE:
		ret					
WriteLine endp

end main 
