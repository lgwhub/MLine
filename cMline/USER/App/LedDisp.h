

#ifndef  __LED_DISP_H
#define  __LED_DISP_H


//  #include "LedDisp.h"

void Process_N_NUMBnny(void);
void Process_N_NUMBnnz(void);

extern unsigned char DispBufnny[];
extern unsigned char DispBufnnz[];

void PutValToDispBf(unsigned short val , unsigned char  *position );

#endif

