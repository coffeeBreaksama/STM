#ifndef	_APP_H_
#define	_APP_H_

#include "includes.h"
#include "GUI.h"
#include "DIALOG.h"
#include "UnknowDefine.h"




//
// Redefine number of layers for this configuration file. Must be equal or less than in GUIConf.h!
//
#undef  LCD_NUM_LAYERS
#define LCD_NUM_LAYERS    2               //ÉèÖÃÏÔÊ¾²ãÊý

#if   LCD_NUM_LAYERS == 1                 //Èç¹û½öÓÐÒ»´ÎÊ¹ÓÃWM_HBKWINÎªÖ÷ÏÔÊ¾²ã
  #define HDTWIN      WM_HBKWIN
#elif LCD_NUM_LAYERS == 2
  #define HDTWIN      WM_GetDesktopWindowEx(1)
#else
  #error LCD_NUM_LAYERS must be set to 1 or 2.
#endif


#define DTCOLOR         0X200000
#define TEXTCOLOR       GUI_WHITE
#define APPBKCOLOR  	0X00BCBCBC
#define APPTEXTCOLOR    GUI_WHITE


#define FORMID_MAINTEST				0
#define FORMID_USERSET				1
#define FORMID_SYSTEMSET			2
#define FORMID_SAMPLEINFO			3
#define FORMID_PRINTRESULT			4

#define FORMID_TESTTYPE				5
#define FORMID_TESTMODULE			6
#define FORMID_LOADKEEP				7
#define FORMID_FORCEUNIT			8
#define FORMID_ELONGUNIT			9
#define FORMID_STRESSUNIT			10
#define FORMID_SENSORSELECT			11
#define FORMID_BREAKTYPE			12
#define FORMID_SPEEDSET				13
#define FORMID_SOFTACCELE			14
#define FORMID_PROTECT				15
#define FORMID_PRELOAD				16
#define FORMID_AOTURETURN			17
#define FORMID_CLAMPSET				18
#define FORMID_PRINTER				19
#define FORMID_LANGUAGE				20
#define FORMID_TIME					21
#define FORMID_DISCODE				22

#define FORMID_MACHINEDIRECT		23
#define FORMID_MOTORTYPE			24
#define FORMID_SPEEDCEL				25
#define FORMID_SELCONTROLTYPE		26
#define FORMID_DISPFORM				27
#define FORMID_CALELONGDISP			28
#define FORMID_CALLOADICON			29

#define FORMID_PRECISIORSET			30
#define FORMID_SELSENSORCONF		31
#define FORMID_ZEROPOINT			32
#define FORMID_AMP1					33
#define FORMID_AMP2					34
#define FORMID_AMP3					35
#define FORMID_AMP4					36
#define FORMID_AMP5					37
#define FORMID_AMP6					38

#define RORMID_SYSSPEEDSCANF        39
#define FORMID_APPMENU				40
#define FORMID_SYSPASSWORD			41
#define FORMID_GASSET				42
#define FORMID_ABOUT				43
#define FORMID_KEYBOARD				44
/*
** *******************************************************************************************************
*                                              Public data
*********************************************************************************************************

*/

//总控制台中需要保存的窗口数据
typedef struct {
	char*  Name;
	unsigned char frmId;
	WM_HWIN FrmHandle;
	unsigned char Type;//Icon 0,Freamwin 1
	unsigned int (* creatFrmFunc)(void);
}INFO_WINDOW;


/*typedef struct{
	unsigned char fatherFrmId;
	unsigned char type;
	WM_HWIN handle;
	void (*saveFunction) ();
	int GuiId;
	//TODO 未完成功能，留待以后使用的：每个窗口下的小工具句柄资源表结构定义
}WIDGET_INFO;*/

//Iconview使用的图标图片和图标名称
typedef struct {
  const GUI_BITMAP * pBitmap;
  const char       * pText;
} BITMAP_ITEM;

//创建Iconview使用的数据
typedef struct WIN_PARA{			
	int xSizeLCD, ySizeLCD;			
	int xPosWin,  yPosWin;			
	int xSizeWin, ySizeWin;			
	int xSizeBM,  ySizeBM;
	WM_HWIN hWinMid;				
}WIN_PARA;

//Iconview中的图标使用的数据-图标名字和对应的formId
typedef struct{
	const char* pstr[3];
	unsigned int formId;
}STRING_2_FORM;

extern GUI_FONT     XBF_XINSONGTI25;
extern GUI_FONT     XBF_XINSONGTI19;
extern  const GUI_FONT GUI_Font12HZK;
extern  const GUI_FONT GUI_Font12HZKF;
extern  const GUI_FONT GUI_Font20HZK;
extern  const GUI_FONT GUI_Font20HZKF;

extern char __strBuf[30][30];//string字符的缓冲区，主要用于缓存不同语言的相应窗口字符
INFO_WINDOW __WindowsInfo[];//所有窗口的数据
unsigned char __FormIdOfRunning;//正在运行的窗口ID
unsigned char __SaveDataSuccess;//保存成功，允许点击下一步


//小键盘所需的全局变量函数的声明
extern uint8_t  keypadflag;
extern WM_HWIN  hkeypad;
void   KeyPad_Interface(uint16_t hwin,uint8_t flag); 

//所有不同窗口的创建函数的声明
unsigned int   RunFrmMainTest(void);
unsigned int   RunFrmUserSetIconView(void);
unsigned int   RunFrmSystemSetIconView(void);
unsigned int   RunFrmSampleInfo(void);
unsigned int   RunFrmPrintResult(void);

unsigned int RunFrmUserSetTestType(void);
unsigned int RunFrmUserSetTestCtrlMode(void);
unsigned int RunFrmUserSetLoadKeep(void);
unsigned int RunFrmUserSetForceUnit(void);
unsigned int RunFrmUserSetElongUnit(void);
unsigned int RunFrmUserSetStressUnit(void);
unsigned int RunFrmUserSetSensorSel(void);
unsigned int RunFrmUserSetTestStopType(void);
unsigned int RunFrmUserSetSpeed(void);
unsigned int RunFrmUserSetSoftA(void);
unsigned int RunFrmUserSetSoftProtect(void);
unsigned int RunFrmUserSetProLoad(void);
unsigned int RunFrmUserSetAutoReturn(void);
unsigned int RunFrmUserSetClampDistence(void);
unsigned int RunFrmUserSetPrintType(void);
unsigned int RunFrmUserSetLanguage(void);
unsigned int RunFrmUserSetTime(void);
unsigned int RunFrmSysDiscoder(void);

unsigned int RunFrmSysSetMachineDir(void);
unsigned int RunFrmSysSetMotorType(void);
unsigned int RunFrmSysSpeedCelSel(void);
unsigned int RunFrmSysSetControlerType(void);
unsigned int RunFrmSysSetDispFrom(void);
unsigned int RunFrmSysCelElongOrDisp(void);
unsigned int RunFrmSysCalLoadIconView(void);
unsigned int RunFrmSysLoadPrecisiorSet(void);
unsigned int RunFrmSysLoadCelSensorCfg(void);
unsigned int RunFrmSysLoadCelZeroPoint(void);
unsigned int RunFrmSysLoadCalAmplifierCoe1(void);
unsigned int RunFrmSysSpeedScanf(void);
unsigned int FrmRunAppMenu(void);
unsigned int RunFrmSysPassword(void);
unsigned int RunFrmUserSetGasSet(void);
unsigned int RunFrmAboutInfo(void);



//窗口控制函数的申明
unsigned int RunNextFrom(int);
unsigned int GetNextForm(int);
void UI_CloseWindows(WM_HWIN handle);
unsigned int ERR_ThrowError(unsigned char ErrorId);

void UI_SetListBoxTextByLgvg(WM_HWIN hItem,GUI_ConstString *str1,GUI_ConstString *str2,GUI_ConstString *str3);
void UI_MoveUpListBoxSel(WM_HWIN hList,int time);
void UI_MoveDownListBoxSel(WM_HWIN hList,int time);

unsigned char UI_RtSysMenuSaveSuc(WM_MESSAGE * pMsg);
unsigned char UI_RunSysNextSaveSuc(WM_MESSAGE * pMsg);
unsigned char UI_RunUserNextSaveSuc(WM_MESSAGE * pMsg);
unsigned char UI_RtUserMenuSaveSuc(WM_MESSAGE * pMsg);
unsigned char UI_RtLoadMenuSaveSuc(WM_MESSAGE * pMsg);
unsigned char UI_RunLoadNextSaveSuc(WM_MESSAGE * pMsg);
unsigned char UI_GetWindowInfoIndexId(unsigned char FrmId);

 
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void emWinMainApp(void);
#endif	//_APP_H_
   
