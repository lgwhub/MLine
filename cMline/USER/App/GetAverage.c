

#include <includes.h>


//�μ�ƽ�������ݸ���
#define MaxAvergeList           50
//#define MaxAvergeAD7705  40

//ͨ������
#define MaxChs        MAX_BLDC_CH6

unsigned short int AvergeOffsetI1[ MaxAvergeList  +  1 ];
//unsigned short int AvergeOffsetV1;
unsigned long int  AvergeBufI[ MaxChs  + 2 ][ MaxAvergeList + 1 ];
//unsigned short int AvergeBufV[MaxAvergeList+1];
///////////////////////////////
//buf ƽ��������
//offset λ��ƫ��
//add �����ӵ�
//MaxSize �������ߴ�
//////////////////////////////
void AddAverage( unsigned long int *buf , unsigned short int *offset , unsigned long int add , unsigned short int MaxSize )
{
	
		if(*offset<MaxSize)
			{
				(*offset)++;
			}
		else{
			 *offset=0;
			 //gFlagGetAverage=1;		//ƽ���������ݾ������
				}
				
*(buf+(*offset))=add;	
	
}
///////////////////////////////

unsigned short int GetAverage(unsigned long int *buf , unsigned short int MaxSize)
{//�Ѳ���ֵ��������������˲�ȡ���ݣ����ݵ�ʱ�䷶Χ
 //���ݵĸ���ʱ��Ϊ
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
	//gFlagGetAverage=0;		//ƽ���������ݾ������
}


