org 0000h
     mov a,40h
     jnz l1
     mov 41h,#01h
here:sjmp here
  l1:mov r1,a
     mov b,#01h
  l2:mul ab
     dec r1
     mov b,r1
     cjne r1,#00h,l2
     mov 41h,b
     mov 42h,a
end
