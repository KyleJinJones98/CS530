.      SOURCE CODE FOR THE XE VERSION OF THE SIC FAMILY OF COMPUTER
0000 SUM     START     0                  
0000 FIRST   LDX       #0         050000  
0003         LDA       #0         010000  
0006         +LDB      #TABLE2    69101790
000A         BASE      TABLE2             
000A LOOP    ADD       TABLE,X    1BA00A  
000D         ADD       TABLE2,X   1BA6F1  
0010         TIX       COUNT      2F2FF1  
0013         JLT       LOOP       3B2FED  
0016         +STA      TOTAL      0F100002
001A MYLIT   LDA       =C'EOF'    032FE8  
001D COUNT   RESW      1                  
0020 TABLE   RESW      2000               
1790 TABLE2  RESW      2000               
2F00 TOTAL   RESW      1                  
2F03 *       =C'EOF'              454F46  
2F06         END       FIRST              
