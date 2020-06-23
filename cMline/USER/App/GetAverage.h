
//		#include	"GetAverage.h"

#ifndef	_GET_AVERAGE_H
#define	_GET_AVERAGE_H


//参加平均的数据个数
#define MaxAvergeList           50
//#define MaxAvergeAD7705  40

//通道组数
#define MaxChs        MAX_BLDC_CH6


extern	unsigned short int AvergeOffsetI1[  ];
//extern	unsigned short int AvergeOffsetV1;
extern	unsigned long int  AvergeBufI[ MaxChs  + 2 ][ MaxAvergeList + 1 ];
//extern	unsigned short int AvergeBufV[MaxAvergeList+1];




//extern	unsigned short int AvergeOffsetI[4];
//extern	unsigned short int AvergeOffsetV[4];
//extern	unsigned short int  AvergeBufI[4][MaxAvergeList+1];
//extern	unsigned short int  AvergeBufV[4][MaxAvergeList+1];


///////////////////////////////
void AddAverage( unsigned long int *buf , unsigned short int *offset , unsigned long int add , unsigned short int MaxSize );
unsigned short int GetAverage(unsigned long int *buf , unsigned short int MaxSize);
void InitAverage(unsigned long int *buf , unsigned short int MaxSize);


#endif

