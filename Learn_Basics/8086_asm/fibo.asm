assume cs:code,ds:data
data segment
count db 01 dup(?)
array db 10 dup(?)
data ends
code segment
start:mov ax,data
      mov ds,ax
      mov al,01h
      lea si,array
      mov cl,count
      mov [si],al
      mov al,00h
      mov bl,[si]
      mov [si],al
      dec cl
   l1:add al,bl
      mov bl,[si]
      inc si
      mov [si],al
      loop l1
      mov ah,4ch
      int 21h
code ends
end start

