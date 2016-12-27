#include "led.h"
#include "delay.h"
LedStatus ledstatus;
u16 Led_Val[16];
;

void LED_MCUInit(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*ʹ��SWD ����ֹJTAG*/

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|\
                               GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //LED �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5

 LEDBUS=0X00;//����PA0~PA7ȫΪ0��

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;//�˿�����, �������
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 LED_LEL1=0;
 LED_LEL2=0;
 LED_LER1=0;
 LED_LER2=0;					
}

void LED_VarInit(void)
{
 u16 i;
 for(i=0;i<16;i++)
 {
    Led_Val[i]=0xffff; 
 }
 
}

void LED_Init()
{
 LED_MCUInit();
 LED_VarInit();

}
/******************************************************
�������ƣ�SelectLE()
��    �ܣ�ѡ��������
��    ����ѡ��������
����ֵ��  ��
*******************************************************/
void SelectLE(Latch latch)
{
  delay_us(100);
  switch(latch)
  {
    case LED_ROWH:
         LED_LEL1=0;
         LED_LEL2=0;
         LED_LER1=0;
         LED_LER2=1;	
        break;
    case LED_ROWL:
         LED_LEL1=0;
         LED_LEL2=0;
         LED_LER1=1;
         LED_LER2=0;	
        break;
    case LED_COLUMNH:
         LED_LEL1=0;
         LED_LEL2=1;
         LED_LER1=0;
         LED_LER2=0;	
        break;
    case LED_COLUMNL:
         LED_LEL1=1;
         LED_LEL2=0;
         LED_LER1=0;
         LED_LER2=0;	
        break;
    default:
         LED_LEL1=0;
         LED_LEL2=0;
         LED_LER1=0;
         LED_LER2=0;	
        break;
  }
   delay_us(100);
    LED_LEL1=0;
    LED_LEL2=0;
    LED_LER1=0;
    LED_LER2=0;	
}
void LedShowBuff(u16*buff)
{
  u8 i;
  u16 row;
  for(i=0;i<16;i++)
  {
  row= (0x0001<<i);//ѡ���һ��
  LEDBUS=row; 
  SelectLE(LED_ROWL);
  LEDBUS=row>>8;
  SelectLE(LED_ROWH);

  LEDBUS=buff[i];
  SelectLE(LED_COLUMNL);
  LEDBUS=buff[i]>>8;
  SelectLE(LED_COLUMNH);
  delay_ms(100);
  }

}
/******************************************************
�������ƣ�Led_Ctrl
��    �ܣ���LED���в���
��    ����row���е�ֵ��column���е�ֵ��ledstatus��LED��״̬
����ֵ��  ��
*******************************************************/
//void Led_Ctrl(u8 row,u8 column,LedStatus ledstatus)
//{
//   u8 temp,i,j;
//  u16 column=0x0001;
//  for(i=0;i<16;i++)
//  {
//    column=<<1;
//    if(i<8)   
//      {
//        LEDBUS=column;//ѡ����
//        SelectLE(LED_COLUMNL);
//      }
//    else
//      {
//         LEDBUS=column>>8;//ѡ����
//         SelectLE(LED_COLUMNL);
//      }
//}
/******************************************************
�������ƣ�LEDTest
��    �ܣ�����LED
��    ����speed�������ٶ�
����ֵ��  ��
*******************************************************/
//void LEDTest(u8 speed)
//{
//  u8 val=0,i;
//  Latch latch=;
//  for(i=0;i<256;i++)
//  {
//    if(i/64)
//    {
//     SelectLE()
//    }
//    val=val|(0x80>>(i%8));
//    Led_Write(val,LED_ROWH);
//  }
//  
//  
//}
 
