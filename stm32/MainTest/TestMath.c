#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <string.h>
#include "testmath.h"

#define MINPREC 	0.0001

extern const float __LoadUnitCol[];
extern const float __ElongUnitCol[];
extern const float __SqareUnitCol[];
extern const float __stressUnitCol[];
extern const float __stressUnitCol2[];

extern const char _scaleDev[];

//力量值换算成另外单位的

float LoadUnitChn(float fRval,U8 rUnitInd,U8 outUninInd) 
{
	fRval *=__LoadUnitCol[rUnitInd];
	fRval /= __LoadUnitCol[outUninInd];
	return(fRval);
}

float ElongUnitChn(float fRval,U8 rUnitInd,U8 outUninInd) 
{
	fRval *=__ElongUnitCol[rUnitInd];
	fRval /= __ElongUnitCol[outUninInd];
	return(fRval);
}

float StressUnitChn(float fRval,U8 rUnitInd,U8 outUninInd) 
{
	fRval *=__stressUnitCol[rUnitInd];
	fRval /= __stressUnitCol[outUninInd];
	return(fRval);
}

float StressCel(float fload,U8 lUnitInd,float fSqare,U8 eUnitInd,U8 outUninInd) 
{
	float fStress = 0;
	fload = LoadUnitChn(fload,lUnitInd,0);
	fSqare *= __SqareUnitCol[eUnitInd];
	fStress = StressUnitChn(fload/fSqare,0,outUninInd);
	return(fStress);
}

float StressUnitChn2(float fRval,U8 rUnitInd,U8 outUninInd) 
{
	fRval *=__stressUnitCol2[rUnitInd];
	fRval /= __stressUnitCol2[outUninInd];
	return(fRval);
}

float StressCel2(float fload,U8 lUnitInd,float fElong,U8 eUnitInd,U8 outUninInd) 
{
	float fStress = 0;
	fload = LoadUnitChn(fload,lUnitInd,0);
	fElong *= __ElongUnitCol[eUnitInd];
	fStress = StressUnitChn2(fload/fElong,0,outUninInd);
	return(fStress);
}

float Stress2Load(float fStress,U8 stressUnit,float fSqare,U8 eUnitInd,U8 loadUnin) 
{
	float fLoad = 0;
	fStress = StressUnitChn(fStress,stressUnit,0); 
	fSqare *= __SqareUnitCol[eUnitInd];	
	fLoad = fStress*fSqare;
	fLoad = LoadUnitChn(fLoad,0,loadUnin);
	return(fLoad);
}

//设置测量得中间值 以便简便计算

float GbGetPrec(float fs)
{
	float	prec, orderedPrec;
	int		order, i;
	prec = fs/2000;
	for(order=0; ; order++) {
		orderedPrec = floor(prec+0.01);
		if(orderedPrec>0.99) {
			if(orderedPrec>4.99) {
				orderedPrec=5;
			} else if(orderedPrec>1.99) {
				orderedPrec=2;
			} else {
				orderedPrec=1;
			}
			break;
		}
		prec*=10;
	}
	for(i=0; i<order; i++) {
		orderedPrec/=10;
	}
	return(orderedPrec);
}

unsigned char  GetDotNum(float mfs,unsigned char scaleIndex)
{
	float fs;
	fs = (float)mfs/_scaleDev[scaleIndex];
	if(fs < 1.999) {
		return(4);
	} else if(fs < 19.99) {
		return(3);
	} else if(fs < 199.9) {
		return(2);
	} else if(fs < 1999) {
		return(1);
	} else {
		return(0);
	}
}

float RoundFloat(float dOrg, float prec)
{
	prec=MAX(prec, MINPREC);
	return(floor(dOrg/prec+(0.5-MINPREC))*prec);
}

void GuiYu(char *buf,float fV,unsigned char dotNum)
{
	switch(dotNum){
	case 1:
		sprintf(buf,"%6.1f",fV);
	break;
	case 2:
		sprintf(buf,"%6.2f",fV);
	break;
	case 3:
		sprintf(buf,"%6.3f",fV);
	break;
	case 4:
		sprintf(buf,"%6.4f",fV);
	break;
	default:
		sprintf(buf,"%6d",(int)(fV));
	break;
	}
	*(buf+6) = '\0';
}

void TrimString(char *pStr)
{
	int i;
	i = strlen(pStr);
	if(i > 0){
		if(strchr(pStr,'.')== NULL) return;
		i--;
		if(i == 0) return;
		for(;;){
			if(pStr[i] == '0') {
				pStr[i] = '\0';
				i--;
				if(i == 0) return;
			}
			else if(pStr[i] == '.'){
				pStr[i] = '\0';
				return;
			}
			else{
				return;
			}
		}
	}
}

static const unsigned short MASKS[] = {
0x49ab, 0x8853, 0xF4CB, 0x1229, 0x3d8E, 0xE012, 0x572A, 0xD892,
0x2C99, 0x0931, 0xDEEE, 0x7123, 0x633A, 0xCC10, 0x94E1, 0xA00D, };

unsigned short MaskMid(unsigned short mid)
{
	int i = (mid & 0x0f);
	return((mid>>1)+(MASKS[i]>>1));
}

long LiderEncode(unsigned short mid, unsigned short ic) //mid 为机器号 ,ic为目标值如 (5*12+6)0506
{
	int i = (ic & 0x0f);
	long lmask = (long)MASKS[i];
	long mmid = (long)MaskMid(mid);
	long ic128 = (((long)ic)<<7);
	return(((mmid+lmask+ic128)<<4)+i); 
}

unsigned short LiderDiscode(unsigned short mid, long oc) //mid 为机器号 ,密码
{
	int i = (oc & 0x0f);
	long lmask = (long)MASKS[i];
	long mmid = (long)MaskMid(mid);
	long ic128 = (((oc-i)>>4)-lmask-mmid);
	if((ic128 & 0x7f) != 0) {
		return(0xFFFF);
	}
	return((unsigned short)(ic128>>7)); //得到目标值
}

extern volatile unsigned int OS_TimeMS;

void TimerInit(TIMER_DATA * pTimer)
{
   pTimer->lastTickCunt = OS_TimeMS;
}

unsigned int TimerIsOver(TIMER_DATA * pTimer,double fTimerS)
{
     pTimer->nowTickCunt = OS_TimeMS;
	 if((pTimer->nowTickCunt - pTimer->lastTickCunt)*1.0/1000 > fTimerS) return 1;
	 else {
	 	return 0;
	}
}

void SoftFifoInit(SOFT_FIFO * pSF,unsigned char *pBuf,unsigned int fifoLen)
{
   pSF->pFifoBuf = pBuf;
   pSF->fifoLen = fifoLen;
   pSF->firstIn = 0;
   pSF->emptyTail = 0;
}

void SoftFifoInput(SOFT_FIFO * pSF,unsigned char *buf,unsigned int len)
{
	int i = 0; 
	for(i=0;i<len;i++) {
		*(pSF->pFifoBuf+(pSF->emptyTail)) = *(buf+i);
		pSF->emptyTail++;
		if(pSF->emptyTail >=  pSF->fifoLen) pSF->emptyTail = 0;
	}	
}

unsigned int SoftFifoOut(SOFT_FIFO * pSF,unsigned char *buf,unsigned int len)
{
  	unsigned int i = 0; 
	for(i=0;(i<len) && (pSF->firstIn != pSF->emptyTail);i++) {
		*(buf+i) = *(pSF->pFifoBuf+(pSF->firstIn));
		pSF->firstIn++;
		if(pSF->firstIn >=  pSF->fifoLen) pSF->firstIn = 0;
	}
	return i;
}

extern const unsigned short CRCTable[256]=  
{0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
							0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
							0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
							0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
							0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
							0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
							0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
							0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
							0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
							0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
							0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
							0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
							0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
							0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
							0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
							0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
							0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
							0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
							0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
							0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
							0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
							0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
							0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
							0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
							0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
							0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
							0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
							0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
							0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
							0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
							0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
							0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
						   };

/********************************************************************************************************************
** 函数名称: INT8U SD_GetCRC16()					Name:	  INT8U SD_GetCRC16()
** 功能描述: 计算CRC16								Function: calculate CRC16 
** 输　  入: INT8U *pSource: 数据					Input:    INT8U *pSource: data
			 INT16U len    : 长度							  INT16U len    : len
** 输 　 出: CRC16码								Output:	  CRC16 code
********************************************************************************************************************/
unsigned short GetCRC16(unsigned char *pSource, unsigned int len)
{
	unsigned short i;
	unsigned short result = 0;

	for (i = 0; i < len; i++)
	    result = (result << 8) ^ (unsigned short)CRCTable[(result >> 8) ^ *pSource++];
	return result;
}

				 //将hex字符表示 转换成字节表示 “1A" 变成二进制 0x1A  
unsigned char HexChar2Byte(unsigned char hexH,unsigned char hexL)
{
	if(hexH >='0' && hexH <='9')  hexH -= '0';
	else if(hexH >='a' && hexH <='f')  {
		hexH -= 'a';
		hexH+=10;
	}
	else if(hexH >='A' && hexH <='F')  {
		hexH -= 'A';
		hexH += 10;
	}
	else hexH = 0;

	if(hexL >='0' && hexL <='9')  hexL -= '0';
	else if(hexL >='a' && hexL <='f')  {
		hexL -= 'a';
		hexL += 10;
	}
	else if(hexL >='A' && hexL <='F')  {
		hexL -= 'A';
		hexL += 10;
	}
	else hexL = 0;
	
	return (hexH<<4)|hexL;
}

void Byte2HexChar(unsigned char c,unsigned char *pHexH,unsigned char *pHexL)
{
	char buf[3];
	sprintf(buf,"%02x",c);
	*pHexH = buf[0];
	*pHexL = buf[1];
}

unsigned int  ByteArray2UI32(unsigned char *pBypte,unsigned int len)//大端在前Int处理
{
	unsigned int ret=0,i= 0;
	for(i=0;i<len;i++){
		ret<<=8;
		ret |= pBypte[i];
	}
	return ret;
}

int  ByteArray2I32(unsigned char *pBypte,unsigned int len)//大端在前Int处理
{
	int ret=0,i= 0;
	for(i=0;i<len;i++){
		ret<<=8;
		ret |= pBypte[i];
	}
	return ret;	
}

unsigned int  Uint2ByteArray(unsigned int val,unsigned char * pBypte)//大端在前Int处理
{
	*pBypte = (val&0xFF000000)>>24;
	*(pBypte+1) = (val&0x00FF0000)>>16;
	*(pBypte+2) = (val&0x0000FF00)>>8;
	*(pBypte+3) = (val&0x000000FF);
	return 1;
}


