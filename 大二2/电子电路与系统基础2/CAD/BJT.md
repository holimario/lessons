# BJT仿真

无04  2019012137  张鸿琳

首先搭建如下仿真电路：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Schematic Editor L Editing_ demo DEMO schematic _@eda 2021_10_18 13_13_05.png)

之后利用dc仿真模式，对$V_{IN}$进行扫描，得到输入输出转移特性曲线。

从理论角度分析，当$V_{IN}$较小时，即$V_{IN}<V_{on}=0.7V$，未能达到二极管的正向导通电压时，此时BE结反偏，BC结也反偏，相当于开路，此时$V_{out}=VCC=5V$，BJT处于截止区。此后随着$V_{IN}$增大，BE结正偏导通，而BC结反偏，故而BJT进入有源区，此时$V_{out}=VCC-i_C\cdot R_C=VCC-\beta i_BR$，而$i_B$随着$V_{IN}$近似指数增长，故而输出电压迅速下降，而与此同时$V_{BE}$变化较为缓慢，基本略大于$V_{on}$，当$V_{C}= V_{BE}-V_{on}$时，其BE结正偏，BC结也正偏，即BJT进入饱和区，之后由于$V_{IN}$大部分电压加载于$R_B$上，$V_{BE}$基本仍为$V_{on}$，故而此时BJT近似为恒压源，电压保持在$V_{BE}-V_{on}$左右。

而通过cadence得到仿真特性曲线如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 14_54_53.png)

根据上面的分析，可知图像中左侧平台，BJT位于截止区，突然下降的部分，BJT位于有源区，而右侧较低的平台，BJT位于饱和区。

为了验证上面理论分析的结果，取$V_{IN}=V_{on}\approx 0.7V$和$V=V_{BE}$两根线，观察其与转移特性曲线的关系。得到下图：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 16_59_29.png)

其中白色虚线对应$V_{IN}=0.7V$，与输出电压（绿线）的交点为第一个临界点，而$V_{BE}$与输出电压在第二个临界点处也相差约为$0.7V$，即$V_{on}$，这说明上面的分析和实际仿真结果相符得很好。

$R_B$的作用是分压，从而放缓$V_{IN}$对$V_{BE}$的影响，使得第二个平台较为平缓，相当于BJT可以近似为恒压源。假如没有$R_B$，那么第二个平台将不再平缓，并且会随着$V_{IN}$近似线性变化，从而使得该功能电路的适用电压范围大大降低。仿真结果如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_18 17_06_40.png)