

#ifndef  __LED_DISP_H
#define  __LED_DISP_H


//  #include "LedDisp.h"

unsigned long  Process_N_NUMBnny(void);
unsigned long  Process_N_NUMBnnz(void);

extern unsigned char DispBufnny[];
extern unsigned char DispBufnnz[];

extern unsigned char   Alm_Flag1;    //����ָʾ��
extern unsigned char   Alm_Flag2;    //����ָʾ��
extern unsigned char   SngnalLed[4];      //����ָʾ��



void PutValToDispBf(unsigned short val , unsigned char  *position );

#endif

