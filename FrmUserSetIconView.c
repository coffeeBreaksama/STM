
#include "includes.h"
#include "app.h"


#define ICONVIEW_Width      70  /* 控件ICONVIEW的宽                         */  
#define ICONVIEW_Height     70  /* 控件ICONVIEW的高，包括图标的Y方向间距    */  
#define ICONVIEW_XSpace     30  /* 控件ICONVIEW的X方向间距                  */ 
#define ICONVIEW_YSpace     40  /* 控件ICONVIEW的Y方向间距                  */ 
#define ICONVIEW_XPos       10  /* 控件ICONVIEW的X方向调整距离              */
#define BOTWIN_YSpace       60  /* 屏幕下方部分窗口Y方向间距                */
#define SetIconview_yPos         40  /* 中间窗口Y方向起始位置即顶部文字可用高度  */
#define SetIconview_xPos          0  /* 中间窗口Y方向起始位置                    */


//prStringArrayAndFormId数组的索引，只在IconIdOfTestType里使用
#define STRID_CONTROLTYPE_RETURN				0  
#define STRID_CONTROLTYPE_TESTTYPE				1
#define STRID_CONTROLTYPE_TESTMODULE			2
#define STRID_CONTROLTYPE_LOADKEEP				3
#define STRID_CONTROLTYPE_FORCEUNIT				4
#define STRID_CONTROLTYPE_ELONGUNIT				5
#define STRID_CONTROLTYPE_STRESSUNIT			6
#define STRID_CONTROLTYPE_SENSORSELECT			7
#define STRID_CONTROLTYPE_BREAKTYPE				8
#define STRID_CONTROLTYPE_SPEEDSET				9
#define STRID_CONTROLTYPE_SOFTACCELE			10
#define STRID_CONTROLTYPE_PROTECT				11
#define STRID_CONTROLTYPE_PRELOAD				12
#define STRID_CONTROLTYPE_AOTURETURN			13
#define STRID_CONTROLTYPE_CLAMPSET				14
#define STRID_CONTROLTYPE_PRINTER				15
#define STRID_CONTROLTYPE_LANGUAGE				16
#define STRID_CONTROLTYPE_TIME					17
#define STRID_CONTROLTYPE_DISCODE				18
#define STRID_CONTROLTYPE_GASSET				19


//图片数据声明
extern GUI_CONST_STORAGE GUI_BITMAP bmIdea;   
extern GUI_CONST_STORAGE GUI_BITMAP bmArrows;
extern GUI_CONST_STORAGE GUI_BITMAP bmClock;
extern GUI_CONST_STORAGE GUI_BITMAP bmCompass;
extern GUI_CONST_STORAGE GUI_BITMAP bmMessages;
extern GUI_CONST_STORAGE GUI_BITMAP bmMusic;
extern GUI_CONST_STORAGE GUI_BITMAP bmPhone;
extern GUI_CONST_STORAGE GUI_BITMAP bmPhotos;
extern GUI_CONST_STORAGE GUI_BITMAP bmVideos;
extern GUI_CONST_STORAGE GUI_BITMAP bmSafari;
extern GUI_CONST_STORAGE GUI_BITMAP bmWeather;
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi;
extern GUI_CONST_STORAGE GUI_BITMAP bmSiri;
extern GUI_CONST_STORAGE GUI_BITMAP bmCamera;
extern GUI_CONST_STORAGE GUI_BITMAP bmUSB;
extern GUI_CONST_STORAGE GUI_BITMAP bmSetting;
extern GUI_CONST_STORAGE GUI_BITMAP bmimsodiao;

//保存设置数据声明
extern CONFIG_DATA_U __configDataU;
extern CONFIG_DATA_S __configDataS;

static  STRING_2_FORM  prStringArrayAndFormId[] ={
	{{"返回","返回","Return"},0xFF}, //0
	{{"试验类型","试验类型","Test Type"}, FORMID_TESTTYPE},	//1   
	{{"试验模式","试验模式","Control Mode"}, FORMID_TESTMODULE},	//2
	{{"力量保持","力量保持","Load keep"}, FORMID_LOADKEEP},//3
	{{"力量单位","力量单位","Force unit"}, FORMID_FORCEUNIT},//4
	{{"位移单位","位移","Elong Unit"}, FORMID_ELONGUNIT},//5
	{{"强度单位","强度单位","Stress Unit"}, FORMID_STRESSUNIT},//6
	{{"荷重元选择","荷重元选择","Sensor Select"}, FORMID_SENSORSELECT},//7
	{{"停机方式","停机方式","break Type"}, FORMID_BREAKTYPE},//8
	{{"速度","速度","Speed Setting"}, FORMID_SPEEDSET},//9
	{{"软速度","软速度","Soft Acceleration"}, FORMID_SOFTACCELE},//10
	{{"保护","保护","Protect"}, FORMID_PROTECT},//11
	{{"预警力","预警力","Pre Load"}, FORMID_PRELOAD},//12
	{{"自动回位","自动回位","Auto Return"}, FORMID_AOTURETURN},//13
	{{"夹持距离","夹持距离","Clamp Set"}, FORMID_CLAMPSET},//14
	{{"打印机","打印机","Printer"}, FORMID_PRINTER},//15
	{{"语言","语言","Language"},FORMID_LANGUAGE },//16
	{{"时间","时间","Time"}, FORMID_TIME},//17
	{{"System Discoder","System Discoder","System Discoder"}, FORMID_DISCODE},//18
	{{"气缸时序","气缸时序","Gas Set"}, FORMID_GASSET},//19 气缸时序
	{{NULL,NULL,NULL},0xFF },//20
} ;

//0xff: the flag of the icon end
static const unsigned char IconIdOfTestType[4][20] = {
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_LOADKEEP,
		STRID_CONTROLTYPE_FORCEUNIT,
		STRID_CONTROLTYPE_ELONGUNIT,
		STRID_CONTROLTYPE_STRESSUNIT,
		STRID_CONTROLTYPE_SENSORSELECT,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_SPEEDSET,
		STRID_CONTROLTYPE_SOFTACCELE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_AOTURETURN,
		STRID_CONTROLTYPE_CLAMPSET,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
	
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_LOADKEEP,
		STRID_CONTROLTYPE_FORCEUNIT,
		STRID_CONTROLTYPE_ELONGUNIT,
		STRID_CONTROLTYPE_STRESSUNIT,
		STRID_CONTROLTYPE_SENSORSELECT,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_SPEEDSET,
		STRID_CONTROLTYPE_SOFTACCELE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_CLAMPSET,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
	
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_GASSET,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_AOTURETURN,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_LOADKEEP,
		STRID_CONTROLTYPE_FORCEUNIT,
		STRID_CONTROLTYPE_ELONGUNIT,
		STRID_CONTROLTYPE_STRESSUNIT,
		STRID_CONTROLTYPE_SENSORSELECT,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_SPEEDSET,
		STRID_CONTROLTYPE_SOFTACCELE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_AOTURETURN,
		STRID_CONTROLTYPE_CLAMPSET,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
};


//如果保存成功，返回上级菜单，否则抛出错误且不返回
unsigned char UI_RtUserMenuSaveSuc(WM_MESSAGE * pMsg)
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunNextFrom(FORMID_USERSET);
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;

		return 0;
	}

}


static unsigned int __curFrmIconIndex = 0xFF;//点击Iconview以后的icon索引
static unsigned char RunUserSetNextStep(void)
{
	int nowIdInStringIcon; 
	int frmId = 0xFF;
	if(__SaveDataSuccess == 1){
		if(IconIdOfTestType[__configDataS.controlerType][__curFrmIconIndex] != 0xFF){
			if(IconIdOfTestType[__configDataS.controlerType][__curFrmIconIndex+1] != 0xFF){
				__curFrmIconIndex++;
				nowIdInStringIcon = IconIdOfTestType[__configDataS.controlerType][__curFrmIconIndex];
				frmId = prStringArrayAndFormId[nowIdInStringIcon].formId;
				RunNextFrom(frmId);
			}
		}
		return 1;
	}
	else return 0;
}

//如果保存数据成功，进入下一级界面，否则抛出错误
unsigned char UI_RunUserNextSaveSuc(WM_MESSAGE * pMsg)
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunUserSetNextStep();
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;

		return 0;
	}
	return 0;
}

static WIN_PARA WinParaOfUserConfig;			


static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmArrows,              &__strBuf[0][0]},//0返回
	{&bmArrows,    	         &__strBuf[1][0]},//1试验类型
	{&bmArrows,              &__strBuf[2][0]},//2试验模式
	{&bmArrows,     	     &__strBuf[3][0]},//3力量保持
  
    {&bmArrows,				 &__strBuf[4][0]},//4力量单位
	{&bmArrows,              &__strBuf[5][0]},//5位移单位
	{&bmArrows, 		     &__strBuf[6][0]},//6强度单位
    {&bmArrows,    	         &__strBuf[7][0]},//7荷重元选择
  
	{&bmArrows,  	 	     &__strBuf[8][0]},//8停机方式   
	{&bmArrows,  	 	     &__strBuf[9][0]},//9速度
    {&bmArrows,   	         &__strBuf[10][0]},//10软速度
	{&bmArrows,  	         &__strBuf[11][0]},//11保护 	
	
	{&bmArrows,              &__strBuf[12][0]},//12预警力
	{&bmArrows,              &__strBuf[13][0]},//13自动回位
	{&bmArrows,              &__strBuf[14][0]},//14夹持距离
	{&bmArrows,              &__strBuf[15][0]},//15打印机
	
	{&bmArrows,              &__strBuf[16][0]},//16语言
	{&bmArrows,              &__strBuf[17][0]},//17时间
	{&bmArrows,              &__strBuf[18][0]},//18 System Discoder
	{&bmArrows,              &__strBuf[19][0]},//19气缸时序
	NULL,
};



void _cbSetIconviewSetting(WM_MESSAGE * pMsg) 
{

	int NCode, Id, iconSel;
	int testType;
	testType = __configDataS.controlerType;
	if(testType>3) testType = 0;
	switch (pMsg->MsgId) {
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) {
				case GUI_ID_ICONVIEW0:
					switch (NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 							
							/* 打开相应选项 */
							iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
							if(iconSel >= 0){
								__curFrmIconIndex = iconSel;
								RunNextFrom(prStringArrayAndFormId[IconIdOfTestType[testType][iconSel]].formId);
								UI_CloseWindows(WinParaOfUserConfig.hWinMid);
							}
						break;	
					}
				break;
			}
		break;
			
		/* 重绘消息*/
		case WM_PAINT:
			{	
				#if   LCD_NUM_LAYERS == 1 
					GUI_SetBkColor(DTCOLOR);
				#elif LCD_NUM_LAYERS == 2
					GUI_SetBkColor(GUI_TRANSPARENT);
				#endif
				GUI_Clear();
			}			
		break;			
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}


static WM_HWIN CreateUserSetIconview(void)
{	
	WM_HWIN SetIconview,TITTLE;
	int i, testType;
	testType = __configDataS.controlerType;
	if(testType>2) testType = 0;
	
	for(i=0;i<GUI_COUNTOF(prStringArrayAndFormId) - 1;i++) strcpy(&__strBuf[i][0],prStringArrayAndFormId[i].pstr[__configDataU.languageSel]);
	
	WinParaOfUserConfig.hWinMid= WM_CreateWindowAsChild(0,0,800,480,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,_cbSetIconviewSetting,sizeof(WIN_PARA *));

	TITTLE = TEXT_CreateEx(0, 5, 800 , 30, WinParaOfUserConfig.hWinMid, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT0, "Setting");	
	TEXT_SetFont(TITTLE, GUI_FONT_32B_1);	
											
	SetIconview=ICONVIEW_CreateEx( 0,25,800,455,WinParaOfUserConfig.hWinMid,WM_CF_SHOW|WM_CF_HASTRANS,
								ICONVIEW_CF_AUTOSCROLLBAR_V,GUI_ID_ICONVIEW0,ICONVIEW_Width,ICONVIEW_Height+20);				      
		
	for (i = 0; i < GUI_COUNTOF(prStringArrayAndFormId); i++) {		
		if(IconIdOfTestType[testType][i] != 0xFF){
			ICONVIEW_AddBitmapItem(SetIconview, _aBitmapItem[IconIdOfTestType[testType][i]].pBitmap,_aBitmapItem[IconIdOfTestType[testType][i]].pText);
			ICONVIEW_SetTextColor(SetIconview,i,GUI_WHITE);
		}
		else break;
	}
		
	ICONVIEW_SetBkColor(SetIconview, ICONVIEW_CI_SEL, 0xffffc0 | 0x80000000);
	switch(__configDataU.languageSel){
		case 0:	ICONVIEW_SetFont(SetIconview,&GUI_Font20HZK);break;
		case 1:ICONVIEW_SetFont(SetIconview,&GUI_Font20HZKF);break;
		default:ICONVIEW_SetFont(SetIconview,GUI_FONT_16B_1);break;
	}
	
	ICONVIEW_SetSel(SetIconview,-1);
	ICONVIEW_SetSpace(SetIconview, GUI_COORD_X, ICONVIEW_XSpace);
	ICONVIEW_SetSpace(SetIconview, GUI_COORD_Y, ICONVIEW_YSpace);
	ICONVIEW_SetIconAlign(SetIconview, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
	return WinParaOfUserConfig.hWinMid;

}



/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

static unsigned int nextFormIn = 0xFF;
unsigned int RunFrmUserSetIconView(void) 
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_USERSET)].FrmHandle = CreateUserSetIconview();
	return nextFormIn;
}


