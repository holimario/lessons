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
jal horspool

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall

#str�ĵ�ַ����$a1���䳤�ȴ���$a0��pattern�ĵ�ַ����$a3���䳤�ȴ���$a2
horspool:
##### your code here #####
move $t0, $a0 #�ݴ�str����
#���붯̬�ռ�
li $a0, 1024  #����256��int�Ŀռ��table����ΪӢ���ַ�����256��
li $v0, 9  #9Ϊsyscall��̬����ռ�ı��
syscall
move $a0, $t0 
move $t9, $v0 #����̬�������ַ�浽$t9
move $t8, $t9 #�ѵ�ַ�ݴ���$t8
move $t7, $a1 #��str��ַ�ݴ���$t7
move $t6, $a3 #��pattern��ַ�ݴ���$t6
li $t0, 0 #i=0
li $t1, 0 #j=0
li $t2, 0 #cnt=0
li $t3, -1 #���ڸ�table���ֵ
li $t4, 256 #�洢table��С

#��table���ֵ
setinitial:
sb $t3, 0($t8) #table[i]=-1
addi $t8, $t8, 4 #table��ַ��һ
addi $t0, $t0, 1 #i+=1 
blt $t0, $t4, setinitial #���i<256������ѭ��

#����table
li $t0, 0 #i=0

gettable:   
add $t8, $t0, $zero #�ݴ�i
add $t8, $t6, $t8 #pattern[i]�ĵ�ַ
lb $t5, 0($t8) #pattern[i]
sll $t5, $t5, 2 #����4
add $t8, $t9, $t5 #table��ַΪpattern[i]+��ʼ��ַ
sw $t0, 0($t8) #table[pattern[i]]=i
addi $t0, $t0, 1 #i+=1 
blt $t0, $a2, gettable #���i<len_pattern������ѭ��

#��ʼ����ƥ��
subi $t0, $a2, 1 #i=len_pattern-1

loopout:
ble $a0, $t0, end #i>=len_str
li $t1, 0 #j=0

loopin:
sub $t3, $a2, $t1 #len_pattern-j
subi $t3, $t3, 1 #len_pattern-1-j
sub $t4, $t0, $t1 #i-j
add $t3, $a3, $t3
add $t4, $a1, $t4
slt $t8, $t1, $a2 #j<len_pattern
lb $t3, 0($t3) #pattern[len_pattern-1-j]
lb $t4, 0($t4) #str[i-j]
seq $t5, $t3, $t4 #pattern[len_pattern-1-j]==str[i-j]
add $t3, $t8, $t5 
li $t4, 2
bne $t3, $t4, if #������ѭ��
addi $t1, $t1, 1 #j+=1
j loopin #��������������ѭ��

if:
bne $t1, $a2, cnt_not_plus
addi $t2, $t2, 1 #cnt+=1

cnt_not_plus:
sub $t3, $a2, $t1 #len_pattern-j
subi $t3, $t3, 1 #len_pattern-1-j
add $t4, $a1, $t0 #str[i]�ĵ�ַ
lb $t4, 0($t4) #str[i]
sll $t4, $t4, 2 #����4
add $t4, $t9, $t4 #table[str[i]]�ĵ�ַ
lw $t4, 0($t4) #table[str[i]]
blt $t3, $t4, else #��table[str[i]]+1>len_pattern-1-j����ִ��else����
add $t0, $a2, $t0 #i+=len_pattern
sub $t0, $t0, $t4 #i-=table[str[i]]
subi $t0, $t0, 1 #i-=1
j loopout #����ѭ��

else:
addi $t0, $t0, 1 #i+=1
j loopout #����ѭ��

#����cnt
end:
move $v0, $t2
jr $ra
