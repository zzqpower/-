#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
extern u16 Led_Val[16];
u16 buff=0xffff;
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	
  uart3_init(115200);  
	LED_Init();		  	//初始化与LED连接的硬件接口
  printf("串口3测试\r\n");
	while(1)
	{
		LedShowBuff(Led_Val);
    //delay_ms(500);
	}
 }

