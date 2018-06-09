org 0000h
l1:mov a,40h
   mov r0,41h
   addc a,r0
   mov 43h,a   
   jc l2
   sjmp l1
l2:mov a,40h
   mov r0,41h
   addc a,r0
   mov 43h+1,a
   mov 43h+2,#01h
end