

#include <includes.h>


//参加平均的数据个数
#define MaxAvergeList           50
//#define MaxAvergeAD7705  40

//通道组数
#define MaxChs        MAX_BLDC_CH6

unsigned short int AvergeOffsetI1[ MaxAvergeList  +  1 ];
//unsigned short int AvergeOffsetV1;
unsigned long int  AvergeBufI[ MaxChs  + 2 ][ MaxAvergeList + 1 ];
//unsigned short int AvergeBufV[MaxAvergeList+1];
///////////////////////////////
//buf 平均缓冲区
//offset 位置偏移
//add 新增加的
//MaxSize 缓冲区尺寸
//////////////////////////////
void AddAverage( unsigned long int *buf , unsigned short int *offset , unsigned long int add , unsigned short int MaxSize )
{
	
		if(*offset<MaxSize)
			{
				(*offset)++;
			}
		else{
			 *offset=0;
			 //gFlagGetAverage=1;		//平均电流数据就绪标记
				}
				
*(buf+(*offset))=add;	
	
}
///////////////////////////////

unsigned short int GetAverage(unsigned long int *buf , unsigned short int MaxSize)
{//把测量值放入个缓冲区，滤波取数据，数据的时间范围
 //数据的更新时间为
unsigned long int average;
unsigned long int  temp32;
unsigned short int  i;

	temp32=0;
	for(i=0;i<MaxSize;i++)
		{
		temp32+=(unsigned long int)*(buf+i);
		}

	average=(unsigned short int)(temp32/MaxSize);
	
return average;
}

////////////
void InitAverage(unsigned long int *buf , unsigned short int MaxSize)
{
	unsigned short int i;
	for(i=0;i<MaxSize;i++)
		{
			*(buf+i)=0;
		}
	//gFlagGetAverage=0;		//平均电流数据就绪标记
}


