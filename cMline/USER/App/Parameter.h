#ifndef _PARAMETER_H
#define _PARAMETER_H


/////struct	struct_save

//参数已经初始化标记
#define FlagParamInitnized	0xB0

extern  unsigned short int Stm32IdSum6;   


#define Max_MemBuf  ( 100 )

extern unsigned char cMemBufA[Max_MemBuf+2];
extern unsigned char cMemBufB[Max_MemBuf+2];


extern unsigned short int TimeForSaveParam;






/////////////////////////////////////////////////////////////////////////////


typedef struct
{
    unsigned long  int  CMD;                  //命令寄存器
    unsigned long  int  WATCHING;             //监视状态
    unsigned long  int  BOARD_STATE;          //插板状态
    unsigned long  int  device_type;          //设备型号
    float               Ts1_AMP;              //温度采样放大倍数1
    float               Ts1_BIAS;             //温度采样偏移系数1
    float               Ts2_AMP;              //温度采样放大倍数2
    float               Ts2_BIAS;             //温度采样偏移系数2
    float               Ts3_AMP;              //温度采样放大倍数3
    float               Ts3_BIAS;             //温度采样偏移系数3
    float               Ts4_AMP;
    float               Ts4_BIAS;
    float               Ts5_AMP;
    float               Ts5_BIAS;
    float               Ts6_AMP;
    float               Ts6_BIAS;
    float               Ts7_AMP;
    float               Ts7_BIAS;
    float               Ts8_AMP;
    float               Ts8_BIAS;



PID_ParaStruct      Pidx[2];   // 5 X 4 X 2 字节  pid参数



    float               MONI_PX1;                //
    float               MONI_IX1;
    float               MONI_DX1;
    signed long int               MONI_QX1;
    
    float               MONI_PX2;                //
    float               MONI_IX2;
    float               MONI_DX2;
    unsigned long int               MONI_QX2;    
        
    float               NC[18];               //old 22

   //0x70  112x2 byte
    unsigned long  int  Burnin_type;          //老化类型

    float               Flag_Runingnny;                     //T_set;                //温度设置值
    float               T_bias_set;           //温度偏差设置值
    float               T_upper_set;          //
    float               T_down_set;           //

    unsigned long  int  Cycle_times_set;      //
    
    float               Flag_Runingnnz;   //TC_sx;                //温度上限设置值
    
    unsigned long  int  unit_onof_flag[8];    //

    unsigned long  int  TC_duty_set[8];          //电加热占空比        设定值
    unsigned long  int  FAN_duty_set[8];         //风机或者水冷占空比  设定值       
    
    unsigned long  int  Moter_step_set;       //强制走几步
    unsigned long  int  Moter_direction;      //方向
    unsigned long  int  one_unit_flag;        //
    unsigned long  int  one_onoff_flag;       //
    unsigned long  int  limit_recode[8];      //


 
   // float               Ts[8];                //
    float   ApmGt[8];    //  速度测量值    

    unsigned long  int  ApmCt[8];    //  速度设定值         //TC_duty[8];           //占空比
    
    signed long  int  ApmDuty[8];      //控制量显示                    //FAN_duty[8];            //步进电机
    
    unsigned long  int  Clcle_times;          //
    
    unsigned long  int  ADC_error_count;      //
    
    

    
        unsigned long  int  lBackupRestore;
    unsigned long  int  SubAdr;
    unsigned long  int  SoftVer;     
    unsigned long  int  lSysSwitch_reserve;          //默认开机 系统开关
    unsigned long  int 	lstats;  //统计信息  
    
    unsigned long  int 	WorkMode;  //普通工作方式还是冷热循环方式
    unsigned long  int 	SignalSelect;  //壳温还是结温
    float               Tin[8];		//结温控制用
    
    
      //    280x2 byte   
    unsigned long  int   SenType;  //
    unsigned long  int   PcbType;  //
    unsigned long  int   xx1UpSpeed;  //渐进设定值速度 //2度每秒  1      0.2度每秒  2       0.05度每秒    3    直接 0，或者其它


   

}  _param_water8;    //  字节

extern _param_water8  Coldw;


extern unsigned char ModBusParaByte[];   //modbus 参数 拷贝缓冲区

extern unsigned char FlagSetAllDefault;

void Default_ParamInit0(void);//不需要保存的参数
void Default_ParamInit1(void); //普通参数  //需要保存的参数
void Default_ParamInit2(void); //整定值

//void Default_ParamInit(void);
void InitSaveParam(void);
unsigned char Write_Param(void);
unsigned char Load_Param(void);

#endif




