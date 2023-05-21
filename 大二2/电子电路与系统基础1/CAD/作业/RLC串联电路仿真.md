# RLC串联电路仿真

无04  2019012137  张鸿琳

对下面电路进行分析：

![](C:\Users\惠普\Videos\Captures\B1-09RLCprn.pdf 和另外 1 个页面 - 个人 - Microsoft​ Edge 2021_11_15 17_49_47.png)

可知传递函数为：
$$
H(s)=\frac{1}{s^2LC+sRC+1}=\frac{\omega_0^2}{s^2+2\xi\omega_0s+\omega_0^2}
$$
自由震荡频率为$\omega_0=\frac{1}{\sqrt{LC}}$，阻尼系数为$\xi=\frac{1}{2}R\sqrt{\frac{C}{L}}$。

首先研究其幅频渐进特性，可以看出$|H(j\omega)|=\frac{1}{\sqrt{1+(4\xi^2-2)(\omega/\omega_0)^2+(\omega/\omega_0)^4}}$，当$\omega$较小时，$ |H(j\omega)|\approx1$，当$\xi<\frac{1}{\sqrt{2}}$时，$|H(j\omega)|$存在最大值，这样在$\omega=\sqrt{(1-2\xi^2)\omega_0}$存在一个极大值点，极大值为$|H(j\omega)|=\frac{1}{2\xi\sqrt{1-\xi^2}}$，而后当频率进一步增大，$|H(j\omega)|\approx \frac{1}{(\omega/\omega_0)^2}$，在伯德图上近似表现为斜率为$-40$的直线。当$\xi\ge\frac{1}{\sqrt{2}}$时，将不会再出现极大值点，幅频特性可以近似用两条相交直线表示。而当$\xi$进一步增大，阻尼系数的影响进一步扩大，会使转折点明显左移，同时也会导致$\omega$较大时的负斜率直线不再平直，会出现一段$|H(j\omega)|\approx\frac{1}{(\omega/\omega_0)\sqrt{4\xi^2-2}}$的区域，在伯德图上表现为斜率近似为$-20$的直线，同时阻尼系数越大，该段直线的跨度会越大。而更精准的近似可以通过观察$H(j\omega)$的零点和极点分布得到。

再分析相频特性有$\angle H(j\omega)=-\arctan(\frac{2\xi\omega_0\omega}{\omega_0^2-\omega^2})$，当$\omega$较小时，显然$\angle H(j\omega)\approx0$。而根据$H(jw)$式子，利用其极点和零点分布进行近似，可以得到，存在两个极点$\omega_1=2\xi\omega_0+2\omega_0\sqrt{\xi^2-1}$，$\omega_2=2\xi\omega_0-2\omega_0\sqrt{\xi^2-1}$，每遇到一个极点，相位下降$90\degree$。当$\xi<1$时，相频曲线在$\omega_0$附近直接下降$180\degree$，而当$\xi>1$时，存在两个实极点，那么会出现一段近似平台，范围是$4\omega_0\sqrt{\xi^2-1}$，随着$\xi$增大而扩大，但是$\angle H(j\omega_0)=-90\degree$始终成立。同时随着$\xi$的增大，$\omega_2$不断减小，$\omega_1$不断增大，也就是相变范围也不断扩大。

假设固定$L$和$C$，可以通过调节$R$的大小确定阻尼系数。本次仿真取$L=1mH$，$C=1mF$，变化电阻的大小来调节阻尼系数，当阻尼系数$\xi$分别为$0.01,0.1,0.5,0.707,0.866,1,2,10,50,100$时的伯德图如下（虚线为相频特性，实线为幅频特性）：

![LTspice XVII - [Draft6.raw] 2021_11_15 20_20_27](C:\Users\惠普\Videos\Captures\LTspice XVII - [Draft6.raw] 2021_11_15 20_20_27.png)

![LTspice XVII - [Draft6.raw] 2021_11_15 20_20_48](C:\Users\惠普\Videos\Captures\LTspice XVII - [Draft6.raw] 2021_11_15 20_20_48.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_21_04.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_21_18.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_21_48.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_22_06.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_22_17.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_22_26.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_22_39.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.asc 2021_11_15 20_22_49.png)

可以看出伯德图与前面的分析基本一致。

下面再同样的条件下，测试输出电压的时域特性，输入电压设定为单位阶跃电压，当调节电阻阻值，使得阻尼系数分别为$0.01,0.1,0.5,0.707,0.866,1,2,10,50,100$时，得到的输出电压时域波形如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_04_34.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_05_01.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_05_26.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_05_58.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_06_29.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_06_59.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_07_09.png)

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft6.raw 2021_11_15 22_07_26.png)

联系课上所学，可知当$\xi<1$时，为弱阻尼，会出现震荡逐渐消失的现象，前5幅图像可以看到该现象，且随着阻尼系数不断增大，达到平衡的时间不断减小，耗时近似与$\xi$成反比。而当$\xi=1$时，达到临界阻尼，不再出现震荡现象，且会以最快的速度达到平衡，而后随着$\xi$进一步增大，进入过阻尼状态，达到平衡的时间随着阻尼系数的增大而不断增加，达到平衡耗时近似为$\frac{1}{(\xi-\sqrt{\xi^2-1})\omega_0}$。