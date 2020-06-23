/**
  ******************************************************************************
  * @file    StepMotor.c
  * @author  Liguowei  ����ΰ
  * @version V0.0.1
  * @date    2/15/2017
  * @brief   This is Steper Motor Driver functions.
  ******************************************************************************
*/

#define NUMBofSTEPs    6

#include "includes.h"

struct step_motor StepMot[NUMBofSTEPs];

void SwitchBitCLK( unsigned char chs , unsigned char level )
{
	if( level == 0 )
		{
		 switch(	chs )
		    {
		    	case 0:
		    	   ClrBitCLK1;
		    	break;
		    	
		    	case 1:
		    	   ClrBitCLK2;
		    	break;	
		    		    	
		    	case 2:
		    	   ClrBitCLK3;
		    	break;
		    	
		    	case 3:
		    	   ClrBitCLK4;
		    	break;		    	
		    		    	
		    	case 4:
		    	   ClrBitCLK5;
		    	break;
		    	
		    	case 5:
		    	   ClrBitCLK6;
		    	break;
	    			    	
		    }
			
		}
	else{
		   switch(	chs )
		      {
		      case 0:
		    	   SetBitCLK1;
		    	break;
		    	
		    	case 1:
		    	   SetBitCLK2;
		    	break;	
		    		    	
		    	case 2:
		    	   SetBitCLK3;
		    	break;
		    	
		    	case 3:
		    	   SetBitCLK4;
		    	break;		    	
		    		    	
		    	case 4:
		    	   SetBitCLK5;
		    	break;
		    	
		    	case 5:
		    	   SetBitCLK6;
		    	break;
		    }
		    		
	    }
	
}
/////////////
void SwitchBitCW( unsigned char chs , unsigned char level )
{
	if( level == 0 )
		{
		 switch(	chs )
		    {
		    	case 0:
		    	   ClrBitCW1;
		    	break;
		    	
		    	case 1:
		    	   ClrBitCW2;
		    	break;	
		    		    	
		    	case 2:
		    	   ClrBitCW3;
		    	break;
		    	
		    	case 3:
		    	   ClrBitCW4;
		    	break;		    	
		    		    	
		    	case 4:
		    	   ClrBitCW5;
		    	break;
		    	
		    	case 5:
		    	   ClrBitCW6;
		    	break;
		    				    			    	
		    }
			
		}
	else{
		   switch(	chs )
		      {
		      case 0:
		    	   SetBitCW1;
		    	break;
		    	
		    	case 1:
		    	   SetBitCW2;
		    	break;	
		    		    	
		    	case 2:
		    	   SetBitCW3;
		    	break;
		    	
		    	case 3:
		    	   SetBitCW4;
		    	break;		    	
		    		    	
		    	case 4:
		    	   SetBitCW5;
		    	break;
		    	
		    	case 5:
		    	   SetBitCW6;
		    	break;
		     }
	    }
	
}

///////////
void SwitchBitEN( unsigned char chs , unsigned char level )
{
	if( level == 0 )
		{
		 switch(	chs )
		    {
		    	case 0:
		    	   ClrBitEN1;
		    	break;
		    	
		    	case 1:
		    	   ClrBitEN2;
		    	break;	
		    		    	
		    	case 2:
		    	   ClrBitEN3;
		    	break;
		    	
		    	case 3:
		    	   ClrBitEN4;
		    	break;		    	
		    		    	
		    	case 4:
		    	   ClrBitEN5;
		    	break;
		    	
		    	case 5:
		    	   ClrBitEN6;
		    	break;
		    				    			    	
		    }
			
		}
	else{
		   switch(	chs )
		    {
		      case 0:
		    	   SetBitEN1;
		    	break;
		    	
		    	case 1:
		    	   SetBitEN2;
		    	break;	
		    		    	
		    	case 2:
		    	   SetBitEN3;
		    	break;
		    	
		    	case 3:
		    	   SetBitEN4;
		    	break;		    	
		    		    	
		    	case 4:
		    	   SetBitEN5;
		    	break;
		    	
		    	case 5:
		    	   SetBitEN6;
		    	break;
		    }
		    		
	    }
}
	
	
	





/////////////////////////////////////////////
//CONFIG_HD_TIM
//void TIM2_IRQHandler(void)
void StepMotInit(void)
{
//����������������ʼ��
unsigned char i;
for(i=0;i<NUMBofSTEPs;i++)
    {
    StepMot[i].Position16=0;  //������������ʾ����λ�ã�������
    SwitchBitEN(i,0);//ClrBitEN1;
    SwitchBitCW(i,0);//ClrBitCW1;
    StepMot[i].PulseCircleSet=20;//20;		//20*50us  = 0.001s
    StepMot[i].PulseCircleCount=0;//StepMot[i].PulseCircleSet;
    StepMot[i].PulseCount=0;
    StepMot[i].Enable=0;
     StepMot[i].ClkStatus=0;
    SwitchBitCLK(i,0);//ClrBitCLK1;
    StepMot[i].Direction=MOTOR_STATUS_OFF;  //����
    }


#if CONFIG_HD_TIM
	Init_Tim2 ();		//����������������
#endif

}
//////////////////////////////////////////////

void StepMoterPulseHandler(void)
{		
	unsigned char i;
for(i=0;i<NUMBofSTEPs;i++)
    {
	  
		if(( StepMot[i].Enable ) && ( StepMot[i].PulseCount > 0 ))
			  {
				if( StepMot[i].PulseCircleCount > 0 )//   ��������ٶȿ���
					{
						StepMot[i].PulseCircleCount --;
					}
				else{
						 StepMot[i].PulseCircleCount =  StepMot[i].PulseCircleSet;//   ��������ٶȿ���
						
						 if( StepMot[i].ClkStatus == 0)
							  {
								StepMot[i].ClkStatus=1;
								SwitchBitCLK(i,1);//SetBitCLK1;
							  }
						else{
								StepMot[i].ClkStatus=0;
								SwitchBitCLK(i,0);//ClrBitCLK1;
								
								StepMot[i].PulseCount--;
								
								if(StepMot[i].Direction == MOTOR_STATUS_FORWORD)		//ǰ
											{
												StepMot[i].Position16++;
											}
								else{
											StepMot[i].Position16--;
											}
								}	
							
						
						}
			 }
    }

}

////////////////////////////////////////////////////////
//�ز������1#
void StepMotStop(unsigned char chs)
{
     SwitchBitEN(chs,0);//ClrBitEN1;
     SwitchBitCW(chs,0);//ClrBitCW1;
     StepMot[chs].PulseCircleCount=0;//StepMot1.PulseCircleSet;

     StepMot[chs].PulseCount=0;
     StepMot[chs].Enable=0;
     StepMot[chs].ClkStatus=0;
     SwitchBitCLK(chs,0);//ClrBitCLK1;

     StepMot[chs].Direction=MOTOR_STATUS_OFF;  //����
}







//���������1#
//step_count>0  --->  ��ǰ MOTOR_STATUS_FORWORD   
//step_count<0  --->  ��� MOTOR_STATUS_BACKWORD  

void StepMotRun( unsigned char chs , signed int step_count)
{
	unsigned  int  step16;
	
  StepMot[chs].Enable=0;
  //-- SwitchBitEN(chs,0);//ClrBitEN1;
  SwitchBitCLK(chs,0);//ClrBitCLK1;

	if(step_count>0)//cw==MOTOR_STATUS_FORWORD)		//ǰ
		{
			StepMot[chs].Direction=MOTOR_STATUS_FORWORD;  //����
		  SwitchBitCW(chs,0);//ClrBitCW1;
		  step16=(unsigned int)step_count;
		}
	else{
		  StepMot[chs].Direction=MOTOR_STATUS_BACKWORD;
			SwitchBitCW(chs,1);//SetBitCW1;
			step16=(unsigned int)(-step_count);
			}
			
//OSTimeDly(OS_TICKS_PER_SEC/20);	    //��ʱ0.05��

StepMot[chs].PulseCircleCount=0;//StepMot[chs].PulseCircleSet;


StepMot[chs].PulseCount=step16;
StepMot[chs].ClkStatus=0;
SwitchBitEN(chs,1);//SetBitEN1;

//OSTimeDly(OS_TICKS_PER_SEC/20);	    //��ʱ0.05��

StepMot[chs].Enable=1;
}


//������������ٶȵ���
//void StepMotAdjSpeed1(uint32 cycle)
//{
//if(	cycle>60000)cycle=60000;	//���������3+3��
//	
////StepMot1.PulseCircleSet=2000;		//2000*50us  = 0.1s
//StepMot1.PulseCircleSet=cycle;
//}
//
//void StepMotAdjSpeed2(uint32 cycle)
//{
//	if(	cycle>60000)cycle=60000;	//���������3+3��
//		
////StepMot2.PulseCircleSet=2000;		//2000*50us  = 0.1s
//StepMot2.PulseCircleSet=cycle;
//}




//


