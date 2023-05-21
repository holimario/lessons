# CAD练习

无04  2019012137  张鸿琳

## 直流电源供电

### 纯电阻

电路图如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic@eda 2021_10_4 19_44_43.png)

其中直流电压源采用方波电压源，设置上升时间为$1as$，从而尽可能地接近理想情况，起始电压设置为$0V$，输出电压设置为$1V$，从而仿真出开关闭合的瞬间。

在仿真时，取电压源上侧节点测量其对地电压，再取电源下端和电阻上端节点电流，利用ADE中自带的calculator计算功率，仿真时取trans模式。

利用上述电路仿真得到功率图像如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 19_55_54.png)

显然电阻一直保持恒定功率，并且完全消耗了电源提供的功率，将电能转化为其他形式的能量。

### 纯电容

电路图如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic _@eda 2021_10_4 19_58_35.png)

利用上述电路仿真得到功率图像如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 20_00_54.png)

可以看出，当闭合开关后，电容迅速充电，也就是一个脉冲电流后，电路中便不再有电流，也就没有能量流动了。

### 电容和电阻串联

电路图如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic@eda 2021_10_4 19_34_58.png)

仿真时的操作与前面类似，利用calculator计算功率，利用上述电路仿真得到功率图像如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 19_29_36.png)

其中绿色曲线为电源输出功率，黄色为电阻功率，红色为电容功率。可以看出开关闭合时，有较大初始电流，随着电容的不断充电，电流逐渐减小，电阻功率随之减小，而电容吸收功率先上升后下降，其曲线所围面积即为电容在充电后存储的能量。

## 交流电源供电

### 纯电阻

电路图如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic _@eda 2021_10_4 20_18_20.png)

得到的功率图像如下：

![Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 17_16_20](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 17_16_20.png)

显然，虽然输入是交流电，但是电阻一直在吸收能量，吸收功率一直为正。

### 纯电容

电路图如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic _@eda 2021_10_4 20_07_40.png)

得到的功率图像如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 17_14_57.png)

可以看出电容一半周期吸收能量，一半周期放出能量，且二者对称，所以理想电容是一个无损元件，不会消耗能量也不会放出能量。

### 电容和电阻串联

电路图如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso_ Analog Design Environment L Editing_ demo DEMO schematic _@eda 2021_10_4 20_24_10.png)

同样利用calculator功能，得到功率图像如下：

![](C:\Users\惠普\Videos\Captures\Virtuoso (R) Visualization & Analysis XL@eda 2021_10_4 17_06_37.png)

其中黄色为电源输出功率，红色为电阻吸收功率，绿色为电容吸收功率，可以看出电容在一半周期内吸收能量并在另一半周期放出能量，仍然是无损的，而电阻一直在吸收能量，不过二者加和后，由于电容放出能量的部分，电源也出现了吸收能量的部分。

