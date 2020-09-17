/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.blkeji.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               app_cfg.h
** Descriptions:            ucosii configuration
**
**--------------------------------------------------------------------------------------------------------

** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
					  

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/
#define  OS_VIEW_MODULE                 0*DEF_ENABLED	     	/* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */

#define  OS_VIEW_USART_NUMBER			2

#if   OS_VIEW_USART_NUMBER == 1
#define  OS_VIEW_USART				     USART1	    
#elif  OS_VIEW_USART_NUMBER == 2
#define  OS_VIEW_USART				     USART2    
#elif  OS_VIEW_USART_NUMBER == 3
#define  OS_VIEW_USART				     USART3    
#endif


#define  CONFIG_ADC		0
#define  CONFIG_PWM		1

#define  CONFIG_HD_TIM		1
#define  CONFIG_CAP_TIM   1


//m3线路板不用显示板
#define  CONFIG_SPI_DISP		0

#define SOFT_VER   02


//#define CONFIG_CHECK_DEVICE_ID  1
/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/

#define CONFIG_TEST_LED_BLINK		1
#define USART1_REMAP						0
//#define JTAG_REMAP							1

#define SWD_DEBUG_DISABLE   0


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                               3


#define  TaskTimePr_PRIO          	 		(OS_LOWEST_PRIO - 33)
#define  TaskModbus_PRIO          	 		(OS_LOWEST_PRIO - 32)

#define  TaskLedy_PRIO          	 		(OS_LOWEST_PRIO - 31)
#define  TaskLedz_PRIO          	 		(OS_LOWEST_PRIO - 30)


#define  TaskSave_PRIO          	 		(OS_LOWEST_PRIO - 24)

#define  TaskRecv_PRIO          	 		(OS_LOWEST_PRIO - 22)


#define  TaskApm_PRIO          	 		(OS_LOWEST_PRIO - 17)

#define  TaskStepMotor_PRIO          	 		(OS_LOWEST_PRIO - 16)

#define  TaskHpwm_PRIO          	 		(OS_LOWEST_PRIO - 14)
#define  TaskStatus_PRIO          	 		(OS_LOWEST_PRIO - 13)


#define  TaskKey_PRIO          	 		(OS_LOWEST_PRIO - 10)
#define  TaskRush_PRIO          	 		(OS_LOWEST_PRIO - 9)

#define  MyTASK_PRIO          	 		(OS_LOWEST_PRIO - 7)
#define  APP_TASK_BLINK_PRIO          	 (OS_LOWEST_PRIO - 6)

#define  APP_TASK_OSVIEW_TERMINAL_PRIO	 (OS_LOWEST_PRIO - 4)
#define  OS_VIEW_TASK_PRIO               (OS_LOWEST_PRIO - 3)
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)



/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                          (64+2)
#define  APP_TASK_BLINK_STK_SIZE                         (128+2)
#define  APP_TASK_OSVIEW_TERMINAL_STK_SIZE   			 128u
#define  OS_VIEW_TASK_STK_SIZE                           128u

#define  MyTASKStk_SIZE                          (64+2u)
#define  TaskApmStk_SIZE                          (250+2u)

#define  TaskLedyStk_SIZE                         90
#define  TaskKeyStk_SIZE                         (124+2u)
#define  TaskLedzStk_SIZE                          (96+2u)

#define  TaskRecvStk_SIZE                          (76+2u)
#define  TaskSaveStk_SIZE                          (124+2u)


#define  TaskRushStk_SIZE                          (106+2u)
#define  TaskModbusStk_SIZE                          (155+2u)
#define  TaskStepMotorStk_SIZE                          (164+2u)
#define  TaskTimePrStk_SIZE                          (88+2u)
#define  TaskHpwmStk_SIZE                          (120+2u)
#define  TaskStatusStk_SIZE                          (84+2u)

/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

/*
*********************************************************************************************************
*                                             io def     
*********************************************************************************************************
*/







#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

