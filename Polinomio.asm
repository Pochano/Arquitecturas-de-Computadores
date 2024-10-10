.data
    msg_grado: .asciiz "Ingrese el grado del polinomio: "
    msg_coeficiente: .asciiz "Ingrese el coeficiente a"
    msg_x_valor: .asciiz "Ingrese el valor de x: "
    msg_salto_linea: .asciiz "\n"
    
.text
    .globl main

main:
    li $v0, 4                   
    la $a0, msg_grado        
    syscall

    li $v0, 5                   
    syscall
    move $t0, $v0              
    
    addi $t1, $t0, 1            
    li $t2, 4                   
    mul $a0, $t1, $t2           
    
    li $v0, 9                   
    syscall
    move $s0, $v0               
    
    li $t3, 0                   

Input_Coeficientes:
    li $v0, 4                   
    la $a0, msg_coeficiente     
    syscall

    li $v0, 1                   
    move $a0, $t3               
    syscall

    li $v0, 4                   
    la $a0, msg_salto_linea
    syscall

    li $v0, 6                   
    syscall

    swc1 $f0, 0($s0)            
    addi $s0, $s0, 4            
    addi $t3, $t3, 1            
    
    blt $t3, $t1, Input_Coeficientes  
    
    li $v0, 4                   
    la $a0, msg_x_valor        
    syscall

    li $v0, 6                   
    syscall
    mov.s $f12, $f0             
    
    subu $s0, $s0, $t1          
    
    li $t3, 0                   
    
    li $t6, 0                   
    mtc1 $t6, $f2               
    cvt.s.w $f2, $f2            

Polinomio_e:
    lwc1 $f4, 0($s0)           
    
    li $t5, 0                   
    mov.s $f6, $f12             

while_exponente:
    beq $t5, $t3, while_end     
    mul.s $f6, $f6, $f12        
    addi $t5, $t5, 1            
    j while_exponente                  

while_end:
    mul.s $f6, $f6, $f4         
    add.s $f2, $f2, $f6         
    
    addi $s0, $s0, 4            
    addi $t3, $t3, 1            
    
    blt $t3, $t1, Polinomio_e  
    
    li $v0, 2                   
    mov.s $f12, $f2             
    syscall

    li $v0, 10                  
    syscall