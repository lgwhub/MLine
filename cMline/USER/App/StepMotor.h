/**
  ******************************************************************************
  * @file    StepMotor.h
  * @author  Liguowei  厉国伟
  * @version V0.0.1
  * @date    2/15/2017
  * @brief   This is Steper Motor Driver functions.
  ******************************************************************************
*/


#ifndef _STEP_MOTOR_H
#define _STEP_MOTOR_H


#define MOTOR_STATUS_OFF				0
#define MOTOR_STATUS_FORWORD		1
#define MOTOR_STATUS_BACKWORD		2

#define NUMBofSTEPs    6

//步进电机
struct step_motor{

signed  long  int   Position16;        //步进电机脉冲表示绝对位置，带符号
unsigned int   PulseCircleSet;		//2000*50us  = 0.1s   脉冲输出速度控制 设置值
unsigned int   PulseCircleCount;  //StepMot1.PulseCircleSet;   脉冲输出速度控制
unsigned long int   PulseCount;
unsigned char  Enable;
unsigned char  ClkStatus;

unsigned char Direction;          //方向  1先前  或者脉冲为正数

};

extern struct step_motor StepMot[ NUMBofSTEPs ];


//extern unsigned int RelativeOrigin;    //相对坐标原点
/////////////////////////
void StepMotInit(void);
void StepMoterPulseHandler(void);

//开步进电机1#
//step_count>0  --->  向前 MOTOR_STATUS_FORWORD   
//step_count<0  --->  向后 MOTOR_STATUS_BACKWORD 

void StepMotRun( unsigned char chs , signed long int step_count);

//步进电机一直走，只有速度调整
void StepMotRpm( unsigned char chs , signed  long int step_count ,  unsigned int   PulseCircleSet);

void StepMotStop(unsigned char chs);


#endif
