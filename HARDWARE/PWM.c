#include "stm32f4xx.h"                  // Device header

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
//void PWM_Init(void)  //PWM
//{  
//    /* 开启时钟 */  
//    
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 开启TIM2的时钟  
//    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE); // 开启GPIOA的时钟  
//  
//    /* GPIO初始化 */  
//    GPIO_InitTypeDef GPIO_InitStructure; 
//	
//		
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_TIM2);
//  
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;// GPIO_Mode_AF_PP 
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; // 改为PA0  
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉？
//    GPIO_Init(GPIOB, &GPIO_InitStructure); // 将PA0引脚初始化为复用推挽输出  
//     
//  
//    /* 配置时钟源 */  
//    TIM_InternalClockConfig(TIM2); // 选择TIM2为内部时钟  注意该处！！不配置时钟源
//  
//    /* 时基单元初始化 */  
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  
//    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
//    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  
//    TIM_TimeBaseInitStructure.TIM_Period =  20000- 1; // 计数周期 20000 
//    TIM_TimeBaseInitStructure.TIM_Prescaler =  84- 1; // 预分频器 72 (-1,-1)
//    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;  
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);  
//  
//    /* 输出比较初始化 - CH1 */  //这里改为了ch3和ch4
//    TIM_OCInitTypeDef TIM_OCInitStructure;  
//    TIM_OCStructInit(&TIM_OCInitStructure);  
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
//    TIM_OCInitStructure.TIM_Pulse = 0; // 初始的CCR值  
//    TIM_OC3Init(TIM2, &TIM_OCInitStructure); // 配置TIM2的输出比较通道1  
//  
//    /* 输出比较初始化 - CH2 */  
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // CH2同样使用PWM模式1  
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // CH2输出极性也设置为高  
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // CH2输出使能  
//    TIM_OCInitStructure.TIM_Pulse = 0; // CH2初始的CCR值  
//    TIM_OC4Init(TIM2, &TIM_OCInitStructure); // 配置TIM2的输出比较通道2  
//  
//    /* TIM使能 */  
//    TIM_Cmd(TIM2, ENABLE);  
//  
//    /* 自动重载预装载使能 */  
//    TIM_ARRPreloadConfig(TIM2, ENABLE);  
//}

void PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTB时钟	
	

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_TIM2);	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PB1 5
	
//	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性低
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = 0;
		
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能 
	TIM_Cmd(TIM2, ENABLE);  //使能TIM3
//	TIM_CtrlPWMOutputs(TIM3,ENABLE);
}


/**
  * 函    数：PWM设置CCR
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCompare3(uint16_t Compare)//改为了ch3 ch4
{
	TIM_SetCompare3(TIM2, Compare);		//设置CCR2的值
}
void PWM_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM2, Compare);		//设置CCR2的值
}

