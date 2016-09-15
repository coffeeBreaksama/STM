/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   用1.5.1版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "includes.h"
#include "app.h"
#include "F20HZK.h"
#include "F20HZKF.h"
/*
*********************************************************************************************************
*                                         宏定义 
*********************************************************************************************************
*/
#define ICONVIEW_Width      70  /* 控件ICONVIEW的宽                         */  
#define ICONVIEW_Height     70  /* 控件ICONVIEW的高，包括图标的Y方向间距    */  
#define ICONVIEW_XSpace     30  /* 控件ICONVIEW的X方向间距                  */ 
#define ICONVIEW_YSpace     40  /* 控件ICONVIEW的Y方向间距                  */ 
#define ICONVIEW_XPos       10  /* 控件ICONVIEW的X方向调整距离              */
#define BOTWIN_YSpace       60  /* 屏幕下方部分窗口Y方向间距                */
#define MIDWIN_yPos         40  /* 中间窗口Y方向起始位置即顶部文字可用高度  */
#define MIDWIN_xPos          0  /* 中间窗口Y方向起始位置                    */

/*
*********************************************************************************************************
*                                      变量
*********************************************************************************************************
*/ 
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

extern CONFIG_DATA_U __configDataU;

char  __strBuf[14][30];
static WIN_PARA _MainIconWinPara;			//用户使用的窗口额外数据
WM_HWIN _mainIcon;//主菜单句柄

static const char*  prStringArray[][3] ={
	{"试验主界面","试验主界面","Main Test"},
	{"用户设置","用户设置","User Set"},
	{"系统设置","系统设置","System Set"},
	{"试样","试验","Sample"},
	{"未定","未定","Null"},
	{"Null","Null","Null"},
	{"Null","Null","Null"},
	{"Null","Null","Null"}
} ;
int __GetValueType(void* value)
{
	char type;
	if(sizeof(value) > 4) type = 10;
	else if(sizeof(value) == 4) type = 4;
	else if(sizeof(value) == 2 ) type = 2;
	else if(sizeof(value) == 1)  type = 1;
	return type;
}
/* 用于桌面ICONVIEW0图标的创建 */
static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmimsodiao,           &__strBuf[0][0]},
	{&bmMusic,    	        &__strBuf[1][0]},
	{&bmSiri,				&__strBuf[2][0]},
	{&bmWeather,     	    &__strBuf[3][0]}, 
  
	{&bmCompass,          "Null"},  
	{&bmClock,              "Null"},
	{&bmSafari, 		       "Null"}, 
	{&bmCamera,    	       "Null"}, 
  
	{&bmPhone,  	 	        "Null"},    
	{&bmMessages,  	 	   "Null"},
	{&bmPhotos,   	      "Null"},		
	{&bmUSB,  	              "Null"},   	
	{&bmArrows,            "Null"}, 
	{&bmSetting,            "Null"},
};

/**********************************************************************************************************
/**	函 数 名: _cbBkWindow
*	功能说明: 桌面窗口的回调函数 
*	形    参：WM_MESSAGE * pMsg
*	返 回 值: 无
*********************************************************************************************************
*/

static unsigned int _nextWindow0[] ={
	FORMID_MAINTEST,
	FORMID_USERSET,
	FORMID_SYSTEMSET,
	FORMID_SAMPLEINFO,
	FORMID_PRINTRESULT,
};

unsigned int (* FormFuncIdArray[])(void) = {
	FUN_ICON0Clicked,//Main Test                        0
	FUN_ICON1Clicked,//Set User Config Icon List		1
	FUN_ICON2Clicked,//Set System config Icon List		2
	FUN_ICON3Clicked,// SampleInfo                      3
	FUN_ICON4Clicked,// PrintResult (TODO)              4
	
	SETUSER_ICON1Clicked,//Test Type					5
	SETUSER_ICON2Clicked,//Test Module					6
	SETUSER_ICON3Clicked,//Load keep					7

	SETUSER_ICON4Clicked,//Force unit					8
	SETUSER_ICON5Clicked,//Elong Unit					9
	SETUSER_ICON6Clicked,//Stress Unit					10
	SETUSER_ICON7Clicked,//Sensor Select				11
	SETUSER_ICON8Clicked,//break Type					12

	SETUSER_ICON9Clicked,//Speed Setting				13
	SETUSER_ICON10Clicked,//Soft Acceleration			14
	SETUSER_ICON11Clicked,//Protece						15
	SETUSER_ICON12Clicked,//Pre Load					16
	SETUSER_ICON13Clicked,//Auto Return					17

	SETUSER_ICON14Clicked,//Clamp Set					18
	SETUSER_ICON15Clicked,//Printer						19
	SETUSER_ICON16Clicked,//Language					20
	SETUSER_ICON17Clicked,//Time						21
	SETUSER_ICON17Clicked,//System discode(TODO)		22

	SETSYS_ICON1Clicked,//Machine Direct				23
	SETSYS_ICON2Clicked,//Motor Yype					24
	SETSYS_ICON3Clicked,//speedCel						25
	SETSYS_ICON4Clicked,//SelectControlType				26
	SETSYS_ICON5Clicked,//Disp Form						27
	SETSYS_ICON6Clicked,//CalElongDisp					28
	SETSYS_ICON7Clicked,//CalLoad Iconview				29
	SETSYS_ICON8Clicked,//Precisior Set					30
	SETSYS_ICON9Clicked,//Sensor Config cel				31
	SETSYS_ICON10Clicked,//Zero Point					32
	SETSYS_ICON11Clicked,//AmplifierCoe 1               33
	SETSYS_ICON12Clicked,//AmplifierCoe 2				34
	SETSYS_ICON13Clicked,//AmplifierCoe 3				35
	SETSYS_ICON14Clicked,//AmplifierCoe 4				36
	SETSYS_ICON15Clicked,//AmplifierCoe 5				37
	SETSYS_ICON16Clicked,//AmplifierCoe 6				38
};



unsigned int RunNextFrom(int nextId)
{
	do{
		if(nextId < 50){
			nextId = (* FormFuncIdArray[nextId])();}
	}while(nextId != 0xFF);
	return 0xFF;
}

void __moveListSelUp(WM_HWIN hList,int time){
	
	char listSel;
	char numOfList = LISTBOX_GetNumItems(hList);
	listSel = LISTBOX_GetSel(hList) - time;
	if(listSel < 0) listSel = numOfList;
	LISTBOX_SetSel(hList,listSel);
};

void __moveListSelDown(WM_HWIN hList,int time){
	
	char listSel;
	char numOfList = LISTBOX_GetNumItems(hList);
	listSel = LISTBOX_GetSel(hList) + time;
	if(listSel > numOfList - 1) listSel = 0;
	LISTBOX_SetSel(hList,listSel);
};

unsigned char __runNextStep(int nowId)
{
	static unsigned char nextIdTestType[][30] = {
		{1,2,3,4},
		{1,2,3,4,5},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
		{17,18,19,20},
	};

	
	int i;
	for(i = 0; i <= 30; i++){
		if(nowId == nextIdTestType[__configDataU.testMethodLaOrYa][i]){
			RunNextFrom(nextIdTestType[__configDataU.testMethodLaOrYa][i+1]);
			break;
		}
	}

	return 0;
}

void __SetListBoxTextAll(WM_HWIN hItem,GUI_ConstString *str1,GUI_ConstString *str2,GUI_ConstString *str3)
{	
	    if(__configDataU.languageSel == 0) LISTBOX_SetText(hItem, str1);
		else if(__configDataU.languageSel == 1) LISTBOX_SetText(hItem, str2);
        else LISTBOX_SetText(hItem, str3); 

}
/*void __SetListBoxTextAllTest(WM_HWIN hItem,const char*  *ppstr)
{		GUI_ConstString *pList;
		int i = 0;
		int sizeOfArray = GUI_COUNTOF(ppstr);
		int a = sizeof(ppstr[0]);
		char *b;
		for(i = 0 + __configDataU.languageSel * a;;i += sizeOfArray){
			if(*(ppstr+i) != NULL) {
				LISTBOX_AddString(hItem, *(ppstr+i));}
			else break;
		}
}*/

unsigned int GetNextFrom(int nextId)
{
	return 0xff;
}

void __CloseWindows(WM_MESSAGE * pMsg)//关闭当前打开的设置窗口
{
	WM_DeleteWindow(pMsg->hWin);
	if(keypadflag == 1){
		WM_DeleteWindow(hkeypad);
		keypadflag = 0;
	  }
	//RunNextFrom(GetNextFrom());
}
void UpdataDesktopLanguage(void)
{		
		unsigned char i;
		for(i=0;i<=4;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
		switch(__configDataU.languageSel){
			case 0:	
				ICONVIEW_SetFont(_mainIcon,&GUI_Font20HZK);
				for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
				break;
			case 1:
				ICONVIEW_SetFont(_mainIcon,&GUI_Font20HZKF);
				for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
			break;
			default:
				ICONVIEW_SetFont(_mainIcon,GUI_FONT_16B_1);
				for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
				break;
		}
}


void _cbBkWindow(WM_MESSAGE * pMsg) 
{

  char text_buffer[20]={0};
	switch (pMsg->MsgId) 
	{
		/* 重绘消息*/
		case WM_PAINT:		
#if   LCD_NUM_LAYERS == 1 
				GUI_SetBkColor(DTCOLOR);
#elif LCD_NUM_LAYERS == 2
          GUI_SetBkColor(GUI_TRANSPARENT);
#endif
		GUI_Clear();	
        ICONVIEW_SetSel(WM_GetDialogItem(_MainIconWinPara.hWinMid, GUI_ID_ICONVIEW0),-1);
		break;
    case WM_TIMER:
      
      break;
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}
/*
*********************************************************************************************************
*	函 数 名: _cbMidWin
*	功能说明: 
*	形    参：WM_MESSAGE * pMsg
*	返 回 值: 无
*********************************************************************************************************
*/
void _cbMidWin(WM_MESSAGE * pMsg) 
{
	int NCode, Id,iconSel;
	switch (pMsg->MsgId) 
	{
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) 
			{
				case GUI_ID_ICONVIEW0:
					switch (NCode) 
					{
						/* ICON控件点击消息 */
						case WM_NOTIFICATION_CLICKED:
							break;
						
						/* ICON控件释放消息 */
						case WM_NOTIFICATION_RELEASED: 							
							/* 打开相应选项 */
							iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
							if(iconSel > -1)
							RunNextFrom(_nextWindow0[ICONVIEW_GetSel(pMsg->hWinSrc)]);
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


/**
  * @brief  CreateTopWin，创建顶部的窗口
  * @param  none
  * @retval none
  */
static void CreateTopWin(void)
{
	WM_HWIN hText;
	/* 顶部的 "wildfire"文本 */
	hText = TEXT_CreateEx(0, 2, 200 , 30, HDTWIN, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "");
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);
	TEXT_SetText(hText,"BH-STM32F429");
	TEXT_SetTextColor(hText,GUI_WHITE);
	

	hText = TEXT_CreateEx(_MainIconWinPara.xSizeLCD/2-50,2,100,30,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,GUI_TA_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT1,"11:56:00");
	TEXT_SetTextColor(hText,GUI_WHITE);
	TEXT_SetFont(hText,GUI_FONT_20B_ASCII);
  
  	/* 状态栏的时间显示文本 */
	hText = TEXT_CreateEx(_MainIconWinPara.xSizeLCD-200,2,200,30,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,GUI_TA_RIGHT|TEXT_CF_VCENTER,GUI_ID_TEXT2,"CPU: 10%");
	TEXT_SetTextColor(hText,GUI_WHITE);
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);
}
/**
  * @brief  CreateMidWin，创建中间的窗口
  * @param  none
  * @retval none
  */
static void CreateMidWin(void)
{
	uint8_t i=0;
	WM_HWIN MIDWIN;
	for(i=0;i<=4;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	_MainIconWinPara.hWinMid= WM_CreateWindowAsChild(
											_MainIconWinPara.xPosWin,											
											_MainIconWinPara.yPosWin,
											_MainIconWinPara.xSizeWin,
											_MainIconWinPara.ySizeWin,	
											HDTWIN, 
											WM_CF_SHOW|WM_CF_MEMDEV,
											_cbMidWin, 
											sizeof(WIN_PARA *)
											);
/*-------------------------------------------------------------------------------------*/
					/*在指定位置创建指定尺寸的ICONVIEW1 小工具*/
					MIDWIN=ICONVIEW_CreateEx(
											 ICONVIEW_XPos, 					          /* 小工具的最左像素（在父坐标中）*/
											 0, 								                /* 小工具的最上像素（在父坐标中）*/
											 _MainIconWinPara.xSizeLCD-ICONVIEW_XPos,	  /* 小工具的水平尺寸（单位：像素）*/
											 3*(_MainIconWinPara.ySizeBM+35), 			      /* 小工具的垂直尺寸（单位：像素）*/
											 _MainIconWinPara.hWinMid, 				          /* 父窗口的句柄。如果为0 ，则新小工具将成为桌面（顶级窗口）的子窗口 */
											 WM_CF_SHOW|WM_CF_HASTRANS,         /* 窗口创建标记。为使小工具立即可见，通常使用 WM_CF_SHOW */ 
											 0,                                 //ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* 默认是0，如果不够现实可设置增减垂直滚动条 */
											 GUI_ID_ICONVIEW0, 			            /* 小工具的窗口ID */
											 ICONVIEW_Width, 				            /* 图标的水平尺寸 */
											 ICONVIEW_Height+20);				        /* 图标的垂直尺寸 */
											 
		/* 向ICONVIEW 小工具添加新图标 */
		for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) 
		{
			ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
			ICONVIEW_SetTextColor(MIDWIN,i,GUI_WHITE);
		}	
		/* 设置小工具的背景色 32 位颜色值的前8 位可用于alpha混合处理效果*/
		ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, 0xffffc0 | 0x80000000);
		/* 设置图标字体 */
		switch(__configDataU.languageSel){
			case 0:	
				ICONVIEW_SetFont(MIDWIN,&GUI_Font20HZK);
				break;
			case 1:
				ICONVIEW_SetFont(MIDWIN,&GUI_Font20HZKF);
			break;
			default:
				ICONVIEW_SetFont(MIDWIN,GUI_FONT_16B_1);
				break;
		}
		/* 设置初始选择的图标为 -1 (表示尚未选择)*/
		ICONVIEW_SetSel(MIDWIN,-1);
		/* 设置图标在x 或y 方向上的间距。*/
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
		/* 设置对齐方式 在5.22版本中最新加入的 */
		ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
		/*将MIDWIN的句柄赋给全局变量*/
		_mainIcon = MIDWIN;
}	
/*-------------------------------------------------------------------------------------*/

/*
*********************************************************************************************************
*	函 数 名: emWinMainApp
*	功能说明: GUI主函数 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void emWinMainApp(void)
{
  FRAMEWIN_SKINFLEX_PROPS FRAMEWIN_pProps;
  RADIO_SKINFLEX_PROPS    RADIO_pProps;



  
	//准备建立3个窗口，以下是使用到的用户定义参数，方便在回调函数中使用
	_MainIconWinPara.xSizeLCD = 800;			            //LCD屏幕尺寸
	_MainIconWinPara.ySizeLCD = 400;				            //LCD屏幕尺寸
	_MainIconWinPara.xSizeBM  = ICONVIEW_Width;				            //图标宽度
	_MainIconWinPara.ySizeBM  = ICONVIEW_Height;				            //图标高度
	_MainIconWinPara.xPosWin	 = MIDWIN_xPos;							          //窗口的起始位置
	_MainIconWinPara.yPosWin  = MIDWIN_yPos;							          //窗口的起始位置
	_MainIconWinPara.xSizeWin = _MainIconWinPara.xSizeLCD;						      //窗口尺寸
	_MainIconWinPara.ySizeWin = _MainIconWinPara.ySizeLCD-_MainIconWinPara.yPosWin;	//窗口尺寸
  
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	//FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
  
  /***************************定制皮肤*****************************/
  FRAMEWIN_GetSkinFlexProps(&FRAMEWIN_pProps,FRAMEWIN_SKINFLEX_PI_ACTIVE);
  FRAMEWIN_pProps.aColorFrame[0]=GUI_BLACK;
  FRAMEWIN_pProps.aColorFrame[1]=GUI_BLACK;
  FRAMEWIN_pProps.aColorFrame[2]=GUI_BLACK;
  FRAMEWIN_pProps.Radius=0;
  FRAMEWIN_pProps.aColorTitle[0]=GUI_BLACK;
  FRAMEWIN_pProps.aColorTitle[1]=GUI_BLACK;
  FRAMEWIN_SetSkinFlexProps(&FRAMEWIN_pProps,FRAMEWIN_SKINFLEX_PI_ACTIVE);
  FRAMEWIN_SetDefaultClientColor(APPBKCOLOR);

  FRAMEWIN_SetDefaultTextColor(1,TEXTCOLOR);
  FRAMEWIN_SetDefaultTitleHeight(30);
  FRAMEWIN_SetDefaultTextAlign(GUI_TA_LEFT | GUI_TA_VCENTER);

  WINDOW_SetDefaultBkColor(APPBKCOLOR);
  
  EDIT_SetDefaultBkColor(EDIT_CI_ENABLED,APPBKCOLOR);
  EDIT_SetDefaultTextColor(EDIT_CI_ENABLED,TEXTCOLOR);
  
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_UNSEL,APPBKCOLOR);
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_SEL,GUI_BLUE);
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_SELFOCUS,GUI_BLUE);
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_DISABLED,APPBKCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_UNSEL,TEXTCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_SEL,TEXTCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_SELFOCUS,TEXTCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_DISABLED,TEXTCOLOR);
  
  TEXT_SetDefaultTextColor(TEXTCOLOR);
  
  RADIO_SetDefaultTextColor(TEXTCOLOR);
  RADIO_GetSkinFlexProps(&RADIO_pProps,0);
  RADIO_pProps.aColorButton[3]=GUI_YELLOW;
  RADIO_SetSkinFlexProps(&RADIO_pProps,0);
  
  CHECKBOX_SetDefaultTextColor(TEXTCOLOR);
  ////////////////////Language Init////////////////////////////////
		switch(__configDataU.languageSel){
			case 0:	
				TEXT_SetDefaultFont(&GUI_Font20HZK);
				FRAMEWIN_SetDefaultFont(&GUI_Font20HZK);
				EDIT_SetDefaultFont(&GUI_Font20HZK);
				LISTBOX_SetDefaultFont(&GUI_Font20HZK);
				BUTTON_SetDefaultFont(&GUI_Font20HZK);
				CHECKBOX_SetDefaultFont(&GUI_Font20HZK);
				break;
			case 1:
				TEXT_SetDefaultFont(&GUI_Font20HZKF);
				FRAMEWIN_SetDefaultFont(&GUI_Font20HZKF);
				EDIT_SetDefaultFont(&GUI_Font20HZKF);
				LISTBOX_SetDefaultFont(&GUI_Font20HZKF);
				BUTTON_SetDefaultFont(&GUI_Font20HZKF);
				CHECKBOX_SetDefaultFont(&GUI_Font20HZKF);
			break;
			default:
				FRAMEWIN_SetDefaultFont(GUI_FONT_16B_1);
				BUTTON_SetDefaultFont(GUI_FONT_16B_1);
				LISTBOX_SetDefaultFont(GUI_FONT_32B_1);
				CHECKBOX_SetDefaultFont(GUI_FONT_32B_1);
				CHECKBOX_SetDefaultFont(GUI_FONT_32B_1);
				break;
		}
  
	/*************************************************************************/
	WM_SetCallback(HDTWIN, _cbBkWindow);
	WM_CreateTimer(HDTWIN, 0, 1000, 0);
	/* 创建三个窗口 状态栏、控制栏、主窗口*/
	CreateMidWin();
	CreateTopWin();
	while(1)
	{	
		GUI_Delay(10);
	}
}
/*************************** End of file ****************************/
