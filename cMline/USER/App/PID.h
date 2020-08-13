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
* PID���ƽṹ������
*********************************************************/
typedef struct 
{
    float Proportion;          //��������
    float Integral;            //���ֳ���
    float Derivative;          //΢�ֳ���
    float QMax;    //MAX_PID_INTEGRAL_2
    float QMin;    

}PID_ParaStruct;


//extern PID_ParaStruct      PidParam[2];


typedef struct 
{
    float SetPoint;            //�趨Ŀ��
    
    float LastError;           //�ϴ�ƫ��
    float PreError;            //���ϴ�ƫ��
    float SumError;            //�ۻ�ƫ��



    float Px;									//P����
    float Ix;        					//I����  ��� Px+Ix+Dx
    float Dx;        					//D����

   
    signed long int Qx;                 //���������
    
}PidBufStruct;  //��ʱ����

extern PidBufStruct HeatPidBuf[MAX_BLDC_CH6];
//extern PidBufStruct StepPidBuf[MAX_BLDC_CH6];


/********************************************************
* Function:    PID_Calc
* Description: PID����
* Input:       pPIDxxx  ��Ҫ�����PID���ƽṹ��ָ��
*              NowPoint         ʵ�ʷ���ֵ
* Output:      float           PID������
* Calls:       ��
* Called by:   CtrlTemp
* Others:
*********************************************************/
//float

void PID_BufInit(PidBufStruct *pidch);
void PID_ParaInit(void);//PID_ParaStruct *types,float p, float i, float d);


void PID_Calc(PID_ParaStruct *types, PidBufStruct *pidch, float NowPoint);
//void PID_Calc(PID_ParaStruct *types, PidBufStruct *pidch, float Error ,unsigned char typeflag);


#endif

