#include "DJ.h"
#include "delay.h"

void TIM2_CH2_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//要开启复用功能的时钟才能重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE); 
	
	//TIM3部分重映射
	/*
	*查看数据手册，引脚的定时器通道是完全映射，还是部分映射
	*二者调用参数不相同
	*完全映射 ：GPIO_FullRemap_TIM4
	*部分映射 ：GPIO_PartialRemap_TIM4
	*/
	
	//设置该引脚为复用输出功能
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//重装载值 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//预分频值 
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1; //时钟分频1、2、4分频	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	 
	 
	//初始化输出比较参数
	
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
	TIM_OC2Init(TIM2,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	//使能预装载寄存器
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

	//使能定时器
	TIM_Cmd(TIM2,ENABLE);
}

void DJRunzuo(int t)
{
	u16  delay_time = t;		     
	 delay_ms(delay_time);
		TIM_SetCompare2(TIM2, 1750); //对应180度

}
void DJRunyou(int t)
{
		u16  delay_time = t;
  delay_ms(delay_time);
	TIM_SetCompare2(TIM2, 1950);//对应0度

}
void DJRuncs(int t)
{
		u16  delay_time = t;
  delay_ms(delay_time);
	TIM_SetCompare2(TIM2, 1850);//对应90度

}



 
