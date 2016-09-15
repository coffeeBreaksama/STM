#ifndef	_APP_H_
#define	_APP_H_

#include "includes.h"
#include "GUI.h"
#include "DIALOG.h"





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
#define FORMID_ANP4					36
#define FORMID_AMP5					37
#define FORMID_AMP6					38

/*
** *******************************************************************************************************
*                                              Public data
*********************************************************************************************************
*/
typedef struct {
  const GUI_BITMAP * pBitmap;
  const char       * pText;
} BITMAP_ITEM;

typedef struct WIN_PARA{			
	int xSizeLCD, ySizeLCD;			
	int xPosWin,  yPosWin;			
	int xSizeWin, ySizeWin;			
	int xSizeBM,  ySizeBM;
	WM_HWIN hWinMid;				
}WIN_PARA;



extern GUI_FONT     XBF_XINSONGTI25;
extern GUI_FONT     XBF_XINSONGTI19;
extern  const GUI_FONT GUI_Font12HZK;
extern  const GUI_FONT GUI_Font12HZKF;
extern  const GUI_FONT GUI_Font20HZK;
extern  const GUI_FONT GUI_Font20HZKF;
extern char __strBuf[14][30];

/************ KeypadInput **************/
extern uint8_t  keypadflag;
extern WM_HWIN  hkeypad;
extern void   KeyPad_Interface(uint16_t hwin,uint8_t flag); //flag:  0:不隐藏点，负号。 1：隐藏
/************************************/

extern unsigned int    FUN_ICON0Clicked(void);
extern unsigned int    FUN_ICON1Clicked(void);
extern unsigned int    FUN_ICON2Clicked(void);
extern unsigned int   FUN_ICON3Clicked(void);
extern unsigned int   FUN_ICON4Clicked(void);



extern unsigned int SETUSER_ICON0Clicked(void);
extern unsigned int SETUSER_ICON1Clicked(void);
extern unsigned int SETUSER_ICON2Clicked(void);
extern unsigned int SETUSER_ICON3Clicked(void);
extern unsigned int SETUSER_ICON4Clicked(void);
extern unsigned int SETUSER_ICON5Clicked(void);
extern unsigned int SETUSER_ICON6Clicked(void);
extern unsigned int SETUSER_ICON7Clicked(void);
extern unsigned int SETUSER_ICON8Clicked(void);
extern unsigned int SETUSER_ICON9Clicked(void);
extern unsigned int SETUSER_ICON10Clicked(void);
extern unsigned int SETUSER_ICON11Clicked(void);
extern unsigned int SETUSER_ICON12Clicked(void);
extern unsigned int SETUSER_ICON13Clicked(void);
extern unsigned int SETUSER_ICON14Clicked(void);
extern unsigned int SETUSER_ICON15Clicked(void);
extern unsigned int SETUSER_ICON16Clicked(void);
extern unsigned int SETUSER_ICON17Clicked(void);


extern unsigned int SETSYS_ICON1Clicked(void);
extern unsigned int SETSYS_ICON2Clicked(void);
extern unsigned int SETSYS_ICON3Clicked(void);
extern unsigned int SETSYS_ICON4Clicked(void);
extern unsigned int SETSYS_ICON5Clicked(void);
extern unsigned int SETSYS_ICON6Clicked(void);
extern unsigned int SETSYS_ICON7Clicked(void);
extern unsigned int SETSYS_ICON8Clicked(void);
extern unsigned int SETSYS_ICON9Clicked(void);
extern unsigned int SETSYS_ICON10Clicked(void);
extern unsigned int SETSYS_ICON11Clicked(void);
extern unsigned int SETSYS_ICON12Clicked(void);
extern unsigned int SETSYS_ICON13Clicked(void);
extern unsigned int SETSYS_ICON14Clicked(void);
extern unsigned int SETSYS_ICON15Clicked(void);
extern unsigned int SETSYS_ICON16Clicked(void);







unsigned int RunNextFrom(int);
unsigned int GetNextForm(int);
void __CloseWindows(WM_MESSAGE * pMsg);
unsigned char __runNextStep(int nowId);
void __SetListBoxTextAll(WM_HWIN hItem,GUI_ConstString *str1,GUI_ConstString *str2,GUI_ConstString *str3);
void __moveListSelUp(WM_HWIN hList,int time);
void __moveListSelDown(WM_HWIN hList,int time);
//void __SetListBoxTextAllTest(WM_HWIN hItem,const char**ppstr);
 
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void emWinMainApp(void);
#endif	//_APP_H_
   
