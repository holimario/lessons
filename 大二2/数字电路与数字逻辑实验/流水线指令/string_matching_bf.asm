.data
str: .space 512     #�洢�ַ���
pattern: .space 512 #�洢ģʽ��
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
li $a2, 1 #ÿ�ζ���һ���ֽ�
li $s0, 0 #len_str = 0
read_str_entry:
slti $t0, $s0, 512 #����������ݳ���ȫ���ռ�������
beqz $t0, read_str_exit
li $v0, 14 #read file syscall index
syscall
lb $t0, 0($a1)
addi $t1, $zero, '\n' #�����������˳�
beq $t0, $t1, read_str_exit
addi $a1, $a1, 1 #��ַ����1λ
addi $s0, $s0, 1 #��¼�ܹ������˶����ֽ�
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
beq $t0, $t1, read_pattern_exit #�����������˳�
addi $a1, $a1, 1 #��ַ����1λ
addi $s1, $s1, 1 #��¼�ܹ������˶����ֽ�
j read_pattern_entry
read_pattern_exit:

#close file
li $v0, 16 #close file syscall index
syscall

#call brute_force
move $a0, $s0
la $a1, str      #str�ĵ�ַ����$a1
move $a2, $s1
la $a3, pattern  #pattern�ĵ�ַ����$a3
jal brute_force

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall

#str�ĵ�ַ����$a1���䳤�ȴ���$a0��pattern�ĵ�ַ����$a3���䳤�ȴ���$a2
brute_force:
##### your code here #####
li $t0, 0 #i=0
li $t2, 0 #cnt=0
sub $t5, $a0, $a2 #$t5�洢len_str-len_pattern��ֵ
move $t9, $a1 #��str��ַ����$t9����ֹ�ı�$a1
move $t8, $a3 #��pattern��ַ����$t8����ֹ�ı�$a3

loopout: #��ѭ������iѭ��
li $t1, 0 #j=0
move $t7, $t9 #��str[i]��ַ�ݴ���$t7
move $t6, $t8 #��pattern��ַ�ݴ���$t6

loopin: #��ѭ������jѭ��
lb $t3, 0($t7) #��str[i+j]����$t3
lb $t4, 0($t6) #��pattern[j]����$t4
bne $t4, $t3, if #�ж�str[i+j]��pattern[j]�Ƿ���ȣ������������ѭ����skip
addi $t1, $t1, 1 #j+=1
addi $t6, $t6, 1 #pattern��ַ��һ
addi $t7, $t7, 1 #str��ַ��һ
blt $t1, $a2, loopin #j<len_pattern������ѭ��

if:
bne $t1, $a2, cnt_not_plus #���j==len_pattern��cnt+=1
addi $t2, $t2, 1 #cnt+=1

cnt_not_plus:
addi $t0, $t0, 1 #i+=1
addi $t9, $t9, 1 #str[i]��ַ��һ
ble $t0, $t5, loopout #i<=len_str-len_pattern������ѭ��

move $v0, $t2 #����cntֵ
jr $ra






