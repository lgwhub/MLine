/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/platform_config.h 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   Evaluation board specific configuration file.
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

/* Define to prevent recursive inclusion -------------------------------------*/

//	#include   "spi.h"

#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
   
   
   
  //////////////////
 
  #define SPI1_MASTER_DMA                DMA1
  #define SPI1_MASTER_DMA_CLK            RCC_AHBPeriph_DMA1  
  #define SPI1_MASTER_Tx_DMA_Channel     DMA1_Channel3
  #define SPI1_MASTER_Tx_DMA_FLAG        DMA1_FLAG_TC3  
  #define SPI1_MASTER_DR_Base            0x4001300C
  //0x4000300C  
  

  #define SPI2_MASTER_DMA                DMA1
  #define SPI2_MASTER_DMA_CLK            RCC_AHBPeriph_DMA1  
  #define SPI2_MASTER_Tx_DMA_Channel     DMA1_Channel5
  #define SPI2_MASTER_Tx_DMA_FLAG        DMA1_FLAG_TC5  
  #define SPI2_MASTER_DR_Base            0x4000380C  
  ////////////// 
   

  #define SPInny                   SPI1
  #define SPInny_CLK               RCC_APB2Periph_SPI1
  #define SPInny_GPIO              GPIOA
  #define SPInny_GPIO_CLK          RCC_APB2Periph_GPIOA  
  #define SPInny_PIN_SCK           GPIO_Pin_5
  //#define SPInny_PIN_MISO          GPIO_Pin_6
  #define SPInny_PIN_MOSI          GPIO_Pin_7
  
  #define SPInnz                    SPI2
  #define SPInnz_CLK                RCC_APB1Periph_SPI2
  #define SPInnz_GPIO               GPIOB
  #define SPInnz_GPIO_CLK           RCC_APB2Periph_GPIOB 
  #define SPInnz_PIN_SCK            GPIO_Pin_13
  //#define SPInnz_PIN_MISO           GPIO_Pin_14
  #define SPInnz_PIN_MOSI           GPIO_Pin_15 
          

#define SPIBufferSize4 ( 4 )
#define SPI_DMA_BufferSize4   4

extern unsigned char  SPInny_Buffer_Tx[ SPIBufferSize4 ];

extern unsigned char  SPInnz_Buffer_Tx[ SPIBufferSize4 ];





void SpiSend8ByteY( unsigned char aaa );

void SpiSend8ByteZ( unsigned char aaa );

void SpiInit_nny(void);
void SpiInit_nnz(void);


void SpiSendDMAnny( unsigned char Size4 );//SPIBufferSize4

void SpiSendDMAnnz( unsigned char Size4 );//SPIBufferSize4

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
