

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
	__sampleInfo.square[testType] = fData;
}

void SAMPLE_Set_fWidthLoaded(float fData)
{
	unsigned char testType = __configDataU.testMethodLaOrYa;
	__sampleInfo.fWidthLoaded[testType] = fData;
}

void SAMPLE_Set_StandartLen(float fData)
{
	__sampleInfo.StandartLen = fData;
}

void SAMPLE_Set_g(float fData)
{
	__sampleInfo.g = fData;
}

void SAMPLE_Set_timeWillUsed(unsigned int Data)
{
	__sampleInfo.timeWillUsed = Data;
}


