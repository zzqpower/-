#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LEDBUS  GPIOA->ODR

#define LED_LEL1 PBout(3)// PB5
#define LED_LEL2 PBout(4)// PE5	
#define LED_LER1 PBout(5)// PB5
#define LED_LER2 PBout(6)// PE5

typedef enum LATCH
{
   LED_ROWH,LED_ROWL,LED_COLUMNH,LED_COLUMNL,LED_ALLOFF
}Latch;

typedef enum status
{
  OFF=0,ON=1
}LedStatus;

void LED_Init(void);//≥ı ºªØ
void LedShowBuff(u16*buff);
		 				    
#endif
