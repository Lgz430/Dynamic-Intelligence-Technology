#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx.h" 
#include "sys.h"


//轮1——PE6 PE12 PA3
//轮2——PE4 PE8  PA1


//轮3——PE5 PE10 PA2
//轮4——PE3 PE7  PA0

//PD10--左轮停止
//PD11--右轮停止
//PA11--左轮正反转
//PA12--右轮正反转

#define A1 PEout(3)
#define A2 PEout(7)

#define B1 PEout(1)
#define B2 PEout(9)

#define C1 PEout(5)
#define C2 PEout(10)

#define D1 PEout(10)
#define D2 PEout(12)


void Motor_PWM_Init(u32 arr,u32 psc);
void Motor_IO_Init(void);
void motor_stop(void);
void motor_go(int16_t speed_l,int16_t speed_r);
/////////////////////////////////////////

void LD_PWM_Init(u32 arr,u32 psc);
void LD_IO_Init(void);
void motor_direction(u8 id,u8 cmd);
void motor1(int16_t speed);
void motor2(int16_t speed);
void motor3(int16_t speed);
void motor4(int16_t speed);

void Bianxing_S(void);
void Bianxing_X(void);
void LD_Circle(void);

//推杆
//正——上升
//负——下降
//		motor3(100);
//		motor1(100);

//履带
//		motor2(100);
//		motor4(100);


#endif
