.data
str: .space 512
pattern: .space 512
filename: .asciiz "test.dat"

.text
main:
#fopen
la $a0, filename #load filename
li $a1, 0 #flag
li $a2, 0 #mode
li $v0, 13 #open file syscall index
syscall

#read str
move $a0, $v0 #load file description to $a0
la $a1, str
li $a2, 1
li $s0, 0 #len_pattern = 0
read_str_entry:
slti $t0, $s0, 512
beqz $t0, read_str_exit
li $v0, 14 #read file syscall index
syscall
lb $t0, 0($a1)
addi $t1, $zero, '\n'
beq $t0, $t1, read_str_exit
addi $a1, $a1, 1
addi $s0, $s0, 1
j read_str_entry
read_str_exit:

#read pattern
la $a1, pattern
li $a2, 1
li $s1, 0 #len_pattern = 0
read_pattern_entry:
slti $t0, $s1, 512
beqz $t0, read_pattern_exit
li $v0, 14 #read file syscall index
syscall
lb $t0, 0($a1)
addi $t1, $zero, '\n'
beq $t0, $t1, read_pattern_exit
addi $a1, $a1, 1
addi $s1, $s1, 1
j read_pattern_entry
read_pattern_exit:

#close file
li $v0, 16 #close file syscall index
syscall

#call brute_force
move $a0, $s0
la $a1, str
move $a2, $s1
la $a3, pattern
jal kmp

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall

#str�ĵ�ַ����$a1���䳤�ȴ���$a0��pattern�ĵ�ַ����$a3���䳤�ȴ���$a2
kmp:
##### your code here #####
li $t0, 0 #i=0
li $t1, 0 #j=0
li $t2, 0 #cnt=0
move $t3, $a2 #�ݴ�len_pattern
sll $t3, $t3, 4 #����16 
move $t3, $a0 #�ݴ�str����
move $a0, $t3  #����4*len_pattern��int�Ŀռ��next����
li $v0, 9  #9Ϊsyscall��̬����ռ�ı��
syscall
move $a0, $t3 
move $t6, $v0 #�������ʼ��ַ�ݴ���$t6
sw $ra, 0($sp) #$ra��ַ��ջ
jal generateNext #����generateNext�ӳ���

while:
ble $a0, $t0, end #���i>=len_str������ѭ��
add $t3, $a3, $t1 #pattern[j]�ĵ�ַ
add $t4, $a1, $t0 #str[i]�ĵ�ַ
lb $t3, 0($t3) #pattern[j]
lb $t4, 0($t4) #str[i]
bne $t3, $t4 , els0 #���patern[j]!=str[i]������ת��else0
sub $t3, $a2, 1 #len_pattern-1
bne $t1, $t3, els00 #���j!=len_pattern-1������ת��else00
addi $t2, $t2, 1 #cnt+=1
sll $t3, $t3, 2 #����4
add $t3, $t6, $t3 #next[len_pattern-1]�ĵ�ַ
lw $t1, 0($t3) #j=next[len_pattern-1]
addi $t0, $t0, 1 #i+=1
j while

els00:
addi $t0, $t0, 1 #i+=1
addi $t1, $t1, 1 #j+=1
j while

els0:
ble $t1, $zero, els10 #���j<=0������ת��else10
subi $t3, $t1, 1 #j-1
sll $t3, $t3, 2 #����4
add $t3, $t6, $t3 #nex[j-1]�ĵ�ַ
lw $t1, 0($t3) #j=next[j-1]
j while

els10:
addi $t0, $t0, 1 #i+=1
j while

end:
#�ͷ�next�ռ�
move $v0, $t2 #����cnt
lw $ra, 0($sp) #��ջ
jr $ra 

#������generateNext����
generateNext:
li $t9, 1 #i=1
li $t8, 0 #j=0
beq $a2, $zero, end1 #���len_pattern==0���򷵻�1
sw $zero, 0($t6) #next[0]=0

loop:
ble $a2, $t9, end0 #���i>=len_pattern��������ѭ��������0
add $t3, $a3, $t9 #pattern[i]�ĵ�ַ
add $t4, $a3, $t8 #pattern[j]�ĵ�ַ
lb $t3, 0($t3) #pattern[i]
lb $t4, 0($t4) #pattern[j]
bne $t4, $t3, else1 #���pattern[i]!=pattern[j]������ת����һ��else
addi $t8, $t8, 1 #j+=1
sll $t4, $t9, 2 #����4
add $t4, $t6, $t4 #next[i]�ĵ�ַ
sw $t8, 0($t4) #next[i]=j
addi $t9, $t9, 1 #i+=1
j loop

else1:
ble $t8, $zero, else2 #���j<=0������ת���ڶ���else
subi $t4, $t8, 1 #j-1
sll $t4, $t4, 2 #����4
add $t4, $t6, $t4 #next[j-1]�ĵ�ַ
lw $t8, 0($t4) #j=next[j-1]
j loop

else2:
sll $t4, $t9, 2 #����4
add $t4, $t6, $t4 #next[i]�ĵ�ַ
sw $zero, 0($t4) #next[i]=0
addi $t9, $t9, 1 #i+=1
j loop

end0:
li $v0, 0 #����0
jr $ra

end1:
li $v0, 1 #����1
jr $ra
