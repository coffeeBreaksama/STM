

#include "sampleInfoSave.h"
#include "includes.h"
extern CONFIG_DATA_U __configDataU;
SAMPLE_SAVE_INFO __sampleInfo = {
	{1.11,1.2,1.3,1.4,1.5},
	{1.11,1.2,1.3,1.4,1.5},
	2.31,
	52.5,
	200,

};

void SAMPLE_Set_square(float fData)
{	
	unsigned char testType = __configDataU.testMethodLaOrYa;
	if(0.001 <= fData <= 999)	__sampleInfo.square[testType] = fData;
	else ERR_ThrowError(0);	

}

void SAMPLE_Set_fWidthLoaded(float fData)
{
	unsigned char testType = __configDataU.testMethodLaOrYa;
	if(0.1 <= fData <= 1000)	__sampleInfo.fWidthLoaded[testType] = fData;
	else ERR_ThrowError(0);	

}

void SAMPLE_Set_StandartLen(float fData)
{
	unsigned char testType = __configDataU.testMethodLaOrYa;
	if(1 <= fData <= 1000)	__sampleInfo.StandartLen = fData;
	else ERR_ThrowError(0);		
}

void SAMPLE_Set_g(float fData)
{
	if(0.1 <= fData <= 1000)	__sampleInfo.g = fData;
	else ERR_ThrowError(0);	

}

void SAMPLE_Set_timeWillUsed(unsigned int Data)
{
	if(100 <= Data <= 99999)	__sampleInfo.timeWillUsed = Data;
	else ERR_ThrowError(0);		
}


