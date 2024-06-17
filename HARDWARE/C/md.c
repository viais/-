#include "stm32f10x.h"
#include "Delay.h"

#include "md.h"
 
void MOTOR_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;  //���ν�L298N  IN1,IN2,IN3,IN4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}	
//��ʱ��4 PWM�����CH1->PA6 CH2->PA7��**TIM_SetComparex(TIMx,xxx);//ռ�ձȺ���
 void TIM4_PWM_Init(u16 arr,u16 psc)
{  

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO���裻������������ҪAFIO���ù���ģ��ʱ����Ҫ���ϣ�  | RCC_APB2Periph_AFIO��
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    

   //��ʼ�����TIM3�ĸ�ͨ��PWM���岨�ε�����(CH1->PA6 CH2->PA7)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH1��CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channe12 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM 3

}

/*
	�������ܣ���������������ٶȺ�����ת
	����˵����
		PWM1��PWM2
		��Χ��-7200��7200
		����������ͬ��ʾ�����ͬ��ת��
*/
void Set_Car_Speed(int PWM1,int PWM2)
{
	if(PWM1>0)
	{
		TIM_SetCompare1(TIM4,PWM1);
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	}
	
	if(PWM2>0)
	{
		TIM_SetCompare2(TIM4,PWM2);
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	}
	
	
	if(PWM1<0)
	{
		TIM_SetCompare1(TIM4,-PWM1);
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	}
	
	if(PWM2<0)
	{
		TIM_SetCompare2(TIM4,-PWM2);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	}
	
	
	if(PWM1==0)
	{
		TIM_SetCompare1(TIM4,0);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	}
	
	if(PWM2==0)
	{
		TIM_SetCompare2(TIM4,0);
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	}
}

