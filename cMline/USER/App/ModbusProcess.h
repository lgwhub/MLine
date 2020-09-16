
#ifndef _MODBUS_PROCESS_H
#define _MODBUS_PROCESS_H
//#include "ModbusProcess.h"


//  modbus  子地址                      Coldw.SubAdr
//默认的
#define MODBUS_SUB_ADR_DEFAULT                  1
//  不回应的广播接收地址
#define MODBUS_SUB_ADR_QUIET0                 255
#define MODBUS_SUB_ADR_QUIET1                 254
#define MODBUS_SUB_ADR_QUIET2                 80



//调整高位在前
#define MODBUS_FLOAT_HIGHBYTE_FORWORD  0
#define MODBUS_HIGHBYTE_FORWORD_2X2    1


#define MODBUS_CHECKSUM_HIGHBYTE_FORWORD  1

// MODBUS的虚拟寄存器地址        
//#define  PARAM_ADR_RAM     0X1000
//#define  PARAM_ADR_MEMORY  0X2000
//#define  PARAM_ADR_PUBLIC  0X3000

//// MODBUS的虚拟寄存器地址        
//#define  PARAM_ADR_READ       0
//#define  PARAM_ADR_USER       0X100
//#define  PARAM_ADR_SYS        0X200
//#define  PARAM_ADR_PID        0X300
//#define  PARAM_ADR_MONI       0X400



//读线圈
#define MODBUS_READ_BIT        0x01
//写线圈
#define MODBUS_WRITE_BIT       0x05
//读寄存器
#define MODBUS_READ_REGISTER   0x03
//写寄存器
#define MODBUS_WRITE_REGISTER  0x10


#define MaxModbusWordNumb   (120)
#define Max_ModbusBuf_Len  ( MaxModbusWordNumb*2 + 9 +1 ) 



void _ModbusReadBit(unsigned char Channl,unsigned char *p,unsigned short int len);//读线圈

///////////////////////
void _ModbusWriteBit(unsigned char Channl,unsigned char *p,unsigned short int len);//写线圈


void _ModbusReadWord(unsigned char Channl, unsigned char *p, unsigned short int len, unsigned char *pr);//读寄存器

///////////////////////
void _ModbusWriteWord(unsigned char Channl,unsigned char *p,unsigned short int len, unsigned char *pr);//写寄存器

///////////////////////
//void _ModbusParameterProcess(unsigned char Channl,unsigned char *p,unsigned short int len);


//接收到MODBUS包处理，判断地址，校验包，应答
//输入：  p整个modbus包指针，len整个modbus包长度
void ModbusRecvProcess(unsigned char *p,unsigned short int len);

unsigned short GetCRC_Checksum4(unsigned char *puchMsg,unsigned short usDataLen);
//unsigned  short int GetModbusCheckSumCrc(unsigned char *p, short int len);

#endif



