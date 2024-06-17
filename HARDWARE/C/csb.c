#include "csb.h"
#include "delay.h"
#include "stdio.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stdio.h"

void CSB_Init(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//����GPIOBʱ�� 
		/*Trig�˿�����*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;    // ��Ӧtrig����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
/*Echo�˿�����*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;    // ��Ӧecho����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
  trig = 0;  //��ʼ�������Ϊ0
}	
/*�������������������
ԭ��������ģ�鷢��˷���һ��10us���ϵ����壬
�������������ģ���ѭ������8��40KHz�������źţ�
���ն˽��յ��������������Ϊ�ߵ�ƽ�����ߵ�ƽʱ��Ϳ����������
*/
	float CSB_Run(void)
	{
		 trig = 1;
		 delay_us(10);
		 trig = 0;
		
		while(echo == 0);
		TIM_Cmd(TIM3,ENABLE);
		while(echo == 1);
		TIM_Cmd(TIM3,DISABLE);
		return (Time.us*340)/2000.0;
	//			Time.us=0;
	//		  printf("%.3f\r\n",Distance);//��ӡ���볤��			
	}
	Times Time;			//����ʱ��ṹ��

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
//������
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
       
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
      
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =	psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
       
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	    
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


//	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx	
	TIM_Cmd(TIM3, DISABLE);		//ʧ��

	/*ʱ�������ʼ��*/
	Time.us = 0;
	Time.ms = 0;
	Time.s = 0;
	Time.min = 0;
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�,10us��һ���ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־
			Time.us++;
		}
}
	


	
	
	
