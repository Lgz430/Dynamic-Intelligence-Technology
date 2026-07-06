#include "openmv.h"
#include "OLED.h"
extern int openmv[7];//stm32接收数据数组
extern int16_t data1;
extern int16_t data2;
extern int16_t data3;
extern int16_t data4;
#include "openmv.h"
#include "Serial.h"
#include <math.h> 
//#include "stm32f10x.h"    

void K210_Receive_Data(int16_t data);

      
int taruge_rect[4][4];


u8 Count=0;//接受OpenMV数据里用到的

int Openmv_X; /*OPENMV X 轴反馈坐标*/
int Openmv_Y; /*OPENMV X 轴反馈坐标*/
uint8_t Stop_flag;

int i=0;
 
void Openmv_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	OLED_ShowNum(3,1,1,3,OLED_6X8);
	static u8 state = 0;
  if((state==0)&&(data==0x2C))
  {
   OLED_ShowNum(4,1,1,3,OLED_6X8);
   state=1;
   USART_RX_BUF[Count++]=data;
  }
  else if((state==1)&&(data==0x12))
  {
   OLED_ShowNum(3,4,1,3,OLED_6X8);
   state=2;
   USART_RX_BUF[Count++]=data;
  }
  else if(state==2)
  {
   OLED_ShowNum(4,4,1,3,OLED_6X8);  
   USART_RX_BUF[Count++] = data;
   if(Count>20||data == 0x5B) state=3;
  }
  else if(state==3)		//state == 3  检测是否接受到结束标志
  {
   OLED_ShowNum(1,4,1,3,OLED_6X8);  
   if(USART_RX_BUF[Count-1] == 0x5B)
   {
    state = 0;
	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//关闭DTSABLE中断
	Openmv_X=4*USART_RX_BUF[2];  
	Openmv_Y =4*USART_RX_BUF[3];  
    OLED_Clear();
	Stop_flag=1;//停止传输标志位
	   //	taruge_rect[0][0] = USART_RX_BUF[4];
//  taruge_rect[0][1] = USART_RX_BUF[5];
//  taruge_rect[1][0] = USART_RX_BUF[6];
//  taruge_rect[1][1] = USART_RX_BUF[7];
//  taruge_rect[2][0] = USART_RX_BUF[8];
//  taruge_rect[2][1] = USART_RX_BUF[9];
//  taruge_rect[3][0] = USART_RX_BUF[10];
//  taruge_rect[3][1] = USART_RX_BUF[11];
	USART_RX_STA = 1;
	Count = 0;

		
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//开启ENABLE中断
   }
   else   //错误
       {
        state = 0;
	    Count=0;
       }
   }    
  else	//错误
	 {
	   state = 0;
	   Count=0;
	 }
//	static u8 state = 0;
//	if(state==0&&data==0x2C)
//	{
//		state=1;
//		openmv[0]=data;
//	}
//	else if(state==1&&data==7)
//	{
//		state=2;
//		openmv[1]=data;
//	}
//	else if(state==2)
//	{
//		state=3;
//		openmv[2]=data;
//	}
//	else if(state==3)
//	{
//		state = 4;
//		openmv[3]=data;
//	}
//	else if(state==4)
//	{
//        state = 5;
//        openmv[4]=data;
//	}
//	else if(state==5)
//	{
//        state = 6;
//        openmv[5]=data;
//	}
//	else if(state==6)		//检测是否接受到结束标志
//	{
//        if(data == 0x5B)
//        {
//            state = 0;
//            openmv[6]=data;
//            Openmv_Data();
//        }
//        else if(data != 0x5B)
//        {
//            state = 0;
//            for(i=0;i<7;i++)
//            {
//                openmv[i]=0x00;
//            }           
//        }
//	}    
//	else
//		{
//			state = 0;
//            for(i=0;i<7;i++)
//            {
//                openmv[i]=0x00;
//            }
//		}
}
 
void Openmv_Data(void)
{
    data1=Openmv_X;
    data2=Openmv_Y;
   
 
}
