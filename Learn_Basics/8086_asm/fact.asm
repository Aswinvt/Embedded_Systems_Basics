assume cs:code,ds:data
data segment
num dw 01 dup(?)
res dw 01 dup(?)
data ends
code segment
start:mov ax,data
      mov ds,ax
      mov ax,01h
   l2:mov cl,num
      mul cl
      jz l1
      dec num
      jnz l2
      mov res,ax
      jmp l3
   l1:mov res,01h
   l3:mov ah,4ch
      int 21h
code ends
end start 
