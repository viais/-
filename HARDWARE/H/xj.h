#ifndef __XJ_H
#define __XJ_H	 
#include "sys.h"

void xunkun_init(void);

//#define LL1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取 PB4
//#define LL2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取 PB5
//#define LL3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//读取 PB6
//#define LL4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//读取 PB7
//#define LL5 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//读取 PB4
//#define LL6 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//读取 PB5
//#define LL7 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//读取 PB6
//#define LL8 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//读取 PB7

//#define TC  1000*LL1+100*LL2+10*RR2+1*RR1

void md_stop(void);	
void md_xj(void);
void md_left(void);
void md_right(void);
void md_run(int time3);
#endif


