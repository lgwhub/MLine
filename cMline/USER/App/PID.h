#ifndef    _PID_INC_H   
#define    _PID_INC_H

#define MAX_PID_RESOULT_1      (1000)
#define MIN_PID_RESOULT_1       (0)

#define MAX_PID_INTEGRAL_1     (900)
#define MIN_PID_INTEGRAL_1      (-50)

//#define MAX_PID_INTEGRAL_2     200
//#define MIN_PID_INTEGRAL_2      (0)

//#define MAX_PID_RESOULT_2     MAX_PID_INTEGRAL_2
//#define MIN_PID_RESOULT_2       MIN_PID_INTEGRAL_2

/********************************************************
* PID控制结构体声明
*********************************************************/
typedef struct 
{
    float Proportion;          //比例常数
    float Integral;            //积分常数
    float Derivative;          //微分常数
    float QMax;    //MAX_PID_INTEGRAL_2
    float QMin;    

}PID_ParaStruct;


//extern PID_ParaStruct      PidParam[2];


typedef struct 
{
    float SetPoint;            //设定目标
    
    float LastError;           //上次偏差
    float PreError;            //上上次偏差
    float SumError;            //累积偏差



    float Px;									//P部分
    float Ix;        					//I部分  结果 Px+Ix+Dx
    float Dx;        					//D部分

   
    signed long int Qx;                 //输出控制量
    
}PidBufStruct;  //临时变量

extern PidBufStruct HeatPidBuf[MAX_BLDC_CH6];
//extern PidBufStruct StepPidBuf[MAX_BLDC_CH6];


/********************************************************
* Function:    PID_Calc
* Description: PID计算
* Input:       pPIDxxx  需要计算的PID控制结构体指针
*              NowPoint         实际反馈值
* Output:      float           PID运算结果
* Calls:       无
* Called by:   CtrlTemp
* Others:
*********************************************************/
//float

void PID_BufInit(PidBufStruct *pidch);
void PID_ParaInit(void);//PID_ParaStruct *types,float p, float i, float d);


void PID_Calc(PID_ParaStruct *types, PidBufStruct *pidch, float NowPoint);
//void PID_Calc(PID_ParaStruct *types, PidBufStruct *pidch, float Error ,unsigned char typeflag);


#endif

