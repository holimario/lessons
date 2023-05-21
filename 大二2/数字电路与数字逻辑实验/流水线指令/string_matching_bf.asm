.data
str: .space 512     #存储字符串
pattern: .space 512 #存储模式串
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
li $a2, 1 #每次读入一个字节
li $s0, 0 #len_str = 0
read_str_entry:
slti $t0, $s0, 512 #如果读入数据充满全部空间则跳出
beqz $t0, read_str_exit
li $v0, 14 #read file syscall index
syscall
lb $t0, 0($a1)
addi $t1, $zero, '\n' #读到换行则退出
beq $t0, $t1, read_str_exit
addi $a1, $a1, 1 #地址增加1位
addi $s0, $s0, 1 #记录总共读入了多少字节
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
beq $t0, $t1, read_pattern_exit #读到换行则退出
addi $a1, $a1, 1 #地址增加1位
addi $s1, $s1, 1 #记录总共读入了多少字节
j read_pattern_entry
read_pattern_exit:

#close file
li $v0, 16 #close file syscall index
syscall

#call brute_force
move $a0, $s0
la $a1, str      #str的地址存在$a1
move $a2, $s1
la $a3, pattern  #pattern的地址存在$a3
jal brute_force

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall

#str的地址存在$a1，其长度存在$a0，pattern的地址存在$a3，其长度存在$a2
brute_force:
##### your code here #####
li $t0, 0 #i=0
li $t2, 0 #cnt=0
sub $t5, $a0, $a2 #$t5存储len_str-len_pattern的值
move $t9, $a1 #把str地址存在$t9，防止改变$a1
move $t8, $a3 #把pattern地址存在$t8，防止改变$a3

loopout: #外循环，对i循环
li $t1, 0 #j=0
move $t7, $t9 #把str[i]地址暂存在$t7
move $t6, $t8 #把pattern地址暂存在$t6

loopin: #内循环，对j循环
lb $t3, 0($t7) #把str[i+j]存在$t3
lb $t4, 0($t6) #把pattern[j]存在$t4
bne $t4, $t3, if #判断str[i+j]与pattern[j]是否相等，不相等则跳出循环到skip
addi $t1, $t1, 1 #j+=1
addi $t6, $t6, 1 #pattern地址加一
addi $t7, $t7, 1 #str地址加一
blt $t1, $a2, loopin #j<len_pattern，继续循环

if:
bne $t1, $a2, cnt_not_plus #如果j==len_pattern，cnt+=1
addi $t2, $t2, 1 #cnt+=1

cnt_not_plus:
addi $t0, $t0, 1 #i+=1
addi $t9, $t9, 1 #str[i]地址加一
ble $t0, $t5, loopout #i<=len_str-len_pattern，继续循环

move $v0, $t2 #返回cnt值
jr $ra






