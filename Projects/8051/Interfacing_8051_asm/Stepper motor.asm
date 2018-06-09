org 0000h     
	 mov a,#66h
back:mov P2,a
	 RR a
	 acall delay
	 sjmp back
delay:mov r1,#10
   h3:mov r2,#250
   h1:mov r3,#255
   h2:djnz r3,h2
      djnz r2,h1
	  djnz r1,h3
 	  ret
	  end