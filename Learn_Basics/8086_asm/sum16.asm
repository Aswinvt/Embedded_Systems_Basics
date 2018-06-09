assume cs:code,ds:data
data segment
num1 dw 01 dup(?)
num2 dw 01 dup(?)
res dw 01 dup(?)
data ends
code segment
start:
mov ax,data
mov ds,ax
mov ax,num1
add ax,num2
mov res,ax
mov ah,4ch
int 21h
code ends
end start
