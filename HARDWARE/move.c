#include "move.h"
#include "motor.h"
#include "Servo.h"
#include "delay.h"
#include "usart.h"

#include "led.h"

#define uart_buffer_size 100//数组的大小
unsigned char uart_rec_buffer[uart_buffer_size];//接收数据的数组
unsigned char index_uart=0;//接收数据位移指针
unsigned char uart_buffer_head_ok;//数据头标志
unsigned char cmd_in=0;//接收完成标志位


void move_march(void)
{
	servo_march();
	delay_ms(2000);
//	motor_go(50,-50);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	TIM_SetCompare3(TIM3,20);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	TIM_SetCompare4(TIM3,20);
		
}

void move_side(void)
{
	servo_side();
	delay_ms(2000);
	motor_go(500,500);
}

void move_stop(void)
{
	motor_go(0,0);
}

void move_circle(void)
{
	servo_circle();
	delay_ms(2000);
	motor_go(500,500);
}



//void USART1_IRQHandler(void)
//{
//  unsigned char c;
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  {
//    USART_ClearITPendingBit( USART1 , USART_IT_RXNE );	
//   //清楚状态标志位，等待下次数据触发中断		
//    c=USART1->DR;
//    if(c==0xEE) //如果收到的数据头是0xEE，进入下面循环
//    {
//      uart_buffer_head_ok=1;//数据头正确			
//      index_uart=0; //指针指向数组的第一个元素
//    }
//    if(uart_buffer_head_ok==1) //当再有数据来时进入此循环
//    {
//      uart_rec_buffer[index_uart++]=c; //以此保存数据到缓存区
//      if(index_uart>=1)//判断数据尾帧
//      {
//        if((uart_rec_buffer[index_uart-1]==0xFF))//帧尾正确
//        {  
//			if((uart_rec_buffer[index_uart]==0xFE))
//			{
//				uart_buffer_head_ok=0; //标志位清零，等待下次接收
//				index_uart=0;
//				cmd_in=1;	
//			}
//        }
//      }
//    }
//    else if(uart_buffer_head_ok==0)
//    {
//      index_uart=0;
//    }

//    if(index_uart>=uart_buffer_size) //如果发生溢出，接收指针清零从新接收
//      index_uart=0;
//  }

//}


void USART2_IRQHandler(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
  unsigned char c;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit( USART2 , USART_IT_RXNE );	
   //清楚状态标志位，等待下次数据触发中断		
    c=USART2->DR;
    if(c==0xEE) //如果收到的数据头是0xEE，进入下面循环
    {
      uart_buffer_head_ok=1;//数据头正确			
      index_uart=0; //指针指向数组的第一个元素
    }
    if(uart_buffer_head_ok==1) //当再有数据来时进入此循环
    {
      uart_rec_buffer[index_uart++]=c; //以此保存数据到缓存区
      if(index_uart>=1)//判断数据尾帧
      {
        if((uart_rec_buffer[index_uart-1]==0xFF))//帧尾正确
        {  
			if((uart_rec_buffer[index_uart]==0xFE))
			{
				uart_buffer_head_ok=0; //标志位清零，等待下次接收
				index_uart=0;
				cmd_in=1;	
			}
        }
      }
    }
    else if(uart_buffer_head_ok==0)
    {
      index_uart=0;
    }

    if(index_uart>=uart_buffer_size) //如果发生溢出，接收指针清零从新接收
      index_uart=0;
  }

}

int a=0;

void Blue_Receive(void)
{
//	if(a==2){
////			LED_Flash();
//			Bianxing_X();
//		    a=0;
//		}
//	
//	if(a==1){
////			LED_Flash();
//			Bianxing_S();
//		    a=0;
//		}
	
	if(cmd_in==1)  //数据正常接收完成
     {  
		cmd_in=0; 
		 
		// LED_Flash();
		 //
		 
		if(uart_rec_buffer[1]==0x01)
		{
			
			servo_march();
			
		}
		if(uart_rec_buffer[2]==0x01)
		{
			servo_side();
			
		}
		if(uart_rec_buffer[3]==0x01)
		{
			servo_circle();
		}
		
		if(uart_rec_buffer[4]==0x01)
		{
			//LD_Circle();
			Bianxing_S();
			
		}
		if(uart_rec_buffer[5]==0x01)
		{

			Bianxing_X();
			

		}
		if(uart_rec_buffer[6]==0x01)
		{
			Bianxing_S();
		}
		if(uart_rec_buffer[9]==0x01)
		{
			TIM_SetCompare2(TIM5,0);
			TIM_SetCompare4(TIM5,0);
		}
		
/////////////////////////////////////////////////////////
		
		if( uart_rec_buffer[10]>=141)//手柄控制轮子前进
				{		
					motor_go((uart_rec_buffer[10]-131)*100/(255-141),(uart_rec_buffer[10]-131)*100/(255-141));					
				}		 
		if(uart_rec_buffer[10]<=100)//手柄控制轮子后退
				{		
					motor_go(-(110-uart_rec_buffer[10])*100/100,-(110-uart_rec_buffer[10])*100/100);					
				}
		if((uart_rec_buffer[10]>=101)&&(uart_rec_buffer[10]<=140)&&(uart_rec_buffer[11]>=91)&&(uart_rec_buffer[11]<=139))//手柄控制履带停
				{		
					motor_stop();
				}
				
/////////////////////////////////////////////////////////////
		if( uart_rec_buffer[12]==0)//手柄控制履带前进
				{		
					TIM_SetCompare2(TIM5,0);
					TIM_SetCompare4(TIM5,0);
				}	
				
		if( uart_rec_buffer[12]>=150)//手柄控制履带前进
				{		
					motor4((uart_rec_buffer[12]-131)*100/(255-141));
					motor2((uart_rec_buffer[12]-131)*100/(255-141));
				}		 
		 if((uart_rec_buffer[12]<=100)&&(uart_rec_buffer[12]!=0))//手柄控制履带后退
				{		
					motor4(-(110-uart_rec_buffer[12])*100/100);
					motor2(-(110-uart_rec_buffer[12])*100/100);
				}
		 if((uart_rec_buffer[12]>=101)&&(uart_rec_buffer[12]<=150)&&(uart_rec_buffer[13]>=91)&&(uart_rec_buffer[13]<=139))//手柄控制履带停
				{		
					TIM_SetCompare2(TIM5,0);
					TIM_SetCompare4(TIM5,0);	
				}		
		 if( uart_rec_buffer[13]<=50)
  				{		
						motor4(100);
						motor2(-100);
//					motor_Right();	
				}
				
		 if( uart_rec_buffer[13]>=190)
  				{		
						motor4(-100);
						motor2(100);
//					motor_Left();
				}				

	 }
}


