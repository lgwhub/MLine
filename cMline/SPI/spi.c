/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/main.c 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   Main program body
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
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
	#include   "spi.h"
#include "includes.h"
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_SoftNSS
  * @{
  */ 



//Select spi Or DMA int
#define SELECTED_SPI_INT   2

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;
DMA_InitTypeDef  DMA_InitStructure;
unsigned char  SPInny_Buffer_Tx[SPIBufferSize4];
unsigned char  SPInnz_Buffer_Tx[SPIBufferSize4];
                                      




/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
  
 /* 
dma{


  DMA_DeInit(SPI1_MASTER_Tx_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI1_MASTER_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)( SPInny_Buffer_Tx + 1 );   //
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = SPIBufferSize4 - 1 ; //
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(SPI1_MASTER_Tx_DMA_Channel, &DMA_InitStructure);


  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_MASTER, &SPI_InitStructure);


  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Rx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  SPI_Init(SPI1_MASTER, &SPI_InitStructure);


  SPI_SSOutputCmd(SPI_MASTER, ENABLE);


  SPI_I2S_DMACmd(SPI1_MASTER, SPI_I2S_DMAReq_Rx, ENABLE);


  SPI_Cmd(SPI1_MASTER, ENABLE);

  SPI_Cmd(SPI_MASTER, ENABLE);


  DMA_Cmd(SPI1_MASTER_Rx_DMA_Channel, ENABLE);




  while (!DMA_GetFlagStatus(SPI1_MASTER_Rx_DMA_FLAG));

}
 */ 
void NVIC_Configuration_SPI_nny(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}  


void NVIC_Configuration_SPI_nnz(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
} 


void NVIC_Configuration_DMA_nny(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}


void NVIC_Configuration_DMA_nnz(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

}

void SpiInit_nny(void)
{
	
	  DMA_DeInit(SPI1_MASTER_Tx_DMA_Channel);
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();


NVIC_Configuration_DMA_nny();

NVIC_Configuration_SPI_nny();



RCC_AHBPeriphClockCmd(SPI1_MASTER_DMA_CLK, ENABLE);


  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI1_MASTER_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)( SPInny_Buffer_Tx  );   //
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = SPI_DMA_BufferSize4  ; //
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(SPI1_MASTER_Tx_DMA_Channel, &DMA_InitStructure);



  /* 1st phase: SPInny Master and SPInnz Slave */
  /* SPInny Config -------------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;//SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;           //SPI_Mode_Slave;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;       //SPI_DataSize_16b;    //
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;            //SPI_CPHA_1Edge;    //
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;               //SPI_NSS_Hard
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//6.4    SPI_BaudRatePrescaler_4;  0.1us
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPInny, &SPI_InitStructure);




  #if SELECTED_SPI_INT == 2
  
  SPI_I2S_DMACmd(SPInny  , SPI_I2S_DMAReq_Tx, ENABLE);
  
#endif

  SPI_Cmd(SPInny, ENABLE);
  
  



  
  #if  SELECTED_SPI_INT == 1
  
  SPI_I2S_ITConfig(SPInny, SPI_I2S_IT_TXE, ENABLE);
  
  
#elif SELECTED_SPI_INT == 2
 
   DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//使能DMA1通道5中断，注意一定要是“DMA_IT_TC”，否则会出现进不了中断的问题。
 
  
#elif SELECTED_SPI_INT == 3
   SPI_I2S_ITConfig(SPInny, SPI_I2S_IT_TXE, ENABLE);
  DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//使能DMA1通道5中断，注意一定要是“DMA_IT_TC”，否则会出现进不了中断的问题。
  
  #endif




 // for(;;)
//  {
//  
//  SpiSend8ByteY(0x55);
//  
//  }




  /* SPInny Re-configuration ---------------------------------------------------*/
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPInny, &SPI_InitStructure);
  
  #if SELECTED_SPI_INT == 2
  
DMA_Cmd(SPI1_MASTER_Tx_DMA_Channel, ENABLE);
  
#endif
  
  
}

void SpiInit_nnz(void)
{
	
	DMA_DeInit(SPI2_MASTER_Tx_DMA_Channel);
	
	
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();


NVIC_Configuration_DMA_nnz();
NVIC_Configuration_SPI_nnz();

RCC_AHBPeriphClockCmd(SPI2_MASTER_DMA_CLK, ENABLE);
  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI2_MASTER_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)( SPInnz_Buffer_Tx  );   //
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = SPI_DMA_BufferSize4;//SPIBufferSize4  ; //
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(SPI2_MASTER_Tx_DMA_Channel, &DMA_InitStructure);


  /* 1st phase: SPInny Master and SPInnz Slave */
  /* SPInny Config -------------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;//SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;           //SPI_Mode_Slave;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;       //SPI_DataSize_16b
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;            //SPI_CPHA_1Edge
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;               //SPI_NSS_Hard
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//6.4    SPI_BaudRatePrescaler_4;  0.1us
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPInnz, &SPI_InitStructure);



  SPI_I2S_DMACmd(SPInnz, SPI_I2S_DMAReq_Tx, ENABLE);

  /* Enable SPInnz */
  SPI_Cmd(SPInnz, ENABLE);

   #if SELECTED_SPI_INT == 1

   SPI_I2S_ITConfig(SPInnz, SPI_I2S_IT_TXE, ENABLE);

   #elif SELECTED_SPI_INT == 2

   DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);//使能DMA1通道5中断，注意一定要是“DMA_IT_TC”，否则会出现进不了中断的问题。

   #elif SELECTED_SPI_INT ==3
   SPI_I2S_ITConfig(SPInnz, SPI_I2S_IT_TXE, ENABLE);  
   DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);//使能DMA1通道5中断，注意一定要是“DMA_IT_TC”，否则会出现进不了中断的问题。

   #endif

  /* SPInnz Re-configuration ---------------------------------------------------*/
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPInnz, &SPI_InitStructure);

DMA_Cmd(SPI2_MASTER_Tx_DMA_Channel, ENABLE);

}


/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{


  /* PCLK2 = HCLK/2 */
//RCC_PCLK2Config(RCC_HCLK_Div8); 
//RCC_PCLK1Config(RCC_HCLK_Div8); 
/* Enable peripheral clocks --------------------------------------------------*/

//void RCC_PCLK2Config(uint32_t RCC_HCLK)



#if  0
  /* Enable GPIO clock for SPInny and SPInnz */
  RCC_APB2PeriphClockCmd(SPInny_GPIO_CLK | SPInnz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable SPInny Periph clock */
  RCC_APB1PeriphClockCmd(SPInny_CLK, ENABLE);
                           
#else
  /* Enable SPInny clock and GPIO clock for SPInny and SPInnz */
  RCC_APB2PeriphClockCmd(SPInny_GPIO_CLK | SPInnz_GPIO_CLK | SPInny_CLK, ENABLE);
#endif
  /* Enable SPInnz Periph clock */
  RCC_APB1PeriphClockCmd(SPInnz_CLK, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

#if 0
  /* Enable SPI3 Pins Software Remapping */
  GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
#endif

  /* Configure SPInny pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = SPInny_PIN_SCK  | SPInny_PIN_MOSI;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPInny_GPIO, &GPIO_InitStructure);

  /* Configure SPInnz pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = SPInnz_PIN_SCK  | SPInnz_PIN_MOSI;
  GPIO_Init(SPInnz_GPIO, &GPIO_InitStructure);
}




void SpiSendDMAnny( unsigned char Size4 )//SPI_DMA_BufferSize4  SPIBufferSize4
{
	    // Wait for SPInny Tx buffer empty
    while (SPI_I2S_GetFlagStatus(SPInny, SPI_I2S_FLAG_TXE) == RESET);
		   DMA1_Channel3->CNDTR = Size4;  //SPI_DMA_BufferSize4  SPIBufferSize4;
       DMA_Cmd(DMA1_Channel3,ENABLE);	
}

void SpiSendDMAnnz( unsigned char Size4 )//SPI_DMA_BufferSize4  SPIBufferSize4
{
	    // Wait for SPInny Tx buffer empty
    while (SPI_I2S_GetFlagStatus(SPInnz, SPI_I2S_FLAG_TXE) == RESET);
		   DMA1_Channel5->CNDTR = Size4;  //SPI_DMA_BufferSize4  SPIBufferSize4;
       DMA_Cmd(DMA1_Channel5,ENABLE);	
}


void SpiSend8ByteY( unsigned char aaa )
{

    /* Wait for SPInny Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPInny, SPI_I2S_FLAG_TXE) == RESET);

          SPI_I2S_SendData(SPInny, aaa);

}






void SpiSend8ByteZ( unsigned char aaa  )
{

    /* Wait for SPInny Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPInnz, SPI_I2S_FLAG_TXE) == RESET);
    /* Send SPInnz data */
    SPI_I2S_SendData(SPInnz, aaa);

}


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
