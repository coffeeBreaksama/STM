#ifndef __confDataU_c__
	#define __confDataU_c__

#include "userConf.h"
#include <stdint.h>


CONFIG_DATA_U __configDataU = {
	0,
	0,
	123.2,
	213.1,
	321.3,
	123.1,
	52,
	25,
	3601,

	{30,29,28,27,26,25},
	{25,26,27,28,29,30},
	123.1,
	222.1,
	7200,

	20,

	33,
	54,
	22,

	0,
	12,

	1,
	1,
	1,
	0,

	1,
	25.1,
	31,
	1,
	3,
	2,

	25,
	21,
	34,
	154.1,
	154.55
};

DT __systemData = {
	2016,
	8,
	19,
	9,
	26,
	20

};


void USER_Set_testMethodLaOrYa (unsigned char data)
{
	__configDataU.testMethodLaOrYa  =  data;
}

void USER_Set_ctrlMethod (unsigned char data)
{
	__configDataU.ctrlMethod  =  data;
}

void USER_Set_fTestSpeed (float data)
{
	__configDataU.fTestSpeed  =  data;
}

void USER_Set_fFastSpeed (float data)
{
	__configDataU.fFastSpeed  =  data;
}

void USER_Set_fSlowSpeed (float data)
{
	__configDataU.fSlowSpeed  =  data;
}

void USER_Set_fLoadKeeping (float data)
{
	__configDataU.fLoadKeeping  =  data;
}

void USER_Set_chiSuPrecent (unsigned char data)
{
	__configDataU.chiSuPrecent  =  data;
}

void USER_Set_loadKeepPrec (unsigned char data)
{
	__configDataU.loadKeepPrec  =  data;
}

void USER_Set_fTimeLoadKeep (unsigned int data)
{
	__configDataU.fTimeLoadKeep  =  data;
}

void USER_Set_fJudgeBreakBegin (unsigned short data)
{	
	unsigned char testMethod = __configDataU.testMethodLaOrYa;
	__configDataU.fJudgeBreakBegin[testMethod]  =  data;
}

void USER_Set_breakJudgePrecent (unsigned char data)
{	
	unsigned char testMethod = __configDataU.testMethodLaOrYa;
	__configDataU.breakJudgePrecent[testMethod]  =  data;
}

void USER_Set_fLoadStop (float data)
{
	__configDataU.fLoadStop  =  data;
}

void USER_Set_fDispStop (float data)
{
	__configDataU.fDispStop  =  data;
}

void USER_Set_fTimeStop (float data)
{
	__configDataU.fTimeStop  =  data;
}

void USER_Set_overLoadPre (unsigned char data)
{
	__configDataU.overLoadPre  =  data;
}

void USER_Set_loadProtect (int data)
{
	__configDataU.loadProtect  =  data;
}

void USER_Set_dispProtect (int data)
{
	__configDataU.dispProtect  =  data;
}


void USER_Set_whichLoadCell (unsigned char data)
{
	__configDataU.whichLoadCell  =  data;
}


void USER_Set_whichElongCell (unsigned char data)
{
	__configDataU.whichElongCell  =  data;
}


void USER_Set_loadUion (unsigned char data)
{
	__configDataU.loadUion  =  data;
}


void USER_Set_elongUion (unsigned char data)
{
	__configDataU.elongUion  =  data;
}


void USER_Set_stressUion (unsigned char data)
{
	__configDataU.stressUion  =  data;
}


void USER_Set_languageSel (unsigned char data)
{
	__configDataU.languageSel  =  data;
}


void USER_Set_curveSel (unsigned char data)
{
	__configDataU.curveSel  =  data;
}


void USER_Set_fYujinli (float data)
{
	__configDataU.fYujinli  =  data;
}


void USER_Set_yujinClrFlagLoad (unsigned char data)
{
	__configDataU.yujinClrFlagLoad  =  data;
}

void USER_Set_yujinClrFlagDisp (unsigned char data)
{
	__configDataU.yujinClrFlagDisp  =  data;
}



void USER_Set_autoReturn (unsigned char data)
{
	__configDataU.autoReturn  =  data;
}


void USER_Set_printerType (unsigned char data)
{
	__configDataU.printerType  =  data;
}


void USER_Set_speedBegin (unsigned char data)
{
	__configDataU.speedBegin  =  data;
}


void USER_Set_aCol (unsigned char data)
{
	__configDataU.aCol  =  data;
}


void USER_Set_dispFrom (unsigned char data)
{
	__configDataU.dispFrom  =  data;
}



void USER_Set_dnLimitClampDisp (float data)
{
	__configDataU.dnLimitClampDisp  =  data;
}


void USER_Set_testClampDisp (float data)
{
	__configDataU.testClampDisp  =  data;
}


void USER_Set_fTimeProtect (char data)
{
	__configDataU.fTimeProtect  =  data;
}


void USER_Set_printerIntensity(unsigned char data)
{
	__configDataU.printerIntensity  =  data;

}

/////////////////////////////////////////////////////
void SYS_Set_year(unsigned short data)
{
	__systemData.year = data;
}

void SYS_Set_month(unsigned char data)
{
	__systemData.month = data;
}

void SYS_Set_day(unsigned char data)
{
	__systemData.day = data;
}

void SYS_Set_hour(unsigned char data)
{
	__systemData.hour = data;
}
void SYS_Set_minute(unsigned char data)
{
	__systemData.minute = data;
}

void SYS_Set_second(unsigned char data)
{
	__systemData.second = data;
}

#endif