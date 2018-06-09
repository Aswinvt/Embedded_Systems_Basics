assume cs:code,ds:data
data segment
x dw 01 dup(?)
sq dw 01 dup(?)
data ends
code segment
start:mov ax,data
      mov ds,ax
      mov ax,x
      mov bx,x
      mul bx
      mov sq,ax
      mov ah,4ch
      int 21h
code ends
end start

