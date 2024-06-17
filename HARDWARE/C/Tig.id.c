#include "stdlib.h"
#include "stm32f10x.h"  
#include "usart.h"
#include "Tig.id.h"
#include "delay.h"
#include "OLED.h"

u16 t; 
int FT;
u16 len;	

void Read_id(int r){
char FA[t];		

switch(r){
	case 1:

		  len=USART1_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				
			FA[t]= USART1_RX_BUF[t];//收到的数据
		  FT =atoi(FA);	//字符串转int
	   	OLED_ShowString(0, 18, "Tig.id:", OLED_8X16);		
 		  OLED_ShowNum(55, 18,FT, 1, OLED_8X16);
		  OLED_Update();			
			delay_ms(500);	
			USART1_RX_STA = 0;	
			}
		case 2:

		  len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				
			FA[t]= USART2_RX_BUF[t];//收到的数据
		  FT =atoi(FA);	//字符串转int
	   	OLED_ShowString(0, 18, "Tig.id:", OLED_8X16);		
 		  OLED_ShowNum(55, 18,FT, 1, OLED_8X16);
		  OLED_Update();			
			delay_ms(500);	
			USART2_RX_STA = 0;	
			}
			case 3:

		  len=USART3_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				
			FA[t]= USART3_RX_BUF[t];//收到的数据
		  FT =atoi(FA);	//字符串转int
	   	OLED_ShowString(0, 18, "Tig.id:", OLED_8X16);		
 		  OLED_ShowNum(55, 18,FT, 1, OLED_8X16);
		  OLED_Update();			
			delay_ms(500);	
			USART3_RX_STA = 0;	
			}
				
			
	
		}	
	
}
















