#include "stm32f10x.h"
#include "delay.h"
#include "xj.h"
#include "md.h"
#include "stdlib.h"
void xunkun_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB的时钟
		
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入模式
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0,PB1,PB3,PB4,PB5管脚的初始化
	  
//	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭STM32f103c8t6的JTAGD功能，使PB3和PB4用作普通的IO管脚//必须开启复用功能的时钟才能关闭该功能
}

//void md_xj(){
//	int SZLK=0,j=0;
//		switch(TC){                         //黑为1，值越小速度越快   

//					case 110:
//						Set_Car_Speed(600,600); break;   //直行	
//					case 1100:
//						
//						Set_Car_Speed(550,450); break;   //小左转
//					case 100:
//						Set_Car_Speed(550,450); break;   //小左转
//					case 1000:
//						
//						Set_Car_Speed(500,400); break;   //大左转					
//					case 11:
//						
//            Set_Car_Speed(450,550); break;   //小右转
//					case 10:
//						
//            Set_Car_Speed(450,550); break;   //小右转
//					case 1:
//					
//            Set_Car_Speed(400,550); break;   //大右转
//					case 1110:  
//			    	md_left();break;//左转
//		      case 111:
//			    	md_right();break;//右转
//					
//				 case 0:        //十字路口
//	      	 ++SZLK;		 
//				 if(SZLK<3)
//				 {
//				   md_run(2600);
//					 
//				 }  
//         	else
//					{
//					md_stop();
//						SZLK=3;
//					}	break;
//					
//		     case 1111:     //空白路口
//			 ++j;
//			if(j==1){
//				 md_run(2600);
//			   j=2; 
//		        	}   
//      else if(j>1)
//			{
//			  md_stop();
//				j=1;
//			} break;
//			
//}
		
//}
void md_left()//2600
{
	
	Set_Car_Speed(-600,600);   //左转		
  delay_ms(2600);
	Set_Car_Speed(0,0);      //停止
	
}

void md_right(){
	Set_Car_Speed(600,-600);  //右转
	  delay_ms(2600);
	Set_Car_Speed(0,0);      //停止
}

void md_stop(){

Set_Car_Speed(0,0);   //停止	
}
void md_run(int time3){

Set_Car_Speed(500,500);   //直行	
	delay_ms(time3);
}

