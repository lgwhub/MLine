
#include "includes.h"
#include "stm32f10x.h"



#if	CONFIG_EXTI

//#define KEY_BUTTON_EXTI_LINE        EXTI_Line8
//#define KEY_BUTTON_PORT_SOURCE      GPIO_PortSourceGPIOG
//#define KEY_BUTTON_PIN_SOURCE       GPIO_PinSource8
//#define KEY_BUTTON_IRQn             EXTI9_5_IRQn



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* Initialize LED1 and Key Button mounted on STM3210X-EVAL board */       
  //               STM_EVAL_LEDInit(LED1);
  //               STM_EVAL_PBInit(Button_KEY, Mode_EXTI);  

  /* Generate software interrupt: simulate a falling edge applied on Key Button EXTI line */
  //             EXTI_GenerateSWInterrupt(KEY_BUTTON_EXTI_LINE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Exti_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable Button GPIO clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,ENABLE); 
  /* Configure Button pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  
//  if (Button_Mode == Mode_EXTI)
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

//    if(Button != Button_WAKEUP)
//    {
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    }
//    else
//    {
//      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//    }
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
   //////////////////////////////////////////////////////////////////////// 
/*
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);

    // Configure Button EXTI line
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;


      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);    
    */

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;;//EXTI9_5_IRQn;//EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
  }
}

#endif


