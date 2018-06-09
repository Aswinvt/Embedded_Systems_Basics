assume cs:code,ds:data
data segment
num db 01 dup(?)
res db 01 dup(?)
data ends
code segment
start:mov ax,data
      mov ds,ax
      mov al,num
      mov ah,00h
      mov bl,01h
      mov cl,00h
   s1:sub ax,bx
      jb s2
      add bl,0002h
      add cl,0001h
      jmp s1
   s2:mov res,cl
      mov ah,4ch
      int 21h
code ends
end start
      

