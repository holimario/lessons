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

#str的地址存在$a1，其长度存在$a0，pattern的地址存在$a3，其长度存在$a2
horspool:
##### your code here #####
move $t0, $a0 #暂存str长度
#申请动态空间
li $a0, 1024  #分配256个int的空间给table，因为英文字符共有256个
li $v0, 9  #9为syscall动态分配空间的编号
syscall
move $a0, $t0 
move $t9, $v0 #将动态数组初地址存到$t9
move $t8, $t9 #把地址暂存在$t8
move $t7, $a1 #把str地址暂存在$t7
move $t6, $a3 #把pattern地址暂存在$t6
li $t0, 0 #i=0
li $t1, 0 #j=0
li $t2, 0 #cnt=0
li $t3, -1 #用于给table设初值
li $t4, 256 #存储table大小

#给table设初值
setinitial:
sb $t3, 0($t8) #table[i]=-1
addi $t8, $t8, 4 #table地址加一
addi $t0, $t0, 1 #i+=1 
blt $t0, $t4, setinitial #如果i<256，继续循环

#生成table
li $t0, 0 #i=0

gettable:   
add $t8, $t0, $zero #暂存i
add $t8, $t6, $t8 #pattern[i]的地址
lb $t5, 0($t8) #pattern[i]
sll $t5, $t5, 2 #乘以4
add $t8, $t9, $t5 #table地址为pattern[i]+初始地址
sw $t0, 0($t8) #table[pattern[i]]=i
addi $t0, $t0, 1 #i+=1 
blt $t0, $a2, gettable #如果i<len_pattern，继续循环

#开始进行匹配
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
bne $t3, $t4, if #跳出该循环
addi $t1, $t1, 1 #j+=1
j loopin #满足条件，继续循环

if:
bne $t1, $a2, cnt_not_plus
addi $t2, $t2, 1 #cnt+=1

cnt_not_plus:
sub $t3, $a2, $t1 #len_pattern-j
subi $t3, $t3, 1 #len_pattern-1-j
add $t4, $a1, $t0 #str[i]的地址
lb $t4, 0($t4) #str[i]
sll $t4, $t4, 2 #乘以4
add $t4, $t9, $t4 #table[str[i]]的地址
lw $t4, 0($t4) #table[str[i]]
blt $t3, $t4, else #若table[str[i]]+1>len_pattern-1-j，则执行else内容
add $t0, $a2, $t0 #i+=len_pattern
sub $t0, $t0, $t4 #i-=table[str[i]]
subi $t0, $t0, 1 #i-=1
j loopout #继续循环

else:
addi $t0, $t0, 1 #i+=1
j loopout #继续循环

#返回cnt
end:
move $v0, $t2
jr $ra
