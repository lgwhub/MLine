

#ifndef  __LED_DISP_H
#define  __LED_DISP_H


//  #include "LedDisp.h"

unsigned long  Process_N_NUMBnny(void);
unsigned long  Process_N_NUMBnnz(void);

extern unsigned char DispBufnny[];
extern unsigned char DispBufnnz[];

extern unsigned char   Alm_Flag1;    //报警指示灯
extern unsigned char   Alm_Flag2;    //报警指示灯
extern unsigned char   SngnalLed[4];      //单独指示灯



void PutValToDispBf(unsigned short val , unsigned char  *position );

#endif

