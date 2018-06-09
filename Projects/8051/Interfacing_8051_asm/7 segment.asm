     org 0000h
back:mov p2,#03h
     acall delay
	 mov p2,#08h
	 acall delay
     sjmp back
delay:mov r1,#05
   h3:mov r2,#250
   h1:mov r3,#255
   h2:djnz r3,h2
      djnz r2,h1
	  djnz r1,h3
 	  ret
	  end