//  #include "HD_159.h"

//AddP3201.pcb
#ifndef _HD_159_H
#define _HD_159_H

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////







//PC0--PC3     S1_1:4  拨码开关
//#define InPin_SW10	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0))
//#define InPin_SW11	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
//#define InPin_SW12	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//#define InPin_SW13	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))


#define SPI_STR_Lowy		  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define SPI_STR_Highy			GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define SPI_STR_LownnZ		  GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SPI_STR_HighnnZ			GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define SPI_Kiny	        (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6))
#define SPI_KinnnZ	        (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14))



#define InPin_K1	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))
#define InPin_K2	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))
//PC1  开发板上
#define InPin_K3	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
#define InPin_K4	1
#define InPin_K5	1

//PC5  
#define LED1_OFF		GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define LED1_ON			GPIO_SetBits(GPIOC,GPIO_Pin_5)
//PC13     FK103M5开发板上
#define LED2_OFF		GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define LED2_ON			GPIO_SetBits(GPIOC,GPIO_Pin_13)
//PD15  TIM4--CH4
#define LED3_OFF		;//GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define LED3_ON			;//GPIO_SetBits(GPIOD,GPIO_Pin_15)

//PC0  FK103M3开发板上
#define LED4_OFF		GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define LED4_ON			GPIO_ResetBits(GPIOC,GPIO_Pin_0)

// BUZ
#define BUZ_OFF		;
#define BUZ_ON			;





////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//EN485 FOR TXD3  -> PB9 
//#define SetEn485_3		GPIO_SetBits(GPIOB,GPIO_Pin_9)
//#define ClrEn485_3		GPIO_ResetBits(GPIOB,GPIO_Pin_9)



//PD8--PD15 PE8--PE14 PC6--PC9 步进电机控制

#define SetBitEN1				GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define ClrBitEN1				GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define SetBitCW1				GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define ClrBitCW1				GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define SetBitCLK1				GPIO_SetBits(GPIOE,GPIO_Pin_1)
#define ClrBitCLK1				GPIO_ResetBits(GPIOE,GPIO_Pin_1)

#define SetBitEN2				GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define ClrBitEN2				GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define SetBitCW2				GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define ClrBitCW2				GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define SetBitCLK2				GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define ClrBitCLK2			GPIO_ResetBits(GPIOE,GPIO_Pin_4)
//
#define SetBitEN3				GPIO_SetBits(GPIOE,GPIO_Pin_8)
#define ClrBitEN3				GPIO_ResetBits(GPIOE,GPIO_Pin_8)
#define SetBitCW3				GPIO_SetBits(GPIOE,GPIO_Pin_6)
#define ClrBitCW3				GPIO_ResetBits(GPIOE,GPIO_Pin_6)
#define SetBitCLK3				GPIO_SetBits(GPIOE,GPIO_Pin_7)
#define ClrBitCLK3				GPIO_ResetBits(GPIOE,GPIO_Pin_7)

#define SetBitEN4				GPIO_SetBits(GPIOE,GPIO_Pin_15)
#define ClrBitEN4				GPIO_ResetBits(GPIOE,GPIO_Pin_15)
#define SetBitCW4				GPIO_SetBits(GPIOE,GPIO_Pin_10)
#define ClrBitCW4				GPIO_ResetBits(GPIOE,GPIO_Pin_10)
#define SetBitCLK4				GPIO_SetBits(GPIOE,GPIO_Pin_12)
#define ClrBitCLK4				GPIO_ResetBits(GPIOE,GPIO_Pin_12)


#define SetBitEN5				;
#define ClrBitEN5				;
#define SetBitCW5				;
#define ClrBitCW5				;
#define SetBitCLK5			;
#define ClrBitCLK5			;

#define SetBitEN6				;
#define ClrBitEN6				;
#define SetBitCW6				;
#define ClrBitCW6				;
#define SetBitCLK6			;
#define ClrBitCLK6			;




//PD0--PD5	加热控制
#define SetHeat1				;
#define ClrHeat1			  ;
#define SetHeat2				;
#define ClrHeat2			  ;
#define SetHeat3				;
#define ClrHeat3			  ;
#define SetHeat4				;
#define ClrHeat4			  ;
#define SetHeat5				;
#define ClrHeat5			  ;
#define SetHeat6				;
#define ClrHeat6			  ;
#define SetHeat7				;
#define ClrHeat7			  ;
#define SetHeat8				;
#define ClrHeat8			  ;


////////////////////////////////////////////////////

#define SetEn485_1    GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define ClrEn485_1    GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define SetEn485_2    ;
#define ClrEn485_2    ;
#define SetEn485_3    ;
#define ClrEn485_3    ;
#define SetEn485_4    ;
#define ClrEn485_4    ;
#define SetEn485_5    ;
#define ClrEn485_5    ;


//I2C
//#define bSDA					(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
//#define SetbSDDA			GPIO_SetBits(GPIOB,GPIO_Pin_9)
//#define Clr_SDDA			GPIO_ResetBits(GPIOB,GPIO_Pin_9)
//#define SetbSCCL			GPIO_SetBits(GPIOB,GPIO_Pin_8)
//#define Clr_SCCL			GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define bSDA					(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
#define SetbSDDA			GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define Clr_SDDA			GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SetbSCCL			GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define Clr_SCCL			GPIO_ResetBits(GPIOB,GPIO_Pin_6)





void InitGpio(void);
//UART
////OS_VIEW_USART				     USART1
//TXD1  PA9



void  Init_Tim2 (void);

void InitUSART1(INT32U baud_rate,uint16_t parity);
void InitUSART2(INT32U baud_rate,uint16_t parity);
void InitUSART3(INT32U baud_rate,uint16_t parity);
void InitUART4(INT32U baud_rate,uint16_t parity);
void InitUART5(INT32U baud_rate,uint16_t parity);

#if CONFIG_UART1
void  USART1_RxTxISRHandler (void);
#endif

#if CONFIG_UART2
void  USART2_RxTxISRHandler (void);
#endif

#if CONFIG_UART3
void  USART3_RxTxISRHandler (void);
#endif

#if CONFIG_UART4
void  UART4_RxTxISRHandler (void);
#endif

#if CONFIG_UART5
void  UART5_RxTxISRHandler (void);
#endif

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)  ;


/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
//uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);

///////////////////////////////////////////////////////////////////////


////////////////////////////////////
/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIO_Remap: selects the pin to remap.
  *   This parameter can be one of the following values:
  *     @arg GPIO_Remap_SPI1             : SPI1 Alternate Function mapping
  *     @arg GPIO_Remap_I2C1             : I2C1 Alternate Function mapping
  *     @arg GPIO_Remap_USART1           : USART1 Alternate Function mapping
  *     @arg GPIO_Remap_USART2           : USART2 Alternate Function mapping
  *     @arg GPIO_PartialRemap_USART3    : USART3 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_USART3       : USART3 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap_TIM1      : TIM1 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_TIM1         : TIM1 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap1_TIM2     : TIM2 Partial1 Alternate Function mapping
  *     @arg GPIO_PartialRemap2_TIM2     : TIM2 Partial2 Alternate Function mapping
  *     @arg GPIO_FullRemap_TIM2         : TIM2 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap_TIM3      : TIM3 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_TIM3         : TIM3 Full Alternate Function mapping
  *     @arg GPIO_Remap_TIM4             : TIM4 Alternate Function mapping
  *     @arg GPIO_Remap1_CAN1            : CAN1 Alternate Function mapping
  *     @arg GPIO_Remap2_CAN1            : CAN1 Alternate Function mapping
  *     @arg GPIO_Remap_PD01             : PD01 Alternate Function mapping
  *     @arg GPIO_Remap_TIM5CH4_LSI      : LSI connected to TIM5 Channel4 input capture for calibration
  *     @arg GPIO_Remap_ADC1_ETRGINJ     : ADC1 External Trigger Injected Conversion remapping
  *     @arg GPIO_Remap_ADC1_ETRGREG     : ADC1 External Trigger Regular Conversion remapping
  *     @arg GPIO_Remap_ADC2_ETRGINJ     : ADC2 External Trigger Injected Conversion remapping
  *     @arg GPIO_Remap_ADC2_ETRGREG     : ADC2 External Trigger Regular Conversion remapping
  *     @arg GPIO_Remap_ETH              : Ethernet remapping (only for Connectivity line devices)
  *     @arg GPIO_Remap_CAN2             : CAN2 remapping (only for Connectivity line devices)
  *     @arg GPIO_Remap_SWJ_NoJTRST      : Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
  *     @arg GPIO_Remap_SWJ_JTAGDisable  : JTAG-DP Disabled and SW-DP Enabled
  *     @arg GPIO_Remap_SWJ_Disable      : Full SWJ Disabled (JTAG-DP + SW-DP)
  *     @arg GPIO_Remap_SPI3             : SPI3/I2S3 Alternate Function mapping (only for Connectivity line devices)
  *     @arg GPIO_Remap_TIM2ITR1_PTP_SOF : Ethernet PTP output or USB OTG SOF (Start of Frame) connected
  *                                        to TIM2 Internal Trigger 1 for calibration (only for Connectivity line devices)
  *                                        If the GPIO_Remap_TIM2ITR1_PTP_SOF is enabled the TIM2 ITR1 is connected to 
  *                                        Ethernet PTP output. When Reset TIM2 ITR1 is connected to USB OTG SOF output.    
  *     @arg GPIO_Remap_PTP_PPS          : Ethernet MAC PPS_PTS output on PB05 (only for Connectivity line devices)
  *     @arg GPIO_Remap_TIM15            : TIM15 Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM16            : TIM16 Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM17            : TIM17 Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_CEC              : CEC Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM1_DMA         : TIM1 DMA requests mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM9             : TIM9 Alternate Function mapping (only for XL-density devices)
  *     @arg GPIO_Remap_TIM10            : TIM10 Alternate Function mapping (only for XL-density devices)
  *     @arg GPIO_Remap_TIM11            : TIM11 Alternate Function mapping (only for XL-density devices)
  *     @arg GPIO_Remap_TIM13            : TIM13 Alternate Function mapping (only for High density Value line and XL-density devices)
  *     @arg GPIO_Remap_TIM14            : TIM14 Alternate Function mapping (only for High density Value line and XL-density devices)
  *     @arg GPIO_Remap_FSMC_NADV        : FSMC_NADV Alternate Function mapping (only for High density Value line and XL-density devices)
  *     @arg GPIO_Remap_TIM67_DAC_DMA    : TIM6/TIM7 and DAC DMA requests remapping (only for High density Value line devices)
  *     @arg GPIO_Remap_TIM12            : TIM12 Alternate Function mapping (only for High density Value line devices)
  *     @arg GPIO_Remap_MISC             : Miscellaneous Remap (DMA2 Channel5 Position and DAC Trigger remapping, 
  *                                        only for High density Value line devices)     
  * @param  NewState: new state of the port pin remapping.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
//void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)  ;





#endif




