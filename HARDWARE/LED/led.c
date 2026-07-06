#include "led.h" 
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4工程模板-库函数版本
//genbotter.com							  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PC0为输出口.并使能其时钟		    
//LED IO初始化

void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟

  //GPIOC0初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;//LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);//设置高，灯灭

}


void LED_Flash(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);  //LED2对应引脚GPIOC0拉低，亮  等同LED2=0;
	delay_ms(500);  		   
	GPIO_SetBits(GPIOC,GPIO_Pin_0);	   //LED2对应引脚GPIOC0拉高，灭  等同LED2=1;
	delay_ms(500); 
}




