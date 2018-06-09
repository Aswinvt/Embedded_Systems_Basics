org 0000h
mov r0,#40h
mov r1,#40h
mov r2,3fh
outer:
mov a,r2
mov r3,a
mov a,r0
mov r1,a
inner:
mov a,@r0
mov b,@r1
cjne a,b,check
cont:
inc r1
djnz r3,inner
inc r0
djnz r2,outer
ljmp last

check:
jc cont
mov @r0,b
mov @r1,a
ljmp cont 

last:
mov a,00h
end


