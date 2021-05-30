;.586 ;Target processor. Use instructions for Pentium class machines
.MODEL FLAT, C ;Use the flat memory model. Use C calling conventions
;.xmm
.CODE ;Indicates the start of the code segment.


PUBLIC binarize
binarize PROC
	push ebp
	mov ebp,esp

	;-------Variaveis----------
	mov edx ,0; Counter
	mov ebx, [ebp+8]; Limite
	mov ecx, [ebp+12];ArrayChars
	mov esi,[ebp+16]; tamanho
	;--------------------------

	;loop para colocar o limite em compara
	sub bl, 128 ; subtrair 128 para a comparação
loopCompara:  
	mov compara[edx] , bl
	inc edx
	cmp dl, 64
	jne loopCompara

	VMOVDQU ymm2, ymmword ptr compara ; mover array compara para ymm2
	VMOVDQU ymm1, ymmword ptr subtrai ; ymm1 == Array subtrai
	;-----------------loop----------------------------------

	mov eax, [ebp+16] ; tamanho 
	shr eax, 4 ;Shift Right 4 bits

loopArr:
	cmp eax , 0
	je PassarXmm
	cmp eax, 2
	jae ymmcount

	movdqu xmm0, [ecx] ; Mover 16 bytes do array para xmm0
	;como são signed vão de -128 a 127 tendo que subtrair 128 para ficar correto
	PSUBB xmm0, xmm1; subtrai 128
	vpcmpgtb xmm0, xmm0, xmm2 ; comparar e colocar os valores em xmm0
	movdqu [ecx], xmm0 ; colocar os primeiros 16 bytes do array iguais a xmm0
	add ecx, 16
	dec eax
	jmp loopArr

ymmcount:
	VMOVDQU ymm0, ymmword ptr [ecx] ; Mover 32 bytes do array para ymm0
	VPSUBB ymm0,ymm0, ymm1; Subtrair
	VPCMPGTB ymm0, ymm0, ymm2 ; compara e coloca em ymm0
	VMOVDQU ymmword ptr [ecx], ymm0
	add ecx, 32
	sub eax, 2
	jmp loopArr

;--------------------Fazer um a um os valores de sobra guardados em al-------

PassarXmm:
	mov eax, 0
	mov al, [ebp+16];Tamanho
	and al, 0FH ; Guardar ultimos 4 bits

	cmp al, 0
	je final

LoopResto:
	mov edx, [ecx]; Mover Valores de Array para EDX, Ficam reservados no AL
	sub dl , 128  ; Subtrair os 128
	cmp dl,	compara[0]
	jle elseloop
	mov edx, [ecx]
	mov dh ,255
	sub dh, dl
	add [ecx], dh
	jmp end_if
elseloop:
	mov edx, [ecx]
	sub [ecx], dl
end_if:
	inc ecx
	dec eax
	cmp eax, 0
	jne LoopResto

final:
	pop ebp
	ret

binarize ENDP

.DATA
	compara byte 64 dup (?)
	subtrai byte 64 dup (128)
END

