/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "OLED.h"
#include "handle.h"
#include "sound.h"

unsigned short pNote=0,nDuration=0;//��¼���ŵ�������ʣ������
extern unsigned char state[128][8];//����ΪOLED.c�е��ⲿ������Ҳ���ǵ����������dot����Ϣ�洢��ά����
extern const unsigned short note[520];//����Ϊsound.c�е��ⲿ��������¼����
extern const unsigned short duration[520];//����Ϊsound.c�е��ⲿ��������¼����
extern int all;//����Ϊhandle.c�е��ⲿ��������¼�������ڲ����Ŀ������
extern unsigned char pos;//����Ϊhandle.c�е��ⲿ��������¼�������ڲ����Ŀ����̬
extern int next;//����Ϊhandle.c�е��ⲿ��������¼��һ��ˢ�µĿ������
extern char str[5];//����Ϊhandle.c�е��ⲿ���������ڷ�������ʾ
extern unsigned char sc;//����Ϊhandle.c�е��ⲿ��������¼����
extern unsigned char now[4][2];//����Ϊhandle.c�е��ⲿ��������¼�����ƶ��Ŀ���ĸ���λ���ӵ����½�λ�ã�4����ÿ�ֿ鶼�����ĸ���λ���ӹ��ɣ�2����λ�������½ǵ�����(x,y)
extern unsigned char test[4][2];//����Ϊhandle.c�е��ⲿ��������¼ģ��ĳ�ֱ仯�����ĸ���λ���ӵ����½�λ�ã�4����ÿ�ֿ鶼�����ĸ���λ���ӹ��ɣ�2����λ�������½ǵ�����(x,y)
extern unsigned char lightened[64][80];//����Ϊhandle.c�е��ⲿ��������¼�����Ѿ�����λ�ã���Ӧ��Ϸ�����64*80�����ص�
extern unsigned char high;//����Ϊhandle.c�е��ⲿ��������¼ĳһ�����䵽�ײ�����ײ�λ�ã��������Ƿ������ȥ
extern unsigned char low;//����Ϊhandle.c�е��ⲿ��������¼ĳһ�����䵽�ײ����䶥��λ�ã��������Ƿ������ȥ
extern unsigned char min;//����Ϊhandle.c�е��ⲿ��������¼���ڵ������ѻ�����ߵ�


void SysTick_Handler (void) {//ʱ���жϺ��������ڲ�������
unsigned int i;
if(nDuration==0) {
if(note[pNote]==0xff) pNote=0;//���ò����µ���
TPM0_Set ((unsigned short)( note[pNote])); 
nDuration = duration[pNote];
pNote++;
} 
nDuration--; 
i = SYST_CSR; //�����������־λ
}

void PORTA_IRQHandler(){//�����жϺ������ж��ж�Դ����ִ����Ӧ�Ĳ���
	if((GPIOA_PDIR & 0b1000000000000)==0)//��ʱ����ת
	{
		if(testlrotate()==1)
		{
			lrotate();
		}

	}
	else if((GPIOA_PDIR & 0b10000000000000)==0)//˳ʱ����ת
	{
		if(testrrotate()==1)
		{
			rrotate();
		}
	}
	else if((GPIOA_PDIR & 0b100000000000000)==0)//����ƽ��һ����
	{
		if(testleft()==1)
		{
			left();
		}
	}
	else if((GPIOA_PDIR & 0b10000000000000000)==0)//����ƽ��һ����
	{
		if(testright()==1)
		{
			right();
		}
	}
	else if((GPIOA_PDIR & 0b1000000000000000)==0)//��������ƽ��
		{
		if(testmove()==1)
		{
			move();
		}
		if(testmove()==1)
		{
			move();
		}
		if(testmove()==1)
		{
			move();
		}
		if(testmove()==1)
		{
			move();
		}
		}
	delay();//ͨ����ʱ���ⰴ�����
	PORTA_PCR12|=0x01000000;//��־λ���
	PORTA_PCR13|=0x01000000;//��־λ���
	PORTA_PCR14|=0x01000000;//��־λ���
	PORTA_PCR15|=0x01000000;//��־λ���
	PORTA_PCR16|=0x01000000;//��־λ���
}



int main(void) {
	Inintstate();//state��ʼ��
	Initlight();//lightened��ʼ��
	
	SIM_SCGC5|=((1<<11)|(1<<9));// ����ģ��PORTCʱ��
	
	asm("CPSIE i");//����ȫ���ж�
	NVIC_ISER|=0x40000000;//����PORTA�ж�
	
	PORTA_PCR12=0x000A0102;//�������½������ж�
	PORTA_PCR12|=0x01000000;//������־λ
	
	PORTA_PCR13=0x000A0102;//����Ҽ��½������ж�
	PORTA_PCR13|=0x01000000;//������־λ
	
	PORTA_PCR14=0x000A0102;//�Ҳ�����½������ж�
	PORTA_PCR14|=0x01000000;//������־λ
		
	PORTA_PCR15=0x000A0102;//�Ҳ�����½������ж�
	PORTA_PCR15|=0x01000000;//������־λ
	
	PORTA_PCR16=0x000A0102;//�Ҳ��Ҽ��½������ж�
	PORTA_PCR16|=0x01000000;//������־λ
	
	// ָ������GPIO
	PORTC_PCR0 = 0x0100;
	PORTC_PCR3 = 0x0100;
	
	GPIOC_PDDR |= 0x09;
	GPIOC_PDOR &= (~0x09);
	
	
	OLED_Init();//OLED��ʼ��
	
	
	OLED_Clr();//����
	
	TPM0_Init();
	SYSTICK_Init();
	
	//���ָ���
	OLED_W_Dot(0,80,0b11111111);
	OLED_W_Dot(8,80,0b11111111);
	OLED_W_Dot(16,80,0b11111111);
	OLED_W_Dot(24,80,0b11111111);
	OLED_W_Dot(32,80,0b11111111);
	OLED_W_Dot(40,80,0b11111111);
	OLED_W_Dot(48,80,0b11111111);
	OLED_W_Dot(56,80,0b11111111);
	OLED_W_Dot(61,80,0b11111111);
	
	OLED_W_Str(0,82,"score:");
	addscore();
	OLED_W_Str(4,85,"next:");
	int i;
	next=(rand()%7)+1;//������ɿ�
	for(;;)
	{
		all=next;
		next=(rand()%7)+1;
		getnext();//������һ�������Ϣ
		lighten(all);//�����µ�����Ŀ�
		move();
		move();
		for(;testmove()==1;)//��û��ײ������Ŀ�֮ǰ���������ƶ�
		{
			move();
			delay();
		}
		for(i=0;i<=3;i++)//��¼������Ӧ�Ŀ����Ϣ
		{
			lightened[now[i][0]][now[i][1]]=1;
			lightened[now[i][0]-1][now[i][1]]=1;
			lightened[now[i][0]][now[i][1]+1]=1;
			lightened[now[i][0]-1][now[i][1]+1]=1;
		}
		if(min>mmin(now[0][0],now[1][0],now[2][0],now[3][0]))//���������ѻ�����ߴ���Ϣ
		{
			min=mmin(now[0][0],now[0][0],now[2][0],now[3][0]);
		}
		high=mmax(now[0][0],now[1][0],now[2][0],now[3][0]);//���¸ո����µĿ�ķ�Χ��Ϣ�������ж��ͼ���÷�
		low=mmin(now[0][0],now[1][0],now[2][0],now[3][0]);//���¸ո����µĿ�ķ�Χ��Ϣ�������ж��ͼ���÷�
		score();//����÷ֲ�����
		lose();//�ж��Ƿ����
	}
}



