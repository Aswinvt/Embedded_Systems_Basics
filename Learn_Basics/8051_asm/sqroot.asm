	org 0000h
	mov a,40h
	mov r0,#01h
	mov r1,#00h
 l1:subb a,r0
	jc l2
	inc r1
	inc r0
	inc r0
	jnz l1
 l2:mov 43h,r1
	end
