

#ifndef _USER_H
#define _USER_H




//��ƷΨһ��ݱ�ʶ�Ĵ�����96λ��
//����ַ0X1FFF F7E8
//λ15:0
//��ַƫ��0x02
//λ31:16
//��ַƫ��0x04
//λ63:32
//��ַƫ��0x06
//λ95:64




//#define PCB_TYPE_18SENSOR   0
//#define PCB_TYPE_8xAD590    0
//#define PCB_TYPE_8xPT1000   0
//#define PCB_TYPE_ONLY_MOTOR2  1


//ͨ����


   #define MAX_BLDC_CH6   6



   //Capture_Flag[i] = 0
   //...
   //FREQ[0] = (u32)72000000  * Capture_number1 / (CaptureValueEnd1 - CaptureValueStart1)  ; 
   //Capture_number[i] = 0
   
   //CaptureValueStart[6+1] 
   //CaptureValueEnd[6+1]





extern unsigned  char Capture_Flag[MAX_BLDC_CH6 + 1] ;
extern unsigned  long int Apm_FREQ[MAX_BLDC_CH6 + 1] ; 
extern unsigned  long int Capture_number[MAX_BLDC_CH6 +1 ] ;

//extern unsigned  long int Capture_number_All32  ;  //��Զ�����������������


extern unsigned  short int  BLDC_PwmVal[ MAX_BLDC_CH6 + 1 ];   //pwm�ٶȿ���ֵ   1000  max 


//#define Flag_test_spi_DMA   0

//#if Flag_test_spi_DMA     
//    extern unsigned  long int Capture_testSPI_number[6+1] ;
//#endif

extern unsigned  long int CaptureValueStart[6+1] ;
extern unsigned  long int CaptureValueEnd[6+1];
//��Ϊʹ��16λ��ʱ������������������Ҳʹ��16λ
//extern unsigned  short int CaptureValueStart[6+1] ;
//extern unsigned  short int CaptureValueEnd[6+1];
extern unsigned  long int CaptureValueHigh_T3;
extern unsigned  long int CaptureValueHigh_T4;
///////////////////////////////

extern unsigned char EventTimeBuz;
extern unsigned char EventTimeLed;


#define Led_Test_Key_On1		;//LED1_ON
#define Led_Test_Key_Off1		;//LED1_OFF

#define Led_Test_Adc_On1		;//LED1_ON
#define Led_Test_Adc_Off1		;//LED1_OFF

#define Led_Status_On		LED1_ON
#define Led_Status_Off		LED1_OFF

//EventTimeLed
#define Led_Event_On		LED3_ON
#define Led_Event_Off		LED3_OFF


//void MotorsRun(unsigned char ch, signed short int steps);

void TaskRush(void * pdata);
void TaskModbus(void * pdata);
void TaskStepMotor(void * pdata);
void TaskTimePr(void * pdata);
void TaskHpwm(void * pdata);
void TaskStatus(void * pdata);

void TaskLedy(void * pdata);
void TaskSync(void * pdata);
void TaskKey(void * pdata);
void TaskApm(void * pdata);
void TaskRecv(void * pdata);
void TaskSave(void * pdata);
void TaskLedz(void * pdata);

void ModbusCommand2(void);

#endif
