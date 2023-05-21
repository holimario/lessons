# 用FFT分析信号频谱

无04  2019012137  张鸿琳

首先搭建如下电路：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic _@eda 2021_10_10 21_21_35.png)

其中电压源为$0-5V$之间变化，周期为$1ms$的方波，电阻阻值恒定为$1k\Omega$，电容值为变量，之后测量电容上侧电势表示电容两端电压$V_C$，再测量电阻两端电势之差表示电阻两端电压$V_R$，分别将电容值设定为$10^{-9},10^{-8},10^{-7},10^{-6},10^{-5},10^{-4},10^{-3}F$，观察电阻和电容两端电压的时域波形，下面以电容值取$10^{-3}F$的时域波形为例，得到稳定时电阻两端波形如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_22_12.png)

可见其中基本保留了电压源中的交流分量，是峰峰值为$5V$、频率为$1kHz$的方波，而电容两端电压波形如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_21_19.png)

经过一段时间后，电容两端电压基本稳定为直流电压$2.5V$，而这也正是电压源中的直流分量，这体现出了该电路的滤波作用，低频信号主要被加载在电容上，而高频信号则主要被加载在电阻上，下面利用calculator中的dft函数对不同电容值的电路稳定后的电阻和电容两端信号波形进行频域分析，随着电容值逐渐减小，电容两端电压频谱特征如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_32_05.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_39_42.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_42_15.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_45_31.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 18_05_29.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 19_24_27.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 19_27_32.png)

随着电容值逐渐减小，电阻两端电压频谱特征如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_31_59.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_39_48.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_42_08.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 17_45_20.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 18_05_36.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 19_24_34.png)

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 19_27_39.png)

由上图可以看出，随着电容减小，电容两端电压中较高频率的组分逐渐增加，而电阻两端电压中较低频率的组分逐渐减少，也就是滤波的分界点发生了偏移。

考察时间常数$\tau$对应的频率$f_0=\frac{1}{2\pi RC}$，当$C=1mF$时，$f_0\approx0.159Hz$，此时由图像也可以看出，$f<f_0$的组分几乎全部被加到电容上，而$f>f_0$的组分，也就是交流电的组分几乎全部被加到了电阻上。而当电容再减小一个数量级，此时$f_0\approx1.59Hz$，此时电容两端已经出现了一定$1Hz$的交流分量，将纵坐标轴换为20dB坐标更为清晰，当$C=100\mu F$，电阻两端电压频谱(dB纵坐标)如下：（存在一些噪声）

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 20_26_32.png)

当$C=100\mu F$，电容两端电压频谱(dB纵坐标)如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 20_26_39.png)

可见电容分压中已经有较为明显的$1Hz$组分。再将电容降低一个数量级，即$C=10\mu F$时，此时$f_0\approx 15.9Hz$，电阻两端电压频谱(dB纵坐标)如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 20_33_42.png)

当$C=10\mu F$，电容两端电压频谱(dB纵坐标)如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 20_33_37.png)

可以比较明显的看出高频和低频的分界点的右移，下图将所有电容值对应的(dB纵坐标)电容两端电压频谱放在一起，更为清晰地体现了分界点的变化：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 20_53_17 (2).png)

同样，有不同电容值对应的电阻电压频谱(dB纵轴)对比：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_11 21_02_09.png)

对比上面二图，可以看出$f_0=\frac{1}{2\pi RC}$确实为低频与高频的分界点，决定了上述电路的滤波特性。
