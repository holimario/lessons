# MOS开关仿真

无04  2019012137  张鸿琳

（本次仿真实验不太顺利，主要是对CMOS开关的衬底的连接方式有较大疑问，同时由于情况太多，所以分析不是很充分，对一些现象没有很好地阐释）

## 开关静态传输特性

### NMOS开关

#### 电阻负载

此时，将NMOS的衬底接到电路中的地，负载电阻阻值为$1k\Omega$，将开关控制电压$V_C$置为$10V$，此后对输入方波的幅度进行$1-5V$的扫描，可以得到输出波形如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 20_36_24.png)

可见随着输入方波电压幅值的增大，输出波形也为方波，但是幅值有所减小，可以分析知，是由于NMOS处于欧姆区，故而近似为一个电阻，有一定分压。

#### 电感负载

将负载替换为$C=1nF$的电容，其他条件不变，再次进行测试，可以得到输出波形如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 20_47_31.png)

可以看到输出波形基本和输入波形一致，幅度也没有什么变化，这是因为选取的电容较小，充电较快，同时排除了NMOS的等效电阻的分压效应。

### PMOS开关

由于PMOS与NMOS基本相互对称，所以可以预估其实验现象与上面NMOS实验现象基本一致。

#### 电阻负载

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 20_55_11.png)

与NMOS现象基本一致，由于PMOS位于欧姆区，所以存在一定程度的分压，导致输出波形幅值降低。

#### 电感负载

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 20_53_01.png)

与NMOS现象一致。

### CMOS开关

#### 电阻负载

![Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 21_16_31](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 21_16_31.png)

同样的条件下，可以看到利用CMOS开关时，输出电压幅值有明显上升，这是因为相当于NMOS等效电阻与PMOS等效电阻相互并联，总体等效电阻下降，从而使得负载电阻分压增大，相比于NMOS和PMOS开关，CMOS开关更为理想。

#### 电感负载

![Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 21_21_05](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_28 21_21_05.png)

负载为电容时，效果并不明显，但是这是因为电容取值太小，分析可知，由于CMOS等效电阻小于NMOS和PMOS开关，所以充电、放电时间更短，输出波形会更接近理想方波，故而电容为负载时，仍然是CMOS更接近理想开关。

## 开关动态特性

由于此处情况太多，仿真比较麻烦且效率较低，故而先进行理论分析，再对其中现象显著的情况进行仿真展示。

CMOS中同时具有NMOS和PMOS，如下图：

![](C:\Users\惠普\Videos\Captures\B2-22数字门prn.pdf 和另外 1 个页面 - 个人 - Microsoft​ Edge 2021_10_29 19_56_16 (2).png)

CMOS中的PMOS的衬底接到高电位端，NMOS衬底接到低电位端，这样，当C为高电位时，PMOS和NMOS都存在沟道，但是随着外加电压$V$的增大，对于PMOS来说$V_{SD}$逐渐增大，而对于NMOS$V_{DS}$也逐渐增大，故而二者都导通，且等效电阻更小，而当C为低电位时，二者都截止，故而为开路。

当开关为CMOS，负载为电阻$R=1k\Omega$时，电压源为直流电压$V_{dc}=5V$，随着控制方波，得到的输出电压如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft1.raw 2021_10_29 21_42_47.png)

而将CMOS替换为NMOS后，波形如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft1.asc 2021_10_29 21_58_12.png)

可见NMOS的等效电阻更大，PMOS也是类似情况，故而CMOS更接近理想开关。

再将负载替换为电容，也可发现NMOS和PMOS得到波形相较于CMOS略有起伏，这也是由于等效电阻较大，导致充电较慢。

下面再测试利用CMOS开关时，负载为电阻（$R=1k\Omega$），而电压源为正弦波（$f=100Hz$,$A=2V$）的情况：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - [Draft1.raw] 2021_10_29 22_24_11.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - [Draft1.raw] 2021_10_29 22_25_43.png)



与之对应地，将开关换为NMOS，那么得到输出波形为：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - [Draft1.raw] 2021_10_29 22_29_05.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - [Draft1.raw] 2021_10_29 22_28_57.png)

可以看到在输出振幅有所下降的同时，正弦波的中心位置也有所偏移，这也说明CMOS更接近理想开关。而将NMOS替换为PMOS的情况，以及负载替换为电容的情况也相仿。

对开关时间的分析，也表明CMOS开关更为理想。
