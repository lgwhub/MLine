/**
  ******************************************************************************
  * @file    TIM/InputCapture/main.c 

  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

		#include "TimCap.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_Input_Capture
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration_T3(void);
void GPIO_Configuration_T3(void);
void NVIC_Configuration_T3(void);
void Cap_Configuration_T3(void);
void RCC_Configuration_T4(void);
void GPIO_Configuration_T4(void);
void NVIC_Configuration_T4(void);
 void Cap_Configuration_T4(void);


/* Private functions ---------------------------------------------------------*/


//CONFIG_CAP_TIM
void Init_Capture_T3(void)
{

  /* System Clocks Configuration */
  RCC_Configuration_T3();

  /* NVIC configuration */
  NVIC_Configuration_T3();

  /* Configure the GPIO ports */
  GPIO_Configuration_T3();


  Cap_Configuration_T3();

  /* TIM3 configuration: Input Capture mode ---------------------
     The external signal is connected to TIM3 CH2 pin (PA.07)  
     The Rising edge is used as active edge,
     The TIM3 CCR2 is used to compute the frequency value 
  ------------------------------------------------------------ */
}


void Init_Capture_T4(void)
{

  /* System Clocks Configuration */
  RCC_Configuration_T4();

  /* NVIC configuration */
  NVIC_Configuration_T4();

  /* Configure the GPIO ports */
  GPIO_Configuration_T4();


  Cap_Configuration_T4();
  /* TIM3 configuration: Input Capture mode ---------------------
     The external signal is connected to TIM3 CH2 pin (PA.07)  
     The Rising edge is used as active edge,
     The TIM3 CCR2 is used to compute the frequency value 
  ------------------------------------------------------------ */
}

void Cap_Configuration_T3(void)
{
	
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	  TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
   	TIM_TimeBaseStructure.TIM_Prescaler     = 72000000/100000-1;			//Ô¤·ÖÅä¼Ä´æÆ÷   100khz    0.5S.<65536
//    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//TIM_CounterMode_Down;//
//    TIM_TimeBaseStructure.TIM_Period        = 1000;		//  1/1000
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
//    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	
	
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);  
  
  
  /* TIM enable counter */
  TIM_Cmd(TIM3, ENABLE);

  /* Enable the CC3 CC4 Interrupt Request */
  TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
TIM_ITConfig(TIM3, TIM_IT_CC4, ENABLE);
}

void Cap_Configuration_T4(void)
{
	
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	
	
		  TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
   	TIM_TimeBaseStructure.TIM_Prescaler     = 72000000/100000-1;			//Ô¤·ÖÅä¼Ä´æÆ÷   100khz    0.5S.<65536
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
	
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);    
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);     
  /* TIM enable counter */
  TIM_Cmd(TIM4, ENABLE);
  
 

  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);  
  
  
}


/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration_T3(void)
{
 // SystemInit();

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOA and GPIOB clock enable */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


void RCC_Configuration_T4(void)
{
 // SystemInit();

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOA and GPIOB clock enable */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}
/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration_T3(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM3 channel 3 4 pin (PB.0 PB.1) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void GPIO_Configuration_T4(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;


 GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); 


  /* TIM3 channel 2 pin (PD.06 PD.07 PD.08 PD.9) configuration */
    /* TIM4 channel 2 pin (PD.12 PD.13 PD.14 PD.15) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOD, &GPIO_InitStructure);
}
/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration_T3(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void NVIC_Configuration_T4(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
