#ifndef __CSB_H
#define __CSB_H	 
#include "sys.h"

#define trig PAout(7)	// Pc2
#
#define echo  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)  
void CSB_Init(void);//≥ı ºªØ	 				
float CSB_Run(void);
typedef struct
{
	unsigned int us;
	unsigned int ms;
	unsigned int s;
	unsigned int min;
}Times;
extern Times Time;

void TIM3_Int_Init(u16 arr,u16 psc);
#endif
