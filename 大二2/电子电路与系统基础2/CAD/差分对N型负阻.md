# 差分对构造的N型负阻

无04  2019012137  张鸿琳

对下面电路进行仿真：

![](C:\Users\惠普\Videos\Captures\B2-28正反馈prn.pdf 和另外 4 个页面 - 个人 - Microsoft​ Edge 2021_12_9 17_36_56.png)

搭建如下电路进行仿真：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft14.asc 2021_12_9 17_48_57.png)

令$I_{EE}=2A$，通过加压求流，得到图像如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft14.raw 2021_12_9 18_16_43.png)

可见确实在图像中部出现了负阻区，是N型负阻。

下面将该N型负阻与LC谐振腔并联，仿真电路如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft14.asc 2021_12_9 18_09_10.png)

取电容容值为$1mF$，电感值为$1mH$，直流电压为$V_{CC}=1V$，得到电容两端电压变化如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft14.asc 2021_12_9 18_08_58.png)

可见经过一段时间的震荡，达到平衡时，电容两端电压基本为正弦波形式。

再将电容容值改为$1\mu A$，得到电容两端电压波形图如下：

![](C:\Users\惠普\Videos\Captures\LTspice XVII - Draft14.raw 2021_12_9 18_12_52.png)

可见平衡时的波形已经偏离了正弦波，是张弛振荡。
