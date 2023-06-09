/*
 * sound.c
 *
 *  Created on: Jul 7, 2021
 *      Author: 惠普
 */

#include "derivative.h"
#include "sound.h"

const unsigned short note[520] //记录音高
= {H1,H1,NN,H1,H1,H1,NN,H1,
M66,M66,NN,M6,M6,M6,M66,
H1,H1,NN,H1,H1,H1,NN,H1,
M66,M66,NN,M6,M6,M6,M66,//1
H3,H3,H4,H3,H2,H1,H1,
H2,H4,H4,H4,
H3,H3,H4,H3,H2,H1,H1,
H2,M66,M66,M66,//2
H3,H3,H4,H3,H2,H1,H1,
H2,H4,H4,H4,
H3,H3,H4,H3,H2,H1,H1,
H66,NN,H6,NN,H4,M3,//3
M3,M5,M5,M5,M5,M3,M3,M6,
NN,M5,NN,NN,M3,M3,
M3,M5,M5,M5,M5,M3,M3,M6,
NN,M7,NN,NN,M3,M2,M3,//4
M2,M1,NN,NN,M1,M1,M22,
M22,M2,M1,M4,M4,M3,M2,M1,
M1,M1,M2,M3,M1,M2,M3,M1,
M1,M1,M2,M1,M2,M1,M3,M3,//5
M3,M5,M5,M5,M5,NN,M3,M6,
NN,M5,NN,NN,M3,M3,
M3,M5,M5,M5,M5,M3,M3,M6,
NN,M7,NN,NN,M3,M2,M3,//6
M2,M1,NN,NN,M1,M1,M22,
M22,M2,M1,M4,M4,M3,M2,M1,
M1,M1,M2,M3,M1,M2,M3,M1,
M1,M1,M2,M1,M2,M3,M3,M3,//7
H1,M7,M6,M5,NN,M3,
M3,M3,NN,M3,M2,M3,
M2,M1,M1,M1,M1,M2,M3,M4,
M4,M3,NN,NN,M3,M3,M3,//8
H1,M7,M6,M5,NN,M3,
M3,M3,NN,M3,M3,M3,
M4,M3,M4,M5,M5,M44,M5,M666,//9
M666,M5,M666,M66,M66,M66,
M5,M5,M5,M5,
M5,M5,M5,M5,M5,M5,M4,M5,NN,H1,//10
H1,H1,NN,H2,H2,H3,
H2,H3,H2,H2,H1,M7,H1,
H1,H1,NN,M6,H1,
H3,H2,H2,H1,H1,H1,H2,H2,//11
H1,NN,H1,H1,M7,M6,M5,
M5,M3,M3,M6,M6,NN,M6,
H1,M6,H1,M6,H1,M6,M6,H3,
H3,H3,H2,H1,H2,NN,//12
H1,H1,M5,H2,H2,M5,H3,M5,
H2,H2,M5,H2,H2,H1,M7,H1,
H1,H1,NN,M6,H1,
H3,H2,H2,H2,H5,M7,M7,H1,//13
H1,NN,H1,H1,M7,M6,M5,
M5,M5,H2,H2,H2,H1,H1,NN,
H1,H1,H1,H1,
M66,M66,M66,M66,//14
H1,H1,H1,H1,
H1,H1,H1,H1,
H3,H3,H4,H3,H2,H1,H1,
H2,M66,M66,M66,//15
H3,H3,H4,H3,H2,H1,H1,
H2,H4,H4,H4,
H3,H3,H4,H3,H2,H1,H1,
H66,H6,H4,//16
H4,H4,H4,H4,
H3,H4,H5,H1,NN,NN,
0xff};
const unsigned short duration[520] //记录音长
= {0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x04,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x04,//1
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x02,0x04,0x04,
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x02,0x04,0x04,//2
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x02,0x04,0x04,
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x06,0x02,0x02,//3
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x04,0x04,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x04,0x02,0x02,0x02,0x02,//4
0x02,0x04,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,//5
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x04,0x04,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x04,0x02,0x02,0x02,0x02,//6
0x02,0x04,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,//7
0x04,0x04,0x02,0x02,0x02,0x02,
0x04,0x04,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x06,0x02,0x02,0x02,0x02,//8
0x04,0x04,0x02,0x02,0x02,0x02,
0x04,0x04,0x04,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,//9
0x02,0x02,0x02,0x02,0x04,0x04,
0x04,0x04,0x04,0x04,
0x02,0x01,0x01,0x02,0x01,0x01,0x02,0x02,0x02,0x02,//10
0x02,0x02,0x02,0x02,0x04,0x04,
0x04,0x02,0x02,0x02,0x02,0x02,0x02,
0x04,0x04,0x04,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,//11
0x04,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x04,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x04,0x02,0x02,0x04,//12
0x04,0x01,0x01,0x02,0x03,0x01,0x03,0x01,
0x04,0x01,0x01,0x02,0x02,0x02,0x02,0x02,
0x04,0x04,0x04,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,//13
0x04,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x04,0x04,0x04,0x04,
0x04,0x04,0x04,0x04,//14
0x04,0x04,0x04,0x04,
0x04,0x04,0x04,0x04,
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x02,0x04,0x04,//15
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x02,0x04,0x04,
0x06,0x01,0x01,0x02,0x02,0x02,0x02,
0x06,0x06,0x04,//16
0x04,0x04,0x04,0x04,
0x02,0x02,0x04,0x04,
0}; 

void TPM0_Init (void) //PWM初始化
{
//SIM Init
SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
//PORT Init
PORTC_PCR8 = 0x0300;
//PWM Init
TPM0_CNT = 0;
TPM0_MOD = 0x00;
TPM0_SC = (0x0008 | 0x0007); // 设置PWM时钟
TPM0_C4SC = (0x0020 | 0x0008); //设置PEM模式
TPM0_C4V = 0x00;
}

void SYSTICK_Init (void) {//时钟初始化
SYST_RVR = 2621250; //1/8 sec @ 20.97MHz
SYST_CVR = 0x00; //Clear Value
SYST_CSR = 0x07; //Enable Clock
}

void TPM0_Set (unsigned short period) //设置PWM频率
{
TPM0_MOD = period;
TPM0_C4V = period/2; //占空比，可调节音量
}


