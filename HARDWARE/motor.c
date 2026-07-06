#include "motor.h"


//A6-TIM3_CH1
//A7-TIM3_CH2
//B0-TIM3_CH3
//B1-TIM3_CH4


void Motor_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTB时钟	
	

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           
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
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性低
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = 0;
		
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);

	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
//	TIM_CtrlPWMOutputs(TIM3,ENABLE);
} 


//PD10--左轮停止
//PD11--右轮停止
//PA11--左轮正反转
//PA12--右轮正反转

void Motor_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOC时钟

  //GPIOC0初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOD,GPIO_Pin_10);
	GPIO_SetBits(GPIOD,GPIO_Pin_11);

//	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	
}


void motor_stop(void)
{
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
//	GPIO_ResetBits(GPIOD,GPIO_Pin_10);
//	GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	
}


void motor_go(int16_t speed_l,int16_t speed_r)
{
	if(speed_l>0)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare3(TIM3,speed_l);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare3(TIM3,-speed_l);
	}
	
	
	if(speed_r>0)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_1);
		TIM_SetCompare4(TIM3,speed_r);
	}
	else
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_1);
		TIM_SetCompare4(TIM3,-speed_r);
	}
	
}


//A0-TIM5_CH1
//A1-TIM5_CH2
//A2-TIM5_CH3
//A3-TIM5_CH4


void LD_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTB时钟	
	

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PB1 5
	
//	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性低
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
		
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);

	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE使能 
	TIM_Cmd(TIM5, ENABLE);  //使能TIM3
//	TIM_CtrlPWMOutputs(TIM3,ENABLE);
} 


//轮1——PE6 PE12 PA3
//轮2——PE4 PE8  PA1
//轮3——PE5 PE10 PA2
//轮4——PE3 PE7  PA0

void LD_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOC时钟

  //GPIOC0初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
		
}

void motor_direction(u8 id,u8 cmd)
{
	
	if(id==1)
	{
		if(cmd==0){A1=0;A2=0;}    
		else if(cmd==1){A1=1;A2=0;}   //
		else if(cmd==2){A1=0;A2=1;}   //
	}
	else if(id==2)
	{
		if(cmd==0){B1=0;B2=0;}    
		else if(cmd==1){B1=1;B2=0;}   //
		else if(cmd==2){B1=0;B2=1;}   //
	}
		else if(id==3)
	{
		if(cmd==0){C1=0;C2=0;}    
		else if(cmd==1){C1=1;C2=0;}   //
		else if(cmd==2){C1=0;C2=1;}   //
	}
		else if(id==4)
	{
		if(cmd==0){D1=0;D2=0;}    
		else if(cmd==1){D1=1;D2=0;}   //
		else if(cmd==2){D1=0;D2=1;}   //
	}
		else if(id==0)
	{
		if(cmd==0){A1=0;A2=0;B1=0;B2=0;C1=0;C2=0;D1=0;D2=0;}    
		else if(cmd==1){A1=1;A2=0;B1=1;B2=0;C1=1;C2=0;D1=1;D2=0;}   //轮子正转测试
		else if(cmd==2){A1=0;A2=1;B1=0;B2=1;C1=0;C2=1;D1=0;D2=1;}   //轮子反转测试
	}

	
}

void motor1(int16_t speed)
{
	if(speed>0)
	{
		motor_direction(1,1);
		TIM_SetCompare1(TIM5,speed);
	}
	else
	{
		motor_direction(1,2);
		TIM_SetCompare1(TIM5,-speed);
	}
	
}

void motor2(int16_t speed)
{
	if(speed>0)
	{
		motor_direction(2,1);
		TIM_SetCompare2(TIM5,speed);
	}
	else
	{
		motor_direction(2,2);
		TIM_SetCompare2(TIM5,-speed);
	}
	
}

void motor3(int16_t speed)
{
	if(speed>0)
	{
		motor_direction(3,1);
		TIM_SetCompare3(TIM5,speed);
	}
	else
	{
		motor_direction(3,2);
		TIM_SetCompare3(TIM5,-speed);
	}
	
}


void motor4(int16_t speed)
{
	if(speed>0)
	{
		motor_direction(4,2);
		TIM_SetCompare4(TIM5,speed);
	}
	else
	{
		motor_direction(4,1);
		TIM_SetCompare4(TIM5,-speed);
	}
	
}


void Bianxing_S(void)
{
//	LED_Flash();
	motor3(100);
	motor1(100);
}

void Bianxing_X(void)
{
//	LED_Flash();
	motor3(-100);
	motor1(-100);
}

void LD_Circle(void)
{
	motor2(50);
	motor4(-50);
}

	