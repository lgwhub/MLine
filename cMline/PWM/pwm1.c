    
#include "includes.h"

//tim1 _ pwm1234
//tim5 _ pwm12


//void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
//void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
//void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
//void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);


#if CONFIG_PWM    
    
    /*
    TIM1 TIM8是高级定时器
    高级定时器输入时钟72MHZ,利用TIM1产生3个互补输出的信号，频率1HZ,占空比25%，50%,75%,分辨率1/10000，并加入死区时间。
    
    预分配寄存器的值=72000000/10000  -1 =7199
    比较寄存器1的值=10000x25%=2500
		比较寄存器2的值=10000x50%=5000
		比较寄存器3的值=10000x75%=7500    
    */
    
void PWM_T1_Configuration(void)
{
    
    TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
		TIM_OCInitTypeDef						TIM_OCInitStructure;
		//TIM_BDTRInitTypeDef					TIM_BDTRInitStructure;


    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

   	TIM_TimeBaseStructure.TIM_Prescaler     = 72000000/2000/1000-1;			//预分配寄存器   2khz    
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//TIM_CounterMode_Down;//

    TIM_TimeBaseStructure.TIM_Period        = 1000;		//  1/1000
    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    

		//设置通道1,2,3运行在PWM模式
		TIM_OCInitStructure.TIM_OCMode				=	TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState		=	TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState	=	TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse					=	0;//500;
    TIM_OCInitStructure.TIM_OCPolarity		=	TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity		=	TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState		=	TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState	=	TIM_OCNIdleState_Set;
    
    
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);			//pwm新值通过缓冲器在更新事件时装载
    
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);			//pwm新值通过缓冲器在更新事件时装载
    TIM_OCInitStructure.TIM_Pulse					=	0;//500;
    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
    
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);			//pwm新值通过缓冲器在更新事件时装载
    TIM_OCInitStructure.TIM_Pulse					=	0;//500;
    TIM_OC3Init(TIM1,&TIM_OCInitStructure);   

    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);			//pwm新值通过缓冲器在更新事件时装载
    TIM_OCInitStructure.TIM_Pulse					=	0;//500;
    TIM_OC4Init(TIM1,&TIM_OCInitStructure);       
    
    
    /*
    //输出允许，刹车信号允许，设置死区时间，锁定配置
    TIM_BDTRInitStructure.TIM_OSSRState		=		TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState		=		TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel		=		TIM_LOCKLevel_1;
    TIM_BDTRInitStructure.TIM_DeadTime			=		0;		//死区时间2us
    //TIM_BDTRInitStructure.TIM_Break				=		TIM_Break_Enable;
    //TIM_BDTRInitStructure.TIM_BreakPolarity		=		TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput	=		TIM_AutomaticOutput_Disable;
    
    TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);
    
    
    */
    
    
//    TIM_SetCounter(TIM2, 0);
//    TIM_PrescalerConfig(TIM2, 256, TIM_PSCReloadMode_Immediate);
		
		
		// ??   TIM_CCPreloadControl(TIM1, ENABLE);  //TIMx->CR2 |= TIM_CR2_CCPC;
		
		
		//TIM1允许计数
    TIM_Cmd(TIM1, ENABLE);
    //控制输出允许
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    
}

////////////////////////    

void GPIO_Configuration_PWM_T1(void)
{
		GPIO_InitTypeDef	GPIO_InitStructure;
		

//PartialRemap_TIM1  /*!< TIM1 Partial Alternate Function mapping */
//GPIO_FullRemap_TIM1
		  /* TIM1 Full remapping pins */
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); 
		
		
		//GPIOA通道1,2,3,4			PE9 PE11 PE13 PE14   //TIM1_REMAP[1:0] = 11
		GPIO_InitStructure.GPIO_Pin		=		GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode	=		GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed	=		GPIO_Speed_50MHz;
		GPIO_Init(GPIOE,&GPIO_InitStructure);
		

}


void GPIO_Configuration_PWM_T5(void)
{
		GPIO_InitTypeDef	GPIO_InitStructure;
		
		
		//GPIOA通道1,2 PA0  PA1   //TIM1_REMAP[1:0] = 11
		GPIO_InitStructure.GPIO_Pin		=		GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode	=		GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed	=		GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		

}

void PWM_T5_Configuration(void)
{
    
    TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
		TIM_OCInitTypeDef						TIM_OCInitStructure;


		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		
	TIM_TimeBaseStructure.TIM_Prescaler     = 72000000/2000/1000-1;			//预分配寄存器   2khz  ;			//预分配寄存器  36mhz 18khz    
    
	
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//TIM_CounterMode_Down;//
    TIM_TimeBaseStructure.TIM_Period        = 1000;//PWM_PERIOD_PULSE;//2000;  //36mhz/2000=18khz   (36000000/f
    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  //RCR重复寄存器

    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    

		//设置通道12运行在PWM模式
		TIM_OCInitStructure.TIM_OCMode				=	TIM_OCMode_PWM1;//TIM_OCMode_Active;//TIM_OCMode_Timing;//

    TIM_OCInitStructure.TIM_OutputState		=	TIM_OutputState_Enable;

    TIM_OCInitStructure.TIM_OCPolarity		=	TIM_OCPolarity_High;  //极性


//OC1
    TIM_OCInitStructure.TIM_Pulse					=	0;//PmwVal_TIM51_Buf;
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);			//pwm新值通过缓冲器在更新事件是装载
    TIM_OC1Init(TIM5,&TIM_OCInitStructure);

//OC2    
    TIM_OCInitStructure.TIM_Pulse					=	0;//PmwVal_TIM52_Buf;
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);			//pwm新值通过缓冲器在更新事件是装载
    TIM_OC2Init(TIM5,&TIM_OCInitStructure);
    



    TIM_CCPreloadControl(TIM5, ENABLE);  //TIMx->CR2 |= TIM_CR2_CCPC;

		//TIM4允许计数
    TIM_Cmd(TIM5, ENABLE);

    

    
}


#endif

