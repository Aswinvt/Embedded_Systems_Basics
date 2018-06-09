ORG 0H
MOV A,#38H // Use 2 lines and 5x7 matrix
ACALL COMNWRT
ACALL DELAY
MOV A,#0EH // LCD ON, cursor ON, cursor blinking ON
ACALL COMNWRT
ACALL DELAY
MOV A,#01H //Clear screen
ACALL COMNWRT
ACALL DELAY
MOV A,#06H //Increment cursor
ACALL COMNWRT
ACALL DELAY
MOV A,#84H //Cursor line one , position 2
ACALL COMNWRT
ACALL DELAY
MOV A,#'N'
ACALL DATAWRT
ACALL DELAY
MOV A,#'O'
ACALL DATAWRT
AGAIN:SJMP AGAIN
COMNWRT:MOV P1,A
	    CLR P2.0
	    CLR P2.1
   	    SETB P2.2
	    ACALL DELAY
	    CLR P2.2
	    RET
DATAWRT:MOV P1,A
	    SETB P2.0
   	    CLR P2.1
	    SETB P2.2
	    ACALL DELAY
	    CLR P2.2
	    RET
delay:mov r3,#50
   h2:mov r4,#255
    h:djnz r4,h
      djnz r3,h2
 	  ret
	  end