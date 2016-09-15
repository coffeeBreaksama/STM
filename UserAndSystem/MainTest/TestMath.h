#ifndef __TESTMATH_H__
#define __TESTMATH_H__
#include "bdef.h"

	float LoadUnitChn(float fRval,U8 rUnitInd,U8 outUninInd); 
	float ElongUnitChn(float fRval,U8 rUnitInd,U8 outUninInd); 
	float StressUnitChn(float fRval,U8 rUnitInd,U8 outUninInd); 
	float StressCel(float fload,U8 lUnitInd,float fSqare,U8 eUnitInd,U8 outUninInd); 

    float StressUnitChn2(float fRval,U8 rUnitInd,U8 outUninInd); 
    float StressCel2(float fload,U8 lUnitInd,float fElong,U8 eUnitInd,U8 outUninInd);
	float Stress2Load(float fStress,U8 stressUnit,float fSqare,U8 eUnitInd,U8 loadUnin); 
	float GbGetPrec(float fs);
	unsigned char  GetDotNum(float mfs,unsigned char scaleIndex);
	float RoundFloat(float dOrg, float prec);
	void GuiYu(char *buf,float fV,unsigned char dotNum);
	void TrimString(char *pStr);long LiderEncode(unsigned short mid, unsigned short ic); //mid 为机器号 ,ic为目标值如 (5*12+6)0506
	unsigned short LiderDiscode(unsigned short mid, long oc); //mid 为机器号 ,密码
	
	typedef struct{
		unsigned int lastTickCunt;
		unsigned int nowTickCunt;
	}TIMER_DATA;

	void TimerInit(TIMER_DATA * pTimer);
	unsigned int TimerIsOver(TIMER_DATA * pTimer,double fTimerS);
	
	unsigned short GetCRC16(unsigned char *pSource, unsigned int len);

	typedef struct {
		volatile unsigned int firstIn;
		volatile unsigned int emptyTail;
		volatile unsigned char *pFifoBuf;
		unsigned int fifoLen;
	} SOFT_FIFO;
   	void SoftFifoInit(SOFT_FIFO * pSF,unsigned char *pBuf,unsigned int fifoLen);
	void SoftFifoInput(SOFT_FIFO * pSF,unsigned char *buf,unsigned int len);
	unsigned int SoftFifoOut(SOFT_FIFO * pSF,unsigned char *buf,unsigned int len);

	unsigned char HexChar2Byte(unsigned char hexH,unsigned char hexL);
	void Byte2HexChar(unsigned char c,unsigned char *pHexH,unsigned char *pHexL);
	unsigned int  ByteArray2UI32(unsigned char *pBypte,unsigned int len);//大端在前Int处理
	int  ByteArray2I32(unsigned char *pBypte,unsigned int len);//大端在前Int处理

	unsigned int  Uint2ByteArray(unsigned int val,unsigned char * pBypte);//大端在前Int处理

#endif

