.     A Simplified First Test
0000 Test1   START     0                  
0000 FIRST   LDX       #0         050000  
.      Comment Line in middle of Source
0003 LOOP    ADD       MYLIT,X    1BA006  
0006 MYLIT   LDA       =C'EOF'    032003  
0009         LTORG                        
0009 *       =C'EOF'              27454F4627
000C COUNT   RESW      10                 
002A TOTAL   RESB      5                  
002F         FLOAT                C0      
0030         MULR      X,T        9815    
0032 MYSYM   EQU       5                  
0032         LDA       #MYSYM*5   010019  
0035         END       FIRST              
