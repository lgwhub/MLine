#ifndef    _PID_H   
#define    _PID_H


//水冷  增量控制
//#define MAX_PID_INTEGRAL_1   100
//#define MIN_PID_INTEGRAL_1   (-100)

//2400在8分频时是300步步进电机的极限行程   MOTOR_MAX_STEP == 2400
#define MAX_PID_INTEGRAL_1   (MOTOR_MAX_STEP/24)
#define MIN_PID_INTEGRAL_1   (-MAX_PID_INTEGRAL_1)


extern PidBufStruct StepPidBuf[MAX_TEMPRATURE_CHNALL];
/********************************************************
* PID控制结构体声明
*********************************************************/
//typedef struct 
//{
//    float Proportion;          //比例常数
//    float Integral;            //积分常数
//    float Derivative;          //微分常数
//    float Max;    
//    float Min;    
//
//}PID_ParaStruct;
//
//
//
//
//typedef struct 
//{
//    float SetPoint;            //设定目标
//    
//    float LastError;           //上次偏差
//    float PreError;            //上上次偏差
//    float SumError;            //累积偏差
//
//
//
//    float Px;									//P部分
//    float Ix;        					//I部分  结果 Px+Ix+Dx
//    float Dx;        					//D部分
//
//   
//    signed long int Qx;                 //输出控制量
//    
//}PidBufStruct;  //临时变量
//


/********************************************************
* Function:    PID_INC_Calc
* Description: PID计算
* Input:       pPIDxxx  需要计算的PID控制结构体指针
*              NowPoint         实际反馈值
* Output:      float           PID运算结果
* Calls:       无
* Called by:   CtrlTemp
* Others:
*********************************************************/
//float

//void PID_Inc_BufInit(PidBufStruct *pidch);
void PID_Inc_ParaInit(void);
void PID_Inc_Calc( PidBufStruct *ch, float Error);
#endif

