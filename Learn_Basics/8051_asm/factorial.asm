org 0000h
mov 45h,41h
mov r1,45h
here:
mov b,r1
dec b
mov r1,b
mov b,r1
mov r0,b
mov 42h,40h
mov 43h,41h
addd:
clr c
mov a,41h
add a,43h
mov 41h,a
mov a,40h
addc a,42h
mov 40h,a
mov b,r0
dec b
mov r0,b
cjne r0,#01h,addd
cjne r1,#02h,here
end