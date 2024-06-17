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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//开启GPIOB时钟 
		/*Trig端口配置*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;    // 对应trig引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
/*Echo端口配置*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;    // 对应echo引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
  trig = 0;  //初始化发射端为0
}	
/*超声波测距运行主函数
原理：超声波模块发射端发送一个10us以上的脉冲，
发射脉冲后超声波模块会循环发射8个40KHz的脉冲信号，
接收端接收到超声波脉冲后会变为高电平，检测高电平时间就可以算出距离
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
	//		  printf("%.3f\r\n",Distance);//打印距离长度			
	}
	Times Time;			//定义时间结构体

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
//超声波
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
       
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
      
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =	psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
       
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	    
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


//	TIM_Cmd(TIM3, ENABLE);  //使能TIMx	
	TIM_Cmd(TIM3, DISABLE);		//失能

	/*时间参数初始化*/
	Time.us = 0;
	Time.ms = 0;
	Time.s = 0;
	Time.min = 0;
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断,10us进一次中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志
			Time.us++;
		}
}
	


	
	
	
