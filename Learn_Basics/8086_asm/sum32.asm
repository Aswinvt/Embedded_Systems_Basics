ASSUME CS:CODE,DS:DATA
DATA SEGMENT
A DW 02 DUP(?)
B DW 02 DUP(?)
RES DW 04 DUP(?)
C DD 01 DUP(?)
DATA ENDS
CODE SEGMENT
START: MOV AX,DATA 
       MOV DS,AX
       MOV AX,A
       ADD AX,B
       MOV RES,AX
       MOV AX,A+2
       ADC AX,B+2
       mov res+2,ax
       jnc l
       mov res+4,01h
    l: MOV AH,4CH
       INT 21H
CODE ENDS
END START

