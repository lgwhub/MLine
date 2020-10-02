/**
  ******************************************************************************
  * @file    StepMotor.h
  * @author  Liguowei  ����ΰ
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

//�������
struct step_motor{

signed  long  int   Position16;        //������������ʾ����λ�ã�������
unsigned int   PulseCircleSet;		//2000*50us  = 0.1s   ��������ٶȿ��� ����ֵ
unsigned int   PulseCircleCount;  //StepMot1.PulseCircleSet;   ��������ٶȿ���
unsigned long int   PulseCount;
unsigned char  Enable;
unsigned char  ClkStatus;

unsigned char Direction;          //����  1��ǰ  ��������Ϊ����

};

extern struct step_motor StepMot[ NUMBofSTEPs ];


//extern unsigned int RelativeOrigin;    //�������ԭ��
/////////////////////////
void StepMotInit(void);
void StepMoterPulseHandler(void);

//���������1#
//step_count>0  --->  ��ǰ MOTOR_STATUS_FORWORD   
//step_count<0  --->  ��� MOTOR_STATUS_BACKWORD 

void StepMotRun( unsigned char chs , signed long int step_count);

//�������һֱ�ߣ�ֻ���ٶȵ���
void StepMotRpm( unsigned char chs , signed  long int step_count ,  unsigned int   PulseCircleSet);

void StepMotStop(unsigned char chs);


#endif
