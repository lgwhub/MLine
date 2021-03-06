
	#include   "spi.h"
	#include "LedDisp.h"
	#include "includes.h"
//#define SPIBufferSize4 4
//





unsigned char DispBufnny[24];


unsigned char DispBufnnz[24];

unsigned char   Alm_Flag1;    //报警指示灯
unsigned char   Alm_Flag2;    //报警指示灯
unsigned char   SngnalLed[4];      //单独指示灯

unsigned char Process_One_Numb1(void);
unsigned char Process_One_Numbnnz(void);
unsigned long  Process_N_NUMBnny(void);
unsigned long  Process_N_NUMBnnz(void);


//前三字节是位码，后一字节是段码

union _Num_X
{
unsigned long int a32;
unsigned char byte4[4];	
};
union _Num_X    NUMnny , NUMnnz ;




//seg7 difine                                        
#define seg_a   0x80                                                   
#define seg_b   0x40                                                   
#define seg_c   0x20                                                   
#define seg_d   0x10                                                   
                                                                        
#define seg_e   0x08
#define seg_f   0x04                                                   
#define seg_g   0x02                                                  
 


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
	seg_a ,                                                        // -a   上横  0x10       g 16
	seg_g ,                                                        // -g	 中横  0x11       h  17     
	seg_d ,                                                        // -d   下横         i
	seg_a + seg_b + seg_f  + seg_g ,	                             //上口               j
  seg_c + seg_d + seg_e  + seg_g ,                               //下口               k   20
	seg_a + seg_b + seg_f  ,	                                     //上盖        0x15      l
  seg_c + seg_d + seg_e  ,                                       //下盖               m   22
	0                                                              //space		   0x17       n   23
	                                                                      
}    ; 


void PutValToDispBf(unsigned short val , unsigned char  *position )
{
	//position+12   position+8  position+4  position+0   DispBufnny
	
	if(val>9999)val=9999;
	
	if(val<1000)  *position         = 0x17 ;  //隐
	else          *position         = val/1000%10;
	
  if(val<100)   *( position +1)   = 0x17 ;  //隐
	else          *( position +1)   = val/100%10;
	
	if(val<10)    *( position +2)   = 0x17 ;  //隐
	else 	        *( position +2)   = val/10%10;
	
	*( position +3) = val%10;	
} 




//四片595最多可以送的位数
#define  	DigMax    24	
	
//要送的位数
#define  	DigNmb    19






unsigned long  Process_N_NUMBnny(void)
{

unsigned char  i;
unsigned long temp32;
static unsigned long LastNum=0;   //键盘采样用
unsigned long KeyGetBit;   //键盘采样用	

KeyGetBit =0;

	temp32 = ( 0x000001 << ( DigMax - DigNmb ) );   //不用的位先移掉
	
	
	
	if(Alm_Flag1 == 0)  //报警指示灯
	   {
     NUMnny.a32 = 0x0;
     }
	else
     {
		NUMnny.a32 = temp32;
	   }

	NUMnny.byte4[3]  =  0xff;
	 
	if ( Process_One_Numb1() )
		{
			KeyGetBit += LastNum;
		}
	
	LastNum = temp32;
	temp32 <<=1;
	NUMnny.a32 = temp32;
	
	
	//单独的指示灯
	NUMnny.byte4[3]  =   ~SngnalLed[0];
	if ( Process_One_Numb1() )
		{
			KeyGetBit += LastNum;
		}
	
	LastNum = temp32;
	temp32 <<=1;
	NUMnny.a32 = temp32;
	
		
	NUMnny.byte4[3]  =   ~SngnalLed[1];
	if ( Process_One_Numb1() )
		{
			KeyGetBit += LastNum;
		}
	
	LastNum = temp32;
	temp32 <<=1;
	NUMnny.a32 = temp32;	
		
for(i=0;i<DigNmb-3;i++)  //16数码管，2-3排指示灯，一个键盘，19-24
	{

	NUMnny.byte4[3]  =  ~LedSegTab [  DispBufnny[i] ] ;// 第4个字节
	
	if ( Process_One_Numb1() )
		{
			KeyGetBit += LastNum;
		}
	
	//NUMnny.byte4[3]  =  0;   //第四字节是A32的最高位

  LastNum = temp32;
  temp32 <<=1;
	NUMnny.a32 = temp32;
	
		
	}
return	KeyGetBit;
}

unsigned long  Process_N_NUMBnnz(void)
{

unsigned char  i;
unsigned long temp32;
static unsigned long LastNum=0;   //键盘采样用
unsigned long KeyGetBit;   //键盘采样用		
	
	KeyGetBit =0;
	
	temp32 = ( 0x000001 << ( DigMax - DigNmb ) );   //不用的位先移掉
	
	if(Alm_Flag2 == 0)  //报警指示灯
	   {
     NUMnnz.a32 = 0x0;
     }
	else
     {
		NUMnnz.a32 = temp32;
	   }

	NUMnnz.byte4[3]  =  0xff; 
	if( Process_One_Numbnnz() )
	   {
	   	KeyGetBit += LastNum;
	  }
	
	LastNum = temp32;
	temp32 <<=1;
	NUMnnz.a32 = temp32;
	
	
	
	NUMnnz.byte4[3]  =   ~SngnalLed[2];
	if( Process_One_Numbnnz() )
	   {
	   	KeyGetBit += LastNum;
	  }
	LastNum = temp32;
	temp32 <<=1;
	NUMnnz.a32 = temp32;
	
		
	NUMnnz.byte4[3]  =   ~SngnalLed[3];
	if( Process_One_Numbnnz() )
	   {
	   	KeyGetBit += LastNum;
	  }
	LastNum = temp32;
	temp32 <<=1;
	NUMnnz.a32 = temp32;	
		
for(i=0;i<DigNmb-3;i++)  //16数码管，2-3排指示灯，一个键盘，19-24
	{

	NUMnnz.byte4[3]  =  ~LedSegTab [  DispBufnnz[i] ] ;// 第4个字节
	
	if( Process_One_Numbnnz() )
	   {
	   	KeyGetBit += LastNum;
	  }
	//NUMnnz.byte4[3]  =  0;   //第四字节是A32的最高位

  LastNum = temp32;

  temp32 <<=1;
	NUMnnz.a32 = temp32;
	
		
	}
return	KeyGetBit;	
}




/////////////////////////////////////


unsigned char Process_One_Numb1(void)
{
	unsigned char i;
	unsigned char KeyBit=0;
	
	for(i=0;i<4;i++)
	{
	SPInny_Buffer_Tx[i] =	NUMnny.byte4[i] ;  //4个字节
		
	}
	
	SPI_STR_Lowy;

  //OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒

  SpiSendDMAnny( SPI_DMA_BufferSize4  );   //SPIBufferSize4
	
//  if(!DMA_GetFlagStatus(SPI1_MASTER_Tx_DMA_FLAG))

  OSTimeDly(OS_TICKS_PER_SEC/1000);	    //延时0.002秒.等4字节传送完成
    
	  if(SPI_Kiny)
  	{//读
  		KeyBit=1;
  	}	
   else KeyBit=0;
//更新
 
  SPI_STR_Highy;    //激活输出
  
	//OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.01秒
	
return KeyBit;
	
}

/////////////////////////////////////


unsigned char Process_One_Numbnnz(void)
{
	unsigned char i;
	unsigned char KeyBit=0;
	
	for(i=0;i<4;i++)
	{
	SPInnz_Buffer_Tx[i] =	NUMnnz.byte4[i] ;  //4个字节
		
	}
	

	SPI_STR_LownnZ;
	

  //OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒

  SpiSendDMAnnz( SPI_DMA_BufferSize4  );   //SPIBufferSize4


//  if(!DMA_GetFlagStatus(SPI2_MASTER_Tx_DMA_FLAG))


  OSTimeDly(OS_TICKS_PER_SEC/1000);	    //延时0.002秒.等4字节传送完成
  
	
	if(SPI_KinnnZ)
  	{//读
  	KeyBit = 1;
  	}    
  else	KeyBit = 0;
  	
//  while (!DMA_GetFlagStatus(SPI2_MASTER_Tx_DMA_FLAG));

//更新

  SPI_STR_HighnnZ;    //激活输出

	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
	return KeyBit;
	
}






