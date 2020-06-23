
	#include   "spi.h"
	#include "LedDisp.h"
	#include "includes.h"
//#define SPIBufferSize4 4
//
//
//extern uint8_t SPInny_Buffer_Tx[SPIBufferSize4];
//extern uint8_t SPInnz_Buffer_Tx[SPIBufferSize4];

//uint8_t SPInny_Buffer_Tx[SPIBufferSize4] = {0x01, 0x02, 0x03, 0x04};



//前三字节是位码，后一字节是段码

union _Num_X
{
unsigned long int a32;
unsigned char byte4[4];	
};
union _Num_X    NUMnny , NUMnnz ;




//seg7 difine                                        
#define seg_a   0x08                                                   
#define seg_b   0x04                                                   
#define seg_c   0x02                                                   
#define seg_d   0x01                                                   
                                                                        
#define seg_f   0x080                                                  
#define seg_g   0x040                                                  
#define seg_e   0x020  


unsigned char LedSegTab[]=                                         
{
	seg_a + seg_b + seg_c + seg_d + seg_e  + seg_f ,               //0          
	seg_b + seg_c ,                                                //1                      
	seg_a + seg_b + seg_d + seg_e + seg_g ,                        //2	            
	seg_a + seg_b + seg_c + seg_d +  seg_g ,                       //3             
	seg_b + seg_c + seg_f + seg_g  ,                               //4                
	seg_a + seg_c + seg_d + seg_f + seg_g ,                        //5             
	seg_a + seg_c + seg_d + seg_e + seg_f + seg_g ,                //6           
	seg_a + seg_b + seg_c ,                                        //7	                  
	seg_a + seg_b + seg_c + seg_d + seg_e + seg_f + seg_g ,        //8	
	seg_a + seg_b + seg_c + seg_d + seg_f + seg_g ,                //9	
	seg_a + seg_b + seg_c + seg_e + seg_f + seg_g ,                //A                                        
	seg_c + seg_d + seg_e + seg_f + seg_g ,                        //b                      
	seg_a + seg_d + seg_e + seg_f  ,                               //C	            
	seg_b + seg_c + seg_d + seg_e + seg_g  ,                       //d             
  seg_a + seg_d + seg_e + seg_f + seg_g  ,                       //E 
  seg_a + seg_e + seg_f + seg_g,                                 //F                 
	seg_a ,                                                        // -a   上横         g 16
	seg_g ,                                                        // -g	 中横         h  17     
	seg_d ,                                                        // -d   下横         i
	seg_a + seg_b + seg_f  + seg_g ,	                             //上口               j
  seg_c + seg_d + seg_e  + seg_g ,                               //下口               k   20
	seg_a + seg_b + seg_f  ,	                                     //上盖               l
  seg_c + seg_d + seg_e  ,                                       //下盖               m   22
	0                                                              //space		          n   23
	                                                                      
}    ; 


unsigned char DispBufnny[24]=
{
	0x0f,	0x0f,	0x0f,	0x0f,
	0x0f,	0x0f,	0x0f,	0x0f,	
	0x0f,	0x0f,	0x0f,	0x0f,	
	0x0f,	0x0f,	0x0f,	0x0f,	
	0x0f,	0x0f,	0x0f,	0x0f,
	0x0f,	0x0f,	0x0f,	0x0f	

	
};


unsigned char DispBufnnz[24]=
{
	0x05,	0x05,	0x05,	0x05,
	0x05,	0x05,	0x05,	0x05,	
	0x05,	0x05,	0x05,	0x05,	
	0x05,	0x05,	0x05,	0x05,	
	0x05,	0x05,	0x05,	0x05,
	0x05,	0x05,	0x05,	0x05	

	
};



void Process_One_Numb1(void);
void Process_One_NumbnnZ(void);
void Process_N_NUMBnny(void);
void Process_N_NUMBnnZ(void);




void Process_N_NUMBnny(void)
{

unsigned char  i;
	
NUMnny.a32 = 0x000001;

for(i=0;i<20;i++)  //16数码管，2-3排指示灯，一个键盘，19-24
	{
	
	NUMnny.byte4[3]  =  LedSegTab [  DispBufnny[i] ] ;// 第4个字节
	
	Process_One_Numb1();
	
	NUMnny.byte4[3]  =  0;
	
	NUMnny.a32 <<= 1 ;
		
	}
	
}


void Process_N_NUMBnnZ(void)
{

unsigned char  i;
	
NUMnnz.a32 = 0x000001;

for(i=0;i<20;i++)  //16数码管，2-3排指示灯，一个键盘，19-24
	{
	
	NUMnnz.byte4[3]  =  LedSegTab [  DispBufnnz[i] ] ;// 第4个字节
	
	Process_One_NumbnnZ();
	
	NUMnnz.byte4[3]  =  0;
	
	NUMnnz.a32 <<= 1 ;
		
	}
	
}


/////////////////////////////////////


void Process_One_Numb1(void)
{
	unsigned char i;
	
	
	for(i=0;i<4;i++)
	{
	SPInny_Buffer_Tx[i] =	NUMnny.byte4[i] ;  //4个字节
		
	}
	

	
	//SPI_STR_Highy;
	SPI_STR_Lowy;
	

  //OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒
	
	//SpiSend8ByteY( 0x55);//SPInny_Buffer_Tx[0] );
  
  SpiSendDMAnny( SPI_DMA_BufferSize4  );   //SPIBufferSize4


	
//  if(!DMA_GetFlagStatus(SPI1_MASTER_Tx_DMA_FLAG))
//	  {
//    OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒
//	  }
//  else {
//    OSTimeDly(OS_TICKS_PER_SEC/400);	    //延时0.002秒
//	  }	

  
  OSTimeDly(OS_TICKS_PER_SEC/400);	    //延时0.002秒.等4字节传送完成
    
//  while (!DMA_GetFlagStatus(SPI1_MASTER_Tx_DMA_FLAG));

//更新
  //SPI_STR_Lowy;
  SPI_STR_Highy;    //激活输出
  
	OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
	
  if(SPI_Kiny)
  	{//读
  		
  	}

	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
	
}

/////////////////////////////////////


void Process_One_NumbnnZ(void)
{
	unsigned char i;
	
	
	for(i=0;i<4;i++)
	{
	SPInnz_Buffer_Tx[i] =	NUMnnz.byte4[i] ;  //4个字节
		
	}
	

	
	//SPI_STR_HighnnZ;
	SPI_STR_LownnZ;
	

  //OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒
	
	//SpiSend8ByteZ( 0x55);//SPInnZ_Buffer_Tx[0] );
  
  SpiSendDMAnnz( SPI_DMA_BufferSize4  );   //SPIBufferSize4


	
//  if(!DMA_GetFlagStatus(SPI2_MASTER_Tx_DMA_FLAG))
//	  {
//    OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒
//	  }
//  else {
//    OSTimeDly(OS_TICKS_PER_SEC/400);	    //延时0.002秒
//	  }	

  
  OSTimeDly(OS_TICKS_PER_SEC/400);	    //延时0.002秒.等4字节传送完成
    
//  while (!DMA_GetFlagStatus(SPI2_MASTER_Tx_DMA_FLAG));

//更新
  //SPI_STR_LownnZ;
  SPI_STR_HighnnZ;    //激活输出
  
	OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
	
  if(SPI_KinnnZ)
  	{//读
  		
  	}

	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
	
}






