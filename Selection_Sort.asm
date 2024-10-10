.text
.globl __start
__start:
    la $a0, iArray     
    la $a1, iArray     
    addi $a1, $a1, 20  
    j sort              

sort: 
    beq $a0, $a1, done 
    jal max             
        
    lw $t0, -4($a1)      
    move $t2, $v1        
    sw $t2, -4($a1)     
    sw $t0, 0($v0)       
    addi $a1, $a1, -4    
    j sort               

max:
    move $v0, $a0        
    lw $v1, 0($v0)       
    
    move $t6, $a0        
    addi $t6, $t6, 4     
    lw $t7, 0($t6)      
     
while_max:
    bge $t6, $a1, Volver 
    
    blt $t7, $v1, Cambio_Valores 
    
    move $v0, $t6      
    addi $t6, $t6, 4    
    lw $t7, 0($t6)       
    j while_max          
    
Cambio_Valores:
    move $v1, $t7        
    move $v0, $t6        
    j while_max          

Volver: 
    jr $ra               

done:

    li $v0, 10          
    syscall

.data
iArray:  .word 3,2,1,6,3
