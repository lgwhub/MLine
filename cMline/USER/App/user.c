//user.c

#include "includes.h"
//extern 





OS_EVENT *OSSemTest1;
OS_EVENT *OSSemTest2;

OS_EVENT *OSSemMotors;
OS_EVENT *OSSemUart1;



OS_EVENT *OSSemTimePid_StepMotor;
OS_EVENT *OSSemTimePid_PWM;

OS_EVENT *OSSemProcCmdx;


//uchar LenFromUser;	
//uchar BufFromUser[252];







unsigned char lAddressKey;  //拨码开关PB12-PB15，值，最低4位


unsigned char EventTimeBuz=0;
unsigned char EventTimeLed=0;



////////////////////////////////////////////
#define   KEY_BIT_STOP                0x00800000
#define   KEY_BIT_RUN                 0x00400000
#define   KEY_BIT_xxx                   0x00200000
#define   KEY_BIT_AUTO_BAK   0x00100000
#define   KEY_BIT_SLOW              0x00080000



unsigned long ShiftKeyCurnny;   //显示板键盘当前值
unsigned long ShiftKeyBnny,ShiftKeyCnny;
unsigned long ShiftKeySavenny;

unsigned long ShiftKeyCurnnz;   //显示板键盘当前值
unsigned long ShiftKeyBnnz,ShiftKeyCnnz;
unsigned long ShiftKeySavennz;

//unsigned char FlagRuningnny;   //控制 34 6 BLDC电机   34 步进电机
//unsigned char FlagRuningnnz;   //控制 12 5 BLDC电机   12 步进电机
#define  FlagRuningnny   (   Coldw.Flag_Runingnny  ) //控制 34 6 BLDC电机   34 步进电机    (Coldw.T_set )              //温度设置值
#define  FlagRuningnnz   (    Coldw.Flag_Runingnnz )    //控制 12 5 BLDC电机   12 步进电机  // (Coldw.TC_sx )                //温度上限设置值


unsigned  short int  ApmSetBuf[ MAX_BLDC_CH6 + 1 ];   //速度设定值中间变量   
unsigned  short int  ApmSetVal[ MAX_BLDC_CH6 + 1 ];   //速度设定值递增变量  //   ApmSetBuf     --->>>>  ApmSetVal    ..........       


unsigned  short int  BLDC_PwmBuf[ MAX_BLDC_CH6 + 1 ];   //pwm速度中间变量
unsigned  short int  BLDC_PwmVal[ MAX_BLDC_CH6 + 1 ];   //pwm递增速度控制值   1000  max 

unsigned  char Capture_Flag[ MAX_BLDC_CH6 + 1 ] ;
//unsigned  long int Apm_FREQ2[ MAX_BLDC_CH6 +1 ] ;   //前一个速度测量值
//unsigned  long int Apm_FREQ1[ MAX_BLDC_CH6 +1 ] ;   //上一个速度测量值
unsigned  long int Apm_FREQ[ MAX_BLDC_CH6 +1 ] ;    //速度测量值  0.1HZ
unsigned  long int Apm_ForLed[ MAX_BLDC_CH6 +1 ] ;    //LED显示速度测量值  apm  or 10APM
//unsigned  long int Apm_ForPc[ MAX_BLDC_CH6 +1 ] ;    //电脑显示速度测量值  apm

unsigned  long int Capture_number[ MAX_BLDC_CH6 + 1 ] ;

//unsigned  long int Capture_number_All32  = 0 ;  //永远计数器。脉冲测量用


//#if Flag_test_spi_DMA     
//  unsigned  long int Capture_testSPI_number[6+1] ;
//#endif

unsigned  long int CaptureValueStart[6+1] ;
unsigned  long int CaptureValueEnd[6+1];
//因为使用16位定时器，所以这两个变量也使用16位
//unsigned  short int CaptureValueStart[6+1] ;
unsigned  long int CaptureValueHigh_T3;
unsigned  long int CaptureValueHigh_T4;
//unsigned  short int CaptureValueEnd[6+1];



signed short int PowerOutBuf[2+( MAX_BLDC_CH6 )];
signed short int TestOutBuf [2+( MAX_BLDC_CH6 ) ];

///////////////////////////////////////////////////////////////////////
void ViewTestStatu(uchar *text)
{
#if (OS_VIEW_MODULE == DEF_ENABLED)
			OSView_TxStr(text, 1);
#else
			SendTestStatu(text);
#endif
}
//////////////////////////////////////////////


void VirtualPwmOutPin(unsigned char ch , unsigned char High)
{
	switch(ch)
	{
		case 0:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat1;
			  }
			else{//关闭有效电平
				  ClrHeat1;
			  }
	  break;
	  
		case 1:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat2;
			  }
			else{//关闭有效电平
				   ClrHeat2;
			  }
	  break;	
	  
		case 2:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat3;
			  }
			else{//关闭有效电平
				  ClrHeat3;
			  }
	  break;
	  
		case 3:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat4;
			  }
			else{//关闭有效电平
				   ClrHeat4;
			  }
	  break;	    

		case 4:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat5;
			  }
			else{//关闭有效电平
				  ClrHeat5;
			  }
	  break;
	  
		case 5:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat6;
			  }
			else{//关闭有效电平
				   ClrHeat6;
			  }
	  break;
	  
		case 6:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat7;
			  }
			else{//关闭有效电平
				  ClrHeat7;
			  }
	  break;
	  
		case 7:
			if(High != 0)
			  {//输出有效电平
			  	SetHeat8;
			  }
			else{//关闭有效电平
				   ClrHeat8;
			  }
	  break;	  		
	}
	
}
//////////////////////////////////////////////
void TaskRush(void * pdata)  //Virtual
{
INT8U err;
unsigned short int   temp32;
unsigned char  i ;

pdata = pdata;                          	 	// 避免编译警告		

//#if CONFIG_ADC
//ADC_Configuration();
//#endif

	    PutValToDispBf(6666 , DispBufnny+12 );
        PutValToDispBf( 0, DispBufnny+8 );
        PutValToDispBf(4444 , DispBufnny+4 );
        PutValToDispBf(3333 , DispBufnny+0 );
        
        PutValToDispBf(5555 , DispBufnnz+12 );
        PutValToDispBf(0, DispBufnnz+8 );
        PutValToDispBf(2222 , DispBufnnz+4 );
        PutValToDispBf(1111 , DispBufnnz+0 ) ;     
        
		OSTimeDly(OS_TICKS_PER_SEC*2);	    //延时10ms 

for(;;)
		{
			
			for(  i = 0  ;  i < MAX_BLDC_CH6  ;  i ++  )
			{
			 temp32	 = GetAverage( &AvergeBufI[ i ][0]    ,  MaxAvergeList  );  //GetAverSS
			
			 switch ( i )
                 {    
                  case 0:
                  case 1:
                  case 2:
                  case 3:                  	
                  	//  max 10000   apm      2x3
                  Apm_ForLed[ i ]   = temp32 / 20;    // Apm_FREQ[ i ]  / 20;  //除以20
                  Coldw.ApmGt[i]  =  (float)temp32 / 2 ;//(float)Apm_FREQ[ i ]/2; //除以2  	 
                                
                                 
                  break;
                  
                  case 4:
                  case 5: 
                  	  	//  max 20000   apm      4x3
                   Apm_ForLed[ i ] =  temp32 / 10;  //Apm_FREQ[ i ]  / 10;  //除以10    
                   Coldw.ApmGt[i]  =   (float)temp32;//(float)Apm_FREQ[ i ];	            
                  break;	  
                             
                  }
			}
		
		        //第1组显示	
        PutValToDispBf(Apm_ForLed[5], DispBufnny+12 );   //Coldw.ApmGt
        if(  FlagRuningnny >=1  )   //控制 34 步进电机
        	    {//显示步进电机速度
                  PutValToDispBf(  Coldw.ApmCt[6], DispBufnny+8 ); 
               }
        else{
        	     PutValToDispBf(  0, DispBufnny+8 ); 
             }       
        PutValToDispBf( Apm_ForLed[3], DispBufnny+4 );
        PutValToDispBf(Apm_ForLed[2] , DispBufnny+0 );
        
        
        //第2组显示
        
        PutValToDispBf(Apm_ForLed[4] , DispBufnnz+12 );
         if(FlagRuningnnz >= 1 )  //控制 12  步进电机
         	{
         		PutValToDispBf( Coldw.ApmCt[6], DispBufnnz+8 );
         	}
        else
        	{
        		PutValToDispBf( 0, DispBufnnz+8 );
        	}
        PutValToDispBf( Apm_ForLed[1], DispBufnnz+4 );
        PutValToDispBf(Apm_ForLed[0] , DispBufnnz+0 ) ;      
        
		  OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒

		}		
}

////////////////////////////////////////
void Test_Adc(void)
{
///////////////////////////////////////////////////////////////////////
//		  #if CONFIG_ADC
					
					  
//					#if CONFIG_UART1
//					AdcFilter();
//						 	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 1) 
//
//											OSSemPend(OSSemUart1,0,&err);
//											
//											SendText_UART1("....");
//											for(i=0;i<MAX_ADC_CH;i++)
//														{
//														MakeValAsc16("",wAdcResoult[i]*330/4096,"V,",buf);
//														
//														SendText_UART1(buf);
//														
//														}
//														
//											SendText_UART1("\r\n");
//											
//											OSSemPost(OSSemUart1);
//											
//							#endif
//					#endif
					
					
//					#if CONFIG_UART1	== 0
//					//ViewTestStatu
//					//AdcFilter();
//					ViewTestStatu("....");//SendText_UART1("....");
//											for(i=0;i<MAX_BLDC_CH6;i++)
//														{
//														MakeValAsc16("",(uint16)(wAdcResoult[i]*10),"(0.1C),",buf);
//														
//														ViewTestStatu(buf);//SendText_UART1(buf);
//														
//														}
//					ViewTestStatu("\r\n");
//					#endif
//					
//			#endif
//			
//			
//
//			OSTimeDly(OS_TICKS_PER_SEC);
}

////////////////////////////////////////
void Test_Uart3(void)
{
uchar temp;
		#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER !=3)
					#if CONFIG_UART3
							if(GetOneFromUart3(&temp))
									{
										Uart3CharSend(temp);
									}
					#endif
		#endif
}
////////////////////////////////////////////////////////////////////
void ModbusCommand2(void)
{
	  INT8U err;
	  signed short int  steps;
	  unsigned char i;
	  
	  if(Coldw.Moter_step_set == 0)return;
	  	
	  if(  Coldw.Moter_direction  == 0 )      //方向
	  	  {
	  	  	  
	  	     	if(Coldw.Moter_step_set>10000)       //强制走几步
	  	     		  {
	  	     			 steps = 10000;
	  	     		  }
	  	     	else{
	  	     		  steps = (signed short int)Coldw.Moter_step_set;
	  	     	    }	
	  	    	

	  	  }
	  else if(	 Coldw.Moter_direction  == 1 )      //方向  
	  	 {
	  	 	     
	        		if(Coldw.Moter_step_set>10000)       //强制走几步
	        			   {
	        				  steps = -10000;
	        			   }
	        		else{
	        			  steps = - ((signed short int)Coldw.Moter_step_set);
	        		    }	
	        			
     	 }


	for( i=0; i<MAX_BLDC_CH6 ; i++)
	              {  		
	              if(	( Coldw.one_unit_flag == 0 ) || ( Coldw.one_unit_flag == ( i + 1 )  ) )
	              	    {
	  	     	           OSSemPend(OSSemMotors,0,&err);	
	  	     	           StepMotRun(i,steps);//MotorsRun(i,steps);
                       OSSemPost(OSSemMotors);
                       }
                      
	  	          }	  	 
	  	          
Coldw.Moter_step_set =0;

Coldw.one_unit_flag = 0;


}
////////////////////////////////////////////////////////////////////
void CheckAdrressKey(void)  //分机地址设置拨码开关
{
	static unsigned char old1,old2,old3,old4,old5;
	
	old1 = GPIO_ReadInputData(GPIOC); //PC0123 ; 
	
	if((old2==old1)&&(old3==old2)&&(old4==old3)&&(old5==old4))//滤波
		{
				lAddressKey=old1;  //拨码开关PB12-PB15，值，最低4位
		}
	old5=old4;
	old4=old3;	
	old3=old2;
	old2=old1;
}
/////////////////////////////////////////////////////////
void TaskModbus(void * pdata)
{
	CPU_SR          cpu_sr;
INT8U err;

unsigned long temp16;

pdata = pdata;                          	 	// 避免编译警告		

lAddressKey=0;  //拨码开关PB12-PB15，值，最低4位

TimeForSaveParam = 0;

 Default_ParamInit0();//不需要保存的参数
 Default_ParamInit1();    ////需要保存的参数
 Default_ParamInit2();    ////整定值
 
// Default_ParamInit();    //?????????问题



  if(Load_Param()==0)		//取设定值
   {
 /*    
    gData[0].AnyError|=8;
    gData[1].AnyError|=8;
    gData[2].AnyError|=8;
    gData[3].AnyError|=8;  
    
      
    //自动恢复默认值，不允许
     _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufB
    cMemBufB[Max_MemBuf-2] =  FlagParamInitnized; 
    Write_Param();
*/  
		 
		 TimeForSaveParam = 0;
   }





temp16 =  Stm32IdSum6 ;

#if CONFIG_CHECK_DEVICE_ID
	
	InitSTM32DeciceID();
	
	
	
		if(GetStm32F103_DeviceId_Sum6() == temp16 )  //Pmbuf->Stm32Id )
				{
					STM32DeviceId.Checked=1;
				}
		else{
			STM32DeviceId.Checked=0;
				}
#endif	

//                Stm32IdSum6 
  		  	  #if CONFIG_CHECK_DEVICE_ID	
  		  	  	
  		     Stm32IdSum6    = GetStm32F103_DeviceId_Sum6();  
  		      
  		      #endif



//第一块   32FFD905564E363131600551




//第二块  0xff31,0x05db,0x5641,0x3636,0x7428,0x5709,    0xc0ff,0xfffc,0x9768,0x00ff,0xc13e,0x7f80,0x5aa5,0x00ff,0x00ff,0x00ff,0x00ff,0x00ff,0x00ff,0x00ff
//0x31,0xFF,0xDB,0x05,0x41,0x56,0x36,0x36,0x28,0x74,0x09,0x57
/*
芯片内BootLoader版本号：2.2
芯片PID：00000414
芯片FLASH容量为512KB
芯片SRAM容量为65535KB(此信息仅供参考,新版本芯片已不包含此信息)
96位的芯片唯一序列号：31FFDB054156363628740957
读出的选项字节:
A55AFF00FF00FF00FF00FF00FF00FF00
*/

OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒

ModbusInit();


//#if TEST_MODBUS_78
// TestModbus();
//#endif

OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒

for(;;)
		{
     

    OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时2毫秒

    //CheckAdrressKey();//分机地址设置拨码开关
    //Coldw.SubAdr = 80 + ( lAddressKey & 0x0f ) ;//          地址设置
	Coldw.SubAdr = 80;
	
	CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
 
 ModbusTimeHandler();	
    
    CPU_CRITICAL_EXIT();
	
		
		
		
		
		
		
		GetModbusPark();  //慢点也可以
		
		}
}
////////////////////
void TaskTimePr(void * pdata)
{
  INT8U err;
  uchar  i;  
  unsigned short int  timer1,timer2;

  pdata = pdata;                   // 避免编译警告		
  OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.5秒
  for(;;)
     {

      OSTimeDly( OS_TICKS_PER_SEC / 100 );	    //延时0.01秒
      
               timer1++;
               if(  timer1  >=  3 )  //30ms
                    {
                     timer1  = 0 ;
                     OSSemPost(OSSemTimePid_PWM);   //电加热PID控制周期

                    }
         
                timer2++;

                if(timer2 >= 100 ) //1s	
                    {
                     timer2 = 0;
                     OSSemPost(OSSemTimePid_StepMotor);   //水冷PID控制周期
                    }

       }
}
////////////////////


////////////////////
void TaskHpwm(void * pdata)
{
INT8U err;

unsigned char i;

pdata = pdata;                          	 	// 避免编译警告		

    for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )	
              {
              	ApmSetBuf [ i ] =  0 ; //   ApmSetBuf     --->>>>  ApmSetVal    ..........       
              	ApmSetVal [ i ] =  0 ;
                          	
              }


OSTimeDly( OS_TICKS_PER_SEC / 100);	    //延时0.01秒

for(;;)
		{
			
			OSSemPend(  OSSemTimePid_PWM , 0 , &err );  //   OSSemTimePid_Heat

		  if( FlagRuningnny  >=  1 )   //控制 34 6 BLDC电机
		  	  {
		  		ApmSetBuf[2] = ( unsigned short int ) Coldw.ApmCt[2]  * 2;  //3
		  		ApmSetBuf[3] = ( unsigned short int )  Coldw.ApmCt[3]  * 2;  //4
		  		ApmSetBuf[5] = ( unsigned short int ) Coldw.ApmCt[5];  //6
		  	  }
		  else{
		  		ApmSetBuf[2] = 0; //   ApmSetBuf     --->>>>  ApmSetVal    ..........       
		  		ApmSetBuf[3] = 0;
		  		ApmSetBuf[5] = 0;		  	
		      }  
		      	
		  if( FlagRuningnnz  >=  1 )  //控制 12 5 BLDC电机
		  	  {
		  		ApmSetBuf[0] = ( unsigned short int ) Coldw.ApmCt[0]  * 2 ;  //1
		  		ApmSetBuf[1] = ( unsigned short int ) Coldw.ApmCt[1]  * 2 ;  //2
		  		ApmSetBuf[4] = ( unsigned short int ) Coldw.ApmCt[4];  //5
		  	  }
		  else{
		  		ApmSetBuf[0] = 0;
		  		ApmSetBuf[1] = 0;
		  		ApmSetBuf[4] = 0;		  	
		      } 		  	
		  	
		  	//软启动  软加速  软减速  速度步进量
		  	#define APM_SET_ADD25  200
		  	#define APM_SET_DEC25  200


                    //   ApmSetBuf     --->>>>  ApmSetVal    ..........
        for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
			        {
                     if(   (  ApmSetVal [ i ]     +    APM_SET_ADD25   )        <            ApmSetBuf [i]    )  // s < a-100
                 	      { 
                 	   	   ApmSetVal [ i ]        +=   APM_SET_ADD25 ;                      // +100
                 	      }
                 else if ( ApmSetVal [ i ]       <      ApmSetBuf[i]    )     // +++++
                 	       {
                           ApmSetVal [ i ]        =    ApmSetBuf[i] ;          //970
                           }
                 else if (  ApmSetVal [ i ]            >             (  ApmSetBuf[i]  +  APM_SET_DEC25  )     )
     	                  {
                 	   	   ApmSetVal [ i ]        -=      APM_SET_DEC25;
                 	      }
                 else{
                             ApmSetVal [ i ]       =      ApmSetBuf[i] ;
                          }
                 
                  if( ApmSetVal [ i ] > 30000 )        
                      {
                      	ApmSetVal [ i ] = 30000;  
                      } 
     	        //Coldw.ApmDuty [ i ]   =    ApmSetVal [ i ];    //显示
     	
              }    



                     
          for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
			    {
                        if  (   ApmSetVal [i ]  >  100  )  //设定值至少大于100转
                        	            {
                                         HeatPidBuf[i].SetPoint = (float) ApmSetVal [ i ] ; //基本上多余 
			                                   PID_Calc(&Coldw.Pidx[0], &HeatPidBuf[i] ,      (float)Apm_FREQ [i]      ); //一般是error = SetPoint - NewPoint ,这里反过来
			                                 }
			          else        {//设定值太小了，或者关闭
			          	                  HeatPidBuf[i].Qx   =  0;
			          	                  HeatPidBuf[i].Ix     =  0;
				                           }      
			     }
	     		  	//软启动  软加速  软减速  步进量
		  	#define DLBC_STEP_ADD25  (10+190)
		  	#define DLBC_STEP_DEC25  (10+190)
        for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
			        {
                     if(   (  BLDC_PwmVal[ i ]  +  DLBC_STEP_ADD25   )  < HeatPidBuf[i].Qx    )  // s < a-100
                 	      { 
                 	   	   BLDC_PwmVal[ i ]  +=   DLBC_STEP_ADD25 ;                      // +100
                 	      }
                 else if ( BLDC_PwmVal[ i ]  < HeatPidBuf[i].Qx   )     // +++++
                 	    {
                        BLDC_PwmVal[ i ] =   HeatPidBuf[i].Qx   ;          //970
                        }
                 else if (  BLDC_PwmVal[ i ] > ( HeatPidBuf[i].Qx   + DLBC_STEP_DEC25 ) )
     	               {
                 	   	BLDC_PwmVal[ i ] -= DLBC_STEP_DEC25;
                 	   }
                 else{
                      BLDC_PwmVal[ i ] =   HeatPidBuf[i].Qx   ;
                      }
                 
                  if( BLDC_PwmVal[ i ] > 1000 )        
                      {
                      	BLDC_PwmVal[ i ] = 1000;  
                      } 
     	
     	        Coldw.ApmDuty [ i ]   =    BLDC_PwmVal[ i ];    //显示
     	
              }    
                     
			     
    Coldw.MONI_PX1 = HeatPidBuf[0].Px;  	   
    Coldw.MONI_IX1 = HeatPidBuf[0].Ix;  	       
    Coldw.MONI_DX1 = HeatPidBuf[0].Dx;  	        
    Coldw.MONI_QX1 = HeatPidBuf[0].Qx; //0.14;           
                     
	   TIM_SetCompare1(TIM5, BLDC_PwmVal[0]);
       TIM_SetCompare2(TIM5, BLDC_PwmVal[1]);   
       TIM_SetCompare1(TIM1, BLDC_PwmVal[2]);
       TIM_SetCompare2(TIM1, BLDC_PwmVal[3]);
       TIM_SetCompare3(TIM1, BLDC_PwmVal[4]);
       TIM_SetCompare4(TIM1, BLDC_PwmVal[5]);
		

		  OSTimeDly(OS_TICKS_PER_SEC/200);	    //延时0.005秒

		}
}
/////////////////////////////////////////
void TaskStatus(void * pdata)
{
INT8U err;
uchar i;
pdata = pdata;                          	 	// 避免编译警告		

		for(i=0;i<10;i++)
					{
					LED1_ON;
					LED2_OFF;
					LED4_ON;

					
					OSTimeDly(OS_TICKS_PER_SEC/20);	    //延时0.05秒
					LED1_OFF;
					LED2_ON;
					LED4_OFF;

					OSTimeDly(OS_TICKS_PER_SEC/20);	    //延时0.05秒
					}
			LED1_OFF;		
			LED2_OFF;
			LED4_OFF;

for(;;)
		{
		if(1)
					{
					Led_Status_Off;
					OSTimeDly(OS_TICKS_PER_SEC/4);	    //延时0.25秒
		
					Led_Status_On;
					OSTimeDly(OS_TICKS_PER_SEC/4);	    //延时0.25秒
					}
			else{
					Led_Status_On;
					OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.5秒
					}	



		if(EventTimeBuz>0)
			{
				EventTimeBuz--;
				BUZ_ON;
			}
		else{
			BUZ_OFF;
			
				}

		if(EventTimeLed>0)
			{
				EventTimeLed--;
				Led_Event_On;
			}
		else{
				Led_Event_Off;
				}

		}
}
////////////////////


void KeyProcess( uchar *curk,uchar *old)
{
	if( * ( curk + 2  )  != 0 )
		{
			if( * ( curk + 2  )  !=  * ( old + 2  ) ) //key3
				{
					

         OSSemPost(OSSemTest1);
          OSSemPost(OSSemTest2);
					
				}
		}
}


void KeyShiftProcessnny( unsigned  long int  *curl , unsigned  long int*oldl )
{
	INT8U err;
	
 if ( ( KEY_BIT_STOP & (*curl) ) != 0 )
 	  {
     	FlagRuningnny = 0 ;   //控制 34 6 BLDC电机   34 步进电机
     	OSSemPend(OSSemMotors,0,&err);
     	//3 #步进电机   
     	 //StepMotStop( 2 ) ;
     	//4 #步进电机  
     	StepMotStop( 3 ) ;
     	OSSemPost(OSSemMotors);		
 	  }
 else{
 	   if ( KEY_BIT_RUN ==  (*curl)  )
 	       {
 	  	    FlagRuningnny = 1 ;   //控制 34 6 BLDC电机   34 步进电机
 	       }
 	    }
 
 OSSemPend(OSSemMotors,0,&err);
 //4 步进电机  动作  一键退刀
  if (  KEY_BIT_AUTO_BAK ==  (*curl)  )	
  	   {
  		 //4 #步进电机
         if (  KEY_BIT_AUTO_BAK!=  (*oldl)  )	
         	{
		  		StepMot[3].PulseCircleSet = 5;  //fast
		  		StepMotRun(  3 ,18*400 );  
		  		}
  	    }
  
  //点动进刀	    
   if (  KEY_BIT_SLOW ==  (*curl)  )		    
 	    {
  		 //4 #步进电机   StepMotStop( 3 ) ;

		  		StepMot[3].PulseCircleSet = 5;  //slow
		  		StepMotRun(  3 ,-60 ); 	    	
 	    }
OSSemPost(OSSemMotors);	    
 	    
}


void KeyShiftProcessnnz( unsigned  long int  *curl , unsigned  long int*oldl )
{
	INT8U err;
	
 if ( ( KEY_BIT_STOP & (*curl) ) != 0 )
 	  {
  	  	FlagRuningnnz = 0 ;   //控制 12 5 BLDC电机   12 步进电机
  	  	OSSemPend(OSSemMotors,0,&err);
  	  	StepMotStop( 1 );	  //2 #步进电机	 
  	  	OSSemPost(OSSemMotors);		
 	  }
 else{
 	   if ( KEY_BIT_RUN ==  (*curl)  )
 	       {
 	  	    FlagRuningnnz = 1 ;   //控制 34 6 BLDC电机   34 步进电机
 	       }
 	    }
			
 OSSemPend(OSSemMotors,0,&err);
 //2 步进电机  动作  一键退刀
  if (  KEY_BIT_AUTO_BAK ==  (*curl)  )	
  	   {
  		 //2 #步进电机
            if (  KEY_BIT_AUTO_BAK  !=  (*oldl)  )	
         	      {
		  		   StepMot[1].PulseCircleSet = 5;  //fast
		  		   StepMotRun(  1 ,18*400 );
		  		  }
  	    }
  
  //点动进刀	    
   if (  KEY_BIT_SLOW ==  (*curl)  )		    
 	    {
  		 //2 #步进电机   StepMotStop( 1 ) ;

		  		StepMot[1].PulseCircleSet = 5;  //slow
		  		StepMotRun(  1 ,-60 ); 	    	
 	    }
OSSemPost(OSSemMotors);			
			
}



////////////////////



////////////////////

void TaskKey(void * pdata)
{
INT8U err;
INT8U  i;
INT8U  bufka[5+1];
INT8U  bufkb[5+1];
INT8U  bufkc[5+1];



	pdata = pdata;        
	
	OSSemTest1   = OSSemCreate(0);
	OSSemTest2   = OSSemCreate(0);
	                  	 	// 避免编译警告	   
//#define InPin_K1	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))
//#define InPin_K2	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))
////PC1  开发板上
//#define InPin_K3	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))


for( i = 0 ; i<5 ; i++ )
  {
  	bufka[ i ] = 0;
  	bufkb[ i ] = 0;
  	bufkc[ i ] = 0;	
  }


		for(;;)
						{
						//OS_ENTER_CRITICAL();
						//OS_EXIT_CRITICAL();
						OSTimeDly(OS_TICKS_PER_SEC/20);	    //延时0.05秒		
						

						if( InPin_K1 )
							{
								bufka[ 0 ] = 0;
							}								
	          else{
	          	  bufka[ 0 ] = 1;
	              }

						if( InPin_K2 )
							{
								bufka[ 1 ] = 0;
							}								
	          else{
	          	  bufka[ 1 ] = 1;
	              }

						if( InPin_K3 )
							{
								bufka[ 2 ] = 0;
							}								
	          else{
	          	  bufka[ 2 ] = 1;
	              }

						if( InPin_K4 )
							{
								bufka[ 3 ] = 0;
							}								
	          else{
	          	  bufka[ 3 ] = 1;
	              }
										
						if( InPin_K5 )
							{
								bufka[ 4 ] = 0;
							}								
	          else{
	          	  bufka[ 4 ] = 1;
	              }


	

            for( i = 0 ; i<5 ; i++ )
                   {
  	                  if ( bufkb[ i ] != bufka[ i ] )
  		                     {//滤波
  			                   bufkb[ i ] = bufka[ i ];
  		                    }
  	               else { 
  	               	
  	               	     if ( bufkc[ i ]  !=  bufkb[ i ] )
  	               	     	   {
  	         	                KeyProcess( bufkc, bufkb);
                              bufkc[ i ] =  bufkb[ i ];
                             }
  	         	          
  	                     }
  	                 
  	                
                  }
										
				}	
}



////////////////////
void TaskLedy(void * pdata)  //TaskCmdx
{
INT8U err;
 


	pdata = pdata;     // 避免编译警告	   

#if CONFIG_SPI_DISP

  SpiInit_nny();
  
#endif  
  


//OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒		

		for(;;)
						{
						//OS_ENTER_CRITICAL();
						//OS_EXIT_CRITICAL();
						#if CONFIG_SPI_DISP
						
//						   #if Flag_test_spi_DMA
//						   OSSemPend(OSSemTest2,0,&err);
//						    #endif
	
						ShiftKeyCurnny = Process_N_NUMBnny();
						
							if ( ShiftKeyBnny != ShiftKeyCurnny )
  		                     {//滤波
  			                   ShiftKeyBnny = ShiftKeyCurnny;
  		                    }
  	               else { 
  	               	
  	               	     if ( ShiftKeyCnny  !=  ShiftKeyBnny )
  	               	     	   {
  	         	                
                              ShiftKeyCnny =  ShiftKeyBnny;
                             }
                          else{//三次相同
														   if ( ShiftKeyCnny != 0)
															     {
                          	       KeyShiftProcessnny( &ShiftKeyCnny, &ShiftKeySavenny);
																	 }
                              }
  	         	          
  	                     }
						
					  if(  FlagRuningnny >=1  )   //控制 34 6 BLDC电机   34 步进电机	
					  	{
					  		SngnalLed[1]  |=  0x80;      //单独指示灯
					  	}
					  else{
					  	  SngnalLed[1]  &=  (~0x80);      //单独指示灯
					     }	
					  	
//            if( ShiftKeyCurnny != 0 )
//            	{
//            		Alm_Flag1 = 1;
//            		SngnalLed[1]=0x0f;      //单独指示灯
//            	}
//            else {
//            	    Alm_Flag1 =0;
//            	    SngnalLed[1]=0;      //单独指示灯
//                }
						   
						   
						   
					//	OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.002秒	

						#else
						
						OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒	
						
						#endif
							

				    }	
}
////////////////////

void TaskLedz(void * pdata)  //TaskSyncUp
{
INT8U err;
 


	pdata = pdata;     // 避免编译警告	   

#if CONFIG_SPI_DISP

  SpiInit_nnz();
  
#endif  
  


//OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒		

		for(;;)
						{
						//OS_ENTER_CRITICAL();
						//OS_EXIT_CRITICAL();
						#if CONFIG_SPI_DISP
						
//						   #if Flag_test_spi_DMA
//						   OSSemPend(OSSemTest2,0,&err);
//						    #endif


						ShiftKeyCurnnz = Process_N_NUMBnnz();  
						
						if ( ShiftKeyBnnz != ShiftKeyCurnnz )
  		                     {//滤波
  			                   ShiftKeyBnnz = ShiftKeyCurnnz;
  		                    }
  	               else { 
  	               	
  	               	     if ( ShiftKeyCnnz  !=  ShiftKeyBnnz )
  	               	     	   {
  	         	                
                              ShiftKeyCnnz =  ShiftKeyBnnz;
                             }
                          else{//三次相同
														   if ( ShiftKeyCnnz != 0)
															     {
                          	        KeyShiftProcessnnz( &ShiftKeyCnnz, &ShiftKeySavennz);
																	 }
                              }
  	         	          
  	                     }
						
						if(FlagRuningnnz >= 1)   //控制 12 5 BLDC电机   12 步进电机	
					  	{
					  		SngnalLed[3]  |=  0x80;      //单独指示灯
					  	}
					  else{
					  	  SngnalLed[3]  &=  (~0x80);      //单独指示灯
					     }	
						
//						if( ShiftKeyCurnnz != 0 )
//            	{
//            		Alm_Flag2 = 1;
//            		SngnalLed[3]=0x03;      //单独指示灯
//            	}
//            else {
//            	    Alm_Flag2 =0;
//            	    SngnalLed[3]=0;      //单独指示灯
//                }
						
						 
						//EventTimeLed=2;   
						   
						//OSTimeDly(OS_TICKS_PER_SEC/1000);	    //延时0.05秒	

						#else
						
						OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒	
						
						#endif
							

				    }	
}



////////////////////////////////////////////////

//  1234号高压电动机12000转  ，  2400HZ脉冲  ，4*3极  * 0.5
//  56号低压电动机24000转  ，    2400HZ脉冲  ，2*3极

void TaskApm(void * pdata) //TaskTs
{
INT8U err;
 	CPU_SR          cpu_sr;
uchar i;

unsigned  long  int    temp32T ,temp32N;

	pdata = pdata;                          	 	// 避免编译警告	
	   
Coldw. T_bias_set = 0; //永远计数器。脉冲测量用
      
//#if Flag_test_spi_DMA     
//  for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
//			        {
//              Capture_testSPI_number[i]= 0; 
//
//               }
//#endif               
        

OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.5秒

//////
	for(;;)
				{
				//OS_ENTER_CRITICAL();
				//OS_EXIT_CRITICAL();
       

Led_Test_Adc_On1;

	
		    Led_Test_Adc_Off1;		
		    	   
      OS_ENTER_CRITICAL();
      
      for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
			        {
              Capture_Flag[i] = 0;   //暂停

               }	

	   OS_EXIT_CRITICAL();


      for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
			        {//读速度
			        	
                     OS_ENTER_CRITICAL();
                      temp32N = Capture_number[i];
                      temp32T = CaptureValueEnd[ i ] - CaptureValueStart[ i ];
                     OS_EXIT_CRITICAL();
              if(  temp32N   >   1  )
              			{
              				                      //temp32T = CaptureValueHigh_T3 + CaptureValueEnd[ i ] - CaptureValueStart[ i ];
              				                      //temp32T = CaptureValueHigh_T4 + CaptureValueEnd[ i ] - CaptureValueStart[ i ];
              				                      temp32T = CaptureValueEnd[ i ] - CaptureValueStart[ i ];

              				
              				
              				if( temp32T != 0)
              					  {
              				      //Apm_FREQ[ i ] = ( long )(  (  temp32N -1 )  * ( float ) 72000000 / temp32T );   //hz
              				      Apm_FREQ[ i ] = ( long )(  (  temp32N -1 )  * ( float ) 720000000 / temp32T );   //0.1hz
              			          }
              			     else{
              			     	  // Apm_FREQ[ i ] = ( long )   (  temp32N -1 )  * 100;  //10ms
              			           }
              			          
              	  }   
              else{
              	    Apm_FREQ[ i ] = 0;
                  }
                  
                
                 
               // #if Flag_test_spi_DMA

              //Coldw.ApmGt[i]=(float)Capture_testSPI_number[ i ];
              // else
                   
                   
                AddAverage( &AvergeBufI[ i ][0]  ,  &AvergeOffsetI1[ i ]  , Apm_FREQ[ i ]  , MaxAvergeList  );     
                   
                            

               }	
               
 
//             #if Flag_test_spi_DMA
//             OSSemPend(OSSemTest1,0,&err);
//             #endif  

							 	Coldw.limit_recode[7] =  CaptureValueStart[0 ];
							 	//Coldw.limit_recode[6] = CaptureValueHigh_T3 + CaptureValueEnd[ 0 ] - CaptureValueStart[0 ] ;
                                Coldw.limit_recode[6] =   CaptureValueEnd[ 0 ] - CaptureValueStart[0 ] ;
								
							
							 
CaptureValueHigh_T3 = 0;
CaptureValueHigh_T4 = 0;


       OS_ENTER_CRITICAL();
				 
             for ( i = 0 ; i < MAX_BLDC_CH6 ; i++ )			
			        {  
			        	
			        	CaptureValueStart[i] =0  ;
                        
			        	CaptureValueEnd[i] =0;
			        	
			        	Capture_number[i] = 0;
               Capture_Flag[i] = 1; //再开始
              }
              
			 OS_EXIT_CRITICAL();			
               

							
				OSTimeDly( OS_TICKS_PER_SEC  /100 );	    //延时10ms  
										

					}
}
/////////////////////////////


//uint32 NumberHexStringToInt32(uchar *p)	//最多8位HEX码的数字字符串转换为32位无符号整型
//{
//uint32 word2;
//uchar i;
//word2=0;
//for(i=0;i<8;i++)
//	{
//	if(IsHexAsc(*p))
//        	{
//        	word2=word2*0X10+AscToHex(*p);
//        	}
//        else break;
//        p++;
//        };
//
//return  word2;    	
//}

////////////////////////////////////


void ReceivedPowerOut(uchar type1,uchar *p)
{
		  INT8U err;
	uint16 temp16;
	uchar buf[MAX_BLDC_CH6+1][8];
	uchar 	num=0; 		//项目字符串记数。
	uchar 	j=0;    	//逗号个数
	uchar 	i=0;			//整个字符串位置计数
	
	
	num=0; 		//项目字符串记数。
	j=0;    	//逗号个数
	i=0;			//整个字符串位置计数
	while((*(p+i))&&(i<250)&&(j<MAX_BLDC_CH6))
		{

		if(*(p+i)==',' )
			{
			num=0;  //项目字符串开始记数。
			j++;    //逗号个数
			}
			

			if(*(p+i)!=',')
				{
				if(num<6)
					{
					buf[j][num]=*(p+i);  // 不包括，号
					buf[j][num+1]=0;
					num++;
					}
				}

		 i++;	
		 }
		 
for(j=0;j<MAX_BLDC_CH6;j++)
		{		 
		temp16=NumberAscStringToInt16(&buf[j][0]);	
		//if(temp16>255)temp16=255;
		if(type1=='P')
					{
					PowerOutBuf[j]=temp16;
					}
		else if(type1=='D')
					{
					TestOutBuf[j]=temp16;
					}
		}	
		 
		if(type1=='P')
					{

					//StepMotRun1(PowerOutBuf[0]+RelativeOrigin-StepMot1.Position16);
					

					
					}
		else if(type1=='D')
					{

					//StepMotRun1(TestOutBuf[0]);
					}		 
}
////////////////////

//void ResponeTempratur(void)
//{				 INT8U err;
//	uchar buf[10+6*(MAX_BLDC_CH6)];
//	uchar i,n;
//
//	uint16 temp16;
//	
//	n=PutString("^T",buf,5);
//
//	
//	for(i=0;i<MAX_BLDC_CH6;i++)
//				{
//
//				if( wAdcResoult[ i ] < 0 )
//					{
//						temp16=0;
//          }
//				else temp16=(uint16)( 10* wAdcResoult[ i ] );//单位0.1度
//					
//				n+=MakeValAsc16("",temp16,",",&buf[n]);//单位0.1度
//
//				}
//	n+=PutString("\r\n",&buf[n],5);
//	
//	#if CONFIG_UART1
//		OSSemPend(OSSemUart1,0,&err);
//
//			SendText_UART1(buf);
//		OSSemPost(OSSemUart1);
//	#endif
//}
///////////////////////////////////////



///////////////////////////////////////
//void ResponePower(void)
//{		INT8U err;
//	uchar buf[10+6*(MAX_BLDC_CH6)];
//	uchar n,i;
//	n=PutString("^P",buf,5);
//
//	
//	for(i=0;i<MAX_BLDC_CH6;i++)
//				{
//				n+=MakeValAsc16("",PowerOutBuf[i],",",&buf[n]);
//				}
//	n+=PutString("\r\n",&buf[n],5);
//	#if CONFIG_UART1
//		OSSemPend(OSSemUart1,0,&err);
//
//			SendText_UART1(buf);
//		OSSemPost(OSSemUart1);
//	#endif
//	
//}

//电脑下传的控制量绝对位置   %P32,33,89,....\r\n
//电脑下传的走几步					%D655,32,77,...\r\n
//请求查询温度  		%RTA\r\n
//单片机上传的温度值   ^T1234,1235,1236,1058,....\r\n

////////////////////
//void ProcessRecvUser(uchar *p,uchar len)
//{
//
//INT8U err;	
//	
//		uint8_t *flash;
//		
//	uint32_t adress;
//	uchar i;
//	
//	if(*p!='%')
//		{
//			return;	
//		}
//
//	
//switch (*(p+1))
//		{
//		case 'R':	//请求查询温度
//
//		//wAdcResoult[MAX_BLDC_CH6];    //用来存放求平均值之后的结果
//	
//		
//		ResponeTempratur();
//		break;	
//			
//		case 'P':  //控制值
//			ReceivedPowerOut(*(p+1),p+2);
//			ResponePower();
//
//		break;	
//		
//		case 'D':  //测试值，前后走几步，有负数
//			ReceivedPowerOut(*(p+1),p+2);
//			ResponePower();
//
//		break;			
//		
//		case 'F':  //读FLASH	
//		adress=NumberHexStringToInt32(p+2);
//		flash=(uchar *)adress;
//
//		//SendTestBufHex(flash,16);
//
//		#if CONFIG_UART1
//		OSSemPend(OSSemUart1,0,&err);
//				SendText_UART1("...");
//				for(i=0;i<16;i++)
//								{
//									Uart1CharSend(HexToAsc(*(flash+i)>>4));
//									Uart1CharSend(HexToAsc(*(flash+i)));
//									Uart1CharSend(0x20);
//								}
//				SendText_UART1("\r\n");
//		OSSemPost(OSSemUart1);
//		#endif
//		break;
//		
//		
//		
//		case 0:
//		default:	
//		break;
//		
//	
//	
//		}
//		
//
//
//	
//}

////////////////////
//void RecvFromUser(uchar temp)
//{
//	
//	switch(temp)
//		{
//			case '%':	
//			BufFromUser[0]=temp;	//'*' or ':';	
//			LenFromUser=1;
//			
//			break;
//			
//			case '\r':
//			BufFromUser[LenFromUser]=0;
//			//处理
//			ProcessRecvUser(BufFromUser,LenFromUser);
//			break;
//			
//			default:
//				if(LenFromUser<250)
//					{
//						BufFromUser[LenFromUser]=temp;
//						LenFromUser++;
//					}
//				else LenFromUser=0;
//			break;	
//			
//			
//		}
//	
//}

/////////////////////////////
void TaskRecv(void * pdata)
{
	INT8U err;
	
//	uchar timeout,temp;
//	uchar flag_recv=0;
	
 	pdata = pdata;                          	 	// 避免编译警告	   


OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒

/*
//ProcessRecvUser(":R08020000\r\n",8);

OSSemPend(OSSemUart1,0,&err);
SendText_UART1(":R08010000\r\n");
OSSemPost(OSSemUart1);

ProcessRecvUser(":R08010000\r\n",8);



//产品唯一身份标识寄存器（96位）
//基地址0X1FFF F7E8
//位15:0
//地址偏移0x02
//位31:16
//地址偏移0x04
//位63:32
//地址偏移0x06
//位95:64


OSSemPend(OSSemUart1,0,&err);
SendText_UART1(":R1FFFF7E8\r\n");
OSSemPost(OSSemUart1);
ProcessRecvUser(":R1FFFF7E8\r\n",8);
*/






//BufFromUser[0]=0;	//'*' or ':';	
//LenFromUser=0;

//////
	for(;;)
				{
				//OS_ENTER_CRITICAL();
				//OS_EXIT_CRITICAL();
/*
						
						timeout=0;
						while(timeout<5)
								{
									#if CONFIG_UART1
								OSSemPend(OSSemUart1,0,&err);
								flag_recv=GetOneFromUart1(&temp);
								OSSemPost(OSSemUart1);
								
								
									if(flag_recv)
										{
											EventTimeLed=2;
										RecvFromUser(temp);
										
										timeout=0;
										}
								   #endif
									timeout++;
								}

*/

    //Coldw.Moter_step_set;       //强制走几步
    //Coldw.Moter_direction;      //方向

	OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.01秒

					}
}
////////////////////


///////////////////////////////////////////////
    






float MaxVal( float a, float b, float c)
{
	if(a<b)
		{
			a = b ;   //留大
		if(a<c)
			{//c最大
				a = c  ;
			}
		//else b最大	
			
		}
else{		
	  if(a < c )
	  	{//c最大
				a = c  ;  //留大
			}
	  //else a最大	
    }

return a;
}

////////////////////
void TaskStepMotor(void * pdata)
{
INT8U err;

uchar i;
unsigned short int TempUs;
	
	
pdata = pdata;    // 避免编译警告		



 OSSemMotors = OSSemCreate(1);

 OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒

						

for(;;)
		{

     OSSemPend(OSSemTimePid_StepMotor,0,&err);  //OSSemPost(OSSemTimePid_StepMotor);   OSSemTimePid_Heat
     
    
     //OSSemPend(OSSemMotors,0,&err);
     
     //OSSemPost(OSSemMotors);
     


      OSSemPend(OSSemMotors,0,&err);
     
     		  	  // 200步   2细分  apm  0.1     x*50us
		  	  	 //  T (us)= 1x1000x1000 /  ( apm/10 / 60 * 200 *2 ) /50   = 600*1000*1000/400/50/apm  = 30000 /apm  
	     		 
	     		  // 400步   2细分  apm       x*50us
		  	  	 //  T (us)= 1x1000x1000 /  ( apm/ 60 * 400 *2 ) /50   = 60*1000*1000/800/50/apm  = 1500 /apm  	  	  	 
		  	  	 
//		  	  	 if( Coldw.ApmCt[6]  > 3 )  //0.3apm
//		  	  	 	{
//		  	  	                 TempUs =  30000 /  Coldw.ApmCt[6];
//		  	  	               }
//		  	  	else{
//		  	  		            TempUs = 10000 ;  //500ms 脉冲     2/200/2   * 60  = 0.3    apm
//		  	  	      }
//		  	  	if (  TempUs < 5 )    TempUs  = 5;   //250us      4000/200/2 *60  =  600.0  apm
 		  	  	
 		  	  	 if( Coldw.ApmCt[6]  >=1 )  // 1apm
		  	  	 	{
		  	  	                 TempUs =  1500 /  Coldw.ApmCt[6];
		  	  	               }
		  	  	else{
		  	  		            TempUs = 1500 ;  //1500ms 脉冲     66/400/2   * 60  = 0.5    apm
		  	  	      }
		  	  	if (  TempUs < 5 )    TempUs  = 5;   //250us      4000/400/2 *60  =  300  apm    
     
     	if(  FlagRuningnny >=1  )   //控制 34 步进电机
		  	  {
		  	  	 //3 #步进电机     PulseCircleSet=20;//20;		//20*50us  = 0.001s
		  	  	 

		  	  	  if( Coldw.ApmCt[6]  >=1 ) 
		  	  	  	{
		  		       StepMot[2].PulseCircleSet =  TempUs ;  //fast
		  		      StepMotRun(  2  , 6000  );
		  	         }
		  		
		  			 //4 #步进电机
		  		StepMot[3].PulseCircleSet = 60 +  Coldw.ApmCt[7];  //slow
		  		StepMotRun(  3 ,8 );
		  	  }
		  else{
		  		StepMotStop(2);  	 //3 #步进电机
		  		//StepMotStop(3);  	 //4 #步进电机
		      }  
		      	
		      	
		      	
		      	
		  if(FlagRuningnnz >= 1 )  //控制 12  步进电机
		  	  {
		  	  	  //1 #步进电机
		  	  	  if( Coldw.ApmCt[6]  >=1 ) 
		  	  	  	{
		  	        StepMot[0].PulseCircleSet =  TempUs;  //fast
		  		    StepMotRun(  0 , 6000 );
		  	     }
		  		
		  		 //2 #步进电机	  	
		  		StepMot[1].PulseCircleSet = 60 +  Coldw.ApmCt[7];  //slow
		  		StepMotRun(  1 , 8  );
		  	  }
		  else{
		  		StepMotStop( 0 );  //1 #步进电机
		  		//StepMotStop( 1 );	  //2 #步进电机	  	
		      } 
     OSSemPost(OSSemMotors);


                  
                  Coldw.ApmGt[ 6 ]         =    StepMot[0].PulseCircleSet;    //显示
                  Coldw.ApmGt[ 7 ]         =    StepMot[1].PulseCircleSet;    //显示
                  Coldw.ApmDuty [ 6 ]   =    StepMot[2].PulseCircleSet;    //显示
                  Coldw.ApmDuty [ 7 ]   =    StepMot[3].PulseCircleSet;    //显示
     
                   
    OSTimeDly(OS_TICKS_PER_SEC/50);  //补充延时

		}
}
/////////////////////////////






////////////////////////////////////////////////
void TaskSave(void * pdata)
{
INT8U err;
CPU_SR         cpu_sr;

 
	pdata = pdata;                          	 	// 避免编译警告	   




	for(;;)
				{
				 
				 
          
							
        if(FlagSetAllDefault > 0)//flag
        	   {
        	   	
        	   	if(3 == FlagSetAllDefault)
				 	      {
         
                Default_ParamInit1();    ////需要保存的参数
                Default_ParamInit2();    ////整定值
                }
        	   	else if(2 == FlagSetAllDefault)
				 	      {
         
                Default_ParamInit1();    ////需要保存的参数

                }
        	   	
        	   	Default_ParamInit0();//不需要保存的参数
        	   	
        	   	FlagSetAllDefault = 0 ;
        	   	
        	   	
             //自动恢复默认值
             cMemBufA[Max_MemBuf-2] =  FlagParamInitnized; 
             
             OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
             _Param_SwapMemery(0,cMemBufA);   // parameter ---> cMemBufA
              OS_EXIT_CRITICAL();
              
             Write_Param();  // cMemBufA ---> cMemBufB   --->  memory
             
             }
          
          
          
          
          if(TimeForSaveParam==1)  //延时保存
          	{
							//////
						
						 OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
	            _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufA
	            TimeForSaveParam = 0;
             OS_EXIT_CRITICAL();
             Write_Param();   //cMemBufB  ---> eeprom
            
						}
						
					if(TimeForSaveParam>0)
						{
							TimeForSaveParam	-- ;
						}
				
				
				OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒		
			}		
}





/////////////////



//////////////





