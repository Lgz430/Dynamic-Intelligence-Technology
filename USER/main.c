#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "Servo.h"
#include "motor.h"
#include "move.h"
#include "change.h"
#include "oled.h"
#include "Serial.h"
#include "openmv.h"
#include "PWM.h"
#include "PID.h"

int16_t data1;
int16_t data2;

int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();
	Servo_Init(20000-1,84-1);
	Motor_PWM_Init(100-1,1680-1);
	Motor_IO_Init();
	//uart_init(38400);
	uart2_init(9600);
	uart3_init(9600);
	//BianXing_Init();
	PWM_Init(20000-1,84-1);
	LD_PWM_Init(100-1,1680-1);
	LD_IO_Init();
	Bianxing_X();
	PWM_SetCompare3(2000);
	PWM_SetCompare4(2000);
	
	//GPIO_SetBits(GPIOD,GPIO_Pin_15);
	//OLED_Init();
	//OLED_ShowString(3, 1, "Hello World!", OLED_8X16);
	
	//serv.o_march();
	//motor_go(-20,-20);
	//GPIO_SetBits(GPIOA,GPIO_Pin_11);
//	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	while(1)
	{
		Blue_Receive();
//		if(a==1){
////			 LED_Flash();
////			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
//			Bianxing_S();
//			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
//		}
//		Bianxing_X();
//		delay_ms(1000);
//		Bianxing_S();
//		delay_ms(1000);
//		D2=1;
//		D1=1;
//		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
//		
//		
///////////////////////////////
//		motor2(50);
//		motor4(-50);
		
		
		//

		//motor_go(20,20);

		
	}
	
}






 



