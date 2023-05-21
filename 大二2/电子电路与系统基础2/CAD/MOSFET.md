# MOSFET

无04  2019012137  张鸿琳

## pMOSFET伏安特性曲线及其参量

采用如下电路测量pMOSFET伏安特性曲线：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic@eda 2021_10_18 21_26_13.png)

利用dc模式测量，变量选为$V_{SD}$，再利用Parametric Analysis，对变量$V_{SG}$进行$0-2V$的扫描，共五条曲线，得到下面的伏安特性曲线：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 20_19_11.png)

可以利用上面的系列曲线，求得该MOS的参量，考虑到厄利效应，电流公式如下：
$$
I_{D}=\beta_p(V_{SG}-V_{TH})^2(1+\lambda_pV_{SD})
$$
利用公式，代入$V_{SG}=2V$时的数据，得到：$\lambda_p\approx0.036457$。不妨取$V_{SG}=1V$以及$V_{SG}=2V$两个点进行计算，得到$V_{TH}\approx0.273977V$。再将求得的值代入，可以得到$\beta_p\approx1.539977\times10^{-4}$。

## 电流源设计

### 无负反馈结构

采用如下电路结构设计电流源：

![](C:\Users\惠普\Videos\Captures\B2-19MOSFETprn.pdf 和另外 1 个页面 - 个人 - Microsoft​ Edge 2021_10_14 19_26_36.png)

该MOS为pMOSFET，所以需要首先保证$V_{SG0}>V_{TH}$，才能保证MOS处于导通状态，之后需要保证电路中$V_{SD}>V_{SG0}-V_{TH}$，这样MOS就会处于恒流区，而$V_{SG0}=V_S-V_{G0}=V_{DD}-V_{G0}=V_{DD}-\frac{V_{DD}R_2}{R_1+R_2}=\frac{V_{DD}R_1}{R_1+R_2}$，而为了保证恒流源电流大小为$100\mu A$，则$\beta_n(V_{SG0}-V_{TH})^2=100\mu A$，代入上面求得的参量，可以解得$V_{SG0}\approx1.0798V$，而$V_{DD}=1.8V$，再令$R_1=5.9989k\Omega,R_2=4.0011k\Omega$，为了使MOS保持在恒流源状态，对负载电阻的阻值范围也有一定要求：$IR_L<V_{DD}-(V_{SG0}-V_{TH})$，得到$R_L<9.9418k\Omega$。（实际有所偏差，故而对理论计算得到的$R_1$和$R_2$稍有修改，实际$R_1=5.85k\Omega,R_2=4.15k\Omega$）

### 带负反馈结构

采用如下电路结构设计恒流源：

![](C:\Users\惠普\Videos\Captures\B2-19MOSFETprn.pdf 和另外 1 个页面 - 个人 - Microsoft​ Edge 2021_10_14 19_27_09.png)

不妨取$R_S=1k\Omega$，作为负反馈电阻，那么$V_{R_1}=1.0798+0.1=1.1798V$，那么可以令$R_1=6.5544k\Omega,R_2=3.4456k\Omega$，这样同样也可以实现恒流源，同时需要保证$R_L<8.9418k\Omega$。（实际采用的阻值是$R_1=6.42k\Omega,R_2=3.58k\Omega$）

## 输出电阻

仿真出不带负反馈电路的输出伏安特性曲线为：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 20_44_43.png)

由此可以计算出输出电阻为$R_A=\frac{650m-50m}{101.9527\mu-99.05837\mu}\approx207.3k\Omega$。

而对于带负反馈电路，仿真出的输出伏安特性曲线为：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 21_21_54.png)

可以计算出其输出电阻为$R_B=\frac{650m-50m}{101.76631\mu-99.435831\mu}\approx257.5k\Omega$。

由上面的数据，有$R_{B}>R_{A}$，所以显然带有负反馈机制的电路更接近理想电流源。



## 仿真中遇到的问题

在本次仿真中，出现了一些尚未解决的问题，也是导致本次作业迟交的原因。

首先，仿真时发现，利用$V_{SG}$取值较大时的伏安特性曲线（$V_{SG}$达到$3-5V$的范围）计算出的阈值电压$V_{TH}$为负值，因为计算阈值电压时，采用了公式$I_{D}=\beta_p(V_{SG}-V_{TH})^2(1+\lambda_pV_{SD})$作比的方式，所以该现象的发生可能与实际情况中$\beta_p$，$\lambda_p$这些参量会随外部条件发生变化有关。

同时，当$V_{SD}$较大时，pMOS的衬底产生明显电流，如下图：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 21_37_44.png)

其中红线为pMOS的S端电流，而绿线为B端电流，可以看到当$V_{SD}$达到$9V$左右时，其已经产生了明显的电流，猜测可能是电压过高导致形成了由源极或漏极流向衬底的电流，也就是形成了导通的二极管。
