#include "stm32f4xx.h" 
extern int openmv[7];//stm32接收数据数组
extern int16_t data1;
extern int16_t data2;
extern int16_t data3;
extern int16_t data4;
extern int Openmv_X;          /*OPENMV X 轴反馈坐标*/
extern int Openmv_Y;          /*OPENMV X 轴反馈坐标*/
extern uint8_t Stop_flag;
void Openmv_data(void);
//void Openmv_Recive(void);


extern int taruge_rect[4][4];

extern uint8_t Count;//接受OpenMV数据里用到的

void Usart_Sendata(char moshi);
void Usart_Init( uint32_t bound);

void Openmv_Receive_Data(int16_t data);
void Openmv_Data(void);
