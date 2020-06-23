//user.c

#include "includes.h"
//extern 



#define     MOTOR_LIMIT_CLOSE     MAX_PID_INTEGRAL_1
#define     MOTOR_LIMIT_OPEN    ( MIN_PID_INTEGRAL_1 )

OS_EVENT *OSSemTest1;
OS_EVENT *OSSemTest2;

OS_EVENT *OSSemMotors;
OS_EVENT *OSSemUart1;



OS_EVENT *OSSemTimePid_StepMotor;
OS_EVENT *OSSemTimePid_Heat;

OS_EVENT *OSSemProcCmdx;


//uchar LenFromUser;	
//uchar BufFromUser[252];




float TempratureSet;   //控制用温度设定值   




unsigned char lAddressKey;  //拨码开关PB12-PB15，值，最低4位

unsigned char FlagKey;
unsigned char EventTimeBuz=0;
unsigned char EventTimeLed=0;



float wAdcResoult[MAX_TEMPRATURE_CHNALL];  //MAX_ADC_CH 

/////////////////////////////////////////////


signed short int PowerOutBuf[2+(MAX_TEMPRATURE_CHNALL)];
signed short int TestOutBuf[2+(MAX_TEMPRATURE_CHNALL)];




unsigned  long int Capture_Flag[6+1] ;
unsigned  long int Apm_FREQ[6+1] ; 
unsigned  long int Capture_number[6+1] ;

#if Flag_test_spi_DMA     
  unsigned  long int Capture_testSPI_number[6+1] ;
#endif

//unsigned  long int CaptureValueStart[6+1] ;
//unsigned  long int CaptureValueEnd[6+1];
//因为使用16位定时器，所以这两个变量也使用16位
unsigned  short int CaptureValueStart[6+1] ;
unsigned  short int CaptureValueEnd[6+1];

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
void TaskVirPwm(void * pdata)  //Virtual
{
INT8U err;
unsigned char i;
unsigned char curDuty[8];//占空比
unsigned char curCycle;//周期

pdata = pdata;                          	 	// 避免编译警告		

//#if CONFIG_ADC
//ADC_Configuration();
//#endif
//



curCycle = 200;//周期

OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒
for(;;)
		{
			//电加热 软件 PWM
			/*
			for(i=0;i<8;i++)
			    {
			     if(curDuty[i] > 0)
			     	  {
			     		
			     		 curDuty[i] --;
			     	  }
			     else{//关输出
			     	
			     	   VirtualPwmOutPin(i,0);
			         }
			     }
			
			  if(curCycle > 0)
			     	{
			     		curCycle --;
			     	}
			  else{
			     	 curCycle = 200 ;//周期到
                for(i=0;i<8;i++)
			            {
                   curDuty[i] = Coldw.TC_duty[i]       ;//刷新PWM值
			     	       //开输出
			     	       if(Coldw.unit_onof_flag[i]>0)
			     	       	   {
			     	       		  VirtualPwmOutPin(i,1);
			     	       	   }
			     	       
			     	       }			     	    
			       }
			        
							*/
		  OSTimeDly(OS_TICKS_PER_SEC);	    //延时0.001秒

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
//											for(i=0;i<MAX_TEMPRATURE_CHNALL;i++)
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


	for( i=0; i<MAX_TEMPRATURE_CHNALL ; i++)
	              {  		
	              if(	( Coldw.one_unit_flag == 0 ) || ( Coldw.one_unit_flag == ( i + 1 )  ) )
	              	    {
	  	     	           OSSemPend(OSSemMotors,0,&err);	
	  	     	           MotorsRun(i,steps);
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

unsigned long temp32;

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
   }







#if CONFIG_CHECK_DEVICE_ID
	
	InitSTM32DeciceID();
	
	
		if(GetStm32F103_DeviceId_Sum6() == temp32 )  //Pmbuf->Stm32Id )
				{
					STM32DeviceId.Checked=1;
				}
		else{
			STM32DeviceId.Checked=0;
				}
#endif	

//  		  	  #if CONFIG_CHECK_DEVICE_ID	
//  		  	  	
//  		      Pmbuf->Stm32Id = GetStm32F103_DeviceId_Sum6();  
//  		      
//  		      #endif


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

      OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
      
               timer1++;
               if(timer1 >= 20)  //200ms
                    {
                     timer1  = 0 ;
                     OSSemPost(OSSemTimePid_Heat);   //电加热PID控制周期

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


OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
for(;;)
		{
			
			OSSemPend(OSSemTimePid_Heat,0,&err);  //   OSSemTimePid_Heat


              

      for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )			
			    {

          //HeatPidBuf[i].SetPoint = TempratureSet; //Coldw.T_set; //基本上多余 
			    //PID_Calc(&Coldw.Pidx[1], &HeatPidBuf[i], ( HeatPidBuf[i].SetPoint - TempratureCurrent [ i ] ),0); //一般是error = SetPoint - NewPoint ,这里反过来
			    
			     }
	     
			     
//    Coldw.MONI_PX2 = HeatPidBuf[0].Px;  	   
//    Coldw.MONI_IX2 = HeatPidBuf[0].Ix;  	       
//    Coldw.MONI_DX2 = HeatPidBuf[0].Dx;  	        
//    Coldw.MONI_QX2 = HeatPidBuf[0].Qx; //0.14;
    
		
		
      for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )			
			        {
               //Coldw.ApmCt[i]=400;
              
               }		

		   TIM_SetCompare1(TIM5, Coldw.ApmCt[0]);
       TIM_SetCompare2(TIM5, Coldw.ApmCt[1]);   
       TIM_SetCompare1(TIM1, Coldw.ApmCt[2]);
       TIM_SetCompare2(TIM1, Coldw.ApmCt[3]);
       TIM_SetCompare3(TIM1, Coldw.ApmCt[4]);
       TIM_SetCompare4(TIM1, Coldw.ApmCt[5]);
		

		  OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒

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
					OSTimeDly(OS_TICKS_PER_SEC/4);	    //延时0.05秒
		
					Led_Status_On;
					OSTimeDly(OS_TICKS_PER_SEC/4);	    //延时0.05秒
					}
			else{
					Led_Status_On;
					OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.1秒
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
						
						   #if Flag_test_spi_DMA
						   OSSemPend(OSSemTest2,0,&err);
						    #endif
	
						Process_N_NUMBnny();

						   
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
						
						   #if Flag_test_spi_DMA
						   OSSemPend(OSSemTest2,0,&err);
						    #endif
						//Seg8

						Process_N_NUMBnnz();   
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
 
uchar i;

unsigned  short int temp16 ;

	pdata = pdata;                          	 	// 避免编译警告	
	   

#if Flag_test_spi_DMA     
  for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )			
			        {
              Capture_testSPI_number[i]= 0; 

               }
#endif               
        
        
	      PutValToDispBf(6666 , DispBufnny+12 );
        PutValToDispBf( 0, DispBufnny+8 );
        PutValToDispBf(4444 , DispBufnny+4 );
        PutValToDispBf(3333 , DispBufnny+0 );
        
        PutValToDispBf(5555 , DispBufnnz+12 );
        PutValToDispBf(0, DispBufnnz+8 );
        PutValToDispBf(2222 , DispBufnnz+4 );
        PutValToDispBf(1111 , DispBufnnz+0 ) ;     
        
				OSTimeDly(OS_TICKS_PER_SEC*2);	    //延时10ms  改为 2ms		 改为 1ms	
//OSTimeDly(OS_TICKS_PER_SEC);	    //延时0.5秒

//////
	for(;;)
				{
				//OS_ENTER_CRITICAL();
				//OS_EXIT_CRITICAL();
       

Led_Test_Adc_On1;

	
		    Led_Test_Adc_Off1;			   

      for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )			
			        {
              Capture_Flag[i] = 0;   //暂停

               }	

      for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )			
			        {//读速度
              

              if( Capture_number[i] > 1 )
              			{
              				temp16 = CaptureValueEnd[ i ] - CaptureValueStart[ i ];
              				if( temp16 != 0)
              					  {
              				    //Apm_FREQ[ i ] = 72000000 * Capture_number[i] / temp16;   //hz
              				
              				    Apm_FREQ[ i ] = Capture_number[i]; //temp16;//

              			     }
              	  }   
              else{
              	    Apm_FREQ[ i ] = 0;
                  }
                  
              #if Flag_test_spi_DMA

              Coldw.ApmGt[i]=(float)Capture_testSPI_number[ i ];
              #else
                   
              Coldw.ApmGt[i]=(float)Apm_FREQ[ i ];
              #endif
               

               }	
               
             #if Flag_test_spi_DMA
             OSSemPend(OSSemTest1,0,&err);
             #endif  
             
             for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )			
			        {  
			        	Capture_number[i] = 0;
               Capture_Flag[i] = 1; //再开始
              }
               
               

///////////////
        PutValToDispBf(Apm_FREQ[5], DispBufnny+12 );  
        PutValToDispBf( 0, DispBufnny+8 );
        PutValToDispBf( Apm_FREQ[3]>>1, DispBufnny+4 );
        PutValToDispBf(Apm_FREQ[2]>>1 , DispBufnny+0 );
        
        PutValToDispBf(Apm_FREQ[4] , DispBufnnz+12 );
        PutValToDispBf( 0, DispBufnnz+8 );
        PutValToDispBf( Apm_FREQ[1]>>1, DispBufnnz+4 );
        PutValToDispBf(Apm_FREQ[0]>>1 , DispBufnnz+0 ) ;      
        
// 	      PutValToDispBf(6666 , DispBufnny+12 );
//         PutValToDispBf( 7777, DispBufnny+8 );
//         PutValToDispBf(4444 , DispBufnny+4 );
//         PutValToDispBf(3333 , DispBufnny+0 );
//         
//         PutValToDispBf(5555 , DispBufnnz+12 );
//         PutValToDispBf( 8888, DispBufnnz+8 );
//         PutValToDispBf(2222 , DispBufnnz+4 );
//         PutValToDispBf(1111 , DispBufnnz+0 ) ;    	
							
							
				OSTimeDly(OS_TICKS_PER_SEC);	    //延时10ms  改为 2ms		 改为 1ms	
										

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
	uchar buf[MAX_TEMPRATURE_CHNALL+1][8];
	uchar 	num=0; 		//项目字符串记数。
	uchar 	j=0;    	//逗号个数
	uchar 	i=0;			//整个字符串位置计数
	
	
	num=0; 		//项目字符串记数。
	j=0;    	//逗号个数
	i=0;			//整个字符串位置计数
	while((*(p+i))&&(i<250)&&(j<MAX_TEMPRATURE_CHNALL))
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
		 
for(j=0;j<MAX_TEMPRATURE_CHNALL;j++)
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
//	uchar buf[10+6*(MAX_TEMPRATURE_CHNALL)];
//	uchar i,n;
//
//	uint16 temp16;
//	
//	n=PutString("^T",buf,5);
//
//	
//	for(i=0;i<MAX_TEMPRATURE_CHNALL;i++)
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
//	uchar buf[10+6*(MAX_TEMPRATURE_CHNALL)];
//	uchar n,i;
//	n=PutString("^P",buf,5);
//
//	
//	for(i=0;i<MAX_TEMPRATURE_CHNALL;i++)
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
//		//wAdcResoult[MAX_TEMPRATURE_CHNALL];    //用来存放求平均值之后的结果
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

void MotorsRun(unsigned char ch, signed short int steps)
{
	switch(ch)
	{
		case 0:
		StepMotRun1(steps);	
		break;
			
	  case 1:		
		StepMotRun2(steps);	
		break;
		
		case 2:
			StepMotRun3(steps);			
			
		break;	
	  case 3:		
					StepMotRun4(steps);	
		break;		
		case 4:
					StepMotRun5(steps);	
			
		break;	
	  case 5:		
					StepMotRun6(steps);	
		break;		
		
	}
	
}
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




pdata = pdata;                          	 	// 避免编译警告		
OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒



  
  OSSemMotors = OSSemCreate(1);
  

							

for(;;)
		{

     OSSemPend(OSSemTimePid_StepMotor,0,&err);  //OSSemPost(OSSemTimePid_StepMotor);   OSSemTimePid_Heat
     






    
    
    
     OSSemPend(OSSemMotors,0,&err);
     
     OSSemPost(OSSemMotors);
     
     for ( i = 0 ; i < MAX_TEMPRATURE_CHNALL ; i++ )
         {


//			    PID_Calc(&Coldw.Pidx[0], &StepPidBuf[i], (TempratureSet + 0.2 + 0.0 -  TempratureWaterAdj [ i ]),   0 ); //一般是error = SetPoint - NewPoint ,这里反过来

           			 //  	      Coldw.FAN_duty[i] = StepPidBuf[i].Qx;
 
           					
           				OSSemPend(OSSemMotors,0,&err);	
   
                  OSSemPost(OSSemMotors);

				} 
//		Coldw.MONI_PX1 = StepPidBuf[0].Px;//0.11;                //
//    Coldw.MONI_IX1 = StepPidBuf[0].Ix;//0.12;
//    Coldw.MONI_DX1 = StepPidBuf[0].Dx;//0.13;
//    Coldw.MONI_QX1 = StepPidBuf[0].Qx; //0.14;
//                  
//    Coldw.MONI_PX2 = StepPidBuf[1].Px;  	   
//    Coldw.MONI_IX2 = StepPidBuf[1].Ix;  	       
//    Coldw.MONI_DX2 = StepPidBuf[1].Dx;  	        
//    Coldw.MONI_QX2 = StepPidBuf[1].Qx; //0.14;                  
                  
                  
    OSTimeDly(OS_TICKS_PER_SEC/500);  //补充延时

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
             _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufB
              OS_EXIT_CRITICAL();
              
             Write_Param();
             
             }
          
          
          
          
          if(TimeForSaveParam==1)  //延时保存
          	{
							//////
						
						 OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
	            _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufB
	            TimeForSaveParam = 0;
             OS_EXIT_CRITICAL();
             Write_Param();
            
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





