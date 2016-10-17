#ifndef __userConf_h__
#define __userConf_h__

typedef struct {
	unsigned char testMethodLaOrYa;
	unsigned char ctrlMethod;
	float fTestSpeed;//试验速度
	float fFastSpeed;//快速速度
	float fSlowSpeed;//慢速速度
	
	float fLoadKeeping;//保持力量
	unsigned char chiSuPrecent;  //持速系数
	unsigned char loadKeepPrec;	//力量保持精度
	unsigned int fTimeLoadKeep;//保持力量时间，s为单位
	
	unsigned short fJudgeBreakBegin[6];//力量破坏开始百分比
	unsigned char breakJudgePrecent[6];//力量破坏百分比
	float fLoadStop;//指定停机方式
	float fDispStop;
	float fTimeStop;


	unsigned char overLoadPre;//过载百分比

	int loadProtect;
	int dispProtect;//位移保护
	char fTimeProtect;//时间保护

	unsigned char whichLoadCell;//选择哪个力量传感器 荷重元
	unsigned char whichElongCell;
	
	unsigned char loadUion;//单位
	unsigned char elongUion;
	unsigned char stressUion;
	unsigned char languageSel;
	
	unsigned char curveSel; //选择弯曲
	float fYujinli;	//预警力
	unsigned char yujinClrFlagLoad; //预警清零标志
	unsigned char yujinClrFlagDisp;
	unsigned char autoReturn;//自动返回
	unsigned char printerType;//打印机类型
	unsigned char printerIntensity;//打印强度
	
	unsigned short speedBegin;//软加速开始
	unsigned char aCol;//加速度系数
	unsigned char dispFrom;//位移来源
	float dnLimitClampDisp;//下限位夹距之间的距离
	float testClampDisp;//下限位夹距之间的距离

	unsigned int gasInTime;//加气时间
	unsigned int gasOutTime;//放气时间

} CONFIG_DATA_U; //用户试用设置数据

typedef struct {
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}DT;



void User_Set_testMethodLaOrYa (unsigned char data);
void User_Set_ctrlMode (unsigned char data);
void User_Set_fTestSpeed (float data);
void User_Set_fFastSpeed (float data);		
void User_Set_fSlowSpeed (float data);
void User_Set_fLoadKeeping (float data);
void User_Set_chiSuPrecent (int data);
void User_Set_loadKeepPrec (int data);
void User_Set_fJudgeBreakBegin(int data);
void User_Set_overLoadPre (int data);
void User_Set_loadProtect (int data);
void User_Set_dispProtect (int data);
void User_Set_whichLoadCell (unsigned char data);
void User_Set_whichElongCell (unsigned char data);
void User_Set_loadUion (unsigned char data);
void User_Set_elongUion (unsigned char data);
void User_Set_stressUion (unsigned char data);
void User_Set_languageSel (unsigned char data);
void User_Set_curveSel (unsigned char data);
void User_Set_fYujinli (float data);
void User_Set_yujinClrFlagLoad (unsigned char data);
void User_Set_yujinClrFlagDisp (unsigned char data);

void User_Set_breakJudgePrecent (int data);
void User_Set_printerType (unsigned char data);
void User_Set_speedBegin (int data);
void User_Set_aCol (int data);
void User_Set_dispFrom (unsigned char data);
void User_Set_dnLimitClampDisp (float data);
void User_Set_testClampDisp (float data);
void User_Set_fTimeProtect (int data);
void User_Set_bClosed (float data);
void User_Set_fTimeLoadKeep (int data);
void User_Set_autoReturn (unsigned char data);
void User_Set_printerIntensity(unsigned char data);

void User_Set_fTimeStop (float data);
void User_Set_fLoadStop (float data);
void User_Set_fDispStop (float data);

void SYS_Set_year(int data);
void SYS_Set_month(int data);
void SYS_Set_day(int data);
void SYS_Set_hour(int data);
void SYS_Set_minute(int data);
void SYS_Set_second(int data);

void User_Set_gasInTime (int data);
void User_Set_gasOutTime (int data);
#endif