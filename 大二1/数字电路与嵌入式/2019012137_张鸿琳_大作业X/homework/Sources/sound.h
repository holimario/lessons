/*
 * sound.h
 *
 *  Created on: Jul 7, 2021
 *      Author: ª›∆’
 */

#ifndef SOUND_H_
#define SOUND_H_


#define PWM0_CLK_FREQ 164*1000
#define L1 M1*2 //µÕ∞À∂»
#define L2 M2*2
#define L3 M3*2
#define L4 M4*2
#define L5 M5*2
#define L6 M6*2
#define L7 M7*2
#define M1 (unsigned short)(PWM0_CLK_FREQ/523)
#define M2 (unsigned short)(PWM0_CLK_FREQ/587)
#define M3 (unsigned short)(PWM0_CLK_FREQ/659)
#define M4 (unsigned short)(PWM0_CLK_FREQ/698)
#define M5 (unsigned short)(PWM0_CLK_FREQ/784)
#define M6 (unsigned short)(PWM0_CLK_FREQ/880)
#define M7 (unsigned short)(PWM0_CLK_FREQ/988)
#define H1 M1/2 //∏ﬂ∞À∂»
#define H2 M2/2
#define H3 M3/2
#define H4 M4/2
#define H5 M5/2
#define H6 M6/2
#define H7 M7/2
#define NN 0 //–›÷π∑˚
#define M66 M6*0.9438743//M6…˝∞Î“Ù
#define M22 M2*0.9438743//M2…˝∞Î“Ù
#define M44 M4*0.9438743//M4…˝∞Î“Ù
#define M666 M6*1.059463094//M6Ωµ∞Î“Ù
#define H66 H6*0.9438743//H6…˝∞Î“Ù


void TPM0_Init (void);//PWM≥ı ºªØ
void SYSTICK_Init (void);// ±÷”≥ı ºªØ
void TPM0_Set (unsigned short period);//…Ë÷√PWM∆µ¬ 



#endif /* SOUND_H_ */
