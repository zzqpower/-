#include "led.h"
#include "delay.h"
LedStatus ledstatus;
u16 Led_Val[16];
;

void LED_MCUInit(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //使能PB,PE端口时钟
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*使能SWD ，禁止JTAG*/

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|\
                               GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //LED 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

 LEDBUS=0X00;//设置PA0~PA7全为0；

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;//端口配置, 推挽输出
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
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
函数名称：SelectLE()
功    能：选择锁存器
参    数：选择锁存器
返回值：  无
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
  row= (0x0001<<i);//选择第一行
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
函数名称：Led_Ctrl
功    能：对LED进行操作
参    数：row，行的值，column，列的值，ledstatus，LED的状态
返回值：  无
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
//        LEDBUS=column;//选择列
//        SelectLE(LED_COLUMNL);
//      }
//    else
//      {
//         LEDBUS=column>>8;//选择列
//         SelectLE(LED_COLUMNL);
//      }
//}
/******************************************************
函数名称：LEDTest
功    能：测试LED
参    数：speed，点亮速度
返回值：  无
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
 
