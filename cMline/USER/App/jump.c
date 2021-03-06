
#include "includes.h"

//自动加锁定时器
unsigned short int TimeAutoLock1;
unsigned short int TimeAutoLock2;
unsigned short int TimeAutoLock3;
//STM32F103  #define ISP_ADDR        0x1FFFF000
//STM32F107  #define ISP_ADDR        0x1FFFB000
void JumpAppAdr(unsigned long int adr)
{
	
   void  (*func)(void);	
   unsigned long int  spval;	
	
     spval =  *(unsigned long int *)(adr);
     
     __set_MSP(spval);//设置SP.
     
	   func  =  (void(*)(void))( (unsigned long int )(adr+4)|1 );
	   //func  =  (void(*)(void))( (unsigned long int )(adr+4) );
	   //func ();
     (*func)();

}

////////////////////////////////////////////
void IspMarkLoad(void)
{
//void LoadFromBKP(void)
unsigned short int iMark1,iMark2;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
PWR_BackupAccessCmd(ENABLE);
BKP_ClearFlag();
	
	//IspMarkWrite(CMND_ISP_22);
  //读	
	iMark1  =  BKP_ReadBackupRegister(BKP_DR2);
	//iMark2  =  BKP_ReadBackupRegister(BKP_DR3);

  //clr
  BKP_WriteBackupRegister(BKP_DR2,0);	
  //BKP_WriteBackupRegister(BKP_DR3,0);
	
	

if(iMark1 != CMND_ISP_22)
	{
		return;
	}
//if(iMark2 != (CMND_ISP_22+3) )
//	{
//		return;
//	}	
	
// to isp
	
//JumpAppAdr(unsigned long int adr)
//STM32F103  #define ISP_ADDR        0x1FFFF000
//STM32F107  #define ISP_ADDR        0x1FFFB000
JumpAppAdr(0x1FFFF000);   //跳转到下载程序,STM32F103
//JumpAppAdr(0x1FFFB000);   //跳转到下载程序,STM32F107
}
/////////////////////////////////////////////////////
void IspMarkWrite(uint16_t ix)
{
	BKP_WriteBackupRegister(BKP_DR2,ix);
//	BKP_WriteBackupRegister(BKP_DR3,ix+3);
}	


void SoftReset(void)
{//RCC_BackupResetCmd
 __set_FAULTMASK(1);      // 关闭所有中端
 NVIC_SystemReset();// 复位

//       在官方软件库的 core_cm3.h 文件里 直接提供了 系统复位的函数 
//          
//        static __INLINE void NVIC_SystemReset(void)
//        {
//          SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      | 
//                                   (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) | 
//                                   SCB_AIRCR_SYSRESETREQ_Msk);                   /* Keep priority group unchanged */
//          __DSB();                                                                                       /* Ensure completion of memory access */              
//          while(1);                                                                                        /* wait until reset */
//        }
//        但是不是直接调用这个函数就OK了？ 
//        在Cortex-M3权威指南中有这么一句话 
//        这里有一个要注意的问题：从SYSRESETREQ 被置为有效，到复位发生器执行复位命令， 
//        往往会有一个延时。在此延时期间，处理器仍然可以响应中断请求。但我们的本意往往是要 
//        让此次执行到此为止，不要再做任何其它事情了。所以，最好在发出复位请求前，先把 
//        FAULTMASK 置位。 
//        所以最好在将FAULTMASK 置位才万无一失。 
//        同样官方 core_cm3.h 文件里也直接提供了该函数 
//          
//        static __INLINE void __set_FAULTMASK(uint32_t faultMask)
//        {
//          register uint32_t __regFaultMask       __ASM("faultmask");
//          __regFaultMask = (faultMask & 1);
//        }
 	
}



//////////////////////
void ModbusCommand1(void)//收到参数时执行一下
{
//Coldw.lyy_reserve,Coldw.lSysSwitch_reserve
      if(Coldw.lBackupRestore == 0 ) 
           {
	          return;
            }

          switch(Coldw.lBackupRestore)//Coldw.lyy_reserve
          			{
          			case 1:  //输入 1 ，然后 2 然后
          				TimeAutoLock1 = 6;  //6秒 //自动加锁定时器

          		  break;

          			case 2: //输入 1 ，然后 2
          				if(TimeAutoLock2 > 0 )
          				     {
          				   	  TimeAutoLock3 = 12;  //12秒 //自动加锁定时器
          				     }

          		  break;          
          		  
          			case 3: //输入 1 ，然后 2
          				if(TimeAutoLock1 > 0 )
          				     {
          				   	  TimeAutoLock2 = 6;  //12秒 //自动加锁定时器
          				     }

          		  break;           		  			
          		  
          		  case CMND_RESET_21: //输入 1 ，然后 2 然后21
          			  if(TimeAutoLock3 > 0)
          			  	  {
          			  	  Coldw.lBackupRestore +=3;	
          			  		OSTimeDly(OS_TICKS_PER_SEC*6);
          			  		SoftReset();
          			  	  }
          			break;
          			
          			case CMND_ISP_22: //输入 1 ，然后 2 然后22
          			if(TimeAutoLock3 > 0)
          			  	  {
          			  	  	
          			  	  Coldw.lBackupRestore +=3;		
          			  	  IspMarkWrite(CMND_ISP_22);	//Coldw.lBackupRestore);//
          			  	  
          			  	  
          			  		
          			  		OSTimeDly(OS_TICKS_PER_SEC*6);
          			  		SoftReset();
          			  	  }
          			break;          
          			
  
          		          						

          			case CMND_EXTREN_33:
          			//除modbus外加另外通讯，比如读写存储器
          			if(TimeAutoLock3 > 0)
          				{
          					
          				}
          			
          			break; 

								case CMND_MEMERY_45:
								//initalize backup  Restore  parameter
								if(TimeAutoLock3 > 0)
          				{
          					
          				}
          			break; 

								case 91:
								//initalize 0								
								if(TimeAutoLock3 > 0)
          				{
          					//Default_ParamInit0();
                    FlagSetAllDefault = 1;
                    Coldw.lBackupRestore =0; 
          				}
								break;
          	
          	    
								case 95:
								//initalize   1
								if(TimeAutoLock3 > 0)
          				{

				 	         FlagSetAllDefault = 2;
				 	    
                   Coldw.lBackupRestore =0;
         
                   //Default_ParamInit1();    ////需要保存的参数
                   }
								break;          	
								case 98:
								//initalize 2 all
								if(TimeAutoLock3 > 0)
          				{
          					FlagSetAllDefault = 3;
          					//Default_ParamInit0();
                    //Default_ParamInit1();    ////需要保存的参数
                    //Default_ParamInit2();    ////整定值
                   Coldw.lBackupRestore =0;
          				}
								break;           	
          			}

	
      	
}


