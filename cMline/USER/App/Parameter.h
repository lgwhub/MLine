#ifndef _PARAMETER_H
#define _PARAMETER_H


/////struct	struct_save

//�����Ѿ���ʼ�����
#define FlagParamInitnized	0xB0

#define Max_MemBuf  ( 218 )

extern unsigned char cMemBufA[Max_MemBuf+2];
extern unsigned char cMemBufB[Max_MemBuf+2];


extern unsigned short int TimeForSaveParam;






/////////////////////////////////////////////////////////////////////////////


typedef struct
{
    unsigned long  int  CMD;                  //����Ĵ���
    unsigned long  int  WATCHING;             //����״̬
    unsigned long  int  BOARD_STATE;          //���״̬
    unsigned long  int  device_type;          //�豸�ͺ�
    float               Ts1_AMP;              //�¶Ȳ����Ŵ���1
    float               Ts1_BIAS;             //�¶Ȳ���ƫ��ϵ��1
    float               Ts2_AMP;              //�¶Ȳ����Ŵ���2
    float               Ts2_BIAS;             //�¶Ȳ���ƫ��ϵ��2
    float               Ts3_AMP;              //�¶Ȳ����Ŵ���3
    float               Ts3_BIAS;             //�¶Ȳ���ƫ��ϵ��3
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



PID_ParaStruct      Pidx[2];   //5X4X2 �ֽ�  pid����



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
    unsigned long  int  Burnin_type;          //�ϻ�����

    float               T_set;                //�¶�����ֵ
    float               T_bias_set;           //�¶�ƫ������ֵ
    float               T_upper_set;          //
    float               T_down_set;           //

    unsigned long  int  Cycle_times_set;      //
    
    float               TC_sx;                //�¶���������ֵ
    
    unsigned long  int  unit_onof_flag[8];    //

    unsigned long  int  TC_duty_set[8];          //�����ռ�ձ�        �趨ֵ
    unsigned long  int  FAN_duty_set[8];         //�������ˮ��ռ�ձ�  �趨ֵ       
    
    unsigned long  int  Moter_step_set;       //ǿ���߼���
    unsigned long  int  Moter_direction;      //����
    unsigned long  int  one_unit_flag;        //
    unsigned long  int  one_onoff_flag;       //
    unsigned long  int  limit_recode[8];      //


  //  198x2 byte
    float               Ts[8];                //

    unsigned long  int  ApmCt[8];    //  �ٶ��趨ֵ        TC_duty[8];           //ռ�ձ�
    signed long  int  ApmGt[8];    //  �ٶȲ���ֵFAN_duty[8];          //�������
    unsigned long  int  Clcle_times;          //
    unsigned long  int  ADC_error_count;      //
    
    

    
        unsigned long  int  lBackupRestore;
    unsigned long  int  SubAdr;
    unsigned long  int  SoftVer;     
    unsigned long  int  lSysSwitch_reserve;          //Ĭ�Ͽ��� ϵͳ����
    unsigned long  int 	lstats;  //ͳ����Ϣ  
    
    unsigned long  int 	WorkMode;  //��ͨ������ʽ��������ѭ����ʽ
    unsigned long  int 	SignalSelect;  //���»��ǽ���
    float               Tin[8];		//���¿�����
    
    
      //    280x2 byte   
    unsigned long  int   SenType;  //
    unsigned long  int   PcbType;  //
    unsigned long  int   xx1UpSpeed;  //�����趨ֵ�ٶ� //2��ÿ��  1      0.2��ÿ��  2       0.05��ÿ��    3    ֱ�� 0����������
    unsigned long  int   xx2;  //����
    

				     	
    
    
    
    
    
  unsigned long  int   Counter_MaxOpen[8];				//�¶ȳ����趨ֵ15�����ϣ���ʹ��PID,ǿ�ƴ�ˮ�䣬��n�κ���ͣ��Ȼ����¶ȵ�������Χ
  unsigned long  int   Counter_MaxClose[8];				//�¶ȵ����趨ֵ15�����ϣ���ʹ��PID,ǿ�ƹر�ˮ�䣬��n�κ���ͣ��Ȼ����¶ȵ�������Χ
  
    unsigned long  int   temp32[16]; 
   

}  _param_water8;    //  �ֽ�

extern _param_water8  Coldw;


extern unsigned char ModBusParaByte[];   //modbus ���� ����������

extern unsigned char FlagSetAllDefault;

void Default_ParamInit0(void);//����Ҫ����Ĳ���
void Default_ParamInit1(void); //��ͨ����  //��Ҫ����Ĳ���
void Default_ParamInit2(void); //����ֵ

//void Default_ParamInit(void);
void InitSaveParam(void);
unsigned char Write_Param(void);
unsigned char Load_Param(void);

#endif




