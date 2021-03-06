
#include "includes.h"
#include "PID.h"

//电加热控制
//const float PID_Default[5][3]=
//{
//150  ,     2,       12,	
////5.0  , 0.2  ,0.6	,    //p1  i1  d1
////2.0  , 0.05  ,0.1	,    //p2  i2  d2
////2.0  , 0.05  ,0.1	,
////2.0  , 0.05  ,0.1		
//};


//PID_ParaStruct      PidParam[2];

PidBufStruct HeatPidBuf[MAX_BLDC_CH6];
//PidBufStruct StepPidBuf[MAX_BLDC_CH6];




//////////////////////////

void PID_ParaInit(void)
{


	 
//	 Coldw.Pidx[0].Proportion     =       0.00031001;//20;//3;          //比例常数
//	 Coldw.Pidx[0].Integral         =       0.00031001;//0.02001;          //	 
//	 Coldw.Pidx[0].Derivative     =       0.00002;//22;//55;//50;//2;//1;
//	 Coldw.Pidx[0].QMax           =       MAX_PID_INTEGRAL_1;
//   Coldw.Pidx[0].QMin             =        MIN_PID_INTEGRAL_1;  
   
   
	 Coldw.Pidx[0].Proportion     =      0.31001;// 0.301;//20;//3;          //比例常数
	 Coldw.Pidx[0].Integral         =       0.019001;//0.02801;//0.02001;          //	 
	 Coldw.Pidx[0].Derivative     =       0.000;//22;//55;//50;//2;//1;
	 Coldw.Pidx[0].QMax           =       MAX_PID_INTEGRAL_1;
   Coldw.Pidx[0].QMin             =        MIN_PID_INTEGRAL_1;  		
		
	 Coldw.Pidx[1].Proportion  =  0.301;          //比例常数
	 Coldw.Pidx[1].Integral    =   0.012;//0.01801;          //	 Coldw.Pidx[1].Integral    =   0.00801;          //
	 Coldw.Pidx[1].Derivative  =   0;
	 Coldw.Pidx[1]. QMax       =   MAX_PID_INTEGRAL_1;
   Coldw.Pidx[1]. QMin       =   MIN_PID_INTEGRAL_1;  


}




void PID_BufInit(PidBufStruct *pidch)
{
	  pidch->SetPoint=0;       //设定目标
   
    pidch->LastError	= 0;     //上次偏差
    pidch->PreError   = 0;      //上上次偏差
    pidch->SumError   = 0;     //累积偏差
    pidch->Qx=0;									//输出   结果 Px+Ix+Dx
    pidch->Px=0;		//P部分
    pidch->Ix=0;    //I部分  
    pidch->Dx=0;			//D部分	

}

/********************************************************
* Function:    PID_Calc
* Description: PID计算
* Input:       PIDstruct *  需要计算的PID控制结构体指针
*              NowPoint         实际反馈值
* Output:      float           PID运算结果
* Calls:       无
* Called by:   CtrlTemp
* Others:
*********************************************************/
void PID_Calc(  PID_ParaStruct  *types  ,  PidBufStruct  *pidch  ,  float NowPoint )
{
    float   dError , Error ;
    
    float   total  ,  temp ;
    

    
    Error                           =    pidch->SetPoint   -   NowPoint   ;              //计算偏差  e0
    pidch  ->  SumError    +=   Error;                      							//积分累加  e0++
    dError                        =    pidch->LastError  -  pidch->PreError;     		//当前微分  e1-e2
    
    //更新
    pidch  ->  PreError       =     pidch->LastError;              							//上次偏差赋给上上次偏差  e2=e1
    pidch  ->  LastError      =     Error;                 										//当前偏差赋给上次偏差    e1=e0
    
    
    
    //////////抗饱和////////////////////////////////////////////////////MAX_PID_INTEGRAL

		 
		    
		    
			if(   types  ->  Integral   ==   0   )
			           {
		                pidch  ->  SumError =  0;
                        }
		       else{

                       temp =      types -> Integral    *    pidch -> SumError  ;
        
                        if(   temp     >    MAX_PID_INTEGRAL_1   )
		                            {
		                               pidch -> SumError     =     MAX_PID_INTEGRAL_1  /   (types->Integral);
		                              }
                    else if (     temp    <     MIN_PID_INTEGRAL_1   )
                                 {
		                        pidch -> SumError    =     MIN_PID_INTEGRAL_1  /  (  types -> Integral  );
		                      }
                    }		    
		    
		    
		    
		//////////////////////    


    
    pidch -> Px       =           types -> Proportion   *    Error    ;	          //P部分
    pidch -> Ix        =           types -> Integral       *    pidch -> SumError;	//I部分  
    pidch->Dx         =          types -> Derivative    *    dError;	        //D部分
   
    total                  =           pidch -> Px    +     pidch -> Ix    +    pidch -> Dx;

    if(  total     <     MIN_PID_RESOULT_1  )
    	   {       pidch -> Qx      =      (signed long int) MIN_PID_RESOULT_1;
    	   }
    else if(    total     >   MAX_PID_RESOULT_1 )
    	  {
    		pidch -> Qx       =    (signed long int) MAX_PID_RESOULT_1;
    	  }
    else {
    	    pidch->Qx   = (signed long int)total;
           }
         
        
}



void PID_Calcxxxxx(PID_ParaStruct *types, PidBufStruct *pidch, float Error ,unsigned char typeflag)
{
    float dError;
    
    float total,temp;
    
//////////////////////////////////////////////////////        
    float PidRate;
    
    PidRate = 0;
//////////////////////////////////////////////////////    
 if( typeflag == 1)
 	{
    if( Error>0 )
    	{
    		if(  pidch->LastError >0    )
    			{
    				if( Error > 6 )  //误差6度
    					{
    						 PidRate = 2;
    					}
    				else{
    					    PidRate = 0;
    				    }	
     			}
    	}
 //////////////////////////////
     if( Error<0 )
    	{
    		if(  pidch->LastError <0 )  
    			{
    				if( Error < (-6 ))
    					{
    						 PidRate = 2;
    					}
    				else{
    					    PidRate = 0;
    				    }	
     			}
    	}   
    }
  else{
  	PidRate = 0;
     }	

   if( PidRate >5 )PidRate = 5;
    
    
    //Error            =    pidch->SetPoint   -   NowPoint   ;              //计算偏差  e0
    pidch->SumError  +=   Error;                      							//积分累加  e0++
    dError           =    pidch->LastError  -  pidch->PreError;     		//当前微分  e1-e2
    
    //更新
    pidch->PreError  =    pidch->LastError;              							//上次偏差赋给上上次偏差  e2=e1
    pidch->LastError =    Error;                 										//当前偏差赋给上次偏差    e1=e0
    
    
    
    //////////抗饱和////////////////////////////////////////////////////MAX_PID_INTEGRAL

		    
   
		    
		    
		    
			if( types->Integral == 0 )
			{
		    pidch->SumError =  0;

		  }
		else{

        
        temp =      types->Integral * pidch->SumError ;
        
        if( ( temp ) >  types->QMax )
		          {
		           pidch->SumError  =  types->QMax/(types->Integral);
		          }
        else if( ( temp )  < types->QMin )
		         {
		           pidch->SumError  = types->QMin/(types->Integral);
		         }
	        
        }		    
		    
		    
		    
		//////////////////////    


    
    pidch->Px =   types->Proportion *  Error * ( 1 + PidRate)  ;	          //P部分
    pidch->Ix =   types->Integral   *  pidch->SumError;	//I部分  
    pidch->Dx =   types->Derivative *  dError;	        //D部分
   
   
    total     =   pidch->Px + pidch->Ix + pidch->Dx;


    if( total < types->QMin )
    	{   pidch->Qx  =  (signed long int)types->QMin;
    	}
    else if( total > types->QMax )
    	{
    		pidch->Qx   = (signed long int)types->QMax;
    	}
    else {
    	    pidch->Qx   = (signed long int)total;
         }
         
        
}

