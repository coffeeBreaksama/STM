#ifndef __confDataU_c__
	#define __confDataU_c__

#include "userConf.h"
#include <stdint.h>
#include "app.h"


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
	154.55,

	200,
	300
};

DT __systemDt = {
	2016,
	8,
	19,
	9,
	26,
	20

};


void User_Set_testMethodLaOrYa (unsigned char data)
{
	if(0 <= data && data <= 5)
	__configDataU.testMethodLaOrYa  =  data;
	else __SaveDataSuccess = 0;	
}

void User_Set_ctrlMode (unsigned char data)
{
	if(0 <= data && data <= 2)
	__configDataU.ctrlMethod  =  data;
	else __SaveDataSuccess = 0;		
}

void User_Set_fTestSpeed (float data)
{
	if(0 <= data && data <= 500)
	__configDataU.fTestSpeed  =  data;
	else __SaveDataSuccess = 0;	
}

void User_Set_fFastSpeed (float data)
{
	if(0 <= data && data <= 500)
	__configDataU.fFastSpeed  =  data;
	else __SaveDataSuccess = 0;		
}

void User_Set_fSlowSpeed (float data)
{
	if(0 <= data && data <= 500)
	__configDataU.fSlowSpeed  =  data;
	else __SaveDataSuccess = 0;		
}

void User_Set_fLoadKeeping (float data)
{
	if(0.1 <= data && data <= 10000)
	__configDataU.fLoadKeeping  =  data;
	else __SaveDataSuccess = 0;		
}

void User_Set_chiSuPrecent (int data)
{
	if(1 <= data && data <= 100)
	__configDataU.chiSuPrecent  =  data;
	else __SaveDataSuccess = 0;
}

void User_Set_loadKeepPrec (int data)
{
	if(1 <= data && data <= 100)
	__configDataU.loadKeepPrec  =  data;
	else __SaveDataSuccess = 0;	
}

void User_Set_fTimeLoadKeep (int data)
{
	if(0 <= data && data <= 10000000)
	__configDataU.fTimeLoadKeep  =  data;
	else __SaveDataSuccess = 0;
}

void User_Set_fJudgeBreakBegin (int data)
{	
	if(0 <= data && data <= 100)
	__configDataU.fJudgeBreakBegin[__configDataU.testMethodLaOrYa]  =  data;
	else __SaveDataSuccess = 0;
}

void User_Set_breakJudgePrecent (int data)
{	
	if(0 <= data && data <= 100)
	__configDataU.breakJudgePrecent[__configDataU.testMethodLaOrYa]  =  data;
	else __SaveDataSuccess = 0;	
}

void User_Set_fLoadStop (float data)
{
	if(0 <= data && data <= __loadMfs)
	__configDataU.fLoadStop  =  data;
	else __SaveDataSuccess = 0;	
	//TODO
	//__loadMfs不知道，定义放在Undefine.c里面,搜索“//定义未明”可看到
}

void User_Set_fDispStop (float data)
{
	if(0 <= data && data <= 10000)
	__configDataU.fDispStop  =  data;
	else __SaveDataSuccess = 0;	
}

void User_Set_fTimeStop (float data)
{
	if(0 <= data && data <= 10000)
	__configDataU.fTimeStop  =  data;
	else __SaveDataSuccess = 0;		
}

void User_Set_overLoadPre (int data)
{
	if(10 <= data&&data <= 110)	__configDataU.overLoadPre  =  data;
	else __SaveDataSuccess = 0;		

}

void User_Set_loadProtect (int data)
{
	if(0 <= data && data <= 110)
	__configDataU.loadProtect  =  data;
	else __SaveDataSuccess = 0;		
}

void User_Set_dispProtect (int data)
{
	if(1 <= data&&data <= 3000) __configDataU.dispProtect  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_whichLoadCell (unsigned char data)
{	
	if(0 <= data&&data <= 1)__configDataU.whichLoadCell  =  data;
	else __SaveDataSuccess = 0;	

}


void User_Set_whichElongCell (unsigned char data)
{
	if(1 <= data && data <= 1)
	__configDataU.whichElongCell  =  data;
	else __SaveDataSuccess = 0;	
}


void User_Set_loadUion (unsigned char data)
{
	if(0 <= data && data <= 4)
	__configDataU.loadUion  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_elongUion (unsigned char data)
{
	if(0 <= data && data <= 2)
	__configDataU.elongUion  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_stressUion (unsigned char data)
{
	if(data >= 0 && data <= 5)
	__configDataU.stressUion  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_languageSel (unsigned char data)
{
	if(data <= 2)
	__configDataU.languageSel  =  data;
	else __SaveDataSuccess = 0;	
}


void User_Set_curveSel (unsigned char data)
{
	if(0 <= data && data <= 2)
	__configDataU.curveSel  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_fYujinli (float data)
{
	if(0 <= data&&data <= __loadMfs)
		__configDataU.fYujinli  =  data;
	else __SaveDataSuccess = 0;
}


void User_Set_yujinClrFlagLoad (unsigned char data)
{	
	if(0 <= data&&data <= 1)
	__configDataU.yujinClrFlagLoad  =  data;
	else __SaveDataSuccess = 0;
}

void User_Set_yujinClrFlagDisp (unsigned char data)
{
	if(0 <= data&&data <= 1)
	__configDataU.yujinClrFlagDisp  =  data;
	else __SaveDataSuccess = 0;		
}



void User_Set_autoReturn (unsigned char data)
{
	if(0 <= data && data <= 1)
	__configDataU.autoReturn  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_printerType (unsigned char data)
{
	if(0 <= data && data <= 3)
	__configDataU.printerType  =  data;
	else __SaveDataSuccess = 0;		
}


void User_Set_speedBegin (int data)
{	
	if(1 <= data && data <= 500)
	__configDataU.speedBegin  =  data;	
	else __SaveDataSuccess = 0;

}


void User_Set_aCol (int data)
{

	if(data >= 1 && data <= 200)
	__configDataU.aCol  =  data;	
	else __SaveDataSuccess = 0;

}


void User_Set_dispFrom (unsigned char data)
{
	if(0 <= data&&data <= 1)
	__configDataU.dispFrom  =  data;
	else __SaveDataSuccess = 0;	
}



void User_Set_dnLimitClampDisp (float data)
{
	if(0 <= data&&data <= 999)
	__configDataU.dnLimitClampDisp  =  data;
	else __SaveDataSuccess = 0;	
}


void User_Set_testClampDisp (float data)
{
	if(0 <= data&&data <= 2000)
	__configDataU.testClampDisp  =  data;
	else __SaveDataSuccess = 0;	
}


void User_Set_fTimeProtect (int data)
{
	if(0 <= data&&data <= 100)	
	__configDataU.fTimeProtect  =  data;
	else __SaveDataSuccess = 0;	

}


void User_Set_printerIntensity(unsigned char data)
{
	if(0 <= data&&data <= 1)
	__configDataU.printerIntensity  =  data;
	else __SaveDataSuccess = 0;	

}
void User_Set_gasInTime (int data)
{
	if(0 <= data&&data <= 9999999)
	__configDataU.gasInTime  =  data;
	else __SaveDataSuccess = 0;	

}


void User_Set_gasOutTime (int data)
{
	if(0 <= data&&data <= 9999999)
	__configDataU.gasOutTime  =  data;
	else __SaveDataSuccess = 0;	

}

/////////////////////////////////////////////////////
void SYS_Set_year(int data)
{	
	if(2000 <= data&&data <= 2100)	
	__systemDt.year = data;
	else __SaveDataSuccess = 0;

}

void SYS_Set_month(int data)
{
	if(1 <= data&&data <= 12)	
	__systemDt.month = data;
	else __SaveDataSuccess = 0;
}

void SYS_Set_day(int data)
{
	if(1 <= data&&data <= 31)	
	__systemDt.day = data;
	else __SaveDataSuccess = 0;
}

void SYS_Set_hour(int data)
{
	if(0 <= data&&data <= 23)	
	__systemDt.hour = data;
	else __SaveDataSuccess = 0;	
}
void SYS_Set_minute(int data)
{
	if(0 <= data&&data <= 59)	
	__systemDt.minute = data;
	else __SaveDataSuccess = 0;	
}

void SYS_Set_second(int data)
{
	if(0 <= data&&data <= 59)	
	__systemDt.second = data;
	else __SaveDataSuccess = 0;	
}

#endif