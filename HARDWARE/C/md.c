#include "stm32f10x.h"
#include "Delay.h"

#include "md.h"
 
void MOTOR_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;  //依次接L298N  IN1,IN2,IN3,IN4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}	
//定时器4 PWM输出（CH1->PA6 CH2->PA7）**TIM_SetComparex(TIMx,xxx);//占空比函数
 void TIM4_PWM_Init(u16 arr,u16 psc)
{  

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设；————假如要AFIO复用功能模块时钟则要加上（  | RCC_APB2Periph_AFIO）
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    

   //初始化输出TIM3四个通道PWM脉冲波形的引脚(CH1->PA6 CH2->PA7)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH1、CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channe12 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM 3

}

/*
	函数功能：控制两个电机的速度和正反转
	参数说明：
		PWM1、PWM2
		范围：-7200到7200
		参数正负不同表示电机不同的转向
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

