#include "stm32f10x.h"
#include "delay.h"
#include "xj.h"
#include "md.h"
#include "stdlib.h"
void xunkun_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOB��ʱ��
		
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������ģʽ
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0,PB1,PB3,PB4,PB5�ܽŵĳ�ʼ��
	  
//	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//�ر�STM32f103c8t6��JTAGD���ܣ�ʹPB3��PB4������ͨ��IO�ܽ�//���뿪�����ù��ܵ�ʱ�Ӳ��ܹرոù���
}

//void md_xj(){
//	int SZLK=0,j=0;
//		switch(TC){                         //��Ϊ1��ֵԽС�ٶ�Խ��   

//					case 110:
//						Set_Car_Speed(600,600); break;   //ֱ��	
//					case 1100:
//						
//						Set_Car_Speed(550,450); break;   //С��ת
//					case 100:
//						Set_Car_Speed(550,450); break;   //С��ת
//					case 1000:
//						
//						Set_Car_Speed(500,400); break;   //����ת					
//					case 11:
//						
//            Set_Car_Speed(450,550); break;   //С��ת
//					case 10:
//						
//            Set_Car_Speed(450,550); break;   //С��ת
//					case 1:
//					
//            Set_Car_Speed(400,550); break;   //����ת
//					case 1110:  
//			    	md_left();break;//��ת
//		      case 111:
//			    	md_right();break;//��ת
//					
//				 case 0:        //ʮ��·��
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
//		     case 1111:     //�հ�·��
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
	
	Set_Car_Speed(-600,600);   //��ת		
  delay_ms(2600);
	Set_Car_Speed(0,0);      //ֹͣ
	
}

void md_right(){
	Set_Car_Speed(600,-600);  //��ת
	  delay_ms(2600);
	Set_Car_Speed(0,0);      //ֹͣ
}

void md_stop(){

Set_Car_Speed(0,0);   //ֹͣ	
}
void md_run(int time3){

Set_Car_Speed(500,500);   //ֱ��	
	delay_ms(time3);
}

