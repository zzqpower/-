#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
extern u16 Led_Val[16];
u16 buff=0xffff;
 int main(void)
 {	
	delay_init();	    	 //��ʱ������ʼ��	
  uart3_init(115200);  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
  printf("����3����\r\n");
	while(1)
	{
		LedShowBuff(Led_Val);
    //delay_ms(500);
	}
 }

