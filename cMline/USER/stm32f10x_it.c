/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include <includes.h>


#if ( OS_VIEW_MODULE == DEF_ENABLED )
extern	void OSView_RxTxISRHandler(void);
#endif


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}



/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	CPU_SR         cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */

    OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}





#if CONFIG_HD_TIM



void TIM2_IRQHandler(void)
{//步进电机脉冲输出用
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		
		
		StepMoterPulseHandler();
		
	

  }
}
#endif

//void TIM3_IRQHandler(void)
//{//步进电机脉冲输出用
//  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//  {
//    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);		
//		
//
//	
//
//  }
//}



void TIM3_IRQHandler(void)
{ 
	
 if( TIM_GetITStatus( TIM3 ,  TIM_IT_Update )  ==  SET ) 	
 	{
 		TIM_ClearITPendingBit( TIM3 ,  TIM_IT_Update );
 		 //if(  Capture_Flag[0]  != 0 )
    	    {

          		CaptureValueHigh_T3 += 65536;

 		   }
 	}
 	
  if(TIM_GetITStatus(TIM3, TIM_IT_CC3) == SET) 
     {
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
    
   //Capture_Flag[i] = 0
   //...
   //FREQ[0] = (u32)72000000  * Capture_number1 / (CaptureValueEnd1 - CaptureValueStart1)  ; 
   //Capture_number[i] = 0
   
   //CaptureValueStart[6+1] 
   //CaptureValueEnd[6+1]
   
   
   //.....          
//      #if Flag_test_spi_DMA     
//         Capture_testSPI_number[0]++;
//      #endif   
      
     // Capture_number_All32 ++ ;  //永远计数器。脉冲测量用
      Coldw. T_bias_set++; //永远计数器。脉冲测量用
      
     if( Capture_Flag[0] !=0 )
    	 {
          if(Capture_number[0] == 0)
               {

               CaptureValueStart[0] = TIM_GetCapture3(TIM3) + CaptureValueHigh_T3;
               Capture_number[0] = 1;
               }
         else
               {

               CaptureValueEnd[0]  = TIM_GetCapture3(TIM3)  + CaptureValueHigh_T3; 
               Capture_number[0] ++ ;
               }
         }
  	}
 
 
 
  
  if(TIM_GetITStatus(TIM3, TIM_IT_CC4) == SET) 
     {
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
    
//    #if Flag_test_spi_DMA     
//    Capture_testSPI_number[1]++;
//    #endif
    
     if( Capture_Flag[1] !=0 )
    	   {
         if(Capture_number[1] == 0)
               {

             CaptureValueStart[1] = (unsigned  long int)TIM_GetCapture4(TIM3) +  CaptureValueHigh_T3;
             Capture_number[1] = 1;
               }
          else
               {

               CaptureValueEnd[1]  =  (unsigned  long int)TIM_GetCapture4(TIM3)   +  CaptureValueHigh_T3; 
               Capture_number[1] ++ ;
               }
        }   

      }  
  
}



void TIM4_IRQHandler(void)
{
	
	 if( TIM_GetITStatus( TIM4 ,  TIM_IT_Update )  ==  SET ) 	
 	{
 		TIM_ClearITPendingBit( TIM4 ,  TIM_IT_Update );
 		 //if(  Capture_Flag[2]  != 0 )
    	    {
          		CaptureValueHigh_T4 += 65536;
 		   }
 	}
	
	
  if(TIM_GetITStatus(TIM4, TIM_IT_CC1) == SET) 
  {
    /* Clear TIM4 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
    
//    #if Flag_test_spi_DMA     
//    Capture_testSPI_number[2]++;
//    #endif
    
    if( Capture_Flag[2] !=0 )
    	   {
         if(Capture_number[2] == 0)
               {

             CaptureValueStart[2] = TIM_GetCapture1(TIM4) + CaptureValueHigh_T4;
             Capture_number[2] = 1;
               }
          else
               {

               CaptureValueEnd[2]  = TIM_GetCapture1(TIM4) + CaptureValueHigh_T4 ; 
               Capture_number[2] ++ ;
               }
        }
    
  } 
  
  if(TIM_GetITStatus(TIM4, TIM_IT_CC2) == SET) 
  {
    /* Clear TIM4 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
     
//     #if Flag_test_spi_DMA     
//     Capture_testSPI_number[3]++;
//    #endif
    
    if( Capture_Flag[3] !=0 )
    	   {
         if(Capture_number[3] == 0)
               {

             CaptureValueStart[3] = TIM_GetCapture2(TIM4) + CaptureValueHigh_T4;
             Capture_number[3] = 1;
               }
          else
               {

               CaptureValueEnd[3]  = TIM_GetCapture2(TIM4) + CaptureValueHigh_T4 ; 
               Capture_number[3] ++ ;
               }
        }
  } 

  if(TIM_GetITStatus(TIM4, TIM_IT_CC3) == SET) 
  {
    /* Clear TIM4 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
    
//      #if Flag_test_spi_DMA     
//        Capture_testSPI_number[4]++;
//      #endif
        
    if( Capture_Flag[4] !=0 )
    	   {
         if(Capture_number[4] == 0)
               {

             CaptureValueStart[4] = TIM_GetCapture3(TIM4) + CaptureValueHigh_T4;
             Capture_number[4] = 1;
               }
          else
               {

               CaptureValueEnd[4]  = TIM_GetCapture3(TIM4) + CaptureValueHigh_T4 ; 
               Capture_number[4] ++ ;
               }
        }
    
  } 
  
  if(TIM_GetITStatus(TIM4, TIM_IT_CC4) == SET) 
  {
    /* Clear TIM4 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
    
    
//    #if Flag_test_spi_DMA    
//        Capture_testSPI_number[5]++;
//     #endif    
     
    if( Capture_Flag[5] !=0 )
    	   {
         if(Capture_number[5] == 0)
               {

             CaptureValueStart[5] = TIM_GetCapture4(TIM4) + CaptureValueHigh_T4;
             Capture_number[5] = 1;
               }
          else
               {

               CaptureValueEnd[5]  = TIM_GetCapture4(TIM4) + CaptureValueHigh_T4 ; 
               Capture_number[5] ++ ;
               }
        }
    
  }   
    
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USART1_IRQHandler(void)
{
	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 1)
	#if CONFIG_UART1
	USART1_RxTxISRHandler();
	#endif
	#endif	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
				#if   OS_VIEW_USART_NUMBER == 1
							OSView_RxTxISRHandler();
				#endif	
	#endif
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USART2_IRQHandler(void)
{
#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 2)
#if CONFIG_UART2
	USART2_RxTxISRHandler();
	#endif
	#endif
	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
		#if   OS_VIEW_USART_NUMBER == 2			
				OSView_RxTxISRHandler();
		#endif	
#endif
}

void USART3_IRQHandler(void)
{
#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 3)
		#if CONFIG_UART3
	USART3_RxTxISRHandler();
	#endif
	#endif	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
		#if   OS_VIEW_USART_NUMBER == 3			
				OSView_RxTxISRHandler();
		#endif	
#endif
}

void UART4_IRQHandler(void)
{
	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 4)
	#if CONFIG_UART4
	UART4_RxTxISRHandler();
	#endif
	#endif	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
		#if   OS_VIEW_USART_NUMBER == 4			
				OSView_RxTxISRHandler();
		#endif	
#endif
}


void UART5_IRQHandler(void)
{
	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 5)
	#if CONFIG_UART5
	UART5_RxTxISRHandler();
	#endif
	#endif	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
		#if   OS_VIEW_USART_NUMBER == 5			
				OSView_RxTxISRHandler();
		#endif	
#endif
}

/////////////////////////////
void SPI1_IRQHandler(void)
{
	
	//unsigned char xxx;
  if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) != RESET)
  {
SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);

  SPI_I2S_ClearITPendingBit(SPI1,  SPI_I2S_IT_TXE);     
  //SPI_I2S_ClearITPendingBit(SPI1,  SPI_I2S_FLAG_TXE); 

		
	//	SPI1->SR  =0;
//xxx=SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) ;
		
      //SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
	//	xxx+=0x80;
		

  }
}
//////////////////////////////

void SPI2_IRQHandler(void)
{
  /* Store SPI_SLAVE received data */
 // SPI_SLAVE_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI_SLAVE);
 
   if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_TXE) != RESET)
  {

SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);

      //SPI_I2S_ITConfig(SPI_MASTER, SPI_I2S_IT_TXE, DISABLE);

  }
 
 
}



//SELECTED_SPI_INT
void DMA1_Channel3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC3)==SET)
        {
         DMA_Cmd(DMA1_Channel3,DISABLE);
        //DMA1_Channel3->CNDTR = 3;//ADC_DATASIZE;
         //DMA_Cmd(DMA1_Channel3,ENABLE);
         DMA_ClearITPendingBit(DMA1_IT_TC3);
        }
}
////////////////////////////////////
void DMA1_Channel5_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC5)==SET)
        {
          DMA_Cmd(DMA1_Channel5,DISABLE);
         // DMA1_Channel5->CNDTR = 3;//ADC_DATASIZE;
        // DMA_Cmd(DMA1_Channel5,ENABLE);
          DMA_ClearITPendingBit(DMA1_IT_TC5);
        }
}







#if	CONFIG_EXTI

//#define KEY_BUTTON_EXTI_LINE        EXTI_Line8
//#define KEY_BUTTON_PORT_SOURCE      GPIO_PortSourceGPIOG
//#define KEY_BUTTON_PIN_SOURCE       GPIO_PinSource8
//#define KEY_BUTTON_IRQn             EXTI9_5_IRQn

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(KEY_BUTTON_EXTI_LINE) != RESET)
  {
    /* Toggle LED1 */
  //   STM_EVAL_LEDToggle(LED1);

    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE);
  }
}
#endif



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
