#include "led.h"
#include "delay.h"
#include "sys.h"
extern u16 Led_Val[16];
u16 buff=0xffff;
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
 
	while(1)
	{
		LedShowBuff(Led_Val);
    //delay_ms(500);
	}
 }

