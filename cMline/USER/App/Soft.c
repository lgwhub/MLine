/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.blkeji.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uctsk_Blink.c
** Descriptions:            The uctsk_Blink application function
**
**--------------------------------------------------------------------------------------------------------

** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <includes.h>            



extern OS_EVENT *OSSemProcCmdx;
//extern OS_EVENT *OSSemblinkOut2;
//extern OS_EVENT *OSSemblinkOut3;
extern OS_EVENT *OSSemUart1;
//extern OS_EVENT *OSSemUart2;
extern OS_EVENT *OSSemTimePid_StepMotor;
extern OS_EVENT *OSSemTimePid_Heat;


/* Private variables ---------------------------------------------------------*/
static  OS_STK         App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE];

static  OS_STK         MyTASKStk[MyTASKStk_SIZE];
static  OS_STK         TaskRecvStk[TaskRecvStk_SIZE];
static  OS_STK         TaskApmStk[TaskApmStk_SIZE];
static  OS_STK         TaskLedyStk[TaskLedyStk_SIZE];
static  OS_STK         TaskKeyStk[TaskKeyStk_SIZE];
static  OS_STK         TaskSaveStk[TaskSaveStk_SIZE];
static  OS_STK         TaskLedzStk[TaskLedzStk_SIZE];

static  OS_STK         TaskVirPwmStk[TaskVirPwmStk_SIZE];
static  OS_STK         TaskModbusStk[TaskModbusStk_SIZE];
static  OS_STK         TaskStepMotorStk[TaskStepMotorStk_SIZE];
static  OS_STK         TaskTimePrStk[TaskTimePrStk_SIZE];
static  OS_STK         TaskHpwmStk[TaskHpwmStk_SIZE];
static  OS_STK         TaskStatusStk[ TaskStatusStk_SIZE];


/* Private function prototypes -----------------------------------------------*/
static void uctsk_Blink (void);
static void MyTASK (void);
//extern void TaskRecv(void);
//extern void TaskApm(void);
//extern void TaskSave(void * pdata);
 
void  App_BlinkTaskCreate (void)
{
    CPU_INT08U  os_err;

	os_err = os_err; /* prevent warning... */
	
#if CONFIG_TEST_LED_BLINK
	os_err = OSTaskCreate((void (*)(void *)) uctsk_Blink,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_BLINK_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task LED Blink", &os_err);
	#endif
#endif



//OSSemblinkOut2 = OSSemCreate(0);
//OSSemblinkOut3 = OSSemCreate(0);

OSSemUart1 = OSSemCreate(1);
//OSSemUart2 = OSSemCreate(1);
			
OSSemTimePid_StepMotor = OSSemCreate(0);
OSSemTimePid_Heat = OSSemCreate(0);

OSSemProcCmdx = OSSemCreate(0);
//MyStk
//	os_err = OSTaskCreate((void (*)(void *)) MyTASK,				
//                          (void          * ) 0,							
//                          (OS_STK        * )&MyTASKStk[MyTASKStk_SIZE - 1],		
//                          (INT8U           ) MyTASK_PRIO  );	

    os_err = OSTaskCreateExt((void (*)(void *)) MyTASK,
                             (void          * ) 0,
                             (OS_STK        * )&MyTASKStk[MyTASKStk_SIZE - 1],
                             (INT8U           ) MyTASK_PRIO,
                             (INT16U          ) MyTASK_PRIO,
                             (OS_STK        * )&MyTASKStk[0],
                             (INT32U          ) MyTASKStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));



    os_err = OSTaskCreateExt((void (*)(void *)) TaskLedy,
                             (void          * ) 0,
                             (OS_STK        * )&TaskLedyStk[TaskLedyStk_SIZE - 1],
                             (INT8U           ) TaskLedy_PRIO,
                             (INT16U          ) TaskLedy_PRIO,
                             (OS_STK        * )&TaskLedyStk[0],
                             (INT32U          ) TaskLedyStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskKey,
                             (void          * ) 0,
                             (OS_STK        * )&TaskKeyStk[TaskKeyStk_SIZE - 1],
                             (INT8U           ) TaskKey_PRIO,
                             (INT16U          ) TaskKey_PRIO,
                             (OS_STK        * )&TaskKeyStk[0],
                             (INT32U          ) TaskKeyStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));



    os_err = OSTaskCreateExt((void (*)(void *)) TaskRecv,
                             (void          * ) 0,
                             (OS_STK        * )&TaskRecvStk[TaskRecvStk_SIZE - 1],
                             (INT8U           ) TaskRecv_PRIO,
                             (INT16U          ) TaskRecv_PRIO,
                             (OS_STK        * )&TaskRecvStk[0],
                             (INT32U          ) TaskRecvStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskApm,
                             (void          * ) 0,
                             (OS_STK        * )&TaskApmStk[TaskApmStk_SIZE - 1],
                             (INT8U           ) TaskApm_PRIO,
                             (INT16U          ) TaskApm_PRIO,
                             (OS_STK        * )&TaskApmStk[0],
                             (INT32U          ) TaskApmStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
    
    os_err = OSTaskCreateExt((void (*)(void *)) TaskLedz,
                             (void          * ) 0,
                             (OS_STK        * )&TaskLedzStk[TaskLedzStk_SIZE - 1],
                             (INT8U           ) TaskLedz_PRIO,
                             (INT16U          ) TaskLedz_PRIO,
                             (OS_STK        * )&TaskLedzStk[0],
                             (INT32U          ) TaskLedzStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskSave,
                             (void          * ) 0,
                             (OS_STK        * )&TaskSaveStk[TaskSaveStk_SIZE - 1],
                             (INT8U           ) TaskSave_PRIO,
                             (INT16U          ) TaskSave_PRIO,
                             (OS_STK        * )&TaskSaveStk[0],
                             (INT32U          ) TaskSaveStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskVirPwm,
                             (void          * ) 0,
                             (OS_STK        * )&TaskVirPwmStk[TaskVirPwmStk_SIZE - 1],
                             (INT8U           ) TaskVirPwm_PRIO,
                             (INT16U          ) TaskVirPwm_PRIO,
                             (OS_STK        * )&TaskVirPwmStk[0],
                             (INT32U          ) TaskVirPwmStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    os_err = OSTaskCreateExt((void (*)(void *)) TaskModbus,
                             (void          * ) 0,
                             (OS_STK        * )&TaskModbusStk[TaskModbusStk_SIZE - 1],
                             (INT8U           ) TaskModbus_PRIO,
                             (INT16U          ) TaskModbus_PRIO,
                             (OS_STK        * )&TaskModbusStk[0],
                             (INT32U          ) TaskModbusStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    os_err = OSTaskCreateExt((void (*)(void *)) TaskStepMotor,
                             (void          * ) 0,
                             (OS_STK        * )&TaskStepMotorStk[TaskStepMotorStk_SIZE - 1],
                             (INT8U           ) TaskStepMotor_PRIO,
                             (INT16U          ) TaskStepMotor_PRIO,
                             (OS_STK        * )&TaskStepMotorStk[0],
                             (INT32U          ) TaskStepMotorStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
                             
    os_err = OSTaskCreateExt((void (*)(void *)) TaskTimePr,
                             (void          * ) 0,
                             (OS_STK        * )&TaskTimePrStk[TaskTimePrStk_SIZE - 1],
                             (INT8U           ) TaskTimePr_PRIO,
                             (INT16U          ) TaskTimePr_PRIO,
                             (OS_STK        * )&TaskTimePrStk[0],
                             (INT32U          ) TaskTimePrStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));                         
                             
     os_err = OSTaskCreateExt((void (*)(void *)) TaskHpwm,
                             (void          * ) 0,
                             (OS_STK        * )&TaskHpwmStk[TaskHpwmStk_SIZE - 1],
                             (INT8U           ) TaskHpwm_PRIO,
                             (INT16U          ) TaskHpwm_PRIO,
                             (OS_STK        * )&TaskHpwmStk[0],
                             (INT32U          ) TaskHpwmStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));                                
                             
      os_err = OSTaskCreateExt((void (*)(void *)) TaskStatus,
                             (void          * ) 0,
                             (OS_STK        * )&TaskStatusStk[TaskStatusStk_SIZE - 1],
                             (INT8U           ) TaskStatus_PRIO,
                             (INT16U          ) TaskStatus_PRIO,
                             (OS_STK        * )&TaskStatusStk[0],
                             (INT32U          ) TaskStatusStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));                               
                             
                             
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(MyTASK_PRIO, "MyTASK", &os_err);

    	OSTaskNameSet(TaskApm_PRIO, "TaskApm", &os_err);
			OSTaskNameSet(TaskLedy_PRIO, "TaskLedy", &os_err);    	
			OSTaskNameSet(TaskKey_PRIO, "TaskKey", &os_err);    	
			OSTaskNameSet(TaskRecv_PRIO, "TaskRecv", &os_err);
    	OSTaskNameSet(TaskLedz_PRIO, "TaskLedz", &os_err);			
    	OSTaskNameSet(TaskSave_PRIO, "TaskSave", &os_err);
    	
    	OSTaskNameSet(TaskVirPwm_PRIO, "TaskVirPwm", &os_err);
    	
    	OSTaskNameSet(TaskModbus_PRIO, "TaskModbus", &os_err);
    	OSTaskNameSet(TaskStepMotor_PRIO, "TaskStepMotor", &os_err);
     	OSTaskNameSet(TaskTimePr_PRIO, "TaskTimePr", &os_err);
    	
    	OSTaskNameSet(TaskHpwm_PRIO, "TaskHpwm", &os_err);
    	OSTaskNameSet(TaskStatus_PRIO, "TaskStatus", &os_err);   	
    	
    	
	#endif
}
/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
//////////////
static void MyTASK (void)
{
	
	for(;;)
	{
		
		
		OSTimeDlyHMSM(0, 0,1, 100);	 /* 1 seconds  */
		//ClrPowJspOut1;
		//ClrResumMegnet;
		//GPIO_ResetBits(GPIOE , GPIO_Pin_1);
		//LED1_ON;
		//LED2_OFF;
		//GPIO_ResetBits(GPIOE,GPIO_Pin_1);
		//Delay(60000);
		OSTimeDlyHMSM(0, 0, 1, 100);
		//SetPowJspOut1;
		//SetResumMegnet;
		//LED2_ON;
		//LED1_OFF;
//GPIO_SetBits(GPIOE , GPIO_Pin_1);
	
	
	
		}
}


#if CONFIG_TEST_LED_BLINK
static void uctsk_Blink (void) {                 
  
   
   	for(;;)
   	{   
	    //Delay( rand()%0xfffff ); 	
	    #if CONFIG_TEST_LED_BLINK
//LED1_ON;	    
//LED2_ON;
//GPIO_SetBits(GPIOE , GPIO_Pin_0);
#endif
//OSTimeDly(OS_TICKS_PER_SEC);
OSTimeDlyHMSM(0, 0, 0,50);	//50ms
		//OSTimeDlyHMSM(0, 0, 1, 0);	 /* 1 seconds  */
	 	/* LED1-ON LED2-OFF */
	//	GPIO_SetBits(GPIOE , GPIO_Pin_0);
		//GPIO_ResetBits(GPIOE , GPIO_Pin_1);

	    //Delay( rand()%0xfffff ); 
	    #if CONFIG_TEST_LED_BLINK
//LED1_OFF;
//LED2_OFF;
//GPIO_ResetBits(GPIOE , GPIO_Pin_0);
#endif
//OSTimeDly(OS_TICKS_PER_SEC);
OSTimeDlyHMSM(0, 0, 0,50);	//50ms
      	
	    /* LED1-OFF LED2-ON */
		//GPIO_ResetBits(GPIOE , GPIO_Pin_0);
		//GPIO_SetBits(GPIOE , GPIO_Pin_1);
   }
}
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
